/** @file
 * Header file for queue data structure implementation
 * @author Gevorg Chobanyan
 * @date 25.05.2020
 */
#ifndef GAMMA_QUEUE_H
#define GAMMA_QUEUE_H
#include <stdint.h>
#include <stdbool.h>

/** @brief Structure for a cell
 */
typedef struct cell {
	uint32_t x; ///< X coordinate
	uint32_t y; ///< Y coordinate
} cell_t;

/** @brief Structure for a queue node
 */
typedef struct queue_node {
	cell_t cell;              ///< Cell data
	struct queue_node* right; ///< Pointer to right node
	struct queue_node* left;  ///< Pointer to left node
} queue_node_t;

/** @brief Structure for queue
 */
typedef struct queue {
	queue_node_t* first; ///< Pointer to the first item from left
	queue_node_t* last;  ///< Pointer to the last item from right
} queue_t;

/** @brief Make a new queue
 * @return Pointer to a newly allocated memory for queue or
 * @p NULL if problems with memory allocation have occurred
 */
queue_t* q_new();

/** @brief Free the queue
 * @param [in] q - Queue to be freed
 */
void q_free(queue_t* q);

/** @brief Enqueue an item to  the queue
 * @param [in, out] q - Queue
 * @param [in] c - Cell
 * @return @p true if enqueue operation was successful, @p false
 * otherwise
 */
bool q_enqueue(queue_t* q, cell_t c);

/** @brief Dequeue an item to  the queue
 * @param [in, out] q - Queue
 * @return Removed cell
 */
cell_t q_dequeue(queue_t* q);

/** @brief Enqueue an item to  the queue
 * @param [in, out] q - Queue
 * @return @p true if queue is empty, @p false otherwise
 */
bool q_empty(queue_t* q);

#endif //GAMMA_QUEUE_H
