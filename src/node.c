#include "libs/node.h"

struct _node {
	void *itm;
	node_t *nxt;
};

node_t *new_node(void *itm) {
	node_t *nw = (node_t *) calloc(1, sizeof(node_t));
	nw->itm = itm;
	nw->nxt = NULL;
	return nw;
}

void destroy_node(node_t **nd, void (*destroy_item)(void *)) {
	if((*nd) != NULL) {
		destroy_node(&(*nd)->nxt, destroy_item);
		if(destroy_item != NULL) {
			destroy_item((*nd)->itm);
		}
		free((*nd));
		(*nd) = NULL;
	}
}

void *item(node_t *nd) {
	if(nd != NULL) {
		return nd->itm;
	} else {
		return NULL;
	}
}

void set_item(node_t *nd, void *itm) {
	if(nd != NULL) {
		nd->itm = itm;
	}
}

node_t *next(node_t *nd) {
	if(nd != NULL) {
		return nd->nxt;
	} else {
		return NULL;
	}
}

void set_next(node_t *nd, node_t *nxt) {
	if(nd != NULL) {
		nd->nxt = nxt;
	}
}