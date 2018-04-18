#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct node Node;
typedef struct list List;

List * list_new();
List * list_init(size_t size, int value, ...);
bool list_is_empty(List *self);
int list_peek_front(List *self);
int list_peek_rear(List *self);
bool list_unshift(List *self, int value);
bool list_push(List *self, int value);
int list_shift(List *self);
void list_free(void *self);

Node * list_start(List *self);
Node * list_next(Node *self);
bool list_end(Node *self);

int node_value(Node *self);

#endif // LIST_H