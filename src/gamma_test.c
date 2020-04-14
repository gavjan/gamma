#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "gamma.h"
#include <stdbool.h>
#include <string.h>


int main() {

/*
scenario: test_random_actions
uuid: 808088103
*/
/*
random actions, total chaos
*/
	gamma_t* board = gamma_new(6, 10, 4, 8);
	assert( board != NULL );


	assert( gamma_move(board, 2, 8, 3) == 0 );


	char* board487610384 = gamma_board(board);
	assert( board487610384 != NULL );
	assert( strcmp(board487610384,
								 "......\n"
								 "......\n"
								 "......\n"
								 "......\n"
								 "......\n"
								 "......\n"
								 "......\n"
								 "......\n"
								 "......\n"
								 "......\n") == 0);
	free(board487610384);
	board487610384 = NULL;
	assert( gamma_move(board, 4, 5, 8) == 1 );
	assert( gamma_move(board, 4, 4, 0) == 1 );
	assert( gamma_move(board, 1, 0, 5) == 1 );
	assert( gamma_move(board, 2, 3, 3) == 1 );
	assert( gamma_free_fields(board, 2) == 56 );
	assert( gamma_move(board, 3, 1, 7) == 1 );
	assert( gamma_move(board, 4, 1, 4) == 1 );
	assert( gamma_move(board, 4, 3, 4) == 1 );
	assert( gamma_move(board, 1, 0, 3) == 1 );
	assert( gamma_move(board, 2, 4, 0) == 0 );
	assert( gamma_move(board, 2, 1, 4) == 0 );
	assert( gamma_move(board, 3, 5, 0) == 1 );
	assert( gamma_move(board, 4, 6, 0) == 0 );
	assert( gamma_busy_fields(board, 4) == 4 );
	assert( gamma_move(board, 1, 5, 0) == 0 );
	assert( gamma_move(board, 2, 4, 2) == 1 );
	assert( gamma_move(board, 2, 1, 9) == 1 );
	assert( gamma_move(board, 3, 6, 0) == 0 );
	assert( gamma_move(board, 4, 5, 6) == 1 );
	assert( gamma_golden_possible(board, 4) == 1 );
	assert( gamma_move(board, 1, 1, 3) == 1 );
	assert( gamma_move(board, 1, 1, 7) == 0 );
	assert( gamma_move(board, 2, 3, 4) == 0 );
	assert( gamma_free_fields(board, 2) == 47 );
	assert( gamma_move(board, 3, 4, 4) == 1 );
	assert( gamma_free_fields(board, 3) == 46 );
	assert( gamma_move(board, 4, 8, 2) == 0 );
	assert( gamma_move(board, 4, 5, 6) == 0 );
	assert( gamma_move(board, 1, 0, 2) == 1 );
	assert( gamma_move(board, 1, 2, 2) == 1 );
	assert( gamma_move(board, 3, 0, 0) == 1 );
	assert( gamma_move(board, 4, 0, 4) == 1 );
	assert( gamma_move(board, 4, 2, 1) == 1 );
	assert( gamma_free_fields(board, 4) == 41 );
	assert( gamma_move(board, 1, 2, 6) == 1 );
	assert( gamma_move(board, 2, 6, 0) == 0 );


	char* board508096355 = gamma_board(board);
	assert( board508096355 != NULL );
	assert( strcmp(board508096355,
								 ".2....\n"
								 ".....4\n"
								 ".3....\n"
								 "..1..4\n"
								 "1.....\n"
								 "44.43.\n"
								 "11.2..\n"
								 "1.1.2.\n"
								 "..4...\n"
								 "3...43\n") == 0);
	free(board508096355);
	board508096355 = NULL;
	assert( gamma_move(board, 3, 8, 3) == 0 );
	assert( gamma_move(board, 4, 7, 4) == 0 );
	assert( gamma_free_fields(board, 4) == 40 );
	assert( gamma_move(board, 1, 9, 4) == 0 );
	assert( gamma_golden_possible(board, 1) == 1 );
	assert( gamma_move(board, 2, 2, 5) == 1 );
	assert( gamma_move(board, 2, 1, 3) == 0 );
	assert( gamma_golden_move(board, 2, 1, 2) == 0 );
	assert( gamma_move(board, 3, 1, 5) == 1 );
	assert( gamma_move(board, 3, 0, 6) == 1 );
	assert( gamma_move(board, 4, 8, 3) == 0 );
	assert( gamma_golden_possible(board, 4) == 1 );
	assert( gamma_move(board, 1, 5, 5) == 1 );
	assert( gamma_busy_fields(board, 1) == 7 );
	assert( gamma_golden_move(board, 1, 4, 1) == 0 );
	assert( gamma_move(board, 2, 2, 4) == 1 );
	assert( gamma_move(board, 2, 0, 5) == 0 );
	assert( gamma_move(board, 3, 4, 5) == 1 );
	assert( gamma_free_fields(board, 3) == 34 );
	assert( gamma_move(board, 4, 2, 1) == 0 );
	assert( gamma_move(board, 4, 5, 0) == 0 );
	assert( gamma_free_fields(board, 4) == 34 );
	assert( gamma_move(board, 1, 4, 5) == 0 );
	assert( gamma_move(board, 2, 0, 2) == 0 );
	assert( gamma_move(board, 3, 1, 4) == 0 );
	assert( gamma_move(board, 4, 1, 1) == 1 );
	assert( gamma_busy_fields(board, 4) == 8 );
	assert( gamma_golden_possible(board, 4) == 1 );
	assert( gamma_move(board, 1, 7, 3) == 0 );
	assert( gamma_move(board, 1, 1, 0) == 1 );
	assert( gamma_move(board, 2, 1, 3) == 0 );
	assert( gamma_move(board, 2, 3, 6) == 1 );
	assert( gamma_move(board, 3, 7, 2) == 0 );
	assert( gamma_move(board, 3, 5, 0) == 0 );
	assert( gamma_golden_possible(board, 3) == 1 );
	assert( gamma_busy_fields(board, 4) == 8 );
	assert( gamma_move(board, 1, 1, 9) == 0 );
	assert( gamma_move(board, 1, 0, 0) == 0 );
	assert( gamma_move(board, 2, 0, 2) == 0 );
	assert( gamma_move(board, 2, 5, 3) == 1 );
	assert( gamma_busy_fields(board, 3) == 7 );
	assert( gamma_move(board, 4, 8, 3) == 0 );
	assert( gamma_move(board, 1, 9, 3) == 0 );
	assert( gamma_move(board, 2, 2, 1) == 0 );
	assert( gamma_move(board, 2, 1, 4) == 0 );
	assert( gamma_busy_fields(board, 2) == 7 );
	assert( gamma_free_fields(board, 2) == 30 );
	assert( gamma_move(board, 3, 1, 0) == 0 );
	assert( gamma_busy_fields(board, 3) == 7 );
	assert( gamma_move(board, 4, 0, 5) == 0 );
	assert( gamma_move(board, 4, 4, 4) == 0 );
	assert( gamma_golden_possible(board, 4) == 1 );
	assert( gamma_move(board, 1, 9, 4) == 0 );
	assert( gamma_move(board, 1, 5, 2) == 1 );
	assert( gamma_move(board, 2, 0, 3) == 0 );
	assert( gamma_move(board, 2, 3, 6) == 0 );
	assert( gamma_move(board, 3, 9, 4) == 0 );
	assert( gamma_move(board, 4, 1, 5) == 0 );
	assert( gamma_move(board, 1, 3, 7) == 1 );
	assert( gamma_move(board, 2, 1, 1) == 0 );
	assert( gamma_move(board, 2, 0, 4) == 0 );
	assert( gamma_move(board, 3, 2, 1) == 0 );
	assert( gamma_move(board, 3, 3, 5) == 1 );
	assert( gamma_move(board, 4, 8, 0) == 0 );
	assert( gamma_move(board, 4, 3, 3) == 0 );
	assert( gamma_move(board, 1, 1, 2) == 1 );
	assert( gamma_move(board, 2, 7, 5) == 0 );
	assert( gamma_move(board, 2, 4, 0) == 0 );
	assert( gamma_move(board, 3, 1, 4) == 0 );
	assert( gamma_move(board, 4, 4, 5) == 0 );
	assert( gamma_move(board, 1, 9, 5) == 0 );
	assert( gamma_move(board, 1, 1, 3) == 0 );
	assert( gamma_golden_possible(board, 1) == 1 );
	assert( gamma_move(board, 2, 2, 6) == 0 );
	assert( gamma_move(board, 3, 0, 3) == 0 );
	assert( gamma_move(board, 4, 8, 3) == 0 );
	assert( gamma_move(board, 4, 2, 5) == 0 );
	assert( gamma_move(board, 1, 2, 6) == 0 );
	assert( gamma_move(board, 1, 4, 3) == 1 );
	assert( gamma_move(board, 2, 0, 4) == 0 );
	assert( gamma_move(board, 3, 4, 5) == 0 );
	assert( gamma_move(board, 3, 2, 7) == 1 );
	assert( gamma_golden_possible(board, 3) == 1 );
	assert( gamma_move(board, 4, 6, 1) == 0 );
	assert( gamma_move(board, 4, 1, 7) == 0 );
	assert( gamma_move(board, 1, 1, 0) == 0 );
	assert( gamma_move(board, 1, 2, 9) == 0 );
	assert( gamma_move(board, 2, 5, 4) == 1 );
	assert( gamma_move(board, 3, 9, 2) == 0 );
	assert( gamma_golden_possible(board, 3) == 1 );
	assert( gamma_golden_move(board, 3, 1, 1) == 1 );
	assert( gamma_move(board, 4, 4, 3) == 0 );
	assert( gamma_move(board, 4, 1, 9) == 0 );
	assert( gamma_move(board, 1, 9, 3) == 0 );
	assert( gamma_move(board, 2, 2, 8) == 1 );
	assert( gamma_move(board, 3, 0, 3) == 0 );
	assert( gamma_free_fields(board, 3) == 22 );
	assert( gamma_move(board, 4, 5, 6) == 0 );
	assert( gamma_move(board, 4, 2, 6) == 0 );
	assert( gamma_move(board, 1, 4, 3) == 0 );
	assert( gamma_move(board, 1, 3, 5) == 0 );
	assert( gamma_move(board, 2, 2, 1) == 0 );
	assert( gamma_move(board, 2, 1, 6) == 1 );
	assert( gamma_move(board, 3, 9, 2) == 0 );
	assert( gamma_golden_possible(board, 3) == 0 );
	assert( gamma_move(board, 4, 8, 1) == 0 );
	assert( gamma_move(board, 4, 3, 5) == 0 );
	assert( gamma_move(board, 1, 8, 3) == 0 );
	assert( gamma_move(board, 2, 6, 4) == 0 );
	assert( gamma_move(board, 3, 5, 3) == 0 );
	assert( gamma_move(board, 3, 4, 7) == 1 );
	assert( gamma_move(board, 4, 1, 5) == 0 );
	assert( gamma_move(board, 4, 0, 8) == 1 );
	assert( gamma_move(board, 1, 8, 1) == 0 );
	assert( gamma_move(board, 1, 0, 8) == 0 );
	assert( gamma_golden_possible(board, 1) == 1 );


	char* board814076663 = gamma_board(board);
	assert( board814076663 != NULL );
	assert( strcmp(board814076663,
								 ".2....\n"
								 "4.2..4\n"
								 ".3313.\n"
								 "3212.4\n"
								 "132331\n"
								 "442432\n"
								 "11.212\n"
								 "111.21\n"
								 ".34...\n"
								 "31..43\n") == 0);
	free(board814076663);
	board814076663 = NULL;
	assert( gamma_move(board, 2, 1, 4) == 0 );
	assert( gamma_move(board, 2, 5, 9) == 0 );
	assert( gamma_move(board, 3, 1, 3) == 0 );
	assert( gamma_move(board, 3, 3, 9) == 0 );
	assert( gamma_move(board, 4, 5, 7) == 1 );
	assert( gamma_move(board, 1, 1, 3) == 0 );
	assert( gamma_golden_possible(board, 1) == 1 );
	assert( gamma_move(board, 2, 8, 4) == 0 );
	assert( gamma_busy_fields(board, 2) == 10 );
	assert( gamma_move(board, 3, 1, 3) == 0 );
	assert( gamma_free_fields(board, 3) == 6 );
	assert( gamma_move(board, 4, 8, 4) == 0 );
	assert( gamma_move(board, 4, 2, 6) == 0 );
	assert( gamma_move(board, 1, 0, 3) == 0 );
	assert( gamma_move(board, 2, 5, 6) == 0 );
	assert( gamma_move(board, 3, 3, 2) == 0 );
	assert( gamma_move(board, 4, 1, 3) == 0 );
	assert( gamma_move(board, 4, 5, 1) == 1 );


	char* board888194881 = gamma_board(board);
	assert( board888194881 != NULL );
	assert( strcmp(board888194881,
								 ".2....\n"
								 "4.2..4\n"
								 ".33134\n"
								 "3212.4\n"
								 "132331\n"
								 "442432\n"
								 "11.212\n"
								 "111.21\n"
								 ".34..4\n"
								 "31..43\n") == 0);
	free(board888194881);
	board888194881 = NULL;
	assert( gamma_move(board, 1, 2, 3) == 1 );
	assert( gamma_move(board, 1, 2, 8) == 0 );
	assert( gamma_move(board, 2, 8, 3) == 0 );
	assert( gamma_golden_possible(board, 2) == 1 );
	assert( gamma_move(board, 3, 1, 3) == 0 );
	assert( gamma_move(board, 4, 2, 8) == 0 );
	assert( gamma_move(board, 4, 4, 5) == 0 );
	assert( gamma_free_fields(board, 4) == 16 );
	assert( gamma_move(board, 1, 1, 3) == 0 );
	assert( gamma_move(board, 2, 0, 4) == 0 );
	assert( gamma_free_fields(board, 2) == 7 );
	assert( gamma_move(board, 3, 5, 5) == 0 );
	assert( gamma_move(board, 4, 3, 0) == 1 );
/*
	".2....\n"
	"4.2..4\n"
	".33134\n"
	"3212.4\n"
	"132331\n"
	"442432\n"
	"111212\n"
	"111.21\n"
	".34..4\n"
	"31.443\n"

 */
	assert( gamma_golden_move(board, 4, 2, 2) == 1 );
	assert( gamma_move(board, 1, 5, 7) == 0 );
	assert( gamma_move(board, 2, 3, 8) == 1 );
	assert( gamma_move(board, 2, 4, 8) == 1 );
	assert( gamma_move(board, 3, 4, 7) == 0 );
	assert( gamma_move(board, 4, 8, 1) == 0 );
	assert( gamma_move(board, 1, 4, 5) == 0 );
	assert( gamma_move(board, 1, 2, 6) == 0 );
	assert( gamma_move(board, 2, 9, 5) == 0 );


	char* board805506698 = gamma_board(board);
	assert( board805506698 != NULL );
	assert( strcmp(board805506698,
								 ".2....\n"
								 "4.2224\n"
								 ".33134\n"
								 "3212.4\n"
								 "132331\n"
								 "442432\n"
								 "111212\n"
								 "114.21\n"
								 ".34..4\n"
								 "31.443\n") == 0);
	free(board805506698);
	board805506698 = NULL;
	assert( gamma_move(board, 3, 1, 3) == 0 );
	assert( gamma_busy_fields(board, 3) == 11 );
	assert( gamma_move(board, 4, 4, 6) == 1 );
	assert( gamma_move(board, 4, 5, 1) == 0 );
	assert( gamma_move(board, 1, 9, 5) == 0 );
	assert( gamma_move(board, 1, 2, 1) == 0 );
	assert( gamma_golden_possible(board, 1) == 1 );
	assert( gamma_move(board, 2, 7, 0) == 0 );
	assert( gamma_move(board, 2, 1, 0) == 0 );
	assert( gamma_golden_possible(board, 2) == 1 );
	assert( gamma_move(board, 3, 1, 0) == 0 );
	assert( gamma_free_fields(board, 3) == 3 );
	assert( gamma_move(board, 4, 2, 3) == 0 );


	gamma_delete(board);

	return 0;
}
