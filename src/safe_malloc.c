/** @file
 * Source file for Safe Manual Allocation functions
 * @author Gevorg Chobanyan
 * @date 18.03.2020
 */
#include "safe_malloc.h"
#include <stdlib.h>
void* safe_free(void* p) {
	if(p) free(p);
	return NULL;
}
