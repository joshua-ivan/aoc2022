#include <stdio.h>
#include <stdlib.h>
#include "../minunit.h"
#include "aoc2022-14.h"

int tests_run = 0;

static char const * test_to_coords() {
    coords c = to_coords("10,20");

    char const * fail_msg = "FAILURE: test_to_coords";
    mu_assert(fail_msg, c.x == 10);
    mu_assert(fail_msg, c.y == 20);

    return 0;
}

static char const * test_init_cave() {
    char const * fail_msg = "FAILURE: test_init_cave";

    cave c = init_cave("test_cases/test.txt");
    int expected_first[3][2] = {
        {498, 4}, {498, 6}, {496, 6}
    };
    for (int i = 0; i < 3; i++) {
        mu_assert(fail_msg, c.rocks[0].list[i]->x == expected_first[i][0]);
        mu_assert(fail_msg, c.rocks[0].list[i]->y == expected_first[i][1]);
    }

    int expected_second[4][2] = {
        {503, 4}, {502, 4}, {502, 9}, {494, 9}
    };
    for (int i = 0; i < 4; i++) {
        mu_assert(fail_msg, c.rocks[1].list[i]->x == expected_second[i][0]);
        mu_assert(fail_msg, c.rocks[1].list[i]->y == expected_second[i][1]);
    }

    int expected_floor[2][2] = {
        {0, 11}, {999, 11}
    };
    for (int i = 0; i < 2; i++) {
        mu_assert(fail_msg, c.rocks[2].list[i]->x == expected_floor[i][0]);
        mu_assert(fail_msg, c.rocks[2].list[i]->y == expected_floor[i][1]);
    }


    mu_assert(fail_msg, c.formations == 3);
    mu_assert(fail_msg, c.lowest == 11);

    return 0;
}

static char const * test_build_terrain() {
    cave c = init_cave("test_cases/test.txt");
    int** terrain = build_terrain(c);

    FILE *fp = fopen("test_cases/expected_terrain.txt", "r");
    char const * file_msg = "FAILURE: test_build_terrain__expected_terrain_txt";
    mu_assert(file_msg, fp != NULL);
    
    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    for (int i = 0; i < 9; i++) {
        mu_assert(file_msg, (read = getline(&line, &length, fp)) != -1);
        for (int j = 0; j < 12; j++) {
            char const * fail_msg = "FAILURE: test_build_terrain";
            mu_assert(fail_msg, terrain[493 + j][3 + i] == line[j]);
        }
    }

    fclose(fp);
    return 0;
}

static char const * test_pour_sand() {
    cave c = init_cave("test_cases/test.txt");
    int** terrain = build_terrain(c);
    int units = pour_sand(terrain, c.lowest);

    FILE *fp = fopen("test_cases/expected_sand.txt", "r");
    char const * file_msg = "FAILURE: test_build_terrain__expected_sanad_txt";
    mu_assert(file_msg, fp != NULL);

    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    char const * fail_msg = "FAILURE: test_pour_sand";
    for (int i = 0; i < 12; i++) {
        mu_assert(file_msg, (read = getline(&line, &length, fp)) != -1);
        for (int j = 0; j < 25; j++) {
            mu_assert(fail_msg, terrain[488 + j][i] == line[j]);
        }
    }
    mu_assert(fail_msg, units == 93);

    return 0;
}

static char const * all_tests() {
    mu_run_test(test_to_coords);
    mu_run_test(test_init_cave);
    mu_run_test(test_build_terrain);
    mu_run_test(test_pour_sand);

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

