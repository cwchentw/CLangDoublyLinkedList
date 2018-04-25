#include <stddef.h>
#include <stdio.h>
#include "list.h"

bool test_list_iter()
{
    bool failed = false;

    // List: 4 -> 9 -> 5 -> NULL;
    List *lt = list_init(3, 4, 9, 5);
    if (lt == NULL) {
        perror("Failed to allocate List lt");
        return false;
    }

    int arr[] = {4, 9, 5};
    size_t i = 0;
    // Iterate through lt.
    for (ListIter it = list_start(lt); !list_end(it); it = list_next(it)) {
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

bool test_list_any()
{
    // Nested function, available in GCC.
    bool is_even(int n)
    {
        return n % 2 == 0;
    }

    bool failed = false;

    List *lp = list_new();
    if (lp == NULL) {
        perror("Failed to allocate List lp");
        return false;
    }

    if (list_any(lp, is_even) != false) {
        failed = true;
        goto LIST_P_FREE;
    }

    List *lq = list_init(5, 1, 3, 5, 7, 9);
    if (lq == NULL) {
        perror("Failed to allocate List lq");
        failed = true;
        goto LIST_P_FREE;
    }

    if (list_any(lq, is_even) != false) {
        failed = true;
        goto LIST_Q_FREE;
    }

    List *lr = list_init(5, 1, 2, 3, 4, 5);
    if (lr == NULL) {
        perror("Failed to allocate List lr");
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

bool test_list_all()
{
    // Nested fuction, available in GCC.
    bool is_even(int n)
    {
        return n % 2 == 0;
    }

    bool failed = false;

    List *lp = list_new();
    if (lp == NULL) {
        perror("Failed to allocate List lp");
        return false;
    }

    if (list_all(lp, is_even) != false) {
        failed = true;
        goto LIST_P_FREE;
    }

    List *lq = list_init(5, 1, 2, 3, 4, 5);
    if (lq == NULL) {
        perror("Failed to allocate List lq");
        failed = true;
        goto LIST_P_FREE;
    }

    if (list_all(lq, is_even) != false) {
        failed = true;
        goto LIST_Q_FREE;
    }

    List *lr = list_init(5, 2, 4, 6, 8, 10);
    if (lr == NULL) {
        perror("Failed to allocate List lr");
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

bool test_list_map()
{
    // Nested function, available in GCC.
    int square(int n)
    {
        return n * n;
    }

    bool failed = false;

    // List p: 1 -> 2 -> 3 -> NULL
    List *lp = list_init(3, 1, 2, 3);
    if (lp == NULL) {
        perror("Failed to allocate List lp");
        return false;
    }

    // List q: 1 -> 4 -> 9 -> NULL
    // Traverse in functional style.
    List *lq = list_map(lp, square);
    if (lq == NULL) {
        perror("Failed to allocate List lq");
        failed = true;
        goto LIST_P_FREE;
    }

    int arr[] = {1, 4, 9};
    size_t i = 0;
    for (ListIter it = list_start(lq); !list_end(it); it = list_next(it)) {
        if (node_value(it) != arr[i]) {
            failed = true;
            goto LIST_Q_FREE;
        }

        i++;
    }

LIST_Q_FREE:
    list_free(lq);
LIST_P_FREE:
    list_free(lp);

    if (failed) {
        return false;
    }

    return true;
}
