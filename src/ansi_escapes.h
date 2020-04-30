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

// Check and return if a valid key was pressed
int get_key(game_t* t);

// Implementation of the standard getch() function
int getch(game_t* t);

// Prepare console
void setup_console(game_t* t);

// Restore the console's original state
void restore_console(game_t* t);

// Clear the whole screen
void clear_screen();

// Clear cursors line
void clear_line();

// Move the cursor up
void cursor_up();

// Move the cursor down
void cursor_down();

// Move the cursor right
void cursor_right();

// Move the cursor left
void cursor_left();

// Move to specified location
void move_to(int row, int col);
