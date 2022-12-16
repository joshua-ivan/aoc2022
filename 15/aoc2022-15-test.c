#include <stdio.h>
#include <stdlib.h>
#include "../minunit.h"
#include "aoc2022-15.h"

int tests_run = 0;

static char const * test_init_radar() {
    radar_arr ra = init_radar("test_cases/test.txt");
    int expected[14][4] = {
        {2, 18, -2, 15},
        {9, 16, 10, 16},
        {13, 2, 15, 3},
        {12, 14, 10, 16},
        {10, 20, 10, 16},
        {14, 17, 10, 16},
        {8, 7, 2, 10},
        {2, 0, 2, 10},
        {0, 11, 2, 10},
        {20, 14, 25, 17},
        {17, 20, 21, 22},
        {16, 7, 15, 3},
        {14, 3, 15, 3},
        {20, 1, 15, 3}
    };

    char const * fail_msg = "FAILURE: test_init_radar";
    for (int i = 0; i < 14; i++) {
        mu_assert(fail_msg,
                ra.list[i]->sensor.x == expected[i][0]
                && ra.list[i]->sensor.y == expected[i][1]
                && ra.list[i]->beacon.x == expected[i][2]
                && ra.list[i]->beacon.y == expected[i][3]);
    }

    return 0;
}

static char const * test_taxicab_dist() {
    coords a;
    a.x = 2;
    a.y = 18;
    coords b;
    b.x = -2;
    b.y = 15;

    char const * fail_msg = "FAILURE: test_taxicab_dist";
    mu_assert(fail_msg, taxicab_dist(a, b) == 7);

    return 0;
}

static char const * test_calculate_ranges() {
    radar_arr ra = init_radar("test_cases/test_calc_ranges.txt");
    radar_range_arr rra = calculate_ranges(ra, 10);

    char const * fail_msg = "FAILURE: test_calculate_ranges";
    mu_assert(fail_msg, rra.count == 1);
    mu_assert(fail_msg, rra.list[0]->start.x == 2);
    mu_assert(fail_msg, rra.list[0]->start.y == 10);
    mu_assert(fail_msg, rra.list[0]->end.x == 14);
    mu_assert(fail_msg, rra.list[0]->end.y == 10);

    return 0;
}

static char const * test_is_overlapping() {
    int test_vals[6][4] = {
        {0, 5, 0, 5},
        {3, 8, 0, 5},
        {-2, 3, 0, 5},
        {0, 5, 3, 8},
        {0, 5, -2, 3},
        {0, 5, 6, 10}
    };
    int expected[6] = {1, 1, 1, 1, 1, 0};

    char const * fail_msg = "FAILURE: test_is_overlapping";
    for (int i = 0; i < 6; i++) {
        radar_range a;
        a.start.x = test_vals[i][0];
        a.start.y = 0;
        a.end.x = test_vals[i][1];
        a.end.y = 0;
        radar_range b;
        b.start.x = test_vals[i][2];
        b.start.y = 0;
        b.end.x = test_vals[i][3];
        b.end.y = 0;
        mu_assert(fail_msg, is_overlapping(a, b) == expected[i]);
    }

    return 0;
}

static char const * test_prune_overlap() {
    radar_arr ra = init_radar("test_cases/test.txt");
    radar_range_arr rra = calculate_ranges(ra, 10);
    prune_overlap(&rra);

    char const * fail_msg = "FAILURE: test_prune_overlap";
    mu_assert(fail_msg, rra.count == 1);
    mu_assert(fail_msg, rra.list[0]->start.x == -2);
    mu_assert(fail_msg, rra.list[0]->end.x == 24);

    return 0;
}

static char const * test_positions_wo_beacons() {
    radar_arr ra = init_radar("test_cases/test.txt");
    char const * fail_msg = "FAILURE: test_positions_wo_beacons";
    mu_assert(fail_msg, positions_wo_beacons(ra, 10) == 26);

    return 0;
}

static char const * test_tuning_frequency() {
    radar_arr ra = init_radar("test_cases/test.txt");
    char const * fail_msg = "FAILURE: test_tuning_frequency";
    mu_assert(fail_msg, tuning_frequency(ra, 20, 20) == 56000011);

    return 0;
}

static char const * all_tests() {
    mu_run_test(test_init_radar);
    mu_run_test(test_taxicab_dist);
    mu_run_test(test_calculate_ranges);
    mu_run_test(test_is_overlapping);
    mu_run_test(test_prune_overlap);
    mu_run_test(test_positions_wo_beacons);
    mu_run_test(test_tuning_frequency);

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

