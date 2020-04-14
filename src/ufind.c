#include "ufind.h"
#include <stdlib.h>
unode_t* new_unode(uint32_t player) {
	unode_t* p;
	if((p=malloc(sizeof(unode_t)))==NULL)
		return NULL;
	p->player=player;
	p->parent=NULL;
	p->depth=1;
	p->visited=false;
	return p;
}
unode_t* ufind(unode_t* element) {
	if(element==NULL) return NULL;
	unode_t* original_element=element;
	while(element->parent!=NULL)
		element=element->parent;
	if(element!=original_element->parent && element!=original_element)
		original_element->parent=element;
	return element;
}
bool ujoin(unode_t* a, unode_t* b) {
	if(a==NULL || b==NULL) return false;
	unode_t* root_a=ufind(a);
	unode_t* root_b=ufind(b);
	if(root_a!=root_b) {
		if(root_a->depth>root_b->depth)
			root_b->parent=root_a;
		else if(root_a->depth<root_b->depth)
			root_a->parent=root_b;
		else {
			root_a->parent=root_b;
			root_b->depth++;
		}
	}
	return root_a!=root_b;
}
