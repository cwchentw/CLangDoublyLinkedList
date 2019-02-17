#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct node node_t;
typedef node_t * list_iter_t;
typedef struct list list_t;

typedef bool (*filter_fn) (int);
typedef bool (*predicate_fn) (int, int);
typedef int (*map_fn) (int);
typedef int (*reduce_fn) (int, int);

// Constructor.
list_t * list_new(void);
list_t * list_init(size_t size, int value, ...);

// Destructor.
void list_delete(void *self);

// list_t state.
bool list_is_empty(const list_t *self);
size_t list_size(const list_t *self);

// Getters.
int list_peek_front(const list_t *self);
int list_peek_rear(const list_t *self);
bool list_at(const list_t *self, size_t index, int *out);
bool list_contains(const list_t *self, int value, size_t *index);

// Setters.
bool list_set_at(list_t *self, size_t index, int data);

// list_t manipulation.
bool list_unshift(list_t *self, int value);
bool list_push(list_t *self, int value);
int list_shift(list_t *self);
int list_pop(list_t *self);
bool list_insert_at(list_t *self, size_t index, int value);
int list_remove_at(list_t *self, size_t index);

// Insertion in ordered list.
bool list_insert_by(list_t *self, int value, predicate_fn predicate);

// Iterator
list_iter_t list_start(const list_t *self);
list_iter_t list_next(list_iter_t iter);
bool list_end(list_iter_t iter);

// Higher-order function w/ side effects.
bool list_any(const list_t *self, filter_fn filter);
bool list_all(const list_t *self, filter_fn filter);
bool list_find(const list_t *self, filter_fn filter, size_t *out);
list_t * list_sort(const list_t *self, predicate_fn predicate);
bool list_select_mut(list_t **self, filter_fn filter);
bool list_map_mut(list_t **self, map_fn mapper);
int list_reduce(const list_t *self, reduce_fn reducer);

int node_value(list_iter_t iter);
