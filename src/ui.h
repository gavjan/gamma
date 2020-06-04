/** @file
 * Source file providing access to the functions
 * responsible for the interactive mode
 * @author Gevorg Chobanyan
 * @date 30.04.2020
 */
#ifndef GAMMA_UI_H
#define GAMMA_UI_H

#include <termios.h>
#include <stdint.h>
#include <stdbool.h>
#include "gamma.h"

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
	bool successful_flag;               ///< Flag for indicating memory allocation result
} game_t;


/** @brief Start Interactive Game Mode
 * @param [in] g - pointer to the structure that stores the game state
 * @return @p true when Interactive Mode finishes, and @p false if the
 * given @p g pointer is NULL
 */
bool start_interactive(gamma_t* g);
#endif //GAMMA_UI_H
