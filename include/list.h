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
typedef int (*reduceFn) (int, int);

// Constructor.
List * list_new();
List * list_init(size_t size, int value, ...);

// Destructor.
void list_free(void *self);

// List state.
bool list_is_empty(List *self);
size_t list_size(List *self);

// Getters.
int list_peek_front(List *self);
int list_peek_rear(List *self);
bool list_at(List *self, size_t index, int *out);

// Setters.
bool list_set_at(List *self, size_t index, int data);

// List manipulation.
bool list_unshift(List *self, int value);
bool list_push(List *self, int value);
int list_shift(List *self);
int list_pop(List *self);
bool list_insert_at(List *self, size_t index, int value);
int list_remove_at(List *self, size_t index);

// Insertion in ordered list.
bool list_insert_by(List *self, int value, predicateFn predicate);

// Iterator
ListIter list_start(List *self);
ListIter list_next(ListIter iter);
bool list_end(ListIter iter);

// Higher-order function w/ side effects.
bool list_any(List *self, filterFn filter);
bool list_all(List *self, filterFn filter);
bool list_find(List *self, filterFn filter, size_t *out);
List * list_sort(List *self, predicateFn predicate);
bool list_select_mut(List **self, filterFn filter);
bool list_map_mut(List **self, mapFn mapper);
int list_reduce(List *self, reduceFn reducer);

int node_value(ListIter iter);

#endif // LIST_H
