/** @file
 * Source file for queue data structure implementation
 * @author Gevorg Chobanyan
 * @date 25.05.2020
 */
#include "queue.h"
#include "safe_malloc.h"
#include <stdlib.h>

/** @brief Prepend new doubly link list node
 * Make a new doubly link list node and prepend it from left to an existing
 * node
 * @param [in] c - Cell for new node
 * @param [in, out] right_node - New node's right neighbor
 * @return Pointer to a newly allocated memory for the node or @p NULL if
 * problems with memory allocation have occurred
 */
static queue_node_t* prepend_new_node(cell_t c, queue_node_t* right_node) {
	queue_node_t* n = malloc(sizeof(queue_node_t));
	if(n == NULL) return NULL;
	n->cell = c;
	n->right = right_node;
	n->left = NULL;
	if(right_node != NULL) right_node->left = n;
	return n;
}
queue_t* q_new() {
	queue_t* q = malloc(sizeof(queue_t));
	if(q == NULL) return NULL;
	q->first = q->last = NULL;
	return q;
}

void q_free(queue_t* q) {
	if(q == NULL) return;
	q->last = NULL;
	queue_node_t* l = q->first;
	queue_node_t* del;
	q->first = NULL;

	while(l != NULL) {
		del = l;
		l = l->right;
		if(l != NULL) l->left = NULL;
		safe_free(del);
	}
	safe_free(q);
}

bool q_enqueue(queue_t* q, cell_t c) {
	if(q == NULL) return false;

	queue_node_t* new = prepend_new_node(c, q->first);
	if(new == NULL) return false;

	q->first = new;

	if(q->last == NULL)
		q->last = new;

	return true;
}

cell_t q_dequeue(queue_t* q) {
	if(q == NULL || q->last == NULL) {
		cell_t c = {0, 0};
		return c;
	}

	cell_t c = q->last->cell;
	queue_node_t* del = q->last;
	q->last = q->last->left;

	if(q->last == NULL)
		q->first = NULL;
	else
		q->last->right = NULL;

	del = safe_free(del);

	return c;
}

bool q_empty(queue_t* q) {
	return q == NULL || q->last == NULL;
}
