#include "gamma.h"
#include <stdlib.h>
#include <assert.h>
inline bool adjacent_up(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (y+1<g->height && g->arr[x][y+1]!=NULL && g->arr[x][y+1]->player==player);
}
inline bool adjacent_down(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (y>0 && g->arr[x][y-1]!=NULL && g->arr[x][y-1]->player==player);
}
inline bool adjacent_left(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (x>0 && g->arr[x-1][y]!=NULL && g->arr[x-1][y]->player==player);
}
inline bool adjacent_right(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (x+1<g->width && g->arr[x+1][y]!=NULL && g->arr[x+1][y]->player==player);
}
inline bool exists_up(gamma_t* g, uint32_t x, uint32_t y) {
	return (y+1<g->height && g->arr[x][y+1]!=NULL);
}
inline bool exists_down(gamma_t* g, uint32_t x, uint32_t y) {
	return (y>0 && g->arr[x][y-1]!=NULL);
}
inline bool exists_left(gamma_t* g, uint32_t x, uint32_t y) {
	return (x>0 && g->arr[x-1][y]!=NULL);
}
inline bool exists_right(gamma_t* g, uint32_t x, uint32_t y) {
	return (x+1<g->width && g->arr[x+1][y]!=NULL);
}
inline bool free_adjacent_up(gamma_t* g, uint32_t x, uint32_t y) {
	return (y+1<g->height && g->arr[x][y+1]==NULL);
}
inline bool free_adjacent_down(gamma_t* g, uint32_t x, uint32_t y) {
	return (y>0 && g->arr[x][y-1]==NULL);
}
inline bool free_adjacent_left(gamma_t* g, uint32_t x, uint32_t y) {
	return (x>0 && g->arr[x-1][y]==NULL);
}
inline bool free_adjacent_right(gamma_t* g, uint32_t x, uint32_t y) {
	return (x+1<g->width && g->arr[x+1][y]==NULL);
}
// Check if field x,y has adjacent fields belonging to player
inline bool has_friends(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return adjacent_up(g, player, x, y) ||
				 adjacent_down(g, player, x, y) ||
				 adjacent_left(g, player, x, y) ||
				 adjacent_right(g, player, x, y);
}
// Adds the player counter for fields he can move without increasing his area count
inline void increase_if_no_friends(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	if(!has_friends(g, player, x, y)) g->player_free_fields[player]++;
}
// increase_if_no_friends() on for all 4 neighbors
void add_free_adjacents(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	if(free_adjacent_up(g, x, y)) increase_if_no_friends(g, player, x, y+1);
	if(free_adjacent_down(g, x, y)) increase_if_no_friends(g, player, x, y-1);
	if(free_adjacent_left(g, x, y)) increase_if_no_friends(g, player, x-1, y);
	if(free_adjacent_right(g, x, y)) increase_if_no_friends(g, player, x+1, y);
}
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
void add_and_decrease_distinct(unode_t* master, unode_t** still_connected, int* adder) {
	for(int i=0; i<4; i++) {
		if(still_connected[i]==master)
			return;
		else if(still_connected[i]==NULL) {
			still_connected[i]=master;
			*adder+=1;
			break;
		}
	}
}
inline void add_existing_neighbors(gamma_t* g, uint32_t x, uint32_t y, uint32_t* change) {
	if(exists_up(g, x, y)) add_if_missing(g->arr[x][y+1]->player, change);
	if(exists_down(g, x, y)) add_if_missing(g->arr[x][y-1]->player, change);
	if(exists_left(g, x, y)) add_if_missing(g->arr[x-1][y]->player, change);
	if(exists_right(g, x, y)) add_if_missing(g->arr[x+1][y]->player, change);
}
void decrease_adjacents(gamma_t* g, uint32_t x, uint32_t y) {
	uint32_t change[4]={0, 0, 0, 0};

	add_existing_neighbors(g,x,y,change);

	for(int i=0; i<4; i++)
		if(change[i]!=0) {
			assert(g->player_free_fields[i]);
			g->player_free_fields[i]--;
		}
}
void increase_adjacents(gamma_t* g, uint32_t x, uint32_t y) {
	uint32_t change[4]={0, 0, 0, 0};

	add_existing_neighbors(g,x,y,change);

	for(int i=0; i<4; i++)
		if(change[i]!=0)
			g->player_free_fields[i]++;
}
void reindex(gamma_t* g,uint32_t player,uint32_t x, uint32_t y, unode_t* master, char from) {
	g->arr[x][y]->depth=1;
	g->arr[x][y]->parent=master;
	if(from!=UP && adjacent_up(g, player, x, y)) reindex(g, player, x, y+1, master,DOWN);
	if(from!=DOWN && adjacent_down(g, player, x, y)) reindex(g, player, x, y-1, master,UP);
	if(from!=LEFT && adjacent_left(g, player, x, y)) reindex(g, player, x-1, y, master,RIGHT);
	if(from!=RIGHT && adjacent_right(g, player, x, y)) reindex(g, player, x+1, y, master, LEFT);
}
bool remove_field(gamma_t* g,uint32_t x, uint32_t y) {
	uint32_t player=g->arr[x][y]->player;
	unode_t* master, * del;
	unode_t* still_connected[4]={NULL,NULL,NULL,NULL};
	int adder=-1;

	if(!has_friends(g,player,x,y)) {
		free(g->arr[x][y]);
		g->arr[x][y]=NULL;
		return true;
	}
	else {
		if(adjacent_up(g, player, x, y)) {
			master=new_unode(g->arr[x][y+1]->player);
			reindex(g, player, x, y+1, master,DOWN);
			del=g->arr[x][y+1];
			g->arr[x][y+1]=master;
			free(del);
			add_and_decrease_distinct(ufind(master), still_connected, &adder);
		}
		if(adjacent_down(g, player, x, y)) {
			master=new_unode(g->arr[x][y-1]->player);
			reindex(g, player, x, y-1, master,UP);
			del=g->arr[x][y-1];
			g->arr[x][y-1]=master;
			free(del);
			add_and_decrease_distinct(ufind(master), still_connected, &adder);
		}
		if(adjacent_left(g, player, x, y)) {
			master=new_unode(g->arr[x-1][y]->player);
			reindex(g, player, x-1, y, master,RIGHT);
			del=g->arr[x-1][y];
			g->arr[x-1][y]=master;
			free(del);
			add_and_decrease_distinct(ufind(master), still_connected, &adder);
		}
		if(adjacent_right(g, player, x, y)) {
			master=new_unode(g->arr[x+1][y]->player);
			reindex(g, player, x+1, y, master,LEFT);
			del=g->arr[x+1][y];
			g->arr[x+1][y]=master;
			free(del);
			add_and_decrease_distinct(ufind(master), still_connected, &adder);
		}
		increase_adjacents(g,x,y);
		assert(adder!=-1);
		free(g->arr[x][y]);
		g->arr[x][y]=NULL;
		if(g->max_players-g->player_area_count[player]<(unsigned)adder) {
			g->del_error_flag=true;
			gamma_move(g,player,x,y);
			g->del_error_flag=false;
			return false;
		}
		g->player_area_count[player]+=adder;
	}
	return true;
}
gamma_t* gamma_new(uint32_t width, uint32_t height, uint32_t players, uint32_t areas) {
	// TODO: Check Given Data
	gamma_t* g;
	uint64_t i;
	g=malloc(sizeof(struct gamma));
	g->width=width;
	g->height=height;
	g->free_fields=width*height;
	g->max_areas=areas;
	g->max_players=players;
	g->del_error_flag=false;
	g->arr=malloc(g->width*sizeof(unode_t**));
	g->did_golden_move=malloc((g->max_players+1)*sizeof(bool));
	g->player_area_count=malloc((g->max_players+1)*sizeof(uint64_t));
	g->player_free_fields=malloc((g->max_players+1)*sizeof(uint64_t));
	g->player_busy_fields=malloc((g->max_players+1)*sizeof(uint64_t));
	for(i=0; i<g->width; i++)
		g->arr[i]=malloc(g->height*sizeof(unode_t*));

	for(i=0; i<g->width; i++)
		for(uint32_t j=0; j<g->height; i++)
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
	// TODO: Check Given Data
	for(uint32_t i=0; i<g->width; i++)
		free(g->arr[i]);
	free(g->player_area_count);
	free(g->player_busy_fields);
	free(g->player_free_fields);
	free(g->did_golden_move);
	free(g->arr);
	free(g);
}
bool gamma_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	// TODO: Check Given Data: x<width, y<height, player<=players
	bool has_adjacent_friends=has_friends(g, player, x, y);
	if(g->arr[x][y]!=NULL) return false;
	if(g->player_area_count[player]>=g->max_areas && !has_adjacent_friends && !g->del_error_flag)
		return false;
	add_free_adjacents(g, player, x, y);
	decrease_adjacents(g, x, y);
	if(!has_adjacent_friends) {
		g->player_area_count[player]++;
		g->arr[x][y]=new_unode(player);
	}
	else {
		g->arr[x][y]=new_unode(player);
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
	return true;
}
bool gamma_golden_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	// TODO: Check Given Data
	if(g->player_area_count[player]>=g->max_areas && !has_friends(g,player,x,y)) return false;
	if(remove_field(g,x,y)) return false;
	gamma_move(g,player,x,y);
	g->did_golden_move[player]=true;
	return true;
}
uint64_t gamma_busy_fields(gamma_t* g, uint32_t player) {
	// TODO: Check Given Data
	return g->player_busy_fields[player];
}
uint64_t gamma_free_fields(gamma_t* g, uint32_t player) {
	// TODO: Check Given Data
	assert(g->player_area_count[player]<g->max_areas);
	if(g->player_area_count[player]==g->max_areas)
		return g->player_free_fields[player];
	return g->free_fields;
}
bool gamma_golden_possible(gamma_t* g, uint32_t player) {
	// TODO: Check Given Data
	if(g->did_golden_move[player]) return false;
	uint32_t i;
	for(i=1; i<g->max_players;i++)
		if(g->player_busy_fields[i]>0 && i!=player)
			return true;
	return false;
}
char* gamma_board(gamma_t* g) {
	// TODO: Check Given Data
	uint32_t height=g->height;
	uint32_t width=g->width;
	char* board = malloc((1+height*(width+1)) * sizeof(char));
	unode_t*** arr=g->arr;
	uint32_t i, j;
	for(i = 0; i <  height; i++)
		for (j = 0; j < width; j++)
			*(board + i*(width+1) + j) = arr[height-i][j]!= NULL ? '0' + arr[height-i][j]->player : '.';
	for(i = 0; i <  height; i++)
		*(board + i*(width+1) + width)='\n';
	*(board + (height-1)*(width+1) + width + 1)='\0';
	return NULL;
}
