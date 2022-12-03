#include <stdio.h>
#include "minunit.h"
#include "aoc2022-02.h"

int tests_run = 0;

static char const * test_get_outcome() {
    char const *failure_msg = "FAILURE: test_get_outcome";
    mu_assert(failure_msg, get_outcome('A', 'Y') == 6);
    mu_assert(failure_msg, get_outcome('B', 'Z') == 6);
    mu_assert(failure_msg, get_outcome('C', 'X') == 6);

    mu_assert(failure_msg, get_outcome('A', 'X') == 3);
    mu_assert(failure_msg, get_outcome('B', 'Y') == 3);
    mu_assert(failure_msg, get_outcome('C', 'Z') == 3);

    mu_assert(failure_msg, get_outcome('A', 'Z') == 0);
    mu_assert(failure_msg, get_outcome('B', 'X') == 0);
    mu_assert(failure_msg, get_outcome('C', 'Y') == 0);

    return 0;
}

static char const * test_get_score() {
    char const *failure_msg = "FAILURE: test_get_score";

    mu_assert(failure_msg, get_score('A', 'Y') == 8);
    mu_assert(failure_msg, get_score('B', 'Z') == 9);
    mu_assert(failure_msg, get_score('C', 'X') == 7);

    mu_assert(failure_msg, get_score('A', 'X') == 4);
    mu_assert(failure_msg, get_score('B', 'Y') == 5);
    mu_assert(failure_msg, get_score('C', 'Z') == 6);

    mu_assert(failure_msg, get_score('A', 'Z') == 3);
    mu_assert(failure_msg, get_score('B', 'X') == 1);
    mu_assert(failure_msg, get_score('C', 'Y') == 2);

    return 0;
}


static char const * test_get_shape() {
    char const *failure_msg = "FAILURE: test_get_shape";

    mu_assert(failure_msg, get_shape('A', 'X') == 3);
    mu_assert(failure_msg, get_shape('B', 'X') == 1);
    mu_assert(failure_msg, get_shape('C', 'X') == 2);

    mu_assert(failure_msg, get_shape('A', 'Y') == 1);
    mu_assert(failure_msg, get_shape('B', 'Y') == 2);
    mu_assert(failure_msg, get_shape('C', 'Y') == 3);

    mu_assert(failure_msg, get_shape('A', 'Z') == 2);
    mu_assert(failure_msg, get_shape('B', 'Z') == 3);
    mu_assert(failure_msg, get_shape('C', 'Z') == 1);

    return 0;
}

static char const * test_final_score() {
    char const *failure_msg = "FAILURE: test_final_score";

    mu_assert(failure_msg, final_score('A', 'X') == 3);
    mu_assert(failure_msg, final_score('B', 'X') == 1);
    mu_assert(failure_msg, final_score('C', 'X') == 2);

    mu_assert(failure_msg, final_score('A', 'Y') == 4);
    mu_assert(failure_msg, final_score('B', 'Y') == 5);
    mu_assert(failure_msg, final_score('C', 'Y') == 6);

    mu_assert(failure_msg, final_score('A', 'Z') == 8);
    mu_assert(failure_msg, final_score('B', 'Z') == 9);
    mu_assert(failure_msg, final_score('C', 'Z') == 7);

    return 0;
}

static char const * all_tests() {
    mu_run_test(test_get_outcome);
    mu_run_test(test_get_score);
    mu_run_test(test_get_shape);
    mu_run_test(test_final_score);

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

