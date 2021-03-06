/** @file
 * Source file providing handler function implementation
 * @author Gevorg Chobanyan
 * @date 27.04.2020
 */
#include "handler.h"
#include "gamma.h"
#include "safe_malloc.h"
#include "ui.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
bool handle_command(gamma_t** g, Command command) {
	switch(command.type) {
		case BATCH_MODE:
			if(*g != NULL) return false;
			return (*g = gamma_new(command.width, command.height,
														 command.players, command.areas)) != NULL;

		case INTER_MODE:
			if(*g != NULL) return false;
			*g = gamma_new(command.width, command.height,
										 command.players, command.areas);
			if(*g == NULL) return false;

			if(!start_interactive(*g)) {
				gamma_delete(*g);
				*g = NULL;
				exit(1);
			}
			return true;

		case MOVE:
			if(*g == NULL) return false;
			printf("%d\n", gamma_move(*g, command.player, command.x, command.y));
			return true;

		case GOLDEN_MOVE:
			if(*g == NULL) return false;
			printf("%d\n", gamma_golden_move(*g, command.player, command.x, command.y));
			return true;

		case BUSY_FIELDS:
			if(*g == NULL)
				return false;
			printf("%lu\n", gamma_busy_fields(*g, command.player));
			return true;

		case FREE_FIELDS:
			if(*g == NULL)
				return false;
			printf("%lu\n", gamma_free_fields(*g, command.player));
			return true;

		case GOLDEN_POSSIBLE:
			if(*g == NULL) return false;
			printf("%d\n", gamma_golden_possible(*g, command.player));
			return true;

		case BOARD:
			if(*g == NULL) return false;
			char* b = gamma_board(*g);
			if(b == NULL) return false;
			printf("%s", b);
			safe_free(b);
			return true;
	}
	return false;
}
