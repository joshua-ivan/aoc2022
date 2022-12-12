#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include "aoc2022-08.h"

int tests_run = 0;

static char const * test_get_matrix_bounds() {
    int* dims = get_matrix_bounds("test_cases/test.txt");
    char const * failure_msg = "FAILURE: test_get_matrix_bounds";
    mu_assert(failure_msg, (dims[0] == 5 && dims[1] == 5));

    free(dims);
    return 0;
}

static char const * test_build_matrix() {
    int* dims = malloc(sizeof(int) * 2);
    int width = 5;
    int height = 5;

    int** matrix = build_matrix("test_cases/test.txt", width, height);
    int expected[5][5] = {
        {3, 0, 3, 7, 3},
        {2, 5, 5, 1, 2},
        {6, 5, 3, 3, 2},
        {3, 3, 5, 4, 9},
        {3, 5, 3, 9, 0}
    };

    char const * failure_msg = "FAILURE: test_build_matrix";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            mu_assert(failure_msg, matrix[i][j] == expected[i][j]);
        }
    }

    for (int i = 0; i < dims[1]; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(dims);
    return 0;
}

static char const * test_is_tree_visible() {
    int** test_matrix = build_matrix("test_cases/test.txt", 5, 5);
    int expected[5][5] = {
        {1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1},
        {1, 1, 0, 1, 1},
        {1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1}
    };

    char const * failure_msg = "FAILURE: test_is_tree_visible";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            mu_assert(failure_msg, is_tree_visible(test_matrix, 5, 5, i, j) == expected[i][j]);
        }
    }

    for (int i = 0; i < 5; i++) {
        free(test_matrix[i]);
    }
    free(test_matrix);
    return 0;
}

static char const * test_scenic_score() {
    int** test_matrix = build_matrix("test_cases/test.txt", 5, 5);
    char const * failure_msg = "FAILURE: test_scenic_score";
    mu_assert(failure_msg, scenic_score(test_matrix, 5, 5, 1, 2) == 4);
    mu_assert(failure_msg, scenic_score(test_matrix, 5, 5, 3, 2) == 8);

    for (int i = 0; i < 5; i++) {
        free(test_matrix[i]);
    }
    free(test_matrix);
    return 0;
}

static char const * all_tests() {
    mu_run_test(test_get_matrix_bounds);
    mu_run_test(test_build_matrix);
    mu_run_test(test_is_tree_visible);
    mu_run_test(test_scenic_score);

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

