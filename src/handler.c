#include "handler.h"
#include "gamma.h"
#include "safe_malloc.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
bool handle_command(gamma_t** g, Command command) {
	switch(command.type) {
		case BATCH_MODE:
			if(*g!=NULL) return false;
			return (*g=gamma_new(command.width,command.height,
												 command.players,command.areas));

		case INTER_MODE:
			if(*g!=NULL || command.width == 0 || command.height == 0 ||
			command.players == 0 || command.areas == 0)
				return false;
			printf("Interactive mode: press Enter to start\n"
					"\nJust kidding, bye.");
			return true;

		case MOVE:
			if(*g==NULL) return false;
			printf("%d\n", gamma_move(*g,command.player,command.x,command.y));
			return true;

		case GOLDEN_MOVE:
			if(*g==NULL) return false;
			printf("%d\n", gamma_golden_move(*g,command.player,command.x,command.y));
			return true;

		case BUSY_FIELDS:
			if(*g == NULL || command.player > (*g)->max_players || command.player == 0)
				return false;
			printf("%lu\n",gamma_busy_fields(*g,command.player));
			return true;

		case FREE_FIELDS:
			if(*g == NULL || command.player > (*g)->max_players || command.player == 0)
				return false;
			printf("%lu\n",gamma_free_fields(*g,command.player));
			return true;

		case GOLDEN_POSSIBLE:
			if(*g==NULL) return false;
			printf("%d\n", gamma_golden_possible(*g,command.player));
			return true;

		case BOARD:
			if(*g==NULL) return false;
			char* b=gamma_board(*g);
			assert(b);
			printf("%s",b);
			safe_free(b);
			return true;
	}
	return false;
}
