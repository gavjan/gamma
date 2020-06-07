/** @file
 * Source file providing functions' implementations for Gamma
 * @author Gevorg Chobanyan
 * @date 18.03.2020
 */
#include "gamma.h"
#include <stdlib.h>
#include <assert.h>
#include "safe_malloc.h"
#include "list.h"
/** @brief Check if field up from current field belongs to @p player
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] player - player number, positive number does not exceed value
 * @p players from the @ref gamma_new function,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 * @return Value @p true if up adjacent node belongs to @p player @p false, otherwise
 */
static inline bool adjacent_up(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (y + 1 < g->height && g->arr[x][y + 1] != NULL && g->arr[x][y + 1]->player == player);
}
/** @brief Check if field down from current field belongs to @p player
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] player - player number, positive number does not exceed value
 * @p players from the @ref gamma_new function,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 * @return Value @p true if down adjacent node belongs to @p player @p false, otherwise
 */
static inline bool adjacent_down(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (y > 0 && g->arr[x][y - 1] != NULL && g->arr[x][y - 1]->player == player);
}
/** @brief Check if field left from current field belongs to @p player
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] player - player number, positive number does not exceed value
 * @p players from the @ref gamma_new function,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 * @return Value @p true if left adjacent node belongs to @p player @p false, otherwise
 */
static inline bool adjacent_left(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (x > 0 && g->arr[x - 1][y] != NULL && g->arr[x - 1][y]->player == player);
}
/** @brief Check if field right from current field belongs to @p player
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] player - player number, positive number does not exceed value
 * @p players from the @ref gamma_new function,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 * @return Value @p true if right adjacent node belongs to @p player @p false, otherwise
 */
static inline bool adjacent_right(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return (x + 1 < g->width && g->arr[x + 1][y] != NULL && g->arr[x + 1][y]->player == player);
}
/** @brief Check if field up from current field exists
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 * @return Value @p true if the field at right exists @p false, otherwise
 */
static inline bool exists_up(gamma_t* g, uint32_t x, uint32_t y) {
	return (y + 1 < g->height && g->arr[x][y + 1] != NULL);
}
/** @brief Check if field down from current field exists
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 * @return Value @p true if the field at right exists @p false, otherwise
 */
static inline bool exists_down(gamma_t* g, uint32_t x, uint32_t y) {
	return (y > 0 && g->arr[x][y - 1] != NULL);
}
/** @brief Check if field left from current field exists
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 * @return Value @p true if the field at right exists @p false, otherwise
 */
static inline bool exists_left(gamma_t* g, uint32_t x, uint32_t y) {
	return (x > 0 && g->arr[x - 1][y] != NULL);
}
/** @brief Check if field right from current field exists
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 * @return Value @p true if the field at right exists @p false, otherwise
 */
static inline bool exists_right(gamma_t* g, uint32_t x, uint32_t y) {
	return (x + 1 < g->width && g->arr[x + 1][y] != NULL);
}
/** @brief Check if field up from current field is free
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 * @return Value @p true if the field at up is free @p false, otherwise
 */
static inline bool free_adjacent_up(gamma_t* g, uint32_t x, uint32_t y) {
	return (y + 1 < g->height && g->arr[x][y + 1] == NULL);
}
/** @brief Check if field down from current field is free
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 * @return Value @p true if the field at down is free @p false, otherwise
 */
static inline bool free_adjacent_down(gamma_t* g, uint32_t x, uint32_t y) {
	return (y > 0 && g->arr[x][y - 1] == NULL);
}
/** @brief Check if field left from current field is free
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 * @return Value @p true if the field at left is free @p false, otherwise
 */
static inline bool free_adjacent_left(gamma_t* g, uint32_t x, uint32_t y) {
	return (x > 0 && g->arr[x - 1][y] == NULL);
}
/** @brief Check if field right from current field is free
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 * @return Value @p true if the field at right us free @p false, otherwise
 */
static inline bool free_adjacent_right(gamma_t* g, uint32_t x, uint32_t y) {
	return (x + 1 < g->width && g->arr[x + 1][y] == NULL);
}
/** @brief Check if field @p x,@p y has adjacent fields belonging to @p player
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] player - player number, positive number does not exceed value
 * @p players from the @ref gamma_new function,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 * @return Value @p true if the current field has at least
 * one adjacent field belonging to @p player @p false, otherwise
 */
static inline bool has_friends(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	return adjacent_up(g, player, x, y) ||
		 adjacent_down(g, player, x, y) ||
		 adjacent_left(g, player, x, y) ||
		 adjacent_right(g, player, x, y);
}
/** @brief Increase potential field count that @p player can visit
 * Adds the @p player counter for fields he can move without increasing
 * his area count
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] player - player number, positive number does not exceed value
 * @p players from the @ref gamma_new function,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 */
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
 * @p height from the @ref gamma_new function
 */
static void add_free_adjacents(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	if(free_adjacent_up(g, x, y)) increase_if_no_friends(g, player, x, y + 1);
	if(free_adjacent_down(g, x, y)) increase_if_no_friends(g, player, x, y - 1);
	if(free_adjacent_left(g, x, y)) increase_if_no_friends(g, player, x - 1, y);
	if(free_adjacent_right(g, x, y)) increase_if_no_friends(g, player, x + 1, y);
}
/** @brief Add a player to the list if we are missing that player
 * @param [in] player - player number, positive number does not exceed value
 * @p players from the @ref gamma_new function,
 * @param [in] change - list of players for change
 */
static void add_if_missing(uint32_t player, uint32_t* change) {
	for(int i = 0; i < 4; i++) {
		if(change[i] == player)
			break;
		else if(change[i] == 0) {
			change[i] = player;
			break;
		}
	}
}
/** @brief Add area count if the area will be separated after removal of a field
 * @param [in] master - new master field
 * @param [in] still_connected - list of areas that are still connected
 * @param [in] adder - how many areas will be added
 * @p height from the @ref gamma_new function
 */
static void add_and_decrease_distinct(unode_t* master, unode_t** still_connected, int* adder) {
	for(int i = 0; i < 4; i++) {
		if(ufind(still_connected[i]) == ufind(master))
			return;
		else if(still_connected[i] == NULL) {
			still_connected[i] = master;
			*adder += 1;
			break;
		}
	}
}
/** @brief add_if_missing() for all 4 neighbors
 * Add neighbors in distinct areas
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 * @param [in] change - list of players for change
 */
static inline void add_existing_neighbors(gamma_t* g, uint32_t x, uint32_t y, uint32_t* change) {
	if(exists_up(g, x, y))
		add_if_missing(g->arr[x][y + 1]->player, change);
	if(exists_down(g, x, y))
		add_if_missing(g->arr[x][y - 1]->player, change);
	if(exists_left(g, x, y))
		add_if_missing(g->arr[x - 1][y]->player, change);
	if(exists_right(g, x, y))
		add_if_missing(g->arr[x + 1][y]->player, change);
}
/** @brief Decrease potential free locations for neighbors
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 */
static void decrease_adjacents(gamma_t* g, uint32_t x, uint32_t y) {
	uint32_t change[4] = {0, 0, 0, 0};

	add_existing_neighbors(g, x, y, change);

	for(int i = 0; i < 4; i++)
		if(change[i] != 0) {
			assert(g->player_free_fields[change[i]]);
			g->player_free_fields[change[i]]--;
		}
}
/** @brief Check if a free field has friends
 * Check if a free field has adjacent fields belonging to @p player
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] player - player number, positive number does not exceed value
 * @p players from the @ref gamma_new function,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 * @param [in] from - direction we are coming from
 * @return Value @p true if the current free field has at least
 * one adjacent field belonging to @p player @p false, otherwise
 */
static bool free_has_friends(gamma_t* g, uint32_t player, uint32_t x, uint32_t y, char from) {
	if(g->arr[x][y] != NULL) return true;
	return
		 (adjacent_up(g, player, x, y) && from != UP) ||
				(adjacent_down(g, player, x, y) && from != DOWN) ||
				(adjacent_left(g, player, x, y) && from != LEFT) ||
				(adjacent_right(g, player, x, y) && from != RIGHT);
}
/** @brief Decrease player's free locations
 * When removing lonesome friends we decrease player's free field locations
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 */
static void decrease_player_free_adjacents(gamma_t* g, uint32_t x, uint32_t y) {
	uint32_t player = g->arr[x][y]->player;
	if(free_adjacent_up(g, x, y) && !free_has_friends(g, player, x, y + 1, DOWN))
		g->player_free_fields[player]--;
	if(free_adjacent_down(g, x, y) && !free_has_friends(g, player, x, y - 1, UP))
		g->player_free_fields[player]--;
	if(free_adjacent_left(g, x, y) && !free_has_friends(g, player, x - 1, y, RIGHT))
		g->player_free_fields[player]--;
	if(free_adjacent_right(g, x, y) && !free_has_friends(g, player, x + 1, y, LEFT))
		g->player_free_fields[player]--;
}
/** @brief Increase player's free locations
 * When moving to a location add neighboring free locations to our count
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 */
static void increase_adjacents(gamma_t* g, uint32_t x, uint32_t y) {
	uint32_t change[4] = {0, 0, 0, 0};

	add_existing_neighbors(g, x, y, change);

	for(int i = 0; i < 4; i++)
		if(change[i] != 0)
			g->player_free_fields[change[i]]++;
}
/** @brief Unvisit all cells
 * @param [in, out] g - pointer to the structure that stores the game state,
 */
static void unvisit_all(gamma_t* g) {
	if(g == NULL) return;
	uint32_t height = g->height, width = g->width, x, y;
	for(x = 0; x < width; x++)
		for(y = 0; y < height; y++)
			if(g->arr[x][y] != NULL)
				g->arr[x][y]->visited = false;
}
/** @brief Reindex an area
 * When removing a field we might potentially be breaking an area into two
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] player - player number, positive number does not exceed value
 * @p players from the @ref gamma_new function,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 * @param [in] master - new master field
 * @param [in] from - direction we are coming from
 */
static void reindex(gamma_t* g, uint32_t player, uint32_t x, uint32_t y, unode_t* master, char from) {
	if(g->arr[x][y]->visited) return;
	g->arr[x][y]->visited = true;
	g->arr[x][y]->depth = 1;
	g->arr[x][y]->parent = master;
	if(from != UP && adjacent_up(g, player, x, y))
		reindex(g, player, x, y + 1, master, DOWN);
	if(from != DOWN && adjacent_down(g, player, x, y))
		reindex(g, player, x, y - 1, master, UP);
	if(from != LEFT && adjacent_left(g, player, x, y))
		reindex(g, player, x - 1, y, master, RIGHT);
	if(from != RIGHT && adjacent_right(g, player, x, y))
		reindex(g, player, x + 1, y, master, LEFT);
}
/** @brief Remove a field
 * Removing a field is used for making a golden move
 * @param [in] g - pointer to the structure that stores the game state,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 * @return Value @p true if the field was removed @p false,
 * otherwise
 */
static bool remove_field(gamma_t* g, uint32_t x, uint32_t y) {
	uint32_t player = g->arr[x][y]->player;
	unode_t* master, * del;
	unode_t* still_connected[4] = {NULL, NULL, NULL, NULL};
	int adder = -1;

	decrease_player_free_adjacents(g, x, y);
	increase_adjacents(g, x, y);
	if(!has_friends(g, player, x, y)) {
		g->arr[x][y] = safe_free(g->arr[x][y]);
		g->free_fields++;
		assert(g->player_busy_fields);
		g->player_busy_fields[player]--;
		g->player_area_count[player]--;
		return true;
	} else {
		g->arr[x][y]->visited = true;
		if(adjacent_up(g, player, x, y)) {
			master = new_unode(g->arr[x][y + 1]->player);
			if(master == NULL) return false;
			unvisit_all(g);
			reindex(g, player, x, y + 1, master, DOWN);
			del = g->arr[x][y + 1];
			g->arr[x][y + 1] = master;
			safe_free(del);
			add_and_decrease_distinct(ufind(master), still_connected, &adder);
		}
		if(adjacent_down(g, player, x, y)) {
			master = new_unode(g->arr[x][y - 1]->player);
			if(master == NULL) return false;
			unvisit_all(g);
			reindex(g, player, x, y - 1, master, UP);
			del = g->arr[x][y - 1];
			g->arr[x][y - 1] = master;
			safe_free(del);
			add_and_decrease_distinct(ufind(master), still_connected, &adder);
		}
		if(adjacent_left(g, player, x, y)) {
			master = new_unode(g->arr[x - 1][y]->player);
			if(master == NULL) return false;
			unvisit_all(g);
			reindex(g, player, x - 1, y, master, RIGHT);
			del = g->arr[x - 1][y];
			g->arr[x - 1][y] = master;
			safe_free(del);
			add_and_decrease_distinct(ufind(master), still_connected, &adder);
		}
		if(adjacent_right(g, player, x, y)) {
			master = new_unode(g->arr[x + 1][y]->player);
			if(master == NULL) return false;
			unvisit_all(g);
			reindex(g, player, x + 1, y, master, LEFT);
			del = g->arr[x + 1][y];
			g->arr[x + 1][y] = master;
			safe_free(del);
			add_and_decrease_distinct(ufind(master), still_connected, &adder);
		}
		g->arr[x][y]->visited = false;
		assert(adder != -1);
		g->arr[x][y] = safe_free(g->arr[x][y]);
		g->free_fields++;
		assert(g->player_busy_fields);
		g->player_busy_fields[player]--;
		if(g->max_areas - g->player_area_count[player] < (uint64_t)adder) {
			g->player_area_count[player] += adder;
			g->del_error_flag = true;
			gamma_move(g, player, x, y);
			g->del_error_flag = false;
			return false;
		} else g->player_area_count[player] += adder;
	}
	return true;
}
/** @brief Checks if the player can make a golden move in a given field
 * Checks if the @p player can make a golden move in the the filed @p x, @p y
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] player - player number, positive number does not exceed value
 * @p players from the @ref gamma_new function
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 * @return Value @p true if the player can make a golden move at that field
 * and @p false otherwise
 */
static bool gamma_golden_possible_field(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	if(g->arr[x][y] == NULL) return false;
	if(g->arr[x][y]->player == player) return false;
	if(g->player_area_count[player] >= g->max_areas && !has_friends(g, player, x, y))
		return false;

	uint32_t original_player = g->arr[x][y]->player;
	if(!remove_field(g, x, y)) return false;
	if(!gamma_move(g, original_player, x, y))
		assert(false);
	return true;
}
/** @brief Checks if the player can make a move in a given field
 * Checks if the @p player can make move in the the filed @p x, @p y
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] player - player number, positive number does not exceed value
 * @p players from the @ref gamma_new function
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function
 * @return Value @p true if the player can make a move at that field
 * and @p false otherwise
 */
static bool move_possible(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	bool ans = gamma_move(g, player, x, y);
	if(ans) remove_field(g, x, y);
	return ans;
}
/** @brief Checks if the player can make a golden move
 * Checks if the @p player can make a golden move in at least one field.
 * For interactive mode answers for every field will be written to @p ans_arr.
 * For batch mode @p ans_arr will be NULL upon calling.
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] player - player number, positive number does not exceed value
 * @p players from the @ref gamma_new function
 * @param ans_arr [in, out] - pointer to array which will contain answer for fields
 * @return Value @p true if the player can make a  golden and @p false otherwise
 */
static bool check_golden_possible(gamma_t* g, uint32_t player, bool** ans_arr) {
	if(g == NULL || player > g->max_players || player == 0) return false;
	bool for_interactive = ans_arr != NULL, interactive_ans = false, ans;
	uint32_t height = g->height, width = g->width, x, y;

	if(for_interactive)
		for(x = 0; x < width; x++)
			for(y = 0; y < height; y++)
				ans_arr[x][y] = false;
	if(g->did_golden_move[player]) return false;
	bool available = false;
	uint32_t i;
	for(i = 1; i <= g->max_players; i++)
		if(g->player_busy_fields[i] > 0 && i != player)
			available = true;
	if(!available) return false;

	if(for_interactive) {
		for(x = 0; x < width; x++) {
			for(y = 0; y < height; y++) {
				ans = ans_arr[x][y] = gamma_golden_possible_field(g, player, x, y);
				if(interactive_ans == false && ans == true) interactive_ans = true;
			}
		}
	} else
		for(x = 0; x < width; x++)
			for(y = 0; y < height; y++)
				if(gamma_golden_possible_field(g, player, x, y))
					return true;
	if(for_interactive)
		return interactive_ans;
	else
		return false;
}
bool gamma_golden_available(gamma_t* g, uint32_t player) {
	if(g == NULL || player > g->max_players || player == 0) return false;
	return !g->did_golden_move[player];
}
gamma_t* gamma_new(uint32_t width, uint32_t height, uint32_t players, uint32_t areas) {
	if(width == 0 || height == 0 || players == 0 || areas == 0) return NULL;
	gamma_t* g;
	uint64_t i;
	g = calloc(sizeof(gamma_t), 1);
	if(g == NULL) return NULL;
	g->width = width;
	g->height = height;
	g->free_fields = width * height;
	g->max_areas = areas;
	g->max_players = players;
	size_t max_players = players, max_width = width, max_height = height;
	g->del_error_flag = false;
	g->status_changed = true;

	unode_t** ptr;
	unode_t*** arr;
	uint128_t size = sizeof(unode_t**) * max_width + sizeof(unode_t*) * max_height * max_width;
	if(size > UINT32_MAX) return safe_free(g);
	arr = (unode_t***)malloc(size);
	if(arr == NULL) return safe_free(g);
	ptr = (unode_t**)(arr + max_width);
	for(i = 0; i < width; i++)
		arr[i] = (ptr + max_height * i);
	g->arr = arr;
	arr = NULL;

	g->did_golden_move = calloc((max_players + 1), sizeof(bool));
	g->player_area_count = calloc((max_players + 1), sizeof(uint64_t));
	g->player_free_fields = calloc((max_players + 1), sizeof(uint64_t));
	g->player_busy_fields = calloc((max_players + 1), sizeof(uint64_t));
	if(
		 g->did_golden_move == NULL ||
				g->player_area_count == NULL ||
				g->player_free_fields == NULL ||
				g->player_busy_fields == NULL) {
		safe_free(g->arr);
		safe_free(g->did_golden_move);
		safe_free(g->player_area_count);
		safe_free(g->player_free_fields);
		safe_free(g->player_busy_fields);
		return safe_free(g);
	}

	for(i = 0; i < width; i++)
		for(uint32_t j = 0; j < height; j++)
			g->arr[i][j] = NULL;
	return g;
}
void gamma_delete(gamma_t* g) {
	if(g == NULL) return;
	for(uint32_t i = 0; i < g->width; i++)
		for(uint32_t j = 0; j < g->height; j++)
			safe_free(g->arr[i][j]);
	safe_free(g->player_area_count);
	safe_free(g->player_busy_fields);
	safe_free(g->player_free_fields);
	safe_free(g->did_golden_move);
	safe_free(g->arr);
	safe_free(g);
}
bool gamma_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	if(g == NULL || x >= g->width || y >= g->height || player > g->max_players || player == 0)
		return false;
	bool has_adjacent_friends = has_friends(g, player, x, y);
	if(g->arr[x][y] != NULL) return false;
	if(g->player_area_count[player] >= g->max_areas && !has_adjacent_friends && !g->del_error_flag)
		return false;
	add_free_adjacents(g, player, x, y);
	decrease_adjacents(g, x, y);
	if(!has_adjacent_friends) {
		g->player_area_count[player]++;
		g->arr[x][y] = new_unode(player);
		if(g->arr[x][y] == NULL) return false;
	} else {
		g->arr[x][y] = new_unode(player);
		if(g->arr[x][y] == NULL) return false;
		unode_t* up = adjacent_up(g, player, x, y) ? ufind(g->arr[x][y + 1]) : NULL;
		unode_t* down = adjacent_down(g, player, x, y) ? ufind(g->arr[x][y - 1]) : NULL;
		unode_t* left = adjacent_left(g, player, x, y) ? ufind(g->arr[x - 1][y]) : NULL;
		unode_t* right = adjacent_right(g, player, x, y) ? ufind(g->arr[x + 1][y]) : NULL;
		unode_t* horizontal = NULL;
		unode_t* vertical = NULL;

		if(ujoin(left, right))
			g->player_area_count[player]--;
		if(left != NULL || right != NULL)
			horizontal = ufind(left != NULL ? left : right);

		if(ujoin(up, down))
			g->player_area_count[player]--;
		if(up != NULL || down != NULL)
			vertical = ufind(up != NULL ? up : down);

		if(ujoin(vertical, horizontal))
			g->player_area_count[player]--;

		ujoin(g->arr[x][y], vertical);
		ujoin(g->arr[x][y], horizontal);
	}
	g->player_busy_fields[player]++;
	g->free_fields--;
	g->status_changed = true;
	return true;
}
bool gamma_golden_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
	if(g == NULL || x >= g->width || y >= g->height || player > g->max_players || player == 0)
		return false;
	if(g->did_golden_move[player]) return false;
	if(g->arr[x][y] == NULL) return false;
	if(g->arr[x][y]->player == player) return false;
	if(g->player_area_count[player] >= g->max_areas && !has_friends(g, player, x, y))
		return false;
	if(!remove_field(g, x, y)) return false;
	gamma_move(g, player, x, y);
	g->status_changed = true;
	g->did_golden_move[player] = true;
	return true;
}
uint64_t gamma_busy_fields(gamma_t* g, uint32_t player) {
	if(g == NULL || player > g->max_players || player == 0) return false;
	return g->player_busy_fields[player];
}
uint64_t gamma_free_fields(gamma_t* g, uint32_t player) {
	if(g == NULL || player > g->max_players || player == 0) return false;
	assert(g->player_area_count[player] <= g->max_areas);
	if(g->player_area_count[player] == g->max_areas)
		return g->player_free_fields[player];
	return g->free_fields;
}
bool gamma_golden_possible(gamma_t* g, uint32_t player) {
	return check_golden_possible(g, player, NULL);
}
char* gamma_board(gamma_t* g) {
	if(g == NULL) return NULL;
	uint32_t height = g->height;
	uint32_t width = g->width;
	char* board = calloc(1 + height * (width + 1), sizeof(char));
	if(board == NULL) return NULL;
	unode_t*** arr = g->arr;
	uint32_t i, j;
	for(i = 0; i < height; i++)
		for(j = 0; j < width; j++)
			*(board + i * (width + 1) + j) = arr[j][height - 1 - i] != NULL ?
				 '0' + arr[j][height - 1 - i]->player : '.';
	for(i = 0; i < height; i++)
		*(board + i * (width + 1) + width) = '\n';
	*(board + (height - 1) * (width + 1) + width + 1) = '\0';
	return board;
}
bool gamma_game_over(gamma_t* g) {
	if(g == NULL) return true;
	if(g->status_changed) {
		g->status_changed = false;
		uint32_t max_players = g->max_players;
		for(uint32_t i = 1; i <= max_players; i++)
			if(gamma_free_fields(g, i) != 0 || gamma_golden_possible(g, i))
				return false;
		g->game_over = true;
	}
	return g->game_over;
}
uint32_t gamma_winner(gamma_t* g, bool* draw, list_t** l) {
	*draw = false;
	if(!g->game_over)
		return NO_WINNER;
	uint32_t winner = NO_WINNER;
	for(uint32_t i = 1; i <= g->max_players; i++) {
		if(gamma_busy_fields(g, i) == gamma_busy_fields(g, winner)) {
			*draw = true;
			winner = i;
		} else if(gamma_busy_fields(g, i) > gamma_busy_fields(g, winner)) {
			*draw = false;
			winner = i;
		}
	}
	if(*draw)
		for(uint32_t i = g->max_players; i >= 1; i--)
			if(gamma_busy_fields(g, i) == gamma_busy_fields(g, winner))
				list_insert(l, i);

	return winner;
}
bool gamma_golden_possible_interactive(gamma_t* g, uint32_t player, bool** ans_arr) {
	return check_golden_possible(g, player, ans_arr);
}
void gamma_possible_moves(gamma_t* g, uint32_t player, bool** ans_arr) {
	uint32_t height = g->height, width = g->width, x, y;
	for(x = 0; x < width; x++)
		for(y = 0; y < height; y++)
			if(g->arr[x][y] == NULL)
				ans_arr[x][y] = move_possible(g, player, x, y);
}