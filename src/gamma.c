#include "gamma.h"
#include <stdlib.h>
inline bool adjacent_to_area(gamma_t *g, uint32_t player, uint32_t x, uint32_t y) {
	bool ans=(x+1<g->width && g->arr[x+1][y]==player) ||
					 (x>0 && g->arr[x-1][y]==player) ||
					 (y+1<g->height && g->arr[x][y+1]==player) ||
					 (y>0 && g->arr[x+1][y-1]==player);
	return ans;
}
gamma_t* gamma_new(uint32_t width, uint32_t height, uint32_t players, uint32_t areas) {
	// TODO: Check Given Data
	gamma_t* g;
	g = malloc(sizeof(struct gamma));
	g->width = width;
	g->height = height;
	g->max_areas=areas;
	g->max_players=players;
	g->arr = (uint32_t**)malloc(g->width * sizeof(uint32_t*));
	for (uint32_t i = 0; i<g->width; i++)
		g->arr[i] = (uint32_t*)malloc(height * sizeof(uint32_t));

	return g;
}
void gamma_delete(gamma_t *g) {
	// TODO: Check Given Data
	for (uint32_t i = 0; i<g->width; i++)
		free(g->arr[i]);
	free(g->arr);
	free(g);
}
bool gamma_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y) {
	// TODO: Check Given Data: x<width, y<height, player<=players
	if(g->arr[x][y]!=0) return false;
	//if(!adjacent_to_area(g,player,x,y))

	return true;
}
bool gamma_golden_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y) {
	// TODO: Check Given Data
	return NULL;
}
uint64_t gamma_busy_fields(gamma_t *g, uint32_t player) {
	// TODO: Check Given Data
	return NULL;
}
uint64_t gamma_free_fields(gamma_t *g, uint32_t player) {
	// TODO: Check Given Data
	return NULL;
}
bool gamma_golden_possible(gamma_t *g, uint32_t player) {
	// TODO: Check Given Data
	return NULL;
}
char* gamma_board(gamma_t *g) {
	// TODO: Check Given Data
	return NULL;
}
