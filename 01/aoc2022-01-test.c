#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include "aoc2022-01.h"

int tests_run = 0;

node* create_test_list() {
    int test[5] = {6000, 4000, 11000, 24000, 10000};
    node *list = malloc(sizeof(node));
    node *current = list;
    int i = 0;
    while (i < 4) {
        current->cals = test[i++];
        current->next = malloc(sizeof(node));
        current = current->next;
    }
    current->cals = test[4];
    current->next = NULL;

    return list;
}

static char const * test_build_calorie_list() {
    char const *failure_msg = "FAILURE: test_build_calorie_list";

    node *list = build_calorie_list("test.txt");
    node *current = list;
    int expected[5] = {6000, 4000, 11000, 24000, 10000};
    int i = 0;
    while (current != NULL) {
        mu_assert(failure_msg, current->cals == expected[i++]);
        current = current->next;
    }

    free_list(list);
    return 0;
}

static char const * test_max_value() {
    char const *failure_msg = "FAILURE: test_max_value";

    node *list = create_test_list();
    mu_assert(failure_msg, max_value(list) == 24000);
    free_list(list);

    return 0;
}

static char const * test_list_to_array() {
    char const *failure_msg = "FAILURE: test_list_to_array";

    node *list = create_test_list();
    int expected[5] = {6000, 4000, 11000, 24000, 10000};

    int actual_len;
    int *actual_arr = list_to_array(list, &actual_len);
    for (int i = 0; i < 5; i++) {
        mu_assert(failure_msg, expected[i] == actual_arr[i]);
    }
    mu_assert(failure_msg, actual_len == 5);

    return 0;
}

static char const * test_top_n_sum() {
    char const *failure_msg = "FAILURE: test_top_n_sum";

    node *list = create_test_list();
    mu_assert(failure_msg, top_n_sum(list, 3) == 45000);
    free_list(list);

    return 0;
}

static char const * all_tests() {
    mu_run_test(test_build_calorie_list);
    mu_run_test(test_max_value);
    mu_run_test(test_list_to_array);
    mu_run_test(test_top_n_sum);
    return 0;
}

int main(int argc, char **argv) {
    char const *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}

