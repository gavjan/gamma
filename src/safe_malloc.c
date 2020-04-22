/** @file
 * Source file for Safe Manual Allocation functions
 * @author Gevorg Chobanyan
 * @date 18.03.2020
 */
#include "safe_malloc.h"
#include <stdlib.h>
#include <string.h>
void* safe_free(void* p) {
	if(p) free(p);
	return NULL;
}
//int safe_strcmp(const char *s1, const char *s2) {
//	return strncmp(s1,s2,strlen(s2));
//}
