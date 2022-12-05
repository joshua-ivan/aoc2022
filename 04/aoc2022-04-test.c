#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include "aoc2022-04.h"

int tests_run = 0;

static char const * test_parse_assignment() {
    char *test_arr[] = {
        "2-4,6-8",
        "2-3,4-5",
        "5-7,7-9",
        "2-8,3-7",
        "6-6,4-6",
        "2-6,4-8"
    };
    int expected[6][4] = {
        {2, 4, 6, 8},
        {2, 3, 4, 5},
        {5, 7, 7, 9},
        {2, 8, 3, 7},
        {6, 6, 4, 6},
        {2, 6, 4, 8}
    };

    char const *failure_msg = "FAILURE: test_parse_assignment";
    for (int i = 0; i < 6; i++) {
        int *bounds = parse_assignment(test_arr[i]);
        for (int j = 0; j < 4; j++) {
            mu_assert(failure_msg, bounds[j] == expected[i][j]);
        }
        free(bounds);
    }

    return 0;
}

static char const * test_check_bounds() {
    int test_arr[6][4] = {
        {2, 4, 6, 8},
        {2, 3, 4, 5},
        {5, 7, 7, 9},
        {2, 8, 3, 7},
        {6, 6, 4, 6},
        {2, 6, 4, 8}
    };
    int expected[6] = {0, 0, 0, 1, 1, 0};

    char const *failure_msg = "FAILURE: test_check_bounds";
    for (int i = 0; i < 6; i++) {
        mu_assert(failure_msg, check_bounds(test_arr[i]) == expected[i]);
    }

    return 0;
}

static char const * test_check_overlap() {
    int test_arr[6][4] = {
        {2, 4, 6, 8},
        {2, 3, 4, 5},
        {5, 7, 7, 9},
        {2, 8, 3, 7},
        {6, 6, 4, 6},
        {2, 6, 4, 8}
    };
    int expected[6] = {0, 0, 1, 1, 1, 1};

    char const *failure_msg = "FAILURE: test_check_overlap";
    for (int i = 0; i < 6; i++) {
        mu_assert(failure_msg, check_overlap(test_arr[i]) == expected[i]);
    }

    return 0;
}

static char const * all_tests() {
    mu_run_test(test_parse_assignment);
    mu_run_test(test_check_bounds);
    mu_run_test(test_check_overlap);

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

