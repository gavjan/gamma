/** @file
 * Header file for Safe Manual Allocation Operations
 *
 * @author Gevorg Chobanyan
 * @date 11.04.2020
 */
#ifndef GAMMA_SAFE_MALLOC_H
#define GAMMA_SAFE_MALLOC_H
#include <stdlib.h>
#include <stdio.h>
/** @brief Safe free() wrapper
 * Safely frees a memory location pointed by @p p
 * Does nothing if this indicator is NULL
 * @param [in] p - pointer to the memory location that
 * is to be freed
 * @return NULL pointer
 */
void* safe_free(void* p);

#endif //GAMMA_SAFE_MALLOC_H
