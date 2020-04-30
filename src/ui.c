#include "ui.h"
#include <stdio.h>
#include <stdint.h>
#include <termios.h>
#include "ansi_escapes.h"
#include "gamma.h"
#include "safe_malloc.h"
// Insert a character to the cursor's position and move the cursor back to that position
void insert_char(int c) {
	putchar(c);
	printf("\033[%dD", (1));
}
// Initialize the game board
game_t init_board(gamma_t* g) {
	static struct termios original_terminal;
	static struct termios new_terminal;
	game_t t = {1,
							1,
							g->max_players,
							g->width,
							g->height,
							1,
							false,
							original_terminal,
							new_terminal
	};

	setup_console(&t);
	clear_screen();
	move_to(1, 1);
	char* board = gamma_board(g);
	printf("%s", board);
	safe_free(board);
	move_to(g->height+1, 1);
	printf("PLAYER 1 0 %d\n", g->height*g->width);
	move_to(1, 1);

	return t;
}
// Update the Heads Up Display
void update_hud(game_t* t, gamma_t* g) {
	move_to(t->height+1, 1);
	clear_line();
	move_to(t->height+1, 1);
	uint64_t free_fields = gamma_free_fields(g, t->curr_player);
	uint64_t busy_fields = gamma_busy_fields(g, t->curr_player);

	printf("PLAYER %u %lu %lu", t->curr_player, busy_fields, free_fields);
	if(gamma_golden_possible(g, t->curr_player))
		printf(" G");
	printf("\n");
	move_to(t->cur_i, t->cur_j);
}
// Check if current player can't make a move
static inline bool cant_move(game_t* t, gamma_t* g) {
	return gamma_free_fields(g, t->curr_player) == 0 &&
				 !gamma_golden_possible(g, t->curr_player);
}
// Skip a move
void skip_move(game_t* t, gamma_t* g) {
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
// Make a move
void make_move(game_t* t, gamma_t* g, bool golden) {
	bool move_result = golden ?
										 gamma_golden_move(g, t->curr_player, t->width-t->cur_j, t->height-t->cur_i)
														: gamma_move(g, t->curr_player, t->width-t->cur_j, t->height-t->cur_i);
	if(move_result) {
		insert_char('0'+t->curr_player);
		// Skip or end the game
		skip_move(t, g);
	}
}
bool start_interactive(gamma_t* g) {
	if(g == NULL) return false;
	game_t t = init_board(g);

	while(!t.game_over) {
		switch(get_key(&t)) {
			case KEY_UP:
				if(t.cur_j < t.width) {
					cursor_right();
					t.cur_j++;
				}
				break;

			case KEY_DOWN:
				if(t.cur_j > 1) {
					cursor_left();
					t.cur_j--;
				}
				break;

			case KEY_LEFT:
				if(t.cur_i > 1) {
					cursor_up();
					t.cur_i--;
				}
				break;

			case KEY_RIGHT:
				if(t.cur_i < t.height) {
					cursor_down();
					t.cur_i++;
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
	return true;
}
