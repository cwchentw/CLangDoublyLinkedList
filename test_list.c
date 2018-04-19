#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "test_manipulation.h"
#include "test_traversal.h"

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
    
    if (!test_list_any()) {
        perror("Failed on test_list_any");
        exit(EXIT_FAILURE);
    }
    
    if (!test_list_all()) {
        perror("Failed on test_list_all");
        exit(EXIT_FAILURE);
    }
    
    if (!test_list_map()) {
        perror("Failed on test_list_map");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
