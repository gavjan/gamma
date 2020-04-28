#ifndef GAMMA_UI_H
#define GAMMA_UI_H

#include <termios.h>
#include <stdint.h>
#include <stdbool.h>
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_RIGHT 3
#define KEY_LEFT 4
#define KEY_SPACE 5
#define KEY_G 6
#define KEY_C 7
#define move_right() if(t.cur_j<t.width) {cursor_right(); t.cur_j++; }
#define move_left() if(t.cur_j>1) {cursor_left(); t.cur_j--; }
#define move_up() if(t.cur_i>1) {cursor_up(); t.cur_i--; }
#define move_down() if(t.cur_i<t.height) {cursor_down(); t.cur_i++; }

typedef struct game {
		uint32_t cur_i;
		uint32_t cur_j;
		uint32_t max_players;
		uint32_t width;
		uint32_t height;
		uint32_t curr_player;
		bool game_over;
		struct termios original_terminal;
		struct termios new_terminal;
} game_t;
#endif //GAMMA_UI_H