#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct node Node;
typedef struct list List;

List * list_new();
bool list_is_empty(List *self);
int list_peek_front(List *self);
int list_peek_rear(List *self);
bool list_unshift(List *self, int value);
bool list_push(List *self, int value);
int list_shift(List *self);
void list_free(void *self);

#endif // LIST_H