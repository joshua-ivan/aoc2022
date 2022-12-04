#include <stdio.h>
#include <string.h>
#include "minunit.h"
#include "aoc2022-03.h"

int tests_run = 0;

static char const * test_rucksack_intersect() {
    char *test_arr[] = {
        "vJrwpWtwJgWrhcsFMMfFFhFp",
        "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
        "PmmdzqPrVvPwwTWBwg",
        "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn",
        "ttgJtRGJQctTZtZT",
        "CrZsJsPPZsGzwwsLwLmpwMDw"
    };
    char expected[] = {'p', 'L', 'P', 'v', 't', 's'};

    char const *failure_msg = "FAILURE: test_rucksack_intersect";
    for (int i = 0; i < 6; i++) {
        int len = strlen(test_arr[i]) / 2;
        mu_assert(failure_msg, rucksack_intersect(test_arr[i], test_arr[i] + len, len) == expected[i]);
    }

    return 0;
}

static char const * test_group_intersect() {
    char *test_arr[] = {
        "vJrwpWtwJgWrhcsFMMfFFhFp",
        "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
        "PmmdzqPrVvPwwTWBwg",
        "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn",
        "ttgJtRGJQctTZtZT",
        "CrZsJsPPZsGzwwsLwLmpwMDw"
    };
    char expected[] = {'r', 'Z'};

    char const *failure_msg = "FAILURE: test_group_intersect";
    for (int i = 0; i < 6; i += 3) {
        mu_assert(failure_msg, group_intersect(test_arr[i], test_arr[i + 1], test_arr[i + 2]) == expected[i / 3]);
    }

    return 0;
}

static char const * test_get_compartment_length() {
    char *test_arr[] = {
        "vJrwpWtwJgWrhcsFMMfFFhFp",
        "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
        "PmmdzqPrVvPwwTWBwg",
        "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn",
        "ttgJtRGJQctTZtZT",
        "CrZsJsPPZsGzwwsLwLmpwMDw",
        "vJrwpWtwJgWrhcsFMMfFFhFp\n",
        "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL\n",
        "PmmdzqPrVvPwwTWBwg\n",
        "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn\n",
        "ttgJtRGJQctTZtZT\n",
        "CrZsJsPPZsGzwwsLwLmpwMDw\n",
    };
    int expected[] = {12, 16, 9, 15, 8, 12, 12, 16, 9, 15, 8, 12};

    char const *failure_msg = "FAILURE: test_get_compartment_length";
    for (int i = 0; i < 12; i++) {
        mu_assert(failure_msg, get_compartment_length(test_arr[i]) == expected[i]);
    }

    return 0;

}

static char const * test_get_priority() {
    char items[] = {'p', 'L', 'P', 'v', 't', 's'};
    int expected[] = {16, 38, 42, 22, 20, 19};

    char const *failure_msg = "FAILURE: test_get_priority";
    for (int i = 0; i < 6; i++) {
        mu_assert(failure_msg, get_priority(items[i]) == expected[i]);
    }

    return 0;
}

static char const * all_tests() {
    mu_run_test(test_rucksack_intersect);
    mu_run_test(test_get_priority);
    mu_run_test(test_get_compartment_length);
    mu_run_test(test_group_intersect);

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

