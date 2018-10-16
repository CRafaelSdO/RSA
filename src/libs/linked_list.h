#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

typedef struct _linked_list linked_list_t;
typedef long long int S64_t;

linked_list_t *new_list();

void destroy_list(linked_list_t **, void (void **));

void insert(void *, S64_t, linked_list_t *);

S64_t get_index_of_item(void *, linked_list_t *, bool (void *, void *));

void *get_item_of_index(S64_t, linked_list_t *);

void *remove_by_item(void *, linked_list_t *, bool (void *, void *));

void *remove_by_index(S64_t, linked_list_t *);

S64_t length(linked_list_t *);

bool is_empty(linked_list_t *);

#endif