#include <assert.h>
#include <stdlib.h>
#include "list.h"

struct node {
    int data;
    Node *prev;
    Node *next;
};

struct list {
    Node *head;
    Node *tail;
};

static Node * node_new(int data)
{
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return node;
    }
    
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    
    return node;
}

List * list_new()
{
    List *lt = malloc(sizeof(List));
    if (lt == NULL) {
        return lt;
    }
    
    lt->head = NULL;
    lt->tail = NULL;
    
    return lt;
}

bool list_is_empty(List *self)
{
    assert(self != NULL);
    return self->head == NULL;
}

int list_peek_front(List *self)
{
    assert(!list_is_empty(self));
    return self->head->data;
}

int list_peek_rear(List *self)
{
    assert(!list_is_empty(self));
    return self->tail->data;
}

bool list_unshift(List *self, int value)
{
    assert(self != NULL);
    
    Node *node = node_new(value);
    if (node == NULL) {
        return false;
    }
    
    if (self->head == NULL) {
        self->head = node;
        self->tail = node;
        return true;
    }
    
    node->next = self->head;
    self->head->prev = node;
    self->head = node;
    
    return true;
}

bool list_push(List *self, int value)
{
    assert(self != NULL);
    
    Node *node = node_new(value);
    if (node == NULL) {
        return false;
    }
    
    if (self->tail == NULL) {
        self->head = node;
        self->tail = node;
        return true;
    }
    
    self->tail->next = node;
    node->prev = self->tail;
    self->tail = node;
    
    return true;
}

int list_shift(List *self)
{
    assert(!list_is_empty(self));
    
    if (self->head == self->tail) {
        int popped = self->head->data;
        
        free(self->head);
        self->head = NULL;
        self->tail = NULL;
        
        return popped;
    }
    
    Node *curr = self->head;
    int popped = curr->data;
    
    self->head = curr->next;
    free(curr);
    self->head->prev = NULL;
    
    return popped;
}

void list_free(void *self)
{
    if (self == NULL) {
        return;
    }
    
    Node *curr = ((List *) self)->head;
    Node *temp;
    while (curr != NULL) {
        temp = curr;
        curr = curr->next;
        free(temp);
    }
    
    free(self);
}