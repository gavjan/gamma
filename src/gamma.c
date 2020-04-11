#include "gamma.h"
#include <stdlib.h>
#include <assert.h>
inline bool adjacent_up(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (y+1<g->height && ufind(g->arr[x][y+1])->player==player);
}
inline bool adjacent_down(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (y>0 && ufind(g->arr[x][y-1])->player==player);
}
inline bool adjacent_left(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (x>0 && ufind(g->arr[x-1][y])->player==player);
}
inline bool adjacent_right(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (x+1<g->width && ufind(g->arr[x+1][y])->player==player);
}
inline bool exists_up(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (y+1<g->height && g->arr[x][y+1]!=NULL);
}
inline bool exists_down(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (y>0 && g->arr[x][y-1]!=NULL);
}
inline bool exists_left(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (x>0 && g->arr[x-1][y]!=NULL);
}
inline bool exists_right(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (x+1<g->width && g->arr[x+1][y]!=NULL);
}
inline bool free_adjacent_up(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (y+1<g->height && g->arr[x][y+1]==NULL);
}
inline bool free_adjacent_down(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (y>0 && g->arr[x][y-1]==NULL);
}
inline bool free_adjacent_left(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (x>0 && g->arr[x-1][y]==NULL);
}
inline bool free_adjacent_right(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
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
	if(!has_friends(g,player,x,y)) g->player_free_count[player]++;
}
// increase_if_no_friends() on for all 4 neighbors
void add_free_adjacents(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	if(free_adjacent_up(g, player, x, y)) increase_if_no_friends(g,player,x,y+1);
	if(free_adjacent_down(g, player, x, y)) increase_if_no_friends(g,player,x,y-1);
	if(free_adjacent_left(g, player, x, y)) increase_if_no_friends(g,player,x-1,y);
	if(free_adjacent_right(g, player, x, y)) increase_if_no_friends(g,player,x+1,y);
}
void add_if_missing(uint32_t player, uint32_t* change) {
	for(short i=0; i<4;i++) {
		if(change[i]==player)
			break;
		else if(change[i]==0) {
			change[i]=player; break;
		}
	}
}
void decrease_adjacents(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	uint32_t change[4]= {0,0,0,0};

	if(exists_up(g, player, x, y)) add_if_missing(g->arr[x][y+1]->player,change);
	if(exists_down(g, player, x, y)) add_if_missing(g->arr[x][y-1]->player,change);
	if(exists_left(g, player, x, y)) add_if_missing(g->arr[x-1][y]->player,change);
	if(exists_right(g, player, x, y)) add_if_missing(g->arr[x+1][y]->player,change);

	for(short i=0; i<4;i++)
		if(change[i]!=0) {
			assert(g->player_free_count[i]);
			g->player_free_count[i]--;
		}
}
gamma_t* gamma_new(uint32_t width, uint32_t height, uint32_t players, uint32_t areas) {
	// TODO: Check Given Data
	gamma_t* g;
	g=malloc(sizeof(struct gamma));
	g->width=width;
	g->height=height;
	g->free_fields=width*height;
	g->max_areas=areas;
	g->max_players=players;
	g->arr=malloc(g->width*sizeof(unode_t**));

	uint64_t i;
	for(i=0; i<g->width; i++)
		g->arr[i]=malloc(g->height*sizeof(unode_t*));
	for(i=0; i<g->width; i++)
		for(uint32_t j=0; j<g->height; i++)
			g->arr[i][j]=NULL;

	g->player_area_count=malloc((g->max_players+1)*sizeof(uint64_t));
	g->player_free_count=malloc((g->max_players+1)*sizeof(uint64_t));
	g->player_field_count=malloc((g->max_players+1)*sizeof(uint64_t));
	for(i=0; i<=g->max_players; i++)
		g->player_area_count[i]=0;
	return g;
}
void gamma_delete(gamma_t* g) {
	// TODO: Check Given Data
	for(uint32_t i=0; i<g->width; i++)
		free(g->arr[i]);
	free(g->player_area_count);
	free(g->player_field_count);
	free(g->player_free_count);
	free(g->arr);
	free(g);
}
bool gamma_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	// TODO: Check Given Data: x<width, y<height, player<=players
	bool has_adjacent_friends=has_friends(g, player, x, y);
	if(g->arr[x][y]!=NULL) return false;
	if(g->player_area_count[player]==g->max_areas && !has_adjacent_friends)
			return false;
	add_free_adjacents(g,player,x,y);
	decrease_adjacents(g,player,x,y);
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
	return true;
}
bool gamma_golden_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	// TODO: Check Given Data
	return NULL;
}
uint64_t gamma_busy_fields(gamma_t* g, uint32_t player) {
	// TODO: Check Given Data
	return NULL;
}
uint64_t gamma_free_fields(gamma_t* g, uint32_t player) {
	// TODO: Check Given Data
	return NULL;
}
bool gamma_golden_possible(gamma_t* g, uint32_t player) {
	// TODO: Check Given Data
	return NULL;
}
char* gamma_board(gamma_t* g) {
	// TODO: Check Given Data
	return NULL;
}
