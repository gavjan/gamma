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
	if(c==EOF) ungetc(c,stdin);
}
bool nothing_but_white_left() {
	int c;
	while(isspace(c=getchar()) && c!='\n') ;
	if(c=='\n' || c==EOF) {
		ungetc(c,stdin);
		return true;
	}
	return false;
}
// Take next token
bool get_next_token(Command* command, uint32_t* token) {
	char number[UINT32_MAX_LENGTH+1];
	int c;
	while(isspace(c=getchar()) && c!='\n') ;
	ungetc(c,stdin);
	size_t pos=0;

	while(!(isspace(c=getchar()) && c!='\n')) {
		if(!isdigit(c) || pos>UINT32_MAX_LENGTH) {
			if(c==EOF || c=='\n') {
				ungetc(c,stdin);
				break;
			}
			else
				return ((*command).type=UNRECOGNIZED);
		}
		number[pos]=(char)c;
		pos++;
	}
	number[pos]='\0';

	errno=0;
	*token=strtoul(number,NULL,10);
	if(errno==ERANGE || pos==0)
		return ((*command).type=UNRECOGNIZED);
	return true;
}

int check_first_char() {
	int c = getchar();
	if(c=='B') {return BATCH_MODE;}
	if(c=='I') {return INTER_MODE;}
	if(c=='m') {return MOVE;}
	if(c=='g') {return GOLDEN_MOVE;}
	if(c=='b') {return BUSY_FIELDS;}
	if(c=='f') {return FREE_FIELDS;}
	if(c=='q') {return GOLDEN_POSSIBLE;}
	if(c=='p') {return BOARD;}

	return UNRECOGNIZED;
}

// Separate command into tokens correctly
Command parse_command() {
	Command command={UNRECOGNIZED,0,0,0,0,0,0,0};
	command.type=check_first_char();
	if(command.type==UNRECOGNIZED)
		return command;

	if(command.type==BOARD) {
		command.type=nothing_but_white_left() ? BOARD : UNRECOGNIZED;
		return command;
	}

	if(isspace(fpeek()) && fpeek()!='\n') {
		if(command.type==BATCH_MODE || command.type==INTER_MODE) {
			if(!get_next_token(&command,&command.width) ||
			!get_next_token(&command,&command.height) ||
			!get_next_token(&command,&command.players) ||
			!get_next_token(&command,&command.areas) ||
			!nothing_but_white_left()) {}
			return command;
		}
		else if(command.type==MOVE || command.type==GOLDEN_MOVE){
			if(!get_next_token(&command,&command.player) ||
			!get_next_token(&command,&command.x) ||
			!get_next_token(&command,&command.y) ||
			!nothing_but_white_left()) {}
			return command;
		}
		else {
			if(!get_next_token(&command,&command.player) ||
				 !nothing_but_white_left()) {}
			return command;
		}
	}
	command.type=UNRECOGNIZED;
	return command;
}






