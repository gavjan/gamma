/** @file
 * Header file for List storing drawn players
 * @author Gevorg Chobanyan
 * @date 25.05.2020
 */
#ifndef GAMMA_LIST_H
#define GAMMA_LIST_H
#include <stdint.h>
#include <stdbool.h>

/** @brief Constant for indicating lack of available memory
 */
#define NO_MEM 0

/** @brief Structure for a linked list
 */
typedef struct list {
	uint32_t data;     ///< Stored Data
	struct list* next; ///< Pointer to the next node
} list_t;

/** @brief Free the linked list
 * Free all of the manually allocated memory for all of
 * the linked list's nodes
 * @param [in] l - Linked list's head
 */
void list_free(list_t** l);

/** @brief Free the linked list
 * @param [in] l - Linked list's head
 * @param [in] data - Data to be stored
 * @return @p true if the insertion succeeded and @p false otherwise
 */
bool list_insert(list_t** l, uint32_t data);

#endif //GAMMA_LIST_H
