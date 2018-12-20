#include <stdio.h>
#include "list.h"

bool test_list_is_empty(void)
{
    bool failed = false;

    List *lt = list_new();
    if (lt == NULL) {
        perror("Failed to allocate List lt");
        return false;
    }

    if (!list_is_empty(lt)) {
        failed = true;
        goto LIST_FREE;
    }

LIST_FREE:
    list_free(lt);

    if (failed) {
        return false;
    }

    return true;
}

bool test_list_unshift(void)
{
    bool failed = false;

    List *lt = list_new();
    if (lt == NULL) {
        perror("Failed to allocate List lt");
        return false;
    }

    // List: 9 -> NULL
    if (!list_unshift(lt, 9)) {
        failed = true;
        goto LIST_FREE;
    }

    if (list_peek_front(lt) != 9) {
        failed = true;
        goto LIST_FREE;
    }

    if (list_peek_rear(lt) != 9) {
        failed = true;
        goto LIST_FREE;
    }

    if (list_is_empty(lt)) {
        failed = true;
        goto LIST_FREE;
    }

    // List: 4 -> 9 -> NULL
    if (!list_unshift(lt, 4)) {
        failed = true;
        goto LIST_FREE;
    }

    if (list_peek_front(lt) != 4) {
        failed = true;
        goto LIST_FREE;
    }

    if (list_peek_rear(lt) != 9) {
        failed = true;
        goto LIST_FREE;
    }

LIST_FREE:
    list_free(lt);

    if (failed) {
        return false;
    }

    return true;
}

// Nested function, available in GCC.
static bool is_smaller(int a, int b)
{
    return a < b;
}

bool test_list_insert_when(void)
{
    bool failed = false;

    List *lt = list_new();
    if (lt == NULL) {
        perror("Failed to allocate List lt");
        return false;
    }

    // List: 2 -> NULL
    if (!list_insert_when(lt, 2, is_smaller)) {
        failed = true;
        goto LIST_FREE;
    }

    // List: 2 -> 3 -> NULL
    if (!list_insert_when(lt, 3, is_smaller)) {
        failed = true;
        goto LIST_FREE;
    }

    // List: 1 -> 2 -> 3 -> NULL
    if (!list_insert_when(lt, 1, is_smaller)) {
        failed = true;
        goto LIST_FREE;
    }

    if (list_shift(lt) != 1) {
        failed = true;
        goto LIST_FREE;
    }

    if (list_shift(lt) != 2) {
        failed = true;
        goto LIST_FREE;
    }

    if (list_shift(lt) != 3) {
        failed = true;
        goto LIST_FREE;
    }


    if (!list_is_empty(lt)) {
        failed = true;
        goto LIST_FREE;
    }

LIST_FREE:
    list_free(lt);

    if (failed) {
        return false;
    }

    return true;
}

bool test_list_push(void)
{
    bool failed = false;

    List *lt = list_new();
    if (lt == NULL) {
        perror("Failed to allocate List lt");
        return false;
    }

    // List: 9 -> NULL
    if (!list_push(lt, 9)) {
        failed = true;
        goto LIST_FREE;
    }

    if (list_peek_front(lt) != 9) {
        failed = true;
        goto LIST_FREE;
    }

    if (list_peek_rear(lt) != 9) {
        failed = true;
        goto LIST_FREE;
    }

    // List: 9 -> 5 -> NULL
    if (!list_push(lt, 5)) {
        failed = true;
        goto LIST_FREE;
    }

    if (list_peek_front(lt) != 9) {
        failed = true;
        goto LIST_FREE;
    }

    if (list_peek_rear(lt) != 5) {
        failed = true;
        goto LIST_FREE;
    }

LIST_FREE:
    list_free(lt);

    if (failed) {
        return false;
    }

    return true;
}

bool test_list_shift(void)
{
    bool failed = false;

    List *lt = list_new();
    if (lt == NULL) {
        perror("Failed to allocate List lt");
        return false;
    }

    // List: 9 -> NULL
    if (!list_unshift(lt, 9)) {
        failed = true;
        goto LIST_FREE;
    }

    // List: 4 -> 9 -> NULL
    if (!list_unshift(lt, 4)) {
        failed = true;
        goto LIST_FREE;
    }

    // List: 4 -> 9 -> 5 -> NULL
    if (!list_push(lt, 5)) {
        failed = true;
        goto LIST_FREE;
    }

    // List: 9 -> 5 -> NULL
    if (list_shift(lt) != 4) {
        failed = true;
        goto LIST_FREE;
    }

    // List: 5 -> NULL
    if (list_shift(lt) != 9) {
        failed = true;
        goto LIST_FREE;
    }

    // List: NULL
    if (list_shift(lt) != 5) {
        failed = true;
        goto LIST_FREE;
    }

    if (!list_is_empty(lt)) {
        failed = true;
        goto LIST_FREE;
    }

LIST_FREE:
    list_free(lt);

    if (failed) {
        return false;
    }

    return true;
}

bool test_list_pop(void)
{
    bool failed = false;

    List *lt = list_init(3, 4, 9, 5);
    if (lt == NULL) {
        perror("Failed to allocate List lt");
        return false;
    }

    if (list_pop(lt) != 5) {
        failed = true;
        goto LIST_FREE;
    }

    if (list_pop(lt) != 9) {
        failed = true;
        goto LIST_FREE;
    }

    if (list_pop(lt) != 4) {
        failed = true;
        goto LIST_FREE;
    }

    if (!list_is_empty(lt)) {
        failed = true;
        goto LIST_FREE;
    }

LIST_FREE:
    list_free(lt);

    if (failed) {
        return false;
    }

    return true;
}
