#ifndef GAMMA_UI_H
#define GAMMA_UI_H

#include <termios.h>
#include <stdint.h>
#include <stdbool.h>
#include "gamma.h"
#define GOLDEN true
#define NOT_GOLDEN false
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_RIGHT 3
#define KEY_LEFT 4
#define KEY_SPACE 5
#define KEY_G 6
#define KEY_C 7

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

// Start Interactive Game Mode
bool start_interactive(gamma_t* g);
#endif //GAMMA_UI_H