/** @file
 * Header file providing functions for interacting with the
 * terminal
 * @author Gevorg Chobanyan
 * @date 11.04.2020
 */
#include <stdio.h>
#include "ui.h"



/** @brief Macro for successful execution
 */
#define SUCCESS 0

/** @brief Macro for unsuccessful execution
 */
#define FAIL (-1)

/** @brief Macro for Clearing All flag in terminal
 */
#define CLEAR_ALL 2

/** @brief Macro for moving the Cursor by one
 */
#define MOVE_BY_ONE 1

/** @brief enum for supported keyboard keys
 */
enum Keys {
	NO_KEY,
	KEY_UP,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_SPACE,
	KEY_G,
	KEY_C,
	KEY_CTRL_D,
	UNKNOWN
};
/** @brief enum containing color codes
 */
enum Colors {
	RESET_COLOR = 0,
	GREEN_TXT = 32,
	YELLOW_TXT = 33
};

/** @brief enum containing Key Codes
 */
enum Key_Codes {
	CTRL_D = 4,
	UPPER_C = 67,
	LOWER_C = 99,
	UPPER_G = 71,
	LOWER_G = 103,
	SPACE = 32,
	ESCAPE_CODE = 27,
	ESCAPE_BRACKET = 91,
	UP_CODE = 65,
	DOWN_CODE = 66,
	RIGHT_CODE = 67,
	LEFT_CODE = 68
};
/** @brief Macro for fail-safe execution of functions that can fail
 */
#define safe_exec(res)  if(res != SUCCESS) return FAIL

/** @brief Changes printing color
 * @param [in] code - Color code
 */
void set_text_color(int code);

/** @brief Return a pressed valid key
 * Check if the pressed key is valid and if it is return it
 * Return 0 otherwise
 * @param [in] t - structure containing interactive game's state
 * @param [in] c - flag for the last recognized key after escaping
 * @return a character if it's valid
 */
int get_key(game_t* t, int c);

/** @brief Implementation of the standard getch() function
 * @return a character if it's valid
 */
int getch();

/** @brief Prepare console
 * @param [in] t - structure containing interactive game's state
 * @return 0 upon successful execution and -1 otherwise
 */
int setup_console(game_t* t);

/** @brief Restore the console's original state
 * @param [in] t - structure containing interactive game's state
 * @return 0 upon successful execution and -1 otherwise
 */
int restore_console(game_t* t);

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
