
#include <stdio.h>
#include "ui.h"
#define CLEAR_ALL 2
#define MOVE_BY_ONE 1
#define UNKNOWN 0
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_RIGHT 3
#define KEY_LEFT 4
#define KEY_SPACE 5
#define KEY_G 6
#define KEY_C 7
int get_key(game_t* t);

int getch(game_t* t);

void setup_console(game_t* t);

void restore_console(game_t* t);

void clear_screen();

void clear_line();

void cursor_up();

void cursor_down();

void cursor_right();

void cursor_left();

void move_to(int row, int col);
