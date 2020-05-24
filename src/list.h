/** @file
 * Header file for List storing drawed players
 *
 * @author Gevorg Chobanyan
 * @date 25.05.2020
 */
#ifndef GAMMA_LIST_H
#define GAMMA_LIST_H
#include <stdint.h>
#include <stdbool.h>

typedef struct list {
		uint32_t data;
		struct list* next;
} list_t;

void list_free(list_t** l);

bool list_insert(list_t** l, uint32_t data);

#endif //GAMMA_LIST_H
