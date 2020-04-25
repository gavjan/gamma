#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "parser.h"
#include "gamma.h"
#include "handler.h"


int main() {
	gamma_t* g=NULL;
	Command command;
	int first_char;
	uint64_t line_num=0;
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
