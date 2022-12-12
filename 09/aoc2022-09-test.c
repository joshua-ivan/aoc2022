#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include "aoc2022-09.h"

int tests_run = 0;

static char const * test_move_head() {
    char directions[4] = {'U', 'L', 'R', 'D'};
    int expected[4][2] = { {0, 1}, {-1, 0}, {1, 0}, {0, -1} };
    char const * failure_msg = "FAILURE: test_move_head";
    for (int i = 0; i < 4; i++) {
        coords c;
        c.x = 0;
        c.y = 0;
        move_head(&c, directions[i]);
        mu_assert(failure_msg, c.x == expected[i][0] && c.y == expected[i][1]);
    }
    return 0;
}

static char const * test_move_tail() {
    coords head;
    head.x = 0;
    head.y = 0;

    char const * touching_msg = "FAILURE: test_move_tail__touching";
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            coords tail;
            tail.x = x;
            tail.y = y;
            move_tail(&head, &tail);
            mu_assert(touching_msg, (tail.x == x && tail.y == y));
        }
    }

    int straight_tail_coords[4][2] = { {0, -2}, {2, 0}, {-2, 0}, {0, 2} };
    int straight_expected[4][2] = { {0, -1}, {1, 0}, {-1, 0}, {0, 1} };
    char const * straight_msg = "FAILURE: test_move_tail__straight";
    for (int i = 0; i < 4; i++) {
        coords tail;
        tail.x = straight_tail_coords[i][0];
        tail.y = straight_tail_coords[i][1];
        move_tail(&head, &tail);
        mu_assert(straight_msg, (tail.x == straight_expected[i][0] && tail.y == straight_expected[i][1]));
    }

    int diagonal_tail_coords[8][2] = {
        {2, -1}, {1, -2}, {-1, -2}, {-2, -1},
        {-2, 1}, {-1, 2}, {1, 2}, {2, 1}
    };
    int diagonal_expected[8][2] = {
        {1, 0}, {0, -1}, {0, -1}, {-1, 0},
        {-1, 0}, {0, 1}, {0, 1}, {1, 0}
    };
    char const * diagonal_msg = "FAILURE: test_move_tail__diagonal";
    for (int i = 0; i < 8; i++) {
        coords tail;
        tail.x = diagonal_tail_coords[i][0];
        tail.y = diagonal_tail_coords[i][1];
        move_tail(&head, &tail);
        mu_assert(diagonal_msg, (tail.x == diagonal_expected[i][0] && tail.y == diagonal_expected[i][1]));
    }

    return 0;
}

static char const * test_append_position_list() {
    coords **list = malloc(sizeof(coords *) * 1024);
    for (int i = 0; i < 1024; i++) {
        list[i] = NULL;
    }

    int test_coords[4][2] = { {0, 0}, {0, 1}, {0, 1}, {1, 0} };
    for (int i = 0; i < 4; i++) {
        coords *c = malloc(sizeof(coords));
        c->x = test_coords[i][0];
        c->y = test_coords[i][1];
        append_position_list(list, c);
    }

    int len = -1;

    while (list[++len] != NULL) ;

    char const * list_len_msg = "FAILURE: test_append_position_list__list_len";
    mu_assert(list_len_msg, len == 3);

    int expected_coords[3][2] = { {0, 0}, {0, 1}, {1, 0} };
    char const * coords_msg = "FAILURE: test_append_position_list__coords";
    for (int i = 0; i < 3; i++) {
        mu_assert(coords_msg, list[i]->x == expected_coords[i][0] && list[i]->y == expected_coords[i][1]);
    }

    for (int i = 0; i < len; i++) {
        free(list[i]);
    }
    free(list);
    return 0;
}

static char const * test_count_positions_one() {
    char const * failure_msg = "FAILURE: test_count_positions";
    mu_assert(failure_msg, count_positions_one("test_cases/test.txt") == 13);

    return 0;
}

static char const * test_count_positions_two() {
    char const * failure_msg = "FAILURE: test_count_positions";
    mu_assert(failure_msg, count_positions_two("test_cases/test.txt") == 1);
    mu_assert(failure_msg, count_positions_two("test_cases/larger.txt") == 36);

    return 0;
}

static char const * all_tests() {
    mu_run_test(test_move_head);
    mu_run_test(test_move_tail);
    mu_run_test(test_append_position_list);
    mu_run_test(test_count_positions_one);
    mu_run_test(test_count_positions_two);

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

