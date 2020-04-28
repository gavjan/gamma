/** @file
 * Header file providing functions for Gamma
 *
 * @author Gevorg Chobanyan
 * @date 11.04.2020
 */

#ifndef GAMMA_H
#define GAMMA_H

#include <stdbool.h>
#include <stdint.h>
#include "ufind.h"
/**
 * @brief Macro for direction up
 */
#define UP 0
/**
 * @brief Macro for direction down
 */
#define DOWN 1
/**
 * @brief Macro for direction left
 */
#define LEFT 2
/**
 * @brief Macro for direction right
 */
#define RIGHT 3
/**
 * @brief Structure storing the game state
 */
typedef struct gamma {
		unode_t*** arr;                ///< Two dimensional array for storing the board state
		uint32_t width;                ///< Width of the board
		uint32_t height;              ///< Height of the board
		uint32_t max_players;          ///< Maximum number of players allowed
		uint32_t max_areas;            ///< Maximum number of areas a player can possess
		uint64_t free_fields;          ///< Counter for free fields
		uint64_t* player_area_count;  ///< Array of counters for taken areas
		uint64_t* player_free_fields;  ///< Array of counters for free adjacent fields
		uint64_t* player_busy_fields;  ///< Array of counters for taken fields
		bool del_error_flag;          ///< Error flag used when Golden Move fails
		bool* did_golden_move;        ///< Track of which player has already made a Golden move
} gamma_t;

/** @brief Creates a structure that stores the game state.
 * Allocates memory to a new structure that stores the game state.
 * Initializes this structure to represent the initial state of the game.
 * @param [in] width - board width, positive number,
 * @param [in] height - board height, positive number,
 * @param [in] players - number of players, positive number,
 * @param [in] areas - maximum number of areas,
 * one player can take, a positive number.
 * @return A pointer to the created structure or NULL when failed
 * allocate memory or one of the parameters is incorrect.
 */
gamma_t* gamma_new(uint32_t width, uint32_t height,
									 uint32_t players, uint32_t areas);

/** @brief Removes the structure that stores the game state.
 * Removes from memory the structure indicated by @p g.
 * Does nothing if this indicator is NULL.
 * @param [in] g - pointer to the removed structure.
 */
void gamma_delete(gamma_t* g);

/** @brief Makes a move.
 * Sets the @p player player's pawn in the field (@p x, @p y).
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] player - player number, positive number does not exceed value
 * @p players from the @ref gamma_new function,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function.
 * @return Value @p true if the move was made and @p false,
 * when the move is illegal or one of the parameters is incorrect.
 */
bool gamma_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y);

/** @brief Makes a golden move.
 * Sets the player pawn @p player on the field (@p x, @p y) occupied by another
 * player by removing another player's pawn.
 * @param [in, out] g - pointer to the structure that stores the game state,
 * @param [in] player - player number, positive number does not exceed value
 * @p players from the @ref gamma_new function,
 * @param [in] x - column number, positive number less than value
 * @p width from the @ref gamma_new function,
 * @param [in] y - line number, positive number less than value
 * @p height from the @ref gamma_new function.
 * @return Value @p true if the move was made and @p false,
 * once the player has used his golden move, the move is illegal
 * or one of the parameters is invalid.
 */
bool gamma_golden_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y);

/** @brief Returns the number of fields occupied by the player.
 * Return the number of fields occupied by the player @p player.
 * @param [in] g - pointer to the structure that stores the game state,
 * @param [in] player - player number, positive number does not exceed value
 * @p players from the @ref gamma_new function.
 * @return Number of fields occupied by the player or zero,
 * if any of the parameters is incorrect.
 */
uint64_t gamma_busy_fields(gamma_t* g, uint32_t player);

/** @brief Return the number of fields that the player can still take.
 * Returns the number of free fields on which in the given game state the player @p player can
 * put your pawn in the next move.
 * @param [in] g - pointer to the structure that stores the game state,
 * @param [in] player - player number, positive number does not exceed value
 * @p players from the @ref gamma_new function.
 * @return Number of fields that the player can still take or zero,
 * if any of the parameters is incorrect.
 */
uint64_t gamma_free_fields(gamma_t* g, uint32_t player);

/** @brief Checks if the player can make a golden move.
 * Checks if the @p player has not made a golden move in this game yet
 * and there is at least one space occupied by another player.
 * @param [in] g - pointer to the structure that stores the game state,
 * @param [in] player - player number, positive number does not exceed value
 * @p players from the @ref gamma_new function.
 * @return Value @p true if the player has not yet done in this game
 * golden move and there is at least one space occupied by another player,
 * a @p false otherwise.
 */
bool gamma_golden_possible(gamma_t* g, uint32_t player);

/** @brief Gives an inscription describing the status of the board.
 * Allocates a buffer in memory in which it places a string containing text
 * description of the current state of the board. An example can be found in the gamma_test.c file.
 * The calling function must free this buffer.
 * @param [in] g - pointer to the structure that stores the game state.
 * @return A pointer to an allocated buffer containing a string describing the state
 * board or NULL if memory allocation failed.
 */
char* gamma_board(gamma_t* g);

/** @brief Check if game is over.
 * Check if no more moves are possible by any player.
 * @param [in] g - pointer to the structure that stores the game state.
 * @return Value @p true if at least one player can still make
 * a move and @p false otherwise.
 */
bool gamma_game_over(gamma_t* g);

#endif /* GAMMA_H */
