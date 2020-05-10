/** @file
 * Source file for input parsing functions
 *
 * @author Gevorg Chobanyan
 * @date 27.04.2020
 */
#include "parser.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
int fpeek() {
	int c;
	c = fgetc(stdin);
	ungetc(c, stdin);
	return c;
}
void err(uint64_t line) {
	fprintf(stderr, "ERROR %lu\n", line);
}
void reach_line_end() {
	int c;
	while((c = getchar()) != '\n' && c != EOF);
	if(c == EOF) ungetc(c, stdin);
}

/** @brief Check if the remaining characters of the line are whitespace characters
 * @return @p true or @p false.
 */
bool nothing_but_white_left() {
	int c;
	while(isspace(c = getchar()) && c != '\n');
	if(c == '\n' || c == EOF) {
		ungetc(c, stdin);
		return true;
	}
	return false;
}
/** @brief Take next token
 * Take the next token whilst checking if it is correct.
 * @param [in] token - variable where the taken token will reside
 * @return @p true if the token was correct numerically, @p false otherwise
 */
bool get_next_token(uint32_t* token) {
	char number[UINT32_MAX_LENGTH+1];
	int c;
	while(isspace(c = getchar()) && c != '\n');
	ungetc(c, stdin);
	size_t pos = 0;

	while(!(isspace(c = getchar()) && c != '\n')) {
		if(!isdigit(c) || pos > UINT32_MAX_LENGTH) {
			if(c == EOF || c == '\n') {
				ungetc(c, stdin);
				break;
			}
			else
				return false;
		}
		number[pos] = (char)c;
		pos++;
	}
	number[pos] = '\0';
	uint64_t ans = strtoull(number, NULL, 10);
	if(number[0]=='0' && ans!=0) return false;
	if(ans > UINT32_MAX || pos == 0) return false;
	*token = ans;
	return true;
}
/** @brief Check first character of the line
 * Check and return a recognized character.
 * @return The given character if it was recognized and
 * 0 otherwise.
 */
int check_first_char() {
	int c = getchar();
	if(c == 'B') {return BATCH_MODE;}
	if(c == 'I') {return INTER_MODE;}
	if(c == 'm') {return MOVE;}
	if(c == 'g') {return GOLDEN_MOVE;}
	if(c == 'b') {return BUSY_FIELDS;}
	if(c == 'f') {return FREE_FIELDS;}
	if(c == 'q') {return GOLDEN_POSSIBLE;}
	if(c == 'p') {return BOARD;}

	return UNRECOGNIZED;
}
Command parse_command() {
	Command command = {UNRECOGNIZED, 0, 0, 0, 0, 0, 0, 0};
	command.type = check_first_char();
	if(command.type == UNRECOGNIZED)
		return command;

	if(command.type == BOARD) {
		command.type = nothing_but_white_left() ? BOARD : UNRECOGNIZED;
		return command;
	}

	if(isspace(fpeek()) && fpeek() != '\n') {
		if(command.type == BATCH_MODE || command.type == INTER_MODE) {
			if(!get_next_token(&command.width) ||
				 !get_next_token(&command.height) ||
				 !get_next_token(&command.players) ||
				 !get_next_token(&command.areas) ||
				 !nothing_but_white_left()) {
				command.type = UNRECOGNIZED;
			}
			return command;
		}
		else if(command.type == MOVE || command.type == GOLDEN_MOVE) {
			if(!get_next_token(&command.player) ||
				 !get_next_token(&command.x) ||
				 !get_next_token(&command.y) ||
				 !nothing_but_white_left()) {
				command.type = UNRECOGNIZED;
			}
			return command;
		}
		else {
			if(!get_next_token(&command.player) ||
				 !nothing_but_white_left()) {
				command.type = UNRECOGNIZED;
			}
			return command;
		}
	}
	command.type = UNRECOGNIZED;
	return command;
}






