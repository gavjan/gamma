/** @file
 * Source file for Union Find Data Structure function implementations
 * @author Gevorg Chobanyan
 * @date 18.03.2020
 */
#include "ufind.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
/** @brief Structure storing a Union Find node
 */
struct unode {
	struct unode* parent;  ///< parent of this node
	uint32_t player;         ///< player to which this node belongs
	uint16_t depth;          ///< depth for current node. 1 on creation
	bool visited;            ///< flag for visiting the current node
};
struct unode* new_unode(uint32_t player) {
	struct unode* p;
	if((p = calloc(sizeof(struct unode), 1)) == NULL)
		return NULL;
	p->player = player;
	p->parent = NULL;
	p->depth = 1;
	p->visited = false;
	return p;
}
struct unode* ufind(struct unode* element) {
	if(element == NULL) return NULL;
	struct unode* original_element = element;
	while(element->parent != NULL)
		element = element->parent;
	if(element != original_element->parent && element != original_element)
		original_element->parent = element;
	return element;
}
bool ujoin(struct unode* a, struct unode* b) {
	if(a == NULL || b == NULL) return false;
	struct unode* root_a = ufind(a);
	struct unode* root_b = ufind(b);
	if(root_a != root_b) {
		if(root_a->depth > root_b->depth)
			root_b->parent = root_a;
		else if(root_a->depth < root_b->depth)
			root_a->parent = root_b;
		else {
			root_a->parent = root_b;
			root_b->depth++;
		}
	}
	return root_a != root_b;
}
void set_parent(struct unode* element, struct unode* parent) {
	element->parent = parent;
}
uint32_t get_player(struct unode* element) {
	return element->player;
}
void set_depth(struct unode* element, uint16_t depth) {
	element->depth = depth;
}
void set_visited(struct unode* element, bool visited) {
	element->visited = visited;
}
bool get_visited(struct unode* element) {
	return element->visited;
}
