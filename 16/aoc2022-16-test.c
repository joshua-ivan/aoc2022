#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../minunit.h"
#include "aoc2022-16.h"

int tests_run = 0;

static char const * test_init_graph() {
    graph g = init_graph("test_cases/test.txt");
    char *expected_vertices[10] = {
        "AA", "BB", "CC", "DD", "EE",
        "FF", "GG", "HH", "II", "JJ"
    };
    int expected_flow[10] = {
        0, 13, 2, 20, 3, 0, 0, 22, 0, 21
    };
    char *expected_edges[20][2] = {
        {"AA", "DD"}, {"AA", "II"}, {"AA", "BB"},
        {"BB", "CC"}, {"BB", "AA"},
        {"CC", "DD"}, {"CC", "BB"},
        {"DD", "CC"}, {"DD", "AA"}, {"DD", "EE"},
        {"EE", "FF"}, {"EE", "DD"},
        {"FF", "EE"}, {"FF", "GG"},
        {"GG", "FF"}, {"GG", "HH"},
        {"HH", "GG"},
        {"II", "AA"}, {"II", "JJ"},
        {"JJ", "II"}
    };

    char const * vertex_msg = "FAILURE: test_init_graph__vertex";
    mu_assert(vertex_msg, g.v_len == 10);
    for (int i = 0; i < g.v_len; i++) {
        mu_assert(vertex_msg, !strcmp(g.v[i].name, expected_vertices[i]));
        mu_assert(vertex_msg, g.v[i].flow == expected_flow[i]);
    }
    char const * edge_msg = "FAILURE: test_init_graph__edge";
    mu_assert(edge_msg, g.e_len == 20);
    for (int i = 0; i < g.e_len; i++) {
        mu_assert(edge_msg, !strcmp(g.e[i].v_a, expected_edges[i][0]));
        mu_assert(edge_msg, !strcmp(g.e[i].v_b, expected_edges[i][1]));
    }

    return 0;
}

static char const * test_shortest_paths() {
    graph g = init_graph("test_cases/test.txt");

    char const * fail_msg = "FAILURE: test_shortest_paths";

    int* paths_AA = shortest_paths(g, "AA");
    int expected_AA[10] = {0, 1, 2, 1, 2, 3, 4, 5, 1, 2};
    for (int i = 0; i < g.v_len; i++) {
        mu_assert(fail_msg, paths_AA[i] == expected_AA[i]);
    }

    return 0;
}

static char const * test_build_dist_matrix() {
    graph g = init_graph("test_cases/test.txt");
    dist_matrix dm = build_dist_matrix(g);

    char const * fail_msg = "FAILURE: test_build_dist_matrix";
    int expected[7][7] = {
        {0, 1, 2, 1, 2, 5, 2},
        {1, 0, 1, 2, 3, 6, 3},
        {2, 1, 0, 1, 2, 5, 4},
        {1, 2, 1, 0, 1, 4, 3},
        {2, 3, 2, 1, 0, 3, 4},
        {5, 6, 5, 4, 3, 0, 7},
        {2, 3, 4, 3, 4, 7, 0}
    };

    mu_assert(fail_msg, dm.size == 7);
    mu_assert(fail_msg, dm.start == 0);
    for (int i = 0; i < dm.size; i++) {
        for (int j = 0; j < dm.size; j++) {
            mu_assert(fail_msg, dm.matrix[i][j] == expected[i][j]);
        }
    }

    return 0;
}

static char const * test_max_flow_base() {
    graph g = init_graph("test_cases/test.txt");
    dist_matrix dm = build_dist_matrix(g);
    int** dists = dm.matrix;
    int* flow = malloc(sizeof(int) * dm.size);
    int location = dm.start;
    int* remaining = malloc(sizeof(int) * dm.size - 1);
    short* memo = maxflow_hashtable_init(30, dm.size);

    int j = 0;
    for (int i = 0; i < g.v_len; i++) {
        if (!strcmp(g.v[i].name, "AA") || g.v[i].flow > 0) {
            flow[j++] = g.v[i].flow;
        }
    }
    remaining[0] = 1;
    remaining[1] = 2;

    int max = max_flow(0, dists, flow, dm.size, &memo, location, remaining, 2);
    char const * fail_msg = "FAILURE: test_max_flow_base";
    mu_assert(fail_msg, max == 416);

    return 0;
}

static char const * test_max_flow() {
    graph g = init_graph("test_cases/test.txt");
    dist_matrix dm = build_dist_matrix(g);
    int** dists = dm.matrix;
    int* flow = malloc(sizeof(int) * dm.size);
    int location = dm.start;
    int* remaining = malloc(sizeof(int) * dm.size - 1);
    short* memo = maxflow_hashtable_init(30, dm.size);

    int j = 0;
    for (int i = 0; i < g.v_len; i++) {
        if (!strcmp(g.v[i].name, "AA") || g.v[i].flow > 0) {
            flow[j++] = g.v[i].flow;
        }
    }
    
    int k = 0;
    for (j = 0; j < dm.size; j++) {
        if (j != dm.start) {
            remaining[k++] = j;
        }
    }

    int max = max_flow(0, dists, flow, dm.size, &memo, location, remaining, dm.size - 1);

    char const * fail_msg = "FAILURE: test_max_flow";
    mu_assert(fail_msg, max == 1651);

    return 0;
}

static char const * test_parttwo_hashcalc() {
    int remaining_len = 2;
    int *remaining = malloc(sizeof(int) * remaining_len);
    for (int i = 0; i < remaining_len; i++) {
        remaining[i] = 2 * (i + 1); 
    }

    long hash = parttwo_hashcalc(remaining, remaining_len);

    long expected = 4 + 16;
    char const * fail_msg = "FAILURE: test_parttwo_hashcalc";
    mu_assert(fail_msg, expected == hash);

    return 0;
}

static char const * test_maxflow_hashcalc() {
    int remaining_len = 2;
    int *remaining = malloc(sizeof(int) * remaining_len);
    for (int i = 0; i < remaining_len; i++) {
        remaining[i] = i * 2; 
    }
    int time_elapsed = 12;
    int flow_len = 4;
    int location = 3;

    long hash = maxflow_hashcalc(time_elapsed, flow_len, location, remaining, remaining_len);

    long expected = 1 + 4 + 16 + 32 + 256 + 512;
    char const * fail_msg = "FAILURE: test_calculate_hash";
    mu_assert(fail_msg, expected == hash);

    return 0;
}

static char const * test_parttwo_hashtable_init() {
    short *s = parttwo_hashtable_init(4);

    long max_address = (1 + 2 + 4 + 8) + 1;

    char const * fail_msg = "FAILURE: test_maxflow_hashtable_init";
    for (long i = 0; i < max_address; i++) {
        mu_assert(fail_msg, s[i] == -1);
    }

    free(s);
    return 0;
}

static char const * test_maxflow_hashtable_init() {
    short *s = maxflow_hashtable_init(30, 4);

    long max_address = (1 + 2 + 4 + 8 + 16 + 32 + 128 + 256 + 512 + 1024) + 1;

    char const * fail_msg = "FAILURE: test_maxflow_hashtable_init";
    for (long i = 0; i < max_address; i++) {
        mu_assert(fail_msg, s[i] == -1);
    }

    free(s);
    return 0;
}

static char const * test_part_two() {
    graph g = init_graph("test_cases/test.txt");
    dist_matrix dm = build_dist_matrix(g);
    int** dists = dm.matrix;
    int* flow = malloc(sizeof(int) * dm.size);
    int location = dm.start;
    int* remaining = malloc(sizeof(int) * dm.size - 1);
    short* flow_memo = maxflow_hashtable_init(30, dm.size);
    short* two_memo = parttwo_hashtable_init(dm.size);

    int j = 0;
    for (int i = 0; i < g.v_len; i++) {
        if (!strcmp(g.v[i].name, "AA") || g.v[i].flow > 0) {
            flow[j++] = g.v[i].flow;
        }
    }
    
    int k = 0;
    for (j = 0; j < dm.size; j++) {
        if (j != dm.start) {
            remaining[k++] = j;
        }
    }

    clock_t start = clock();    
    int max = part_two(dists, flow, dm.size, &flow_memo, &two_memo, location, remaining, dm.size - 1);
    clock_t end = clock();

    printf("Execution time: %fus\n", ((end - start) / (double)CLOCKS_PER_SEC) * 1000000.0);
    char const * fail_msg = "FAILURE: test_part_two";
    mu_assert(fail_msg, max == 1707);

    return 0;
}

static char const * all_tests() {
    mu_run_test(test_init_graph);
    mu_run_test(test_shortest_paths);
    mu_run_test(test_build_dist_matrix);
    mu_run_test(test_max_flow_base);
    mu_run_test(test_max_flow);
    mu_run_test(test_part_two);
    mu_run_test(test_maxflow_hashcalc);
    mu_run_test(test_maxflow_hashtable_init);
    mu_run_test(test_parttwo_hashcalc);
    mu_run_test(test_parttwo_hashtable_init);

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

