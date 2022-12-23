#include <stdio.h>
#include <time.h>
#include "../minunit.h"
#include "aoc2022-19.h"

int tests_run = 0;

static const char* test_parse_input() {
    list_blueprint bps = parse_input("test_cases/test.txt");
    int expected[2][4][3] = {
        { {0, 0, 4}, {0, 0, 2}, {0, 14, 3}, {7, 0, 2} },
        { {0, 0, 2}, {0, 0, 3}, {0, 8, 3}, {12, 0, 3} }
    };
    int expected_max_ores[2] = {4, 3};

    const char* fail_msg = "FAILURE: test_parse_input";
    mu_assert(fail_msg, bps.count == 2);
    for (int i = 0; i < 2; i++) {
        mu_assert(fail_msg, bps.list[i].max_ore_cost == expected_max_ores[i]);
        for (int j = 0; j < 3; j++) {
            mu_assert(fail_msg, bps.list[i].ore_cost[j] == expected[i][0][j]);
        }
        for (int j = 0; j < 3; j++) {
            mu_assert(fail_msg, bps.list[i].clay_cost[j] == expected[i][1][j]);
        }
        for (int j = 0; j < 3; j++) {
            mu_assert(fail_msg, bps.list[i].obsidian_cost[j] == expected[i][2][j]);
        }
        for (int j = 0; j < 3; j++) {
            mu_assert(fail_msg, bps.list[i].geode_cost[j] == expected[i][3][j]);
        }
    }

    return 0;
}

static const char* test_geode_state() {
    geode_state init_state = init_geode_state();

    const char* init_msg = "FAILURE: test_init_geode_state";
    mu_assert(init_msg, init_state.time_elapsed == 0);
    for (int i = 0; i < 4; i++) {
        mu_assert(init_msg, init_state.num_resources[i] == 0);
        mu_assert(init_msg, init_state.num_robots[i] == (i == 3));
    }

    init_state.time_elapsed = 5;
    for (int i = 0; i < 4; i++) {
        init_state.num_resources[i] = (i + 1) * 2;
        init_state.num_robots[i] = i + 1;
    }
    geode_state copy_state = copy_geode_state(init_state);

    const char* copy_msg = "FAILURE: test_copy_geode_state";
    mu_assert(copy_msg, copy_state.time_elapsed == init_state.time_elapsed);
    for (int i = 0; i < 4; i++) {
        mu_assert(copy_msg, copy_state.num_resources[i] == init_state.num_resources[i]);
        mu_assert(copy_msg, copy_state.num_robots[i] == init_state.num_robots[i]);
    }

    geode_state empty_state = init_geode_state();
    const char* equals_msg = "FAILURE: test_geode_state_equals";
    mu_assert(equals_msg, geode_state_equals(copy_state, init_state));
    mu_assert(equals_msg, !geode_state_equals(copy_state, empty_state));

    return 0;
}

static const char* test_calculate_hash() {
    geode_state gs = init_geode_state();
    gs.time_elapsed = 32;
    for (int i = 0; i < 4; i++) {
        gs.num_resources[i] = 7;
        gs.num_robots[i] = 5;
    }

    const char* fail_msg = "FAILURE: test_calculate_hash";
    unsigned int expected_hash = 32768 + 128 + 8 + 4;
    mu_assert(fail_msg, calculate_hash(gs) == expected_hash);

    return 0;
}

static const char* test_hash_table() {
    hash_table ht = init_hash_table();

    unsigned int max_addr = 65535;
    const char* init_msg = "FAILURE: test_hash_table__init";
    for (int i = 0; i <= max_addr; i++) {
        mu_assert(init_msg, ht.list[i] == NULL);
    }

    geode_state gs_one = init_geode_state();
    for (int i = 0; i < 4; i++) {
        gs_one.num_resources[i] = 7;
        gs_one.num_robots[i] = 5;
    }
    geode_state gs_two = init_geode_state();
    for (int i = 0; i < 4; i++) {
        gs_two.num_resources[i] = 5;
        gs_two.num_robots[i] = 7;
    }
    ht = insert_hash_table(ht, gs_one, 4);
    ht = insert_hash_table(ht, gs_two, 6);

    const char* insert_msg = "FAILURE: test_hash_table__insert";
    mu_assert(insert_msg, ht.list[calculate_hash(gs_one)]->max_geodes == 4);
    mu_assert(insert_msg, ht.list[calculate_hash(gs_two)]->next->max_geodes == 6);

    geode_state gs_miss = init_geode_state();
    const char* lookup_msg = "FAILURE: test_hash_table__lookup";
    mu_assert(lookup_msg, lookup_hash_table(ht, gs_one) == 4);
    mu_assert(lookup_msg, lookup_hash_table(ht, gs_two) == 6);
    mu_assert(lookup_msg, lookup_hash_table(ht, gs_miss) == -1);

    free_hash_table(ht);
    return 0;
}

static const char* test_sufficient_resources() {
    list_blueprint bps = parse_input("test_cases/test.txt");

    const char* empty_msg = "FAILURE: test_sufficient_resources__empty";
    geode_state empty_state = init_geode_state();
    for (int i = 0; i < 4; i++) {
        mu_assert(empty_msg, !sufficient_resources(i, bps.list[0], empty_state));
    }

    const char* ore_msg = "FAILURE: test_sufficient_resources__ore";
    geode_state ore_state = init_geode_state();
    int ore_test_values[2][2] = {
        {4, 1},
        {3, 0}
    };
    for (int i = 0; i < 2; i++) {
        ore_state.num_resources[3] = ore_test_values[i][0];
        mu_assert(ore_msg, sufficient_resources(3, bps.list[0], ore_state) == ore_test_values[i][1]);
    }

    const char* clay_msg = "FAILURE: test_sufficient_resources__clay";
    geode_state clay_state = init_geode_state();
    int clay_test_values[2][2] = {
        {2, 1},
        {1, 0}
    };
    for (int i = 0; i < 2; i++) {
        clay_state.num_resources[3] = clay_test_values[i][0];
        mu_assert(clay_msg, sufficient_resources(2, bps.list[0], clay_state) == clay_test_values[i][1]);
    }

    const char* obsidian_msg = "FAILURE: test_sufficient_resources__obsidian";
    geode_state obsidian_state = init_geode_state();
    int obsidian_test_values[4][3] = {
        { 3, 14, 1 },
        { 2, 14, 0 },
        { 3, 13, 0 },
        { 2, 13, 0 }
    };
    for (int i = 0; i < 4; i++) {
        obsidian_state.num_resources[3] = obsidian_test_values[i][0];
        obsidian_state.num_resources[2] = obsidian_test_values[i][1];
        mu_assert(obsidian_msg, sufficient_resources(1, bps.list[0], obsidian_state) == obsidian_test_values[i][2]);
    }

    const char* geode_msg = "FAILURE: test_sufficient_resources__geode";
    geode_state gs = init_geode_state();
    int geode_test_values[4][3] = {
        { 2, 7, 1 },
        { 1, 7, 0 },
        { 2, 6, 0 },
        { 1, 6, 0 }
    };
    for (int i = 0; i < 4; i++) {
        gs.num_resources[3] = geode_test_values[i][0];
        gs.num_resources[1] = geode_test_values[i][1];
        mu_assert(geode_msg, sufficient_resources(0, bps.list[0], gs) == geode_test_values[i][2]);
    }

    return 0;
}

static const char* test_max_ore_cost() {
    list_blueprint bps = parse_input("test_cases/test.txt");

    const char* fail_msg = "FAILURE: test_max_ore_cost";
    mu_assert(fail_msg, max_ore_cost(bps.list[0]) == 4);
    mu_assert(fail_msg, max_ore_cost(bps.list[1]) == 3);

    return 0;
}

static const char* test_potential_geodes() {
    geode_state gs = init_geode_state();

    const char* fail_msg = "FAILURE: test_potential_geodes";
    mu_assert(fail_msg, potential_geodes(24, gs) == 276);

    gs.time_elapsed = 14;
    gs.num_resources[0] = 5;
    gs.num_robots[0] = 3;
    mu_assert(fail_msg, potential_geodes(24, gs) == 80);

    return 0;
}

static const char* test_max_geodes() {
    list_blueprint bps = parse_input("test_cases/test.txt");
    hash_table memo = init_hash_table();
    short global_max = 0;

    const char* fail_msg = "FAILURE: test_max_geodes";
    clock_t start = clock();    
    mu_assert(fail_msg, max_geodes(24, bps.list[0], init_geode_state(), &memo, &global_max) == 9);
    clock_t end = clock();
    printf("Time limit: 24 - Execution time: %fs\n", ((end - start) / (double)CLOCKS_PER_SEC));

    free_hash_table(memo);
    memo = init_hash_table();
    global_max = 0;

    start = clock();
    mu_assert(fail_msg, max_geodes(32, bps.list[0], init_geode_state(), &memo, &global_max) == 56);
    end = clock();
    printf("Time limit: 32 - Execution time: %fs\n", ((end - start) / (double)CLOCKS_PER_SEC));

    free_hash_table(memo);
    return 0;
}

static const char* test_sum_quality() {
    const char* fail_msg = "FAILURE: test_sum_quality";
    mu_assert(fail_msg, sum_quality("test_cases/test.txt") == 33);

    return 0;
}

static const char* test_product_blueprints() {
    const char* fail_msg = "FAILURE: test_sum_quality";
    mu_assert(fail_msg, product_blueprints("test_cases/test.txt") == 194432);

    return 0;
}

static const char* all_tests() {
    mu_run_test(test_parse_input);
    mu_run_test(test_geode_state);
    mu_run_test(test_sum_quality);
    mu_run_test(test_product_blueprints);
    mu_run_test(test_max_ore_cost);
    mu_run_test(test_max_geodes);
    mu_run_test(test_potential_geodes);
    mu_run_test(test_sufficient_resources);
    mu_run_test(test_calculate_hash);
    mu_run_test(test_hash_table);

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


