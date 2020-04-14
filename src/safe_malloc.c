#include "safe_malloc.h"
#include <stdlib.h>
void* safe_free(void* p) {
	if(p) free(p);
	return NULL;
}
