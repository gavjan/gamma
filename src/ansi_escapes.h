/** @file
 * Header file providing functions for interacting with the
 * terminal
 * @author Gevorg Chobanyan
 * @date 11.04.2020
 */
#include <stdio.h>
#include "ui.h"

/** @brief Macro for Clearing All flag in terminal
 */
#define CLEAR_ALL 2

/** @brief Macro for moving the Cursor by one
 */
#define MOVE_BY_ONE 1


enum Keys {
		NO_KEY,
		KEY_UP,
		KEY_DOWN,
		KEY_RIGHT,
		KEY_LEFT,
		KEY_SPACE,
		KEY_G,
		KEY_C,
		UNKNOWN
};

enum Colors {
		RESET_COLOR = 0,
		GREEN_TXT = 32,
		YELLOW_TXT = 33
};

void set_text_color(int code);

/** @brief Return a pressed valid key.
 * Check if the pressed key is valid and if it is return it.
 * Return 0 otherwise
 * @param [in] t - structure containing interactive game's state
 * @param [in] c - flag for the last recognized key after escaping
 * @return a character if it's valid
 */
int get_key(game_t* t, int c);

/** @brief Implementation of the standard getch() function
 * @param [in] t - structure containing interactive game's state
 * @return a character if it's valid
 */
int getch(game_t* t);

/** @brief Prepare console
 * @param [in] t - structure containing interactive game's state
 */
void setup_console(game_t* t);

/** @brief Restore the console's original state
 * @param [in] t - structure containing interactive game's state
 */
void restore_console(game_t* t);

/** @brief Clear the whole screen
 */
void clear_screen();

/** @brief Clear cursors line
 */
void clear_line();

/** @brief Move the cursor up
 */
void cursor_up();

/** @brief Move the cursor down
 */
void cursor_down();

/** @brief Move the cursor right
 */
void cursor_right();

/** @brief Move the cursor left
 */
void cursor_left();

/** @brief Move the cursor to a specified location
 * @param [in] row - row number
 * @param [in] column - column number
 */
void move_to(int row, int column);
