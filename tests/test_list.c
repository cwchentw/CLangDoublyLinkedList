#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "test_manipulation.h"
#include "test_traversal.h"

#define TEST(test) { \
        if (!(test)) { \
            fprintf(stderr, "%s on %d: Failed on %s", __FILE__, __LINE__, #test); \
            exit(EXIT_FAILURE); \
        } \
    }

int main()
{
    // Test list state.
    TEST(test_list_is_empty());

    // Test list getters.
    TEST(test_list_at());

    // Test list setters.
    TEST(test_list_set_at());

    // Test list manipulation.
    TEST(test_list_unshift());
    TEST(test_list_push());
    TEST(test_list_shift());
    TEST(test_list_insert_by());
    TEST(test_list_pop());
    TEST(test_list_insert_at());
    TEST(test_list_remove_at());

    // Test list traversal.
    TEST(test_list_iter());
    TEST(test_list_any());
    TEST(test_list_all());
    TEST(test_list_find());
    TEST(test_list_select_mut());
    TEST(test_list_map_mut());
    TEST(test_list_reduce());

    return 0;
}

bool test_list_is_empty(void)
{
    bool failed = false;

    list_t *lt = list_new();
    if (lt == NULL) {
        perror("Failed to allocate list_t lt");
        return false;
    }

    if (!list_is_empty(lt)) {
        failed = true;
        goto LIST_FREE;
    }

    if (list_size(lt) != 0) {
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

bool test_list_at(void)
{
    bool failed = false;

    list_t *lt = list_init(3, 3, 4, 5);

    int *out = malloc(sizeof(int));
    if (!(list_at(lt, 0, out) && *out == 3)) {
        failed = true;
        goto LIST_FREE;
    }

    if (!(list_at(lt, 1, out) && *out == 4)) {
        failed = true;
        goto LIST_FREE;
    }

    if (!(list_at(lt, 2, out) && *out == 5)) {
        failed = true;
        goto LIST_FREE;
    }

LIST_FREE:
    free(out);
    list_free(lt);

    if (failed) {
        return false;
    }

    return true;
}

bool test_list_set_at(void)
{
    bool failed = false;

    list_t *lt = list_init(3, 3, 4, 5);

    int *out = malloc(sizeof(int));
    if (!(list_at(lt, 1, out) && *out == 4)) {
        failed = true;
        goto LIST_FREE;
    }

    if (!list_set_at(lt, 1, 99)) {
        failed = true;
        goto LIST_FREE;
    }

    if (!(list_at(lt, 1, out) && *out == 99)) {
        failed = true;
        goto LIST_FREE;
    }

LIST_FREE:
    free(out);
    list_free(lt);

    if (failed) {
        return false;
    }

    return true;
}

bool test_list_unshift(void)
{
    bool failed = false;

    list_t *lt = list_new();
    if (lt == NULL) {
        perror("Failed to allocate list_t lt");
        return false;
    }

    // list_t: 9 -> NULL
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

    // list_t: 4 -> 9 -> NULL
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

    if (list_size(lt) != 2) {
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

bool test_list_insert_by(void)
{
    bool failed = false;

    list_t *lt = list_new();
    if (!lt) {
        perror("Failed to allocate list_t lt");
        return false;
    }

    // list_t: 2 -> NULL
    if (!list_insert_by(lt, 2, is_smaller)) {
        failed = true;
        goto LIST_FREE;
    }

    // list_t: 2 -> 3 -> NULL
    if (!list_insert_by(lt, 3, is_smaller)) {
        failed = true;
        goto LIST_FREE;
    }

    // list_t: 1 -> 2 -> 3 -> NULL
    if (!list_insert_by(lt, 1, is_smaller)) {
        failed = true;
        goto LIST_FREE;
    }

    if (list_size(lt) != 3) {
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

    if (list_size(lt) != 0) {
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

    list_t *lt = list_new();
    if (lt == NULL) {
        perror("Failed to allocate list_t lt");
        return false;
    }

    // list_t: 9 -> NULL
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

    // list_t: 9 -> 5 -> NULL
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

    if (list_size(lt) != 2) {
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

    list_t *lt = list_new();
    if (lt == NULL) {
        perror("Failed to allocate list_t lt");
        return false;
    }

    // list_t: 9 -> NULL
    if (!list_unshift(lt, 9)) {
        failed = true;
        goto LIST_FREE;
    }

    // list_t: 4 -> 9 -> NULL
    if (!list_unshift(lt, 4)) {
        failed = true;
        goto LIST_FREE;
    }

    // list_t: 4 -> 9 -> 5 -> NULL
    if (!list_push(lt, 5)) {
        failed = true;
        goto LIST_FREE;
    }

    if (list_size(lt) != 3) {
        failed = true;
        goto LIST_FREE;
    }

    // list_t: 9 -> 5 -> NULL
    if (list_shift(lt) != 4) {
        failed = true;
        goto LIST_FREE;
    }

    // list_t: 5 -> NULL
    if (list_shift(lt) != 9) {
        failed = true;
        goto LIST_FREE;
    }

    // list_t: NULL
    if (list_shift(lt) != 5) {
        failed = true;
        goto LIST_FREE;
    }

    if (!list_is_empty(lt)) {
        failed = true;
        goto LIST_FREE;
    }

    if (list_size(lt) != 0) {
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

    list_t *lt = list_init(3, 4, 9, 5);
    if (lt == NULL) {
        perror("Failed to allocate list_t lt");
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

    if (list_size(lt) != 0) {
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

bool test_list_insert_at(void)
{
    bool failed = false;
    int *out = malloc(sizeof(int));

    list_t *lt = list_init(2, 3, 4);
    if (!lt) {
        return false;
    }

    if (!list_insert_at(lt, 0, 2)) {
        failed = true;
        goto LIST_FREE;
    }

    if (!(list_at(lt, 0, out) && *out == 2)) {
        failed = true;
        goto LIST_FREE;
    }

    if (!list_insert_at(lt, 3, 5)) {
        failed = true;
        goto LIST_FREE;
    }

    if (!(list_at(lt, 3, out) && *out == 5)) {
        failed = true;
        goto LIST_FREE;
    }

    if (!(list_size(lt) == 4)) {
        failed = true;
        goto LIST_FREE;
    }

    if (!list_insert_at(lt, 2, 99)) {
        failed = true;
        goto LIST_FREE;
    }

    if (!(list_at(lt, 2, out) && *out == 99)) {
        failed = true;
        goto LIST_FREE;
    }

    if (!(list_size(lt) == 5)) {
        failed = true;
        goto LIST_FREE;
    }

LIST_FREE:
    free(out);
    list_free(lt);

    if (failed) {
        return false;
    }

    return true;
}

bool test_list_remove_at()
{
    bool failed = false;

    // 4 -> 5 -> 6 -> 7 -> 8
    list_t *lt = list_init(5, 4, 5, 6, 7, 8);
    if (!lt) {
        perror("Failed to allocate a list\n");
        return false;
    }

    // 5 -> 6 -> 7 -> 8
    int temp = list_remove_at(lt, 0);
    if (!(temp == 4)) {
        fprintf(stderr, "Wrong value: %d\n", temp);
        failed = true;
        goto LIST_FREE;
    }

    // 5 -> 6 -> 7
    temp = list_remove_at(lt, 3);
    if (!(temp == 8)) {
        fprintf(stderr, "Wrong value: %d\n", temp);
        failed = true;
        goto LIST_FREE;
    }

    // 5 -> 7
    temp = list_remove_at(lt, 1);
    if (!(temp == 6)) {
        fprintf(stderr, "Wrong value: %d\n", temp);
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

bool test_list_iter(void)
{
    bool failed = false;

    // list_t: 4 -> 9 -> 5 -> NULL;
    list_t *lt = list_init(3, 4, 9, 5);
    if (lt == NULL) {
        perror("Failed to allocate list_t lt");
        return false;
    }

    int arr[] = {4, 9, 5};
    size_t i = 0;
    // Iterate through lt.
    for (list_iter_t it = list_start(lt); !list_end(it); it = list_next(it)) {
        if (node_value(it) != arr[i]) {
            failed = true;
            goto LIST_FREE;
        }

        i++;
    }

LIST_FREE:
    list_free(lt);

    if (failed) {
        return false;
    }

    return true;
}

// Nested function, available in GCC.
bool is_even(int n)
{
    return n % 2 == 0;
}

bool test_list_any(void)
{
    bool failed = false;

    list_t *lp = list_new();
    if (lp == NULL) {
        perror("Failed to allocate list_t lp");
        return false;
    }

    if (list_any(lp, is_even) != false) {
        failed = true;
        goto LIST_P_FREE;
    }

    list_t *lq = list_init(5, 1, 3, 5, 7, 9);
    if (lq == NULL) {
        perror("Failed to allocate list_t lq");
        failed = true;
        goto LIST_P_FREE;
    }

    if (list_any(lq, is_even) != false) {
        failed = true;
        goto LIST_Q_FREE;
    }

    list_t *lr = list_init(5, 1, 2, 3, 4, 5);
    if (lr == NULL) {
        perror("Failed to allocate list_t lr");
        failed = true;
        goto LIST_Q_FREE;
    }

    if (list_any(lr, is_even) != true) {
        failed = true;
        goto LIST_R_FREE;
    }

LIST_R_FREE:
    list_free(lr);
LIST_Q_FREE:
    list_free(lq);
LIST_P_FREE:
    list_free(lp);

    if (failed) {
        return false;
    }

    return true;
}

bool test_list_all(void)
{
    bool failed = false;

    list_t *lp = list_new();
    if (lp == NULL) {
        perror("Failed to allocate list_t lp");
        return false;
    }

    if (list_all(lp, is_even) != false) {
        failed = true;
        goto LIST_P_FREE;
    }

    list_t *lq = list_init(5, 1, 2, 3, 4, 5);
    if (lq == NULL) {
        perror("Failed to allocate list_t lq");
        failed = true;
        goto LIST_P_FREE;
    }

    if (list_all(lq, is_even) != false) {
        failed = true;
        goto LIST_Q_FREE;
    }

    list_t *lr = list_init(5, 2, 4, 6, 8, 10);
    if (lr == NULL) {
        perror("Failed to allocate list_t lr");
        failed = true;
        goto LIST_Q_FREE;
    }

    if (list_all(lr, is_even) != true) {
        failed = true;
        goto LIST_R_FREE;
    }

LIST_R_FREE:
    list_free(lr);
LIST_Q_FREE:
    list_free(lq);
LIST_P_FREE:
    list_free(lp);

    if (failed) {
        return false;
    }

    return true;
}

bool test_list_find(void)
{
    bool failed = false;

    list_t *lt = list_init(5, 5, 6, 7, 8, 9);
    if (!lt) {
        return false;
    }

    size_t *index = malloc(sizeof(size_t));
    if (!(list_find(lt, is_even, index) && *index == 1)) {
        fprintf(stderr, "Wrong index: %lu\n", *index);
        failed = true;
        goto LIST_FREE;
    }

LIST_FREE:
    free(index);
    list_free(lt);

    if (failed) {
        return false;
    }

    return true;
}

static bool ascending(int a, int b) {
    return a < b;
}

bool test_list_sort(void)
{
    bool failed = false;

    list_t *lt = list_init(5, 2, 4, 1, 5, 3);
    if (!lt) {
        return false;
    }

    list_t *sorted = list_sort(lt, ascending);
    if (!sorted) {
        failed = true;
        goto LIST_FREE;
    }

    int data[] = {1, 2, 3, 4, 5};
    int *out = malloc(sizeof(int));
    for (size_t i = 0; i < 5; i++) {
        if (!(list_at(lt, i, out) && *out == data[i])) {
            fprintf(stderr, "Wrong array value %d at %lu\n", *out, i);
            failed = true;
            goto SORTED_FREE;
        }
    }

SORTED_FREE:
    free(out);
    list_free(sorted);
LIST_FREE:
    list_free(lt);

    if (failed) {
        return false;
    }

    return true;
}

bool test_list_select_mut(void)
{
    bool failed = false;
    int *temp = NULL;

    list_t *lt = list_init(5, 5, 6, 7, 8, 9);
    if (!lt) {
        return false;
    }

    if (!list_select_mut(&lt, is_even)) {
        failed = true;
        goto LIST_FREE;
    }

    int data[] = {6, 8};
    temp = malloc(sizeof(int));
    for (size_t i = 0; i < 2; i++) {
        if (!(list_at(lt, i, temp) && *temp == data[i])) {
            failed = true;
            goto LIST_FREE;
        }
    }

LIST_FREE:
    free(temp);
    list_free(lt);

    if (failed) {
        return false;
    }

    return true;
}

int square(int n)
{
    return n * n;
}

bool test_list_map_mut(void)
{
    bool failed = false;

    // list_t p: 1 -> 2 -> 3 -> NULL
    list_t *lp = list_init(3, 1, 2, 3);
    if (lp == NULL) {
        perror("Failed to allocate list_t lp");
        return false;
    }

    // list_t q: 1 -> 4 -> 9 -> NULL
    // Traverse in functional style.
    if (!list_map_mut(&lp, square)) {
        perror("Failed to allocate list_t lq");
        failed = true;
        goto LIST_P_FREE;
    }

    int arr[] = {1, 4, 9};
    size_t i = 0;
    for (list_iter_t it = list_start(lp); !list_end(it); it = list_next(it)) {
        if (node_value(it) != arr[i]) {
            failed = true;
            goto LIST_P_FREE;
        }

        i++;
    }

LIST_P_FREE:
    list_free(lp);

    if (failed) {
        return false;
    }

    return true;
}

static int reducer(int a, int b)
{
    return a + b;
}

bool test_list_reduce(void)
{
    bool failed = false;

    list_t *lt = list_init(5, 1, 2, 3, 4, 5);
    if (!lt) {
        return false;
    }

    int result = list_reduce(lt, reducer);
    if (!(result == 15)) {
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
