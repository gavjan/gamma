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
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdbool.h>
#include "ansi_escapes.h"
#include "gamma.h"
#include "safe_malloc.h"
#include "list.h"
/** @brief Macro indicating that the move is golden
 */
#define GOLDEN true
/** @brief Macro indicating that the move isn't golden
 */
#define NOT_GOLDEN false
/** @brief Structure storing the interactive game's state
 */
typedef struct game {
	uint32_t cur_i;                   ///< Cursor's vertical location
	uint32_t cur_j;                   ///< Cursor's horizontal location
	uint32_t max_players;             ///< Maximum amount of players
	uint32_t width;                   ///< Width of the board
	uint32_t height;                  ///< Height of the board
	uint32_t curr_player;             ///< Current player that is to make a move
	bool game_over;                   ///< Game Over flag
	bool** pos_can_move;              ///< Fields where current player can move
	char** arr;                       ///< Board information
	struct termios original_terminal; ///< Structure holding the old terminal
	struct termios new_terminal;      ///< Structure holding the new terminal
	bool successful_flag;             ///< Flag for indicating memory allocation result
} game_t;
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
	struct winsize w;
	bool successful_flag = true;
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == FAIL) {
		fprintf(stderr, "Error setting up the terminal\n");
		successful_flag = false;
	}
	unsigned short rows = w.ws_row;
	unsigned short columns = w.ws_col;
	uint32_t width = get_width(g);
	uint32_t height = get_height(g);
	if(width > columns || height + 2 > rows) {
		successful_flag = false;
		fprintf(stderr, "Error, terminal is too small to fit the board\n");
	}
	bool** pos_can_move = malloc(sizeof(bool*) * width + sizeof(bool) * height * width);
	char** arr = malloc(sizeof(char*) * width + sizeof(char) * height * width);

	if(arr == NULL || pos_can_move == NULL) {
		safe_free(arr);
		safe_free(pos_can_move);
		successful_flag = false;
		fprintf(stderr, "Error allocating memory for interactive mode\n");
	} else {
		uint32_t i;
		char* char_ptr;
		bool* bool_ptr;
		char_ptr = (char*)(arr + width);
		bool_ptr = (bool*)(pos_can_move + width);
		for(i = 0; i < width; i++) {
			arr[i] = (char_ptr + height * i);
			pos_can_move[i] = (bool_ptr + height * i);
		}
		uint32_t x, y;
		for(x = 0; x < width; x++)
			for(y = 0; y < height; y++)
				arr[x][y] = '.';
	}

	game_t t = {
		 1,
		 1,
		 get_max_players(g),
		 width,
		 height,
		 1,
		 false,
		 pos_can_move,
		 arr,
		 original_terminal,
		 new_terminal,
		 successful_flag
	};
	if(!successful_flag) return t;

	if(setup_console(&t.original_terminal, &t.new_terminal) != SUCCESS) {
		t.successful_flag = false;
		fprintf(stderr, "Error setting up the terminal\n");
		return t;
	}
	clear_screen();
	move_to(1, 1);
	char* board = gamma_board(g);

	set_text_color(GREEN_TXT);
	printf("%s", board);
	set_text_color(RESET_COLOR);

	safe_free(board);
	move_to(height + 1, 1);
	printf("PLAYER 1 0 %d\n", height * width);
	move_to(1, 1);

	return t;
}
/** @brief Delete interactive state structure
 * Free manually allocated resources for the interactive state structure
 * @param [in] t - pointer to the structure that stores the interactive state
 */
static void delete_board(game_t* t) {
	safe_free(t->pos_can_move);
	safe_free(t->arr);
}
/** @brief Update the Heads Up Display
 * @param [in] g - pointer to the structure that stores the game state
 * @param [in] t - pointer to the structure that stores the interactive state
 */
static void update_hud(game_t* t, gamma_t* g) {
	move_to(t->height + 1, 1);
	clear_line();
	move_to(t->height + 1, 1);
	uint64_t free_fields = gamma_free_fields(g, t->curr_player);
	uint64_t busy_fields = gamma_busy_fields(g, t->curr_player);

	printf("PLAYER %u %lu %lu", t->curr_player, busy_fields, free_fields);

	if(gamma_golden_possible_interactive(g, t->curr_player, t->pos_can_move))
		set_text_color(YELLOW_TXT);
	if(gamma_golden_available(g, t->curr_player))
		printf(" G");
	set_text_color(RESET_COLOR);
	printf("\n");

	gamma_possible_moves(g, t->curr_player, t->pos_can_move);
	move_to(1, 1);
	uint32_t i, j, width = t->width, height = t->height;
	bool** pos_can_move = t->pos_can_move;
	char** arr = t->arr;
	for(i = 0; i < height; i++) {
		for(j = 0; j < width; j++) {
			if(pos_can_move[width - 1 - j][height - 1 - i])
				set_text_color(arr[width - 1 - j][height - 1 - i] == '.' ? GREEN_TXT : YELLOW_TXT);
			else
				set_text_color(RESET_COLOR);
			printf("%c", arr[width - 1 - j][height - 1 - i]);
		}
		printf("\n");
	}
	set_text_color(RESET_COLOR);

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
	t->curr_player = (t->curr_player) % t->max_players + 1;
	while(cant_move(t, g)) {
		if(gamma_game_over(g)) {
			t->game_over = true;
			break;
		}
		t->curr_player = (t->curr_player) % t->max_players + 1;
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
		 gamma_golden_move(g, t->curr_player, t->width - t->cur_j, t->height - t->cur_i)
		 : gamma_move(g, t->curr_player, t->width - t->cur_j, t->height - t->cur_i);
	if(move_result) {
		insert_char('0' + t->curr_player);
		t->arr[t->width - t->cur_j][t->height - t->cur_i] = '0' + t->curr_player;

		// Skip or end the game
		skip_move(t, g);
	}
}
bool start_interactive(gamma_t* g) {
	if(g == NULL) return false;
	game_t t = init_board(g);

	if(!t.successful_flag) {
		delete_board(&t);
		return false;
	}

	while(!t.game_over) {
		switch(get_key(NO_KEY)) {
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

			case KEY_CTRL_D:
				t.game_over = true;
				break;
			case FAIL:
				t.game_over = true;
				fprintf(stderr, "Error with the terminal\n");
				t.successful_flag = false;
				break;
		}
	}
	if(!t.successful_flag) {
		delete_board(&t);
		return false;
	}

	// Print End Scores
	move_to(t.height + 1, 1);
	clear_line();
	move_to(t.height + 1, 1);
	for(uint32_t i = 1; i <= t.max_players; i++) {
		printf("PLAYER %u %lu", i, gamma_busy_fields(g, i));
		if(gamma_golden_available(g, i))
			printf(" G");
		printf("\n");
	}
	bool draw, exec_success;
	list_t* draw_list = NULL;
	uint32_t winner = gamma_winner(g, &draw, &draw_list, &exec_success);
	if(!exec_success) {
		fprintf(stderr, "Error, ran out of memory\n");
		list_free(&draw_list);
		return false;
	}
	if(draw) {
		list_t* l = draw_list;
		printf("--\nDRAW FOR PLAYERS: %u", l->data);
		l = l->next;
		while(l != NULL) {
			printf(", %u", l->data);
			l = l->next;
		}
		printf("\n");
	} else if(winner != NO_WINNER)
		printf("--\nPLAYER %u WON\n", winner);
	list_free(&draw_list);
	delete_board(&t);

	if(restore_console(&t.original_terminal) != SUCCESS) {
		fprintf(stderr, "Error restoring the terminal\n");
		return false;
	}
	return true;
}
