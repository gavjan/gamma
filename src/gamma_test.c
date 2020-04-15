/** @file
 * Example use of the gamma game engine
 *
 * @author Gevorg Chobanyan
 * @copyright Uniwersytet Warszawski
 * @date 18.03.2020
 */

// CMake release version turns off assertions.
#ifdef NDEBUG
#undef NDEBUG
#endif

#include "gamma.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * This is what the board should look like after all tests.
 */
static const char board[]=
				"1.........\n"
				"..........\n"
				"..........\n"
				"......2...\n"
				".....2....\n"
				"..........\n"
				"..........\n"
				"1.........\n"
				"1221......\n"
				"1.........\n";

/** @brief Tests the gamma engine.
 * Performs sample gamma engine tests.
 * @return Zero, when all tests passed,
 * otherwise the program exit code is an error code.
 */
int main() {
	gamma_t* g;

	g=gamma_new(0, 0, 0, 0);
	assert(g==NULL);

	g=gamma_new(10, 10, 2, 3);
	assert(g!=NULL);

	assert(gamma_move(g, 1, 0, 0));
	assert(gamma_busy_fields(g, 1)==1);
	assert(gamma_busy_fields(g, 2)==0);
	assert(gamma_free_fields(g, 1)==99);
	assert(gamma_free_fields(g, 2)==99);
	assert(!gamma_golden_possible(g, 1));
	assert(gamma_move(g, 2, 3, 1));
	assert(gamma_busy_fields(g, 1)==1);
	assert(gamma_busy_fields(g, 2)==1);
	assert(gamma_free_fields(g, 1)==98);
	assert(gamma_free_fields(g, 2)==98);
	assert(gamma_move(g, 1, 0, 2));
	assert(gamma_move(g, 1, 0, 9));
	assert(!gamma_move(g, 1, 5, 5));
	assert(gamma_free_fields(g, 1)==6);
	assert(gamma_move(g, 1, 0, 1));
	assert(gamma_free_fields(g, 1)==95);
	assert(gamma_move(g, 1, 5, 5));
	assert(!gamma_move(g, 1, 6, 6));
	assert(gamma_busy_fields(g, 1)==5);
	assert(gamma_free_fields(g, 1)==10);
	assert(gamma_move(g, 2, 2, 1));
	assert(gamma_move(g, 2, 1, 1));
	assert(gamma_free_fields(g, 1)==9);
	assert(gamma_free_fields(g, 2)==92);
	assert(!gamma_move(g, 2, 0, 1));
	assert(gamma_golden_possible(g, 2));
	assert(!gamma_golden_move(g, 2, 0, 1));
	assert(gamma_golden_move(g, 2, 5, 5));
	assert(!gamma_golden_possible(g, 2));
	assert(gamma_move(g, 2, 6, 6));
	assert(gamma_busy_fields(g, 1)==4);
	assert(gamma_free_fields(g, 1)==91);
	assert(gamma_busy_fields(g, 2)==5);
	assert(gamma_free_fields(g, 2)==13);
	assert(gamma_golden_move(g, 1, 3, 1));
	assert(gamma_busy_fields(g, 1)==5);
	assert(gamma_free_fields(g, 1)==8);
	assert(gamma_busy_fields(g, 2)==4);
	assert(gamma_free_fields(g, 2)==10);

	char* p=gamma_board(g);
	assert(p);
	assert(strcmp(p, board)==0);
	printf(p);
	free(p);

	gamma_delete(g);
	return 0;
}
