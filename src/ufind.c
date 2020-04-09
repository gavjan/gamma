#include "ufind.h"
#include <stdlib.h>
unode_t* new_unode(uint32_t player) {
	unode_t* p;
	if((p=(unode_t*)malloc(sizeof(unode_t)))==NULL)
		return NULL;
	p->player=player;
	p->parent=NULL;
	p->depth=1;
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
bool free_unode(unode_t* element, ulist_t** l) {
	if(element==NULL)
		return true;
	if(element->depth==1)
		free(element);
	else if(!prepend_unode(element, l))
		return false;
	return true;
}
bool prepend_unode(unode_t* p, ulist_t** head) {
	ulist_t* new;
	new=(ulist_t*)malloc(sizeof(ulist_t));
	if(new==NULL) return false;
	new->u=p;
	new->next=*head;
	*head=new;
	return true;
}
void free_ulist(ulist_t* head) {
	ulist_t* tmp;
	unode_t* u;
	while(head!=NULL) {
		tmp=head;
		head=head->next;
		u=tmp->u;
		tmp->u=NULL;
		free(u);
		free(tmp);
	}
}
