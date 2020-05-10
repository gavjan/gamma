/** @file
 * Header file for input parsing functions
 *
 * @author Gevorg Chobanyan
 * @date 27.04.2020
 */
#ifndef GAMMA_PARSER_H
#define GAMMA_PARSER_H

#include <stdint.h>

/** @brief Macro for Max digit count of UINT32_MAX
 */
#define UINT32_MAX_LENGTH 10

/** @brief Macro for an Unrecognized command
 */
#define UNRECOGNIZED 0

/** @brief Macro for Batch Mode
 */
#define BATCH_MODE 1

/** @brief Macro for Interactive Mode
 */
#define INTER_MODE 2

/** @brief Macro for Move command
 */
#define MOVE 3

/** @brief Macro for Golden Move command
 */
#define GOLDEN_MOVE 4

/** @brief Macro for Busy Fields command
 */
#define BUSY_FIELDS 5

/** @brief Macro for Free Fields command
 */
#define FREE_FIELDS 6

/** @brief Macro for Golden Move Possible command
 */
#define GOLDEN_POSSIBLE 7

/** @brief Macro for Board State command
 */
#define BOARD 8

/** @brief Structure for storing command's tokens
 */
typedef struct command {
		int type;         ///< Type of the command
		uint32_t player;  ///< player token
		uint32_t x;       ///< x coordinate token
		uint32_t y;       ///< y coordinate token
		uint32_t width;   ///< width token
		uint32_t height;  ///< height token
		uint32_t players; ///< players token
		uint32_t areas;   ///< areas token
} Command;

/** @brief Write ERROR
 * Write ERROR with the line number of
 * the error to the standard diagnostic output
 * @return The given character if it was recognized and
 * 0 otherwise.
 */
void err(uint64_t line);


/** @brief Separate command into tokens correctly
 * @return @p Command structure containing the respective tokens
 */
Command parse_command();

/** @brief Reach to the end of the line
 */
void reach_line_end();

/** @brief Peek at stdin
 * Check the first character of the input stream without
 * taking it from the input stream
 * @return The taken character
 */
int fpeek();

#endif //GAMMA_PARSER_H
