#include "gamma.h"
#include <stdlib.h>
#include <assert.h>
#include "safe_malloc.h"
static inline bool adjacent_up(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (y+1<g->height && g->arr[x][y+1]!=NULL && g->arr[x][y+1]->player==player);
}
static inline bool adjacent_down(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (y>0 && g->arr[x][y-1]!=NULL && g->arr[x][y-1]->player==player);
}
static inline bool adjacent_left(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (x>0 && g->arr[x-1][y]!=NULL && g->arr[x-1][y]->player==player);
}
static inline bool adjacent_right(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (x+1<g->width && g->arr[x+1][y]!=NULL && g->arr[x+1][y]->player==player);
}
static inline bool exists_up(gamma_t* g, uint32_t x, uint32_t y) {
	return (y+1<g->height && g->arr[x][y+1]!=NULL);
}
static inline bool exists_down(gamma_t* g, uint32_t x, uint32_t y) {
	return (y>0 && g->arr[x][y-1]!=NULL);
}
static inline bool exists_left(gamma_t* g, uint32_t x, uint32_t y) {
	return (x>0 && g->arr[x-1][y]!=NULL);
}
static inline bool exists_right(gamma_t* g, uint32_t x, uint32_t y) {
	return (x+1<g->width && g->arr[x+1][y]!=NULL);
}
static inline bool free_adjacent_up(gamma_t* g, uint32_t x, uint32_t y) {
	return (y+1<g->height && g->arr[x][y+1]==NULL);
}
static inline bool free_adjacent_down(gamma_t* g, uint32_t x, uint32_t y) {
	return (y>0 && g->arr[x][y-1]==NULL);
}
static inline bool free_adjacent_left(gamma_t* g, uint32_t x, uint32_t y) {
	return (x>0 && g->arr[x-1][y]==NULL);
}
static inline bool free_adjacent_right(gamma_t* g, uint32_t x, uint32_t y) {
	return (x+1<g->width && g->arr[x+1][y]==NULL);
}
// Check if field x,y has adjacent fields belonging to player
static inline bool has_friends(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return adjacent_up(g, player, x, y) ||
				 adjacent_down(g, player, x, y) ||
				 adjacent_left(g, player, x, y) ||
				 adjacent_right(g, player, x, y);
}
// Adds the player counter for fields he can move without increasing his area count
static inline void increase_if_no_friends(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	if(!has_friends(g, player, x, y)) g->player_free_fields[player]++;
}
/** @brief increase_if_no_friends() on for all 4 neighbors
 * Increase adjacent free space count
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] player - player number, positive number does not exceed value
 * @p players from the @ref gamma_new function,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function.
 */
void add_free_adjacents(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	if(free_adjacent_up(g, x, y)) increase_if_no_friends(g, player, x, y+1);
	if(free_adjacent_down(g, x, y)) increase_if_no_friends(g, player, x, y-1);
	if(free_adjacent_left(g, x, y)) increase_if_no_friends(g, player, x-1, y);
	if(free_adjacent_right(g, x, y)) increase_if_no_friends(g, player, x+1, y);
}
/** @brief Add a player to the list if we are missing that player
 * @param [in] player - player number, positive number does not exceed value
 * @p players from the @ref gamma_new function,
 * @param [in] change - list of players for change
 */
void add_if_missing(uint32_t player, uint32_t* change) {
	for(int i=0; i<4; i++) {
		if(change[i]==player)
			break;
		else if(change[i]==0) {
			change[i]=player;
			break;
		}
	}
}
/** @brief Add area count if the area will be separated after removal of a field
 * @param [in] master - new master field
 * @param [in] still_connected - list of areas that are still connected
 * @param [in] adder - how many areas will be added
 * @p height from the @ref gamma_new function.
 */
void add_and_decrease_distinct(unode_t* master, unode_t** still_connected, int* adder) {
	for(int i=0; i<4; i++) {
		if(ufind(still_connected[i])==ufind(master))
			return;
		else if(still_connected[i]==NULL) {
			still_connected[i]=master;
			*adder+=1;
			break;
		}
	}
}
/** @brief add_if_missing() for all 4 neighbors
 * Add neighbors in distinct areas
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] player - player number, positive number does not exceed value
 * @p players from the @ref gamma_new function,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function.
 * @param [in] change - list of players for change
 */
static inline void add_existing_neighbors(gamma_t* g, uint32_t x, uint32_t y, uint32_t* change) {
	if(exists_up(g, x, y)) add_if_missing(g->arr[x][y+1]->player, change);
	if(exists_down(g, x, y)) add_if_missing(g->arr[x][y-1]->player, change);
	if(exists_left(g, x, y)) add_if_missing(g->arr[x-1][y]->player, change);
	if(exists_right(g, x, y)) add_if_missing(g->arr[x+1][y]->player, change);
}
/** @brief Decrease potential free locations for neighbors
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function.
 */
void decrease_adjacents(gamma_t* g, uint32_t x, uint32_t y) {
	uint32_t change[4]={0, 0, 0, 0};

	add_existing_neighbors(g, x, y, change);

	for(int i=0; i<4; i++)
		if(change[i]!=0) {
			assert(g->player_free_fields[change[i]]);
			g->player_free_fields[change[i]]--;
		}
}

bool free_has_friends(gamma_t* g, uint32_t player, uint32_t x, uint32_t y, char from) {
	if(g->arr[x][y]!=NULL) return true;
	return
					(adjacent_up(g, player, x, y) && from!=UP) ||
					(adjacent_down(g, player, x, y) && from!=DOWN) ||
					(adjacent_left(g, player, x, y) && from!=LEFT) ||
					(adjacent_right(g, player, x, y) && from!=RIGHT);
}
/** @brief Decrease player's free locations
 * When removing lonesome friends we decrease player's free field locations
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function.
 */
void decrease_player_free_adjacents(gamma_t* g, uint32_t x, uint32_t y) {
	uint32_t player=g->arr[x][y]->player;
	if(free_adjacent_up(g, x, y) && !free_has_friends(g, player, x, y+1, DOWN)) g->player_free_fields[player]--;
	if(free_adjacent_down(g, x, y) && !free_has_friends(g, player, x, y-1, UP)) g->player_free_fields[player]--;
	if(free_adjacent_left(g, x, y) && !free_has_friends(g, player, x-1, y, RIGHT)) g->player_free_fields[player]--;
	if(free_adjacent_right(g, x, y) && !free_has_friends(g, player, x+1, y, LEFT)) g->player_free_fields[player]--;
}
/** @brief Increase player's free locations
 * When moving to a location add neighboring free locations to our count
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function.
 */
void increase_adjacents(gamma_t* g, uint32_t x, uint32_t y) {
	uint32_t change[4]={0, 0, 0, 0};

	add_existing_neighbors(g, x, y, change);

	for(int i=0; i<4; i++)
		if(change[i]!=0)
			g->player_free_fields[change[i]]++;
}
/** @brief Reindex an area
 * When removing a field we might potentially be breaking an area into two
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function.
 * @param [in] master - new master field
 * @param [in] from - direction we are coming from
 */
void reindex(gamma_t* g, uint32_t player, uint32_t x, uint32_t y, unode_t* master, char from) {
	if(g->arr[x][y]->visited) return;
	g->arr[x][y]->visited=true;
	g->arr[x][y]->depth=1;
	g->arr[x][y]->parent=master;
	if(from!=UP && adjacent_up(g, player, x, y)) reindex(g, player, x, y+1, master, DOWN);
	if(from!=DOWN && adjacent_down(g, player, x, y)) reindex(g, player, x, y-1, master, UP);
	if(from!=LEFT && adjacent_left(g, player, x, y)) reindex(g, player, x-1, y, master, RIGHT);
	if(from!=RIGHT && adjacent_right(g, player, x, y)) reindex(g, player, x+1, y, master, LEFT);
	g->arr[x][y]->visited=false;
}
/** @brief Remove a field
 * Removing a field is used for making a golden move
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function.
 * @return Value @p true if the field was removed @p false,
 * otherwise.
 */
bool remove_field(gamma_t* g, uint32_t x, uint32_t y) {
	uint32_t player=g->arr[x][y]->player;
	unode_t* master, * del;
	unode_t* still_connected[4]={NULL, NULL, NULL, NULL};
	int adder=-1;

	decrease_player_free_adjacents(g, x, y);
	increase_adjacents(g, x, y);
	if(!has_friends(g, player, x, y)) {
		g->arr[x][y]=safe_free(g->arr[x][y]);
		g->free_fields++;
		assert(g->player_busy_fields);
		g->player_busy_fields[player]--;
		g->player_area_count[player]--;
		return true;
	}
	else {
		g->arr[x][y]->visited=true;
		if(adjacent_up(g, player, x, y)) {
			master=new_unode(g->arr[x][y+1]->player);
			if(master==NULL) return false;
			reindex(g, player, x, y+1, master, DOWN);
			del=g->arr[x][y+1];
			g->arr[x][y+1]=master;
			safe_free(del);
			add_and_decrease_distinct(ufind(master), still_connected, &adder);
		}
		if(adjacent_down(g, player, x, y)) {
			master=new_unode(g->arr[x][y-1]->player);
			if(master==NULL) return false;
			reindex(g, player, x, y-1, master, UP);
			del=g->arr[x][y-1];
			g->arr[x][y-1]=master;
			safe_free(del);
			add_and_decrease_distinct(ufind(master), still_connected, &adder);
		}
		if(adjacent_left(g, player, x, y)) {
			master=new_unode(g->arr[x-1][y]->player);
			if(master==NULL) return false;
			reindex(g, player, x-1, y, master, RIGHT);
			del=g->arr[x-1][y];
			g->arr[x-1][y]=master;
			safe_free(del);
			add_and_decrease_distinct(ufind(master), still_connected, &adder);
		}
		if(adjacent_right(g, player, x, y)) {
			master=new_unode(g->arr[x+1][y]->player);
			if(master==NULL) return false;
			reindex(g, player, x+1, y, master, LEFT);
			del=g->arr[x+1][y];
			g->arr[x+1][y]=master;
			safe_free(del);
			add_and_decrease_distinct(ufind(master), still_connected, &adder);
		}
		g->arr[x][y]->visited=false;
		assert(adder!=-1);
		g->arr[x][y]=safe_free(g->arr[x][y]);
		g->free_fields++;
		assert(g->player_busy_fields);
		g->player_busy_fields[player]--;
		if(g->max_areas-g->player_area_count[player]<(uint64_t)adder) {
			g->player_area_count[player]+=adder;
			g->del_error_flag=true;
			gamma_move(g, player, x, y);
			g->del_error_flag=false;
			return false;
		}
		else g->player_area_count[player]+=adder;
	}
	return true;
}
gamma_t* gamma_new(uint32_t width, uint32_t height, uint32_t players, uint32_t areas) {
	if(width==0 || height==0 || players==0 || areas==0) return NULL;
	gamma_t* g;
	uint64_t i;
	g=malloc(sizeof(gamma_t));
	if(g==NULL) return NULL;
	g->width=width;
	g->height=height;
	g->free_fields=width*height;
	g->max_areas=areas;
	g->max_players=players;
	g->del_error_flag=false;
	g->arr=malloc(g->width*sizeof(unode_t**));
	if(g->arr==NULL) return safe_free(g);
	for(i=0; i<g->width; i++)
		g->arr[i]=malloc(g->height*sizeof(unode_t*));
	for(i=0; i<g->width; i++) {
		if(g->arr[i]==NULL) {
			for(uint32_t j=0; j<g->width; j++)
				safe_free(g->arr[i]);
			safe_free(g->arr);
			return safe_free(g);
		}
	}

	g->did_golden_move=malloc((g->max_players+1)*sizeof(bool));
	g->player_area_count=malloc((g->max_players+1)*sizeof(uint64_t));
	g->player_free_fields=malloc((g->max_players+1)*sizeof(uint64_t));
	g->player_busy_fields=malloc((g->max_players+1)*sizeof(uint64_t));
	if(
					g->did_golden_move==NULL ||
					g->player_area_count==NULL ||
					g->player_free_fields==NULL ||
					g->player_busy_fields==NULL) {
		for(uint32_t j=0; j<g->width; j++)
			safe_free(g->arr[i]);
		safe_free(g->arr);
		safe_free(g->did_golden_move);
		safe_free(g->player_area_count);
		safe_free(g->player_free_fields);
		safe_free(g->player_busy_fields);
		return safe_free(g);
	}

	for(i=0; i<g->width; i++)
		for(uint32_t j=0; j<g->height; j++)
			g->arr[i][j]=NULL;
	for(i=0; i<=g->max_players; i++) {
		g->player_area_count[i]=0;
		g->player_free_fields[i]=0;
		g->player_busy_fields[i]=0;
		g->did_golden_move[i]=false;
	}
	return g;
}
void gamma_delete(gamma_t* g) {
	if(g==NULL) return;
	for(uint32_t i=0; i<g->width; i++)
		for(uint32_t j=0; j<g->height; j++)
			safe_free(g->arr[i][j]);
	for(uint32_t i=0; i<g->width; i++)
		safe_free(g->arr[i]);
	safe_free(g->player_area_count);
	safe_free(g->player_busy_fields);
	safe_free(g->player_free_fields);
	safe_free(g->did_golden_move);
	safe_free(g->arr);
	safe_free(g);
}
bool gamma_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	if(g==NULL || x>=g->width || y>=g->height || player>g->max_players || player==0) return false;
	bool has_adjacent_friends=has_friends(g, player, x, y);
	if(g->arr[x][y]!=NULL) return false;
	if(g->player_area_count[player]>=g->max_areas && !has_adjacent_friends && !g->del_error_flag)
		return false;
	add_free_adjacents(g, player, x, y);
	decrease_adjacents(g, x, y);
	if(!has_adjacent_friends) {
		g->player_area_count[player]++;
		g->arr[x][y]=new_unode(player);
		if(g->arr[x][y]==NULL) return false;
	}
	else {
		g->arr[x][y]=new_unode(player);
		if(g->arr[x][y]==NULL) return false;
		unode_t* up=adjacent_up(g, player, x, y) ? ufind(g->arr[x][y+1]) : NULL;
		unode_t* down=adjacent_down(g, player, x, y) ? ufind(g->arr[x][y-1]) : NULL;
		unode_t* left=adjacent_left(g, player, x, y) ? ufind(g->arr[x-1][y]) : NULL;
		unode_t* right=adjacent_right(g, player, x, y) ? ufind(g->arr[x+1][y]) : NULL;
		unode_t* horizontal=NULL;
		unode_t* vertical=NULL;

		if(ujoin(left, right))
			g->player_area_count[player]--;
		if(left!=NULL || right!=NULL)
			horizontal=ufind(left!=NULL ? left : right);

		if(ujoin(up, down))
			g->player_area_count[player]--;
		if(up!=NULL || down!=NULL)
			vertical=ufind(up!=NULL ? up : down);

		if(ujoin(vertical, horizontal))
			g->player_area_count[player]--;

		ujoin(g->arr[x][y], vertical);
		ujoin(g->arr[x][y], horizontal);
	}
	g->player_busy_fields[player]++;
	g->free_fields--;
	return true;
}
bool gamma_golden_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	if(g==NULL || x>=g->width || y>=g->height || player>g->max_players || player==0) return false;
	if(g->did_golden_move[player]) return false;
	if(g->arr[x][y]==NULL) return false;
	if(g->arr[x][y]->player==player) return false;
	if(g->player_area_count[player]>=g->max_areas && !has_friends(g, player, x, y)) return false;
	if(!remove_field(g, x, y)) return false;
	gamma_move(g, player, x, y);
	g->did_golden_move[player]=true;
	return true;
}
uint64_t gamma_busy_fields(gamma_t* g, uint32_t player) {
	if(g==NULL || player>g->max_players || player==0) return false;
	return g->player_busy_fields[player];
}
uint64_t gamma_free_fields(gamma_t* g, uint32_t player) {
	if(g==NULL || player>g->max_players || player==0) return false;
	assert(g->player_area_count[player]<=g->max_areas);
	if(g->player_area_count[player]==g->max_areas)
		return g->player_free_fields[player];
	return g->free_fields;
}
bool gamma_golden_possible(gamma_t* g, uint32_t player) {
	if(g==NULL || player>g->max_players || player==0) return false;
	if(g->did_golden_move[player]) return false;
	uint32_t i;
	for(i=1; i<=g->max_players; i++)
		if(g->player_busy_fields[i]>0 && i!=player)
			return true;
	return false;
}
char* gamma_board(gamma_t* g) {
	if(g==NULL) return false;
	uint32_t height=g->height;
	uint32_t width=g->width;
	char* board=malloc((1+height*(width+1))*sizeof(char));
	if(board==NULL) return false;
	unode_t*** arr=g->arr;
	uint32_t i, j;
	for(i=0; i<height; i++)
		for(j=0; j<width; j++)
			*(board+i*(width+1)+j)=arr[j][height-1-i]!=NULL ?
														 '0'+arr[j][height-1-i]->player : '.';
	for(i=0; i<height; i++)
		*(board+i*(width+1)+width)='\n';
	*(board+(height-1)*(width+1)+width+1)='\0';
	return board;
}
