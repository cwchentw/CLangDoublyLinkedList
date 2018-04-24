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
    // Test list manipulation.
    TEST(test_list_is_empty());
    TEST(test_list_unshift());
    TEST(test_list_push());
    TEST(test_list_shift());
    TEST(test_list_insert_when());
    TEST(test_list_pop());

    // Test list traversal.
    TEST(test_list_iter());
    TEST(test_list_any());
    TEST(test_list_all());
    TEST(test_list_map());

    return 0;
}
