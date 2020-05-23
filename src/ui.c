/** @file
 * Source file providing access to the functions
 * responsible for the interactive mode
 * @author Gevorg Chobanyan
 * @date 30.04.2020
 */
#include "ui.h"
#include <stdio.h>
#include <stdint.h>
#include <termios.h>
#include "ansi_escapes.h"
#include "gamma.h"
#include "safe_malloc.h"
/** @brief Insert a character
 * Insert a character to the cursor's position and move the
 * cursor back to that position
 * @param [in] c - Character that is to be inserted
 */
static inline void insert_char(int c) {
	putchar(c);
	cursor_left();
}
/** @brief Initialize the game board
 * @param [in] g - pointer to the structure that stores the game state
 * @return Structure containing the interactive game's starting state
 */
static game_t init_board(gamma_t* g) {
	static struct termios original_terminal;
	static struct termios new_terminal;
	bool enough_memory = true;
	bool** pos_can_move = malloc(sizeof(bool*)*g->width+sizeof(bool)*g->height*g->width);
	char** arr = malloc(sizeof(char*)*g->width+sizeof(char)*g->height*g->width);

	if(arr == NULL || pos_can_move == NULL) {
		safe_free(arr);
		safe_free(pos_can_move);
		enough_memory = false;
	}
	else {
		uint32_t i;
		char* char_ptr;
		bool* bool_ptr;
		char_ptr = (char*)(arr+g->width);
		bool_ptr = (bool*)(pos_can_move+g->width);
		for(i = 0; i < g->width; i++) {
			arr[i] = (char_ptr+g->height*i);
			pos_can_move[i] = (bool_ptr+g->height*i);
		}
		uint32_t height = g->height, width = g->width, x, y;
		for(x = 0; x < width; x++)
			for(y = 0; y < height; y++)
				arr[x][y] = '.';
	}

	game_t t = {1,
							1,
							g->max_players,
							g->width,
							g->height,
							1,
							false,
							pos_can_move,
							arr,
							original_terminal,
							new_terminal,
							enough_memory
	};

	setup_console(&t);
	clear_screen();
	move_to(1, 1);
	char* board = gamma_board(g);

	setTextColor(GREEN_TXT);
	printf("%s", board);
	setTextColor(RESET_COLOR);

	safe_free(board);
	move_to(g->height+1, 1);
	printf("PLAYER 1 0 %d\n", g->height*g->width);
	move_to(1, 1);

	return t;
}
static void delete_board(game_t* t) {
	safe_free(t->pos_can_move);
	safe_free(t->arr);
}
/** @brief Update the Heads Up Display
 * @param [in] g - pointer to the structure that stores the game state
 * @param [in] t - pointer to the structure that stores the interactive state
 */
static void update_hud(game_t* t, gamma_t* g) {
	move_to(t->height+1, 1);
	clear_line();
	move_to(t->height+1, 1);
	uint64_t free_fields = gamma_free_fields(g, t->curr_player);
	uint64_t busy_fields = gamma_busy_fields(g, t->curr_player);

	printf("PLAYER %u %lu %lu", t->curr_player, busy_fields, free_fields);


	if(gamma_golden_possible_interactive(g, t->curr_player, t->pos_can_move))
		setTextColor(GREEN_TXT);
	if(gamma_golden_available(g,t->curr_player))
		printf(" G");
	setTextColor(RESET_COLOR);
	printf("\n");

	gamma_possible_moves(g, t->curr_player, t->pos_can_move);
	move_to(1, 1);
	uint32_t i, j, width = t->width, height = t->height;
	bool** pos_can_move = t->pos_can_move;
	char** arr = t->arr;
	for(i = 0; i < height; i++) {
		for(j = 0; j < width; j++) {
			if(pos_can_move[width-1-j][height-1-i])
				setTextColor(GREEN_TXT);
			else
				setTextColor(RESET_COLOR);
			printf("%c", arr[width-1-j][height-1-i]);
		}
		printf("\n");
	}
	setTextColor(RESET_COLOR);

	move_to(t->cur_i, t->cur_j);
}
/** @brief Check if current player can't make a move
 * @param [in] t - pointer to the structure that stores the interactive state
 * @param [in] g - pointer to the structure that stores the game state
 * @return @p if the player can't make a move, @p false otherwise
 */
static inline bool cant_move(game_t* t, gamma_t* g) {
	return gamma_free_fields(g, t->curr_player) == 0 &&
				 !gamma_golden_possible(g, t->curr_player);
}
/** @brief Skip a move
 * @param [in] t - pointer to the structure that stores the interactive state
 * @param [in] g - pointer to the structure that stores the game state
 */
static void skip_move(game_t* t, gamma_t* g) {
	t->curr_player = (t->curr_player)%t->max_players+1;
	while(cant_move(t, g)) {
		if(gamma_game_over(g)) {
			t->game_over = true;
			break;
		}
		t->curr_player = (t->curr_player)%t->max_players+1;
	}
	update_hud(t, g);
}
/** @brief Make a move
 * @param [in] t - pointer to the structure that stores the interactive state
 * @param [in] g - pointer to the structure that stores the game state
 * @param [in] golden - boolean value that indicates if the move is golden
 */
static void make_move(game_t* t, gamma_t* g, bool golden) {
	bool move_result = golden ?
										 gamma_golden_move(g, t->curr_player, t->width-t->cur_j, t->height-t->cur_i)
														: gamma_move(g, t->curr_player, t->width-t->cur_j, t->height-t->cur_i);
	if(move_result) {
		insert_char('0'+t->curr_player);
		t->arr[t->width-t->cur_j][t->height-t->cur_i] = '0'+t->curr_player;

		// Skip or end the game
		skip_move(t, g);
	}
}
bool start_interactive(gamma_t* g) {
	if(g == NULL) return false;
	game_t t = init_board(g);

	if(!t.enough_memory) {
		delete_board(&t);
		return false;
	}

	while(!t.game_over) {
		switch(get_key(&t, NO_KEY)) {
			case KEY_UP:
				if(t.cur_i > 1) {
					cursor_up();
					t.cur_i--;
				}
				break;

			case KEY_DOWN:
				if(t.cur_i < t.height) {
					cursor_down();
					t.cur_i++;
				}
				break;

			case KEY_LEFT:
				if(t.cur_j > 1) {
					cursor_left();
					t.cur_j--;
				}
				break;

			case KEY_RIGHT:
				if(t.cur_j < t.width) {
					cursor_right();
					t.cur_j++;
				}
				break;

			case KEY_SPACE:
				make_move(&t, g, NOT_GOLDEN);
				break;

			case KEY_G:
				make_move(&t, g, GOLDEN);
				break;

			case KEY_C:
				skip_move(&t, g);
				break;

			case EOF:
				t.game_over = true;
				break;
		}
	}
	// Print End Scores
	move_to(t.height+1, 1);
	clear_line();
	move_to(t.height+1, 1);
	for(uint32_t i = 1; i <= t.max_players; i++)
		printf("PLAYER %u %lu\n", i, gamma_busy_fields(g, i));
	restore_console(&t);
	delete_board(&t);
	return true;
}
