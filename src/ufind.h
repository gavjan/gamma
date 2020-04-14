#ifndef GAMMA_UFIND_H
#define GAMMA_UFIND_H
#include <stdbool.h>
#include <stdint.h>

// Union node
typedef struct unode_t {
		struct unode_t* parent;
		uint32_t player;
		uint16_t depth;
		bool visited;
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

#endif //GAMMA_UFIND_H
