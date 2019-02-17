#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include "list.h"

struct node {
    int data;
    node_t *prev;
    node_t *next;
};

struct list {
    node_t *head;
    node_t *tail;
    size_t size;
};

static node_t * node_new(int data)
{
    node_t *node = malloc(sizeof(node_t));
    if (!node)
        return node;

    node->data = data;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

int node_value(node_t *self)
{
    assert(self);

    return self->data;
}

list_t * list_new(void)
{
    list_t *lt = malloc(sizeof(list_t));
    if (!lt)
        return lt;

    lt->head = NULL;
    lt->tail = NULL;
    lt->size = 0;

    return lt;
}

list_t * list_init(size_t size, int value, ...)
{
    list_t *lt = malloc(sizeof(list_t));
    if (!lt)
        return lt;

    node_t *first = node_new(value);
    if (!first) {
        list_delete(lt);
        lt = NULL;
        return lt;
    }
    lt->head = first;
    lt->tail = first;
    lt->size = 0;

    va_list args;
    va_start(args, value);
    lt->size++;

    node_t *temp;
    for (size_t i = 1; i < size; i++) {
        temp = node_new(va_arg(args, int));
        if (temp == NULL) {
            va_end(args);

            list_delete(lt);
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

void list_delete(void *self)
{
    if (!self)
        return;

    node_t *curr = ((list_t *) self)->head;
    node_t *temp;
    while (curr) {
        temp = curr;
        curr = curr->next;
        free(temp);
    }

    free(self);
}

bool list_is_empty(const list_t *self)
{
    assert(self);

    return self->head == NULL;
}

size_t list_size(const list_t *self)
{
    assert(self);

    return self->size;
}

int list_peek_front(const list_t *self)
{
    assert(!list_is_empty(self));

    return self->head->data;
}

int list_peek_rear(const list_t *self)
{
    assert(!list_is_empty(self));

    return self->tail->data;
}

bool list_at(const list_t *self, size_t index, int *out)
{
    assert(index < list_size(self));

    node_t* curr = self->head;
    size_t i = 0;
    while (curr) {
        if (index == i) {
            *out = curr->data;
            return true;
        }

        curr = curr->next;
        i++;
    }
    
    *out = 0;  // Fake data.

    return false;
}

bool list_contains(const list_t *self, int value, size_t *index)
{
    assert(self);
    
    node_t *curr = self->head;
    size_t i = 0;
    while (curr) {
        if (value == curr->data) {
            *index = i;
            return true;
        }
        
        curr = curr->next;
        i++;
    }
    
    *index = 0;  // Fake data.
    
    return false;
}

bool list_set_at(list_t *self, size_t index, int data)
{
    assert(self);
    assert(index < list_size(self));

    node_t* curr = self->head;
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

bool list_push(list_t *self, int value)
{
    assert(self);

    node_t *node = node_new(value);
    if (!node)
        return false;

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

bool list_unshift(list_t *self, int value)
{
    assert(self);

    node_t *node = node_new(value);
    if (!node)
        return false;

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

bool list_insert_at(list_t *self, size_t index, int value)
{
    assert(self);
    assert(index <= self->size);

    node_t *node = node_new(value);
    if (!node)
        return false;

    if (!(self->head)) {
        self->head = node;
        self->tail = node;
        self->size++;
        return true;
    }

    node_t *p = NULL;
    node_t *q = self->head;
    size_t i = 0;
    while(q->next) {
        if (i == index) {
            if (!p) {
                node->next = self->head;
                self->head->prev = node;
                self->head = node;
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
        self->tail->next = node;
        node->prev = self->tail;
        self->tail = node;
    }

    self->size++;

    return true;
}

bool list_insert_by(list_t *self, int value, predicate_fn predicate)
{
    assert(self);

    node_t *node = node_new(value);
    if (!node)
        return false;

    if (!(self->head)) {
        self->head = node;
        self->tail = node;

        self->size++;

        return true;
    }

    if (self->head == self->tail) {
        if (predicate(value, self->head->data)) {
            node->next = self->head;
            self->head->prev = node;
            self->head = node;
        }
        else {
            self->tail->next = node;
            node->prev = self->tail;
            self->tail = node;
        }

        self->size++;
        return true;
    }

    node_t *p = NULL;
    node_t *q = self->head;
    while (q->next) {
        if (predicate(value, q->data)) {
            if (!p) {
                node->next = self->head;
                self->head->prev = node;
                self->head = node;
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
        self->tail->next = node;
        node->prev = self->tail;
        self->tail = node;
    }

    self->size++;

    return true;
}

int list_shift(list_t *self)
{
    assert(!list_is_empty(self));

    int popped = self->head->data;

    if (self->head == self->tail) {
        free(self->head);
        self->head = NULL;
        self->tail = NULL;
    }
    else {
        node_t *curr = self->head;
        self->head = curr->next;
        free(curr);
        self->head->prev = NULL;
    }

    self->size--;

    return popped;
}

int list_pop(list_t *self)
{
    assert(!list_is_empty(self));

    int popped = self->tail->data;

    if (self->head == self->tail) {
        free(self->tail);
        self->head = NULL;
        self->tail = NULL;
    }
    else {
        node_t *curr = self->tail;
        self->tail = curr->prev;
        free(curr);
        self->tail->next = NULL;
    }

    self->size--;

    return popped;
}

int list_remove_at(list_t *self, size_t index)
{
    assert(!list_is_empty(self));
    assert(index < list_size(self));

    if (list_size(self) == 1) {
        int result = self->head->data;

        free(self->head);
        self->head = NULL;
        self->tail = NULL;
        self->size--;

        return result;
    }

    int result = 0;
    bool visited = false;

    node_t *p = NULL;
    node_t *q = self->head;
    size_t i = 0;
    while (q->next) {
        if (i == index) {
            result = q->data;
            visited = true;

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
        visited = true;
    }

    self->size--;

    if (!visited)
        assert(0 && "Invalid value");

    return result;
}

node_t * list_start(const list_t *self)
{
    assert(self);

    // Init an iterator.
    node_t *iter = self->head;

    return iter;
}

node_t * list_next(node_t *self)
{
    if (!self)
        return NULL;

    self = self->next;

    return self;
}

bool list_end(node_t *self)
{
    return self == NULL;
}

bool list_any(const list_t *self, filter_fn filter)
{
    assert(self);

    node_t *curr = self->head;

    if (!curr)
        return false;

    while (curr) {
        if (filter(curr->data))
            return true;

        curr = curr->next;
    }

    return false;
}

bool list_all(const list_t *self, filter_fn filter)
{
    assert(self);

    node_t *curr = self->head;

    if (!curr)
        return false;

    while (curr) {
        if (!filter(curr->data))
            return false;

        curr = curr->next;
    }

    return true;
}

bool list_find(const list_t *self, filter_fn filter, size_t *out)
{
    assert(!list_is_empty(self));

    node_t *curr = self->head;
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

list_t * list_sort(const list_t *self, predicate_fn filter)
{
    assert(self);

    if (list_is_empty(self))
        return NULL;

    list_t *out = list_new();
    if (!out)
        return out;

    node_t *curr = self->head;
    list_push(out, curr->data);
    curr = curr->next;

    while (curr) {
        list_insert_by(out, curr->data, filter);

        curr = curr->next;
    }

    return out;
}

bool list_select_mut(list_t **self, filter_fn filter)
{
    assert(*self);

    list_t *out = list_new();
    if (!out)
        return false;

    node_t *curr = (*self)->head;
    while (curr) {
        if (filter(curr->data)) {
            if (!list_push(out, curr->data)) {
                list_delete(out);

                return false;
            }
        }

        curr = curr->next;
    }

    list_delete(*self);
    *self = out;

    return true;
}

bool list_map_mut(list_t **self, map_fn mapper)
{
    assert(*self);

    list_t *result = list_new();
    if (!result)
        return false;

    node_t *p = (*self)->head;
    while (p) {
        if (!list_push(result, mapper(p->data))) {
            list_delete(result);
            result = NULL;
            return false;
        }

        p = p->next;
    }

    list_delete(*self);
    *self = result;

    return true;
}

int list_reduce(const list_t *self, reduce_fn reducer)
{
    assert(!list_is_empty(self));

    node_t *curr = self->head;
    int a = curr->data;
    curr = curr->next;

    while (curr) {
        a = reducer(a, curr->data);

        curr = curr->next;
    }

    return a;
}
