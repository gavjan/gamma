#include "parser.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
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
	while((c=getchar())!='\n' && c!=EOF);
}
bool nothing_but_white_left() {
	int c;
	while(isspace(c=getchar())) {
		//TODO:: hi cunt finish me
	}
	if(c=='\n' )
	ungetc(c,stdin);
}
// Take next token
bool get_next_token(uint32_t* token) {
	char number[UINT32_MAX_LENGTH+1];
	int c;
	while(isspace(c=getchar())) ;
	ungetc(c,stdin);
	size_t pos=0;
	getchar();

	while(!isspace(c=getchar()) && c!='\n') {
		if(!isdigit(c) || pos>UINT32_MAX_LENGTH) { //TODO:: Fix MAX_LENGTH
			if(c==EOF) ungetc(c,stdin);
			return false;
		}
		number[pos]=(char)c;
		pos++;
	}
	number[pos]='\0';

	errno=0;
	*token=strtoul(number,NULL,10);
	if(errno==ERANGE) return false;
	return pos!=0;
}

int check_first_char() {
	int c = getchar();
	if(c=='B') {return BATCH_MODE;}
	else if(c=='I') {return INTER_MODE;}
	else if(c=='m') {return MOVE;}
	else if(c=='g') {return GOLDEN_MOVE;}
	else if(c=='b') {return BUSY_FIELDS;}
	else if(c=='f') {return FREE_FIELDS;}
	else if(c=='q') {return GOLDEN_POSSIBLE;}
	else if(c=='p') {return BOARD;}
	return UNRECOGNIZED;
}

// Separate command into tokens correctly
Command parse_command() {
	uint32_t token;
	Command command={UNRECOGNIZED,0,0,0,0,0,0,0};
	command.type=check_first_char();
	if(command.type==BOARD && nothing_but_white_left()) return command;

	if(isspace(fpeek())) {
		if(!get_next_token(&token)) {
			command.type=UNRECOGNIZED;
			return command;
		}
		if(line[start]=='\0')
			return command;
		if(!get_next_token(&token)) {
			command.type=UNRECOGNIZED;
			return command;
		}
		if(line[start]=='\0')
			return command;
		if(!get_next_token(&token) ||
			 (command.type==PRINT && *command.animal!='\0')) {
			command.type=UNRECOGNIZED;
			return command;
		}
		if(line[start]=='\0')
			return command;
	}
	command.type=UNRECOGNIZED;
	return command;
}






