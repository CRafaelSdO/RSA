#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

typedef struct _node node_t;

node_t *new_node(void *);

void destroy_node(node_t **, void (void *));

void *item(node_t *);

void set_item(node_t *, void *);

node_t *next(node_t *);

void set_next(node_t *, node_t *);

#endif