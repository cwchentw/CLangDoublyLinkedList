#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct node Node;
typedef struct list List;

typedef bool (*predicateFn) (int, int);
typedef int (*mapFn) (int);

List * list_new();
List * list_init(size_t size, int value, ...);
bool list_is_empty(List *self);
int list_peek_front(List *self);
int list_peek_rear(List *self);
bool list_unshift(List *self, int value);
bool list_insert_when(List *self, int value, predicateFn filter);
bool list_push(List *self, int value);
int list_shift(List *self);
int list_pop(List *self);
void list_free(void *self);

// Iterator
Node * list_start(List *self);
Node * list_next(Node *self);
bool list_end(Node *self);

// Higher-order function w/o side effects.
List * list_map(List *self, mapFn mapper);

int node_value(Node *self);

#endif // LIST_H