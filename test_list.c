#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

bool test_list_is_empty();
bool test_list_unshift();
bool test_list_push();
bool test_list_shift();
bool test_list_insert_when();
bool test_list_pop();
bool test_list_iter();
bool test_list_map();

int main()
{
    if (!test_list_is_empty()) {
        perror("Failed on test_list_is_empty");
        exit(EXIT_FAILURE);
    }
    
    if (!test_list_unshift()) {
        perror("Failed on test_list_unshift");
        exit(EXIT_FAILURE);
    }
    
    if (!test_list_push()) {
        perror("Failed on test_list_push");
        exit(EXIT_FAILURE);
    }
    
    if (!test_list_shift()) {
        perror("Failed on test_list_shift");
        exit(EXIT_FAILURE);
    }
    
    if (!test_list_insert_when()) {
        perror("Failed on test_list_when()");
        exit(EXIT_FAILURE);
    }
    
    if (!test_list_pop()) {
        perror("Failed on test_list_pop");
        exit(EXIT_FAILURE);
    }
    
    if (!test_list_iter()) {
        perror("Failed on test_list_iter");
        exit(EXIT_FAILURE);
    }
    
    if (!test_list_map()) {
        perror("Failed on test_list_map");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}

bool test_list_is_empty()
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

bool test_list_unshift()
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

bool test_list_insert_when()
{
    // Nested function, available in GCC.
    bool is_smaller(int a, int b)
    {
        return a < b;
    }

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

bool test_list_push()
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

bool test_list_shift()
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

bool test_list_pop()
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
    for (Node *it = list_start(lt); !list_end(it); it = list_next(it)) {
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
    for (Node *it = list_start(lq); !list_end(it); it = list_next(it)) {
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