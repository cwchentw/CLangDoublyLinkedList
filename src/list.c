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
    size_t size;
};

static Node * node_new(int data)
{
    Node *node = malloc(sizeof(Node));
    if (!node) {
        return node;
    }

    node->data = data;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

int node_value(Node *self)
{
    assert(self);

    return self->data;
}

List * list_new()
{
    List *lt = malloc(sizeof(List));
    if (!lt) {
        return lt;
    }

    lt->head = NULL;
    lt->tail = NULL;
    lt->size = 0;

    return lt;
}

List * list_init(size_t size, int value, ...)
{
    List *lt = malloc(sizeof(List));
    if (!lt) {
        return lt;
    }

    Node *first = node_new(value);
    if (!first) {
        list_free(lt);
        lt = NULL;
        return lt;
    }
    lt->head = first;
    lt->tail = first;
    lt->size = 0;

    va_list args;
    va_start(args, value);
    lt->size++;

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

        lt->size++;
    }

    va_end(args);

    return lt;
}

bool list_is_empty(List *self)
{
    assert(self);

    return self->head == NULL;
}

size_t list_size(List *self)
{
    assert(self);

    return self->size;
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

bool list_at(List *self, size_t index, int *out)
{
    assert(self);
    assert(index < list_size(self));

    Node* curr = self->head;
    size_t i = 0;
    while (curr) {
        if (i == index) {
            *out = curr->data;
            return true;
        }

        curr = curr->next;
        i++;
    }

    return false;
}

bool list_set_at(List *self, size_t index, int data)
{
    assert(self);
    assert(index < list_size(self));

    Node* curr = self->head;
    size_t i = 0;
    while (curr) {
        if (i == index) {
            curr->data = data;
            return true;
        }

        curr = curr->next;
        i++;
    }

    return false;
}

bool list_push(List *self, int value)
{
    assert(self);

    Node *node = node_new(value);
    if (!node) {
        return false;
    }

    if (!(self->tail)) {
        self->head = node;
        self->tail = node;
    }
    else {
        self->tail->next = node;
        node->prev = self->tail;
        self->tail = node;
    }

    self->size++;

    return true;
}

bool list_unshift(List *self, int value)
{
    assert(self);

    Node *node = node_new(value);
    if (!node) {
        return false;
    }

    if (!(self->head)) {
        self->head = node;
        self->tail = node;
    }
    else {
        node->next = self->head;
        self->head->prev = node;
        self->head = node;
    }

    self->size++;

    return true;
}

bool list_insert_at(List *self, size_t index, int value)
{
    assert(self);

    if (!(self->head)) {
        assert(index == 0);
    } else {
        assert(index <= self->size);
    }

    Node *node = node_new(value);
    if (!node) {
        return false;
    }

    if (!(self->head)) {
        self->head = node;
        self->tail = node;
        self->size++;
        return true;
    }

    Node *p = NULL;
    Node *q = self->head;
    size_t i = 0;
    while(q->next) {
        if (i == index) {
            if (!p) {
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
        i++;
    }

    if (q == self->tail) {
        q->next = node;
        node->prev = q;
        q = node;
        self->tail = q;
    }

    self->size++;

    return true;
}

bool list_insert_when(List *self, int value, predicateFn filter)
{
    assert(self);

    Node *node = node_new(value);
    if (!node) {
        return false;
    }

    if (!(self->head)) {
        self->head = node;
        self->tail = node;

        self->size++;

        return true;
    }

    Node *p = NULL;
    Node *q = self->head;
    while (q->next) {
        if (filter(value, q->data)) {
            if (!p) {
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

    self->size++;

    return true;
}

int list_shift(List *self)
{
    assert(!list_is_empty(self));

    int popped = self->head->data;

    if (self->head == self->tail) {
        free(self->head);
        self->head = NULL;
        self->tail = NULL;
    }
    else {
        Node *curr = self->head;
        self->head = curr->next;
        free(curr);
        self->head->prev = NULL;
    }

    self->size--;

    return popped;
}

int list_pop(List *self)
{
    assert(!list_is_empty(self));

    int popped = self->tail->data;

    if (self->head == self->tail) {
        free(self->tail);
        self->head = NULL;
        self->tail = NULL;
    }
    else {
        Node *curr = self->tail;
        self->tail = curr->prev;
        free(curr);
        self->tail->next = NULL;
    }

    self->size--;

    return popped;
}

int list_remove_at(List *self, size_t index)
{
    assert(!list_is_empty(self));

    if (list_size(self) == 1) {
        assert(index == 0);
    }
    else {
        assert(index < list_size(self));
    }

    if (list_size(self) == 1) {
        int result = self->head->data;

        free(self->head);
        self->head = NULL;
        self->tail = NULL;
        self->size--;

        return result;
    }

    int result;

    Node *p = NULL;
    Node *q = self->head;
    size_t i = 0;
    while (q->next) {
        if (i == index) {
            result = q->data;

            if (!p) {
                self->head = q->next;
                free(q);
                self->head->prev = NULL;
            }
            else {
                p->next = q->next;
                q->next->prev = p;
                free(q);
            }

            break;
        }

        p = q;
        q = q->next;
        i++;
    }

    if (q == self->tail) {
        result = q->data;
        self->tail = p;
        free(q);
        self->tail->next = NULL;
    }

    self->size--;

    return result;
}

Node * list_start(List *self)
{
    assert(self);

    // Init an iterator.
    Node *iter = self->head;

    return iter;
}

Node * list_next(Node *self)
{
    if (!self) {
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
    assert(self);

    Node *curr = self->head;

    if (!curr) {
        return false;
    }

    while (curr) {
        if (filter(curr->data)) {
            return true;
        }

        curr = curr->next;
    }

    return false;
}

bool list_all(List *self, filterFn filter)
{
    assert(self);

    Node *curr = self->head;

    if (!curr) {
        return false;
    }

    while (curr) {
        if (!filter(curr->data)) {
            return false;
        }

        curr = curr->next;
    }

    return true;
}

bool list_find(List *self, filterFn filter, size_t *out)
{
    assert(!list_is_empty(self));

    Node *curr = self->head;
    size_t i = 0;
    while (curr) {
        if (filter(curr->data)) {
            *out = i;
            return true;
        }

        curr = curr->next;
        i++;
    }

    *out = 0;
    return false;
}

bool list_select_mut(List **self, filterFn filter)
{
    assert(*self);

    List *out = list_new();
    if (!out) {
        return false;
    }

    Node *curr = (*self)->head;
    while (curr) {
        if (filter(curr->data)) {
            if (!list_push(out, curr->data)) {
                list_free(out);

                return false;
            }
        }

        curr = curr->next;
    }

    list_free(*self);
    *self = out;

    return true;
}

bool list_map_mut(List **self, mapFn mapper)
{
    assert(*self);

    List *result = list_new();
    if (!result) {
        return false;
    }

    Node *p = (*self)->head;
    while (p) {
        if (!list_push(result, mapper(p->data))) {
            list_free(result);
            result = NULL;
            return false;
        }

        p = p->next;
    }

    list_free(*self);
    *self = result;

    return true;
}

int list_reduce(List *self, reduceFn reducer)
{
    assert(!list_is_empty(self));

    Node *curr = self->head;
    int a = curr->data;
    curr = curr->next;

    while (curr) {
        a = reducer(a, curr->data);

        curr = curr->next;
    }

    return a;
}

void list_free(void *self)
{
    if (!self) {
        return;
    }

    Node *curr = ((List *) self)->head;
    Node *temp;
    while (curr) {
        temp = curr;
        curr = curr->next;
        free(temp);
    }

    free(self);
}
