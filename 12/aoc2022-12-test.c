#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include "aoc2022-12.h"

int tests_run = 0;

static char const * test_get_matrix_bounds() {
    int* dims = get_matrix_bounds("test_cases/test.txt");
    char const * failure_msg = "FAILURE: test_get_matrix_bounds";
    mu_assert(failure_msg, (dims[0] == 8 && dims[1] == 5));

    free(dims);
    return 0;
}

static char const * test_coords_list() {
    coords** test_list = init_coords_list(8, 5);
    int max_size = 40;
    char const * init_msg = "FAILURE: test_init_coords_list";
    for (int i = 0; i < 40; i++) {
        mu_assert(init_msg, test_list[i]->x == -1 && test_list[i]->y == -1);
    }

    coords test_coords[3];
    for (int i = 0; i < 3; i++) {
        test_coords[i].x = i;
        test_coords[i].y = i;
        insert_coords_list(test_list, &test_coords[i], max_size);
    }

    coords test_search;
    test_search.x = 1;
    test_search.y = 1;
    coords miss_search;
    miss_search.x = 10;
    miss_search.y = 10;
    char const * search_msg = "FAILURE: test_init_coords__search";
    mu_assert(search_msg, search_coords_list(test_list, &test_search, max_size) == 1);
    mu_assert(search_msg, search_coords_list(test_list, &miss_search, max_size) == -1);

    remove_coords_list(test_list, &test_coords[1], max_size);

    int expected[3][2] = {
        {0, 0},
        {2, 2},
        {-1, -1}
    };
    char const * operations_msg = "FAILURE: test_coords_list__operations";
    for (int i = 0; i < 3; i++) {
        int x = test_list[i]->x;
        int y = test_list[i]->y;
        mu_assert(operations_msg, x == expected[i][0] && y == expected[i][1]);
    }

    return 0;
}

static char const * test_init_heightmap() {
    int** map = init_heightmap("test_cases/test.txt", 8, 5);
    int expected[5][8] = {
        {0, 0, 1, 16, 15, 14, 13, 12},
        {0, 1, 2, 17, 24, 23, 23, 11},
        {0, 2, 2, 18, 25, 25, 23, 10},
        {0, 2, 2, 19, 20, 21, 22, 9},
        {0, 1, 3, 4, 5, 6, 7, 8}
    };

    char const * failure_msg = "FAILURE: test_init_heightmap";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 8; j++) {
            mu_assert(failure_msg, map[i][j] == expected[i][j]);
        }
    }

    return 0;
}

static char const * test_get_waypoints() {
    coords** waypoints = get_waypoints("test_cases/test.txt");
    char const * failure_msg = "FAILURE: test_get_waypoints";
    mu_assert(failure_msg, waypoints[0]->x == 0 && waypoints[0]->y == 0);
    mu_assert(failure_msg, waypoints[1]->x == 5 && waypoints[1]->y == 2);

    return 0;
}

static char const * test_get_closest_candidate() {
    coords** candidates = init_coords_list(3, 3);
    int** distances = malloc(sizeof(int *) * 3);
    for (int i = 0; i < 3; i++) {
        distances[i] = malloc(sizeof(int) * 3);
    }

    int raw_coords[4][2] = { {0, 1}, {1, 0}, {1, 2}, {2, 1} };
    int raw_dists[4] = {5, 2, 3, 4};
    for (int i = 0; i < 4; i++) {
        distances[raw_coords[i][0]][raw_coords[i][1]] = raw_dists[i];
        coords* c = malloc(sizeof(coords));
        c->x = raw_coords[i][1];
        c->y = raw_coords[i][0];
        insert_coords_list(candidates, c, 9);
    }

    coords* closest = get_closest_candidate(candidates, distances, 9);

    char const * failure_msg = "FAILURE: test_get_closest_candidate";
    mu_assert(failure_msg, closest->y == 1 && closest->x == 0);

    return 0;
}

static char const * test_traversible_not_visited() {
    coords** visited = init_coords_list(3, 3);
    coords** test_coords = malloc(sizeof(coords *) * 8);
    int raw_coords[8][2] = { {0, 0}, {0, 1}, {0, 2}, {1, 1}, {-1, 0}, {0, -1}, {4, 0}, {0, 4} };
    for (int i = 0; i < 8; i++) {
        test_coords[i] = malloc(sizeof(coords));
        test_coords[i]->x = raw_coords[i][1];
        test_coords[i]->y = raw_coords[i][0];
    }
    insert_coords_list(visited, test_coords[0], 9);

    int** heightmap = malloc(sizeof(int *) * 3);
    for (int i = 0; i < 3; i++) {
        heightmap[i] = malloc(sizeof(int) * 3);
    }
    heightmap[0][0] = 0;
    heightmap[0][1] = 10;
    heightmap[0][2] = 12;
    heightmap[1][1] = 0;

    coords* src = test_coords[1];
    char const * bound_msg = "FAILURE: test_traversible_not_visited__bounds";
    for (int i = 4; i < 8; i++) {
        mu_assert(bound_msg, !traversible_not_visited(visited, src, test_coords[i], heightmap, 3, 3));
        mu_assert(bound_msg, !traversible_not_visited(visited, test_coords[i], src, heightmap, 3, 3));
    }
    char const * visited_msg = "FAILURE: test_traversible_not_visited__visited";
    mu_assert(visited_msg, !traversible_not_visited(visited, src, test_coords[0], heightmap, 3, 3));
    char const * high_msg = "FAILURE: test_traversible_not_visited__high";
    mu_assert(high_msg, !traversible_not_visited(visited, src, test_coords[2], heightmap, 3, 3));
    char const * failure_msg = "FAILURE: test_traversible_not_visited";
    mu_assert(failure_msg, traversible_not_visited(visited, src, test_coords[3], heightmap, 3, 3));

    return 0;
}

static char const * test_shortest_path() {
    char const * failure_msg = "FAILURE: test_shortest_path";
    mu_assert(failure_msg, shortest_path("test_cases/test.txt", 0) == 31);
    mu_assert(failure_msg, shortest_path("test_cases/test.txt", 1) == 29);

    return 0;
}

static char const * all_tests() {
    mu_run_test(test_get_matrix_bounds);
    mu_run_test(test_coords_list);
    mu_run_test(test_init_heightmap);
    mu_run_test(test_get_waypoints);
    mu_run_test(test_get_closest_candidate);
    mu_run_test(test_traversible_not_visited);
    mu_run_test(test_shortest_path);

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

