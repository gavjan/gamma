// [IPP] Małe Zadanie(Small Task), Gevorg Chobanyan 401929
#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "safe_malloc.h"
#include "parser.h"
#include "gamma.h"
#include "handler.h"
#include <ctype.h>
// Clear tokens and reset strings
static inline Command clear_tokens(Command command) {
	command.player=safe_realloc(command.player, sizeof(char));
	command.tree=safe_realloc(command.tree, sizeof(char));
	command.animal=safe_realloc(command.animal, sizeof(char));
	command.player[0]='\0';
	command.tree[0]='\0';
	command.animal[0]='\0';
	*command.forest_capacity=STARTING_SIZE;
	*command.tree_capacity=STARTING_SIZE;
	*command.animal_capacity=STARTING_SIZE;
	return command;
}

// Check if line contains white spaces
static inline bool isspace_line(const char* line) {
	int i=0;
	while(line[i]) {
		if(!isspace(line[i])) return false;
		i++;
	}
	return true;
}
int main() {
	gamma_t* g=NULL;
	Command command;
	int first_char;
	u_int64_t line_num=0;
	while((first_char=fpeek())!=EOF) {
		line_num++;
		if(first_char == '\n' || first_char == '#')
			reach_line_end();
		else {
			command=parse_command();
			if(command.type == UNRECOGNIZED || !handle_command(&g,command))
				err(line_num);
			else {
				if(command.type == BATCH_MODE)
					printf("OK %lu", line_num);
				if(command.type == INTER_MODE)
					break;
			}
		}
	}
	gamma_delete(g);
	exit(0);
}
