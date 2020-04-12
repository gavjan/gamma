#ifndef GAMMA_UFIND_H
#define GAMMA_UFIND_H
#include <stdbool.h>
#include <stdint.h>

// Union node
typedef struct unode_t {
		struct unode_t* parent;
		uint32_t player;
		uint16_t depth;
} unode_t;

// Linked List with uNodes
typedef struct ulist {
		unode_t* u;
		struct ulist* next;
} ulist_t;

// Returns a new uNode, NULL if no memory is available
unode_t* new_unode(uint32_t player);

// Union find with compression
unode_t* ufind(unode_t* element);

// Merge two unions
bool ujoin(unode_t* a, unode_t* b);

// Free uNode, return false if no memory available, true otherwise
bool free_unode(unode_t* element, ulist_t** l);

// Prepend to a linked list, return false if no memory available, true otherwise
bool prepend_unode(unode_t* p, ulist_t** head);

// Frees a linked list
void free_ulist(ulist_t* head);
#endif //GAMMA_UFIND_H
