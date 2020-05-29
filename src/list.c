/** @file
 * Source file for List storing drawn players
 * @author Gevorg Chobanyan
 * @date 25.05.2020
 */
#include "list.h"
#include "safe_malloc.h"
#include <stdlib.h>
/** @brief Get a linked list new node
 * Allocate memory for a linked list
 * @return pointer to manually allocated memory for the node
 */
list_t* new_node() {
	list_t* l = malloc(sizeof(list_t));
	l->next = NULL;
	return l;
}
void list_free(list_t** head) {
	if(head == NULL) return;
	list_t* l = *head, * del;
	*head = NULL;
	while(l != NULL) {
		del = l;
		l = l->next;
		safe_free(del);
	}
}
bool list_insert(list_t** l, uint32_t data) {
	list_t* new = new_node();
	if(new == NULL) return false;
	new->data = data;
	new->next = *l;
	*l = new;
	return true;
}