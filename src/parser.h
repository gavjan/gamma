#ifndef GAMMA_PARSER_H
#define GAMMA_PARSER_H

#include <stdint.h>

#define UINT32_MAX_LENGTH 10
#define UNRECOGNIZED 0
#define BATCH_MODE 1
#define INTER_MODE 2
#define MOVE 3
#define GOLDEN_MOVE 4
#define BUSY_FIELDS 5
#define FREE_FIELDS 6
#define GOLDEN_POSSIBLE 7
#define BOARD 8
// Structure for storing commands
typedef struct command {
		int type;
		uint32_t player;
		uint32_t x;
		uint32_t y;
		uint32_t width;
		uint32_t height;
		uint32_t players;
		uint32_t areas;
} Command;

// Write ERROR with the line number of the error to the standard diagnostic output
void err(uint64_t line);

// Handle a command
Command parse_command();

// Reach to the end of the line
void reach_line_end();

// Check the first character of the input stream without taking it from the input stream
int fpeek();

#endif //GAMMA_PARSER_H
