#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct node Node;
typedef Node * ListIter;
typedef struct list List;

typedef bool (*filterFn) (int);
typedef bool (*predicateFn) (int, int);
typedef int (*mapFn) (int);

// Constructor.
List * list_new();
List * list_init(size_t size, int value, ...);
// Destructor.
void list_free(void *self);

bool list_is_empty(List *self);
int list_peek_front(List *self);
int list_peek_rear(List *self);
bool list_unshift(List *self, int value);
bool list_push(List *self, int value);
int list_shift(List *self);
int list_pop(List *self);

// Insertion in ordered list.
bool list_insert_when(List *self, int value, predicateFn filter);

// Iterator
ListIter list_start(List *self);
ListIter list_next(ListIter iter);
bool list_end(ListIter iter);

// Higher-order function w/ side effects.
bool list_any(List *self, filterFn filter);
bool list_all(List *self, filterFn filter);
bool list_map(List **self, mapFn mapper);

int node_value(ListIter iter);

#endif // LIST_H
