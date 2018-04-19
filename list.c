#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
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

int node_value(Node *self)
{
    assert(self != NULL);
    
    return self->data;
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

List * list_init(size_t size, int value, ...)
{
    List *lt = malloc(sizeof(List));
    if (lt == NULL) {
        return lt;
    }
    
    Node *first = node_new(value);
    if (first == NULL) {
        list_free(lt);
        lt = NULL;
        return lt;
    }
    lt->head = first;
    lt->tail = first;
    
    va_list args;
    va_start(args, value);

    Node *temp;
    for (size_t i = 1; i < size; i++) {
        temp = node_new(va_arg(args, int));
        if (temp == NULL) {
            list_free(lt);
            lt = NULL;
            return lt;
        }
        
        lt->tail->next = temp;
        temp->prev = lt->tail;
        lt->tail = temp;
    }
    
    va_end(args);
    
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

bool list_insert_when(List *self, int value, predicateFn filter)
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
    
    Node *p = NULL;
    Node *q = self->head;
    while (q->next != NULL) {
        if (filter(value, q->data)) {
            if (p == NULL) {
                node->next = q;
                q->prev = node;
                q = node;
                self->head = q;
            } else {
                p->next = node;
                node->prev = p;
                
                q->prev = node;
                node->next = q;
            }
            
            break;
        }
        
        p = q;
        q = q->next;
    }
    
    if (q == self->tail) {
        q->next = node;
        node->prev = q;
        q = node;
        self->tail = q;
    }
    
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

int list_pop(List *self)
{
    assert(!list_is_empty(self));
    
    if (self->head == self->tail)
    {
        int popped = self->tail->data;
        
        free(self->tail);
        self->head = NULL;
        self->tail = NULL;
        
        return popped;
    }
    
    Node *curr = self->tail;
    int popped = curr->data;
    
    self->tail = curr->prev;
    free(curr);
    self->tail->next = NULL;
    
    return popped;
}

Node * list_start(List *self)
{
    assert(self != NULL);
    
    // Init an iterator.
    Node *iter = self->head;
    
    return iter;
}

Node * list_next(Node *self)
{
    if (self == NULL) {
        return NULL;
    }
    
    self = self->next;
    
    return self;
}

bool list_end(Node *self)
{
    return self == NULL;
}

bool list_any(List *self, filterFn filter)
{
    assert(self != NULL);
    
    Node *curr = self->head;
    
    if (curr == NULL) {
        return false;
    }
    
    while (curr != NULL) {
        if (filter(curr->data)) {
            return true;
        }
        
        curr = curr->next;
    }
    
    return false;
}

bool list_all(List *self, filterFn filter)
{
    assert(self != NULL);
    
    Node *curr = self->head;
    
    if (curr == NULL) {
        return false;
    }
    
    while (curr != NULL) {
        if (!filter(curr->data)) {
            return false;
        }
        
        curr = curr->next;
    }
    
    return true;
}

List * list_map(List *self, mapFn mapper)
{
    assert(self != NULL);
    
    List *result = list_new();
    if (result == NULL) {
        return result;
    }
    
    Node *p = self->head;
    while (p != NULL) {
        if (!list_push(result, mapper(p->data))) {
            list_free(result);
            result = NULL;
            return result;
        }
        
        p = p->next;
    }
    
    return result;
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