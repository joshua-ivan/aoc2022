#include <stdio.h>
#include <stdlib.h>
#include "../minunit.h"
#include "coords.h"

int tests_run = 0;

static char const * test_coords_list() {
    int max_len = 40;
    coords_list test = init_coords_list(max_len);
    char const * init_msg = "FAILURE: test_init_coords_list";
    for (int i = 0; i < 40; i++) {
        mu_assert(init_msg, test.list[i]->x == -1 && test.list[i]->y == -1);
    }

    coords test_coords[3];
    for (int i = 0; i < 3; i++) {
        test_coords[i].x = i;
        test_coords[i].y = i;
        insert_coords_list(test, &test_coords[i]);
    }

    coords test_search;
    test_search.x = 1;
    test_search.y = 1;
    coords miss_search;
    miss_search.x = 10;
    miss_search.y = 10;
    char const * search_msg = "FAILURE: test_init_coords__search";
    mu_assert(search_msg, search_coords_list(test, &test_search) == 1);
    mu_assert(search_msg, search_coords_list(test, &miss_search) == -1);

    remove_coords_list(test, &test_coords[1]);

    int expected[3][2] = {
        {0, 0},
        {2, 2},
        {-1, -1}
    };
    char const * operations_msg = "FAILURE: test_coords_list__operations";
    for (int i = 0; i < 3; i++) {
        int x = test.list[i]->x;
        int y = test.list[i]->y;
        mu_assert(operations_msg, x == expected[i][0] && y == expected[i][1]);
    }

    return 0;
}

static char const * all_tests() {
    mu_run_test(test_coords_list);

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

