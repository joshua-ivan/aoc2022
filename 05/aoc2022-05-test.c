#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include "aoc2022-05.h"

int tests_run = 0;

static char const * test_init_storage() {
    FILE *fp = fopen("test.txt", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    char const *failure_msg = "FAILURE: test_init_storage";
    char *expected[] = {
        "NZ",
        "DCM",
        "P"
    };
    int num_stacks = 3;
    stack *actual = init_storage(fp, num_stacks);
    for (int i = 0; i < num_stacks; i++) {
        int j = 0;
        while (actual[i].index > 0) {
            mu_assert(failure_msg, stack_pop(&actual[i]) == expected[i][j++]);
        }
    }

    return 0;
}

static char const * test_parse_instruction() {
    char *test_insts[] = {
        "move 1 from 2 to 1",
        "move 3 from 1 to 3",
        "move 2 from 2 to 1",
        "move 1 from 1 to 2"
    };
    int expected[4][3] = {
        {1, 1, 0},
        {3, 0, 2},
        {2, 1, 0},
        {1, 0, 1}
    };

    char const *failure_msg = "FAILURE: test_parse_instruction";
    for (int i = 0; i < 4; i++) {
        int *actual = parse_instruction(test_insts[i]);
        for (int j = 0; j < 3; j++) {
            mu_assert(failure_msg, actual[j] == expected[i][j]);
        }
        free(actual);
    }

    return 0;
}

static char const * test_stack() {
    stack s = stack_init();

    char const *init_failure_msg = "FAILURE: test_stack_init";
    mu_assert(init_failure_msg, s.index == 0);
    for (int i = 0; i < AOC_STACK_SIZE; i++) {
        mu_assert(init_failure_msg, s.items[i] == ' ');
    }

    stack_push(&s, 'x');
    stack_push(&s, 'y');
    stack_push(&s, 'z');

    char const *push_failure_msg = "FAILURE: test_stack_push";
    mu_assert(push_failure_msg, s.index == 3);
    char *expected = "xyz";
    for (int i = 0; i < s.index; i++) {
        mu_assert(push_failure_msg, s.items[i] == expected[i]);
    }

    char p = stack_pop(&s);

    char const *pop_failure_msg = "FAILURE: test_stack_pop";
    mu_assert(pop_failure_msg, s.index == 2);
    mu_assert(pop_failure_msg, p == 'z');

    return 0;
}

static char const * all_tests() {
    mu_run_test(test_stack);
    mu_run_test(test_init_storage);
    mu_run_test(test_parse_instruction);

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

