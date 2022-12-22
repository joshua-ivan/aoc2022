#include <stdio.h>
#include "../minunit.h"
#include "aoc2022-18.h"

int tests_run = 0;

static const char * test_init_cube() {
    const char *matrix_msg = "FAILURE: test_init_cube__matrix";
    cube c = init_cube();
    for (int i = 0; i < MAX_DIM_SIZE; i++) {
        for (int j = 0; j < MAX_DIM_SIZE; j++) {
            for (int k = 0; k < MAX_DIM_SIZE; k++) {
                mu_assert(matrix_msg, c.matrix[i][j][k] == 0);
            }
        }
    }

    return 0;
}

static const char * test_insert_cube() {
    cube c = init_cube();
    c = insert_cube(c, 1, 1, 1);
    c = insert_cube(c, 2, 1, 1);

    const char * fail_msg = "FAILURE: test_insert_cube";
    mu_assert(fail_msg, c.matrix[1][1][1] == 1);
    mu_assert(fail_msg, c.matrix[2][1][1] == 1);

    return 0;
}

static const char * test_surface_area() {
    const char *simple_msg = "FAILURE: test_surface_area__simple";
    mu_assert(simple_msg, surface_area("test_cases/test-simple.txt", 0) == 10);

    const char *simple_two_msg = "FAILURE: test_surface_area__simple_two";
    mu_assert(simple_two_msg, surface_area("test_cases/test-simple_2.txt", 0) == 34);

    const char *test_msg = "FAILURE: test_surface_area";
    mu_assert(test_msg, surface_area("test_cases/test.txt", 0) == 64);

    return 0;
}

static const char * test_parse_input() {
    cube c = parse_input("test_cases/test.txt");
    int expected[13][3] = {
        {2, 2, 2},
        {1, 2, 2},
        {3, 2, 2},
        {2, 1, 2},
        {2, 3, 2},
        {2, 2, 1},
        {2, 2, 3},
        {2, 2, 4},
        {2, 2, 6},
        {1, 2, 5},
        {3, 2, 5},
        {2, 1, 5},
        {2, 3, 5}
    };

    const char *fail_msg = "FAILURE: test_parse_input";
    for (int i = 0; i < 13; i++) {
        int x = expected[i][0];
        int y = expected[i][1];
        int z = expected[i][2];

        mu_assert(fail_msg, c.matrix[x][y][z]);
    }

    return 0;
}

static const char * test_is_reachable() {
    cube c = parse_input("test_cases/test.txt");
    cube visited = init_cube();
    const char *fail_msg = "FAILURE: test_is_reachable";
    mu_assert(fail_msg, !is_reachable(&c, &visited, 2, 2, 5));

    return 0;
}

static const char * test_part_two() {
    const char *test_msg = "FAILURE: test_part_two";
    mu_assert(test_msg, surface_area("test_cases/test.txt", 1) == 58);

    return 0;
}

static const char * all_tests() {
    mu_run_test(test_init_cube);
    mu_run_test(test_insert_cube);
    mu_run_test(test_surface_area);
    mu_run_test(test_part_two);
    mu_run_test(test_parse_input);
    mu_run_test(test_is_reachable);

    return 0;
}

int main(int argc, char **argv) {
    const char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}


