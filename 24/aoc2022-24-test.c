#include <stdio.h>
#include <stdlib.h>
#include "../minunit.h"
#include "aoc2022-24.h"

int tests_run = 0;

static const char* assert_blizzards_equal(const char* fail_msg, blizzard* list, int** params, int len) {
    blizzard* l = list;
    int i = 0;
    while (l != NULL) {
        mu_assert(fail_msg, 
                l->position != NULL &&
                l->position[0] == params[i][0] &&
                l->position[1] == params[i][1]);
        mu_assert(fail_msg,
                l->direction != NULL &&
                l->direction[0] == params[i][2] &&
                l->direction[1] == params[i][3]);
        l = l->next;
        i++;
    }
    mu_assert(fail_msg, i == len);

    return 0;
}

void free_int_matrix(int*** mat, int rows) {
    int** m = *mat;
    for (int i = 0; i < rows; i++) {
        free(m[i]);
    }
    free(m);
}

static const char* test_parse_input() {
    valley v = parse_input("test_cases/small.txt");

    const char* blizzard_msg = "FAILURE: test_parse_input__blizzard";
    int expected_blizzards[2][4] = {
        { 4, 4, 1, 0 },
        { 2, 1, 0, 1 }
    };
    int b_len = 2;

    int** b_params = malloc(sizeof(int *) * 2);
    for (int i = 0; i < 2; i++) {
        b_params[i] = malloc(sizeof(int) * 4);
        for (int j = 0; j < 4; j++) {
            b_params[i][j] = expected_blizzards[i][j];
        }
    }
    const char* b_msg = assert_blizzards_equal(blizzard_msg, v.blizzard_list, b_params, b_len);
    free_int_matrix(&b_params, 2);
    if (b_msg != 0) {
        return b_msg;
    }

    const char* map_msg = "FAILURE: test_parse_input__map";
    map *m = v.map;
    mu_assert(map_msg, m->rows == 7);
    mu_assert(map_msg, m->cols == 7);
    mu_assert(map_msg, m->entrance[0] == 0 && m->entrance[1] == 1);
    mu_assert(map_msg, m->exit[0] == 6 && m->exit[1] == 5);
    int spaces[7][7] = {
        {-1,0,-1,-1,-1,-1,-1},
        {-1,0,0,0,0,0,-1},
        {-1,1,0,0,0,0,-1},
        {-1,0,0,0,0,0,-1},
        {-1,0,0,0,1,0,-1},
        {-1,0,0,0,0,0,-1},
        {-1,-1,-1,-1,-1,0,-1},
    };
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            mu_assert(map_msg, m->spaces[i][j] == spaces[i][j]);
        }
    }

    free_valley(&v);
    return 0;
}

static const char* test_move_blizzards() {
    valley v = parse_input("test_cases/small.txt");

    int blizzard_params[5][2][4] = {
        {{ 5, 4, 1, 0 }, { 2, 2, 0, 1 }},
        {{ 1, 4, 1, 0 }, { 2, 3, 0, 1 }},
        {{ 2, 4, 1, 0 }, { 2, 4, 0, 1 }},
        {{ 3, 4, 1, 0 }, { 2, 5, 0, 1 }},
        {{ 4, 4, 1, 0 }, { 2, 1, 0, 1 }}
    };
    int num_blizzards = 2;
    int map_params[5][4][3] = {
        {{ 2, 1, 0 }, { 2, 2, 1 }, { 4, 4, 0 }, { 5, 4, 1 }},
        {{ 2, 2, 0 }, { 2, 3, 1 }, { 5, 4, 0 }, { 1, 4, 1 }},
        {{ 2, 3, 0 }, { 2, 4, 2 }, { 1, 4, 0 }, { 2, 4, 2 }},
        {{ 2, 4, 0 }, { 2, 5, 1 }, { 2, 4, 0 }, { 3, 4, 1 }},
        {{ 2, 5, 0 }, { 2, 1, 1 }, { 3, 4, 0 }, { 4, 4, 1 }}
    };
    const char* blizzard_msg = "FAILURE: test_move_blizzards__blizzard";
    const char* map_msg = "FAILURE: test_move_blizzards__map";
    for (int i = 0; i < 5; i++) {
        move_blizzards(&v);

        int** b_params = malloc(sizeof(int *) * 2);
        for (int j = 0; j < 2; j++) {
            b_params[j] = malloc(sizeof(int) * 4);
            for (int k = 0; k < 4; k++) {
                b_params[j][k] = blizzard_params[i][j][k];
            }
        }
        const char* b_msg = assert_blizzards_equal(blizzard_msg, v.blizzard_list, b_params, num_blizzards);
        free_int_matrix(&b_params, 2);
        if (b_msg != 0) {
            return b_msg;
        }

        for (int j = 0; j < 4; j++) {
            int* params = map_params[i][j];
            mu_assert(map_msg, v.map->spaces[params[0]][params[1]] == params[2]);
        }

    }

    free_valley(&v);
    return 0;
}

static const char* test_vector_set() {
    vector_set vs = init_vector_set();

    const char* init_msg = "FAILURE: test_vector_set__init";
    mu_assert(init_msg, vs.length == 0);
    for (int i = 0; i < VECTOR_SET_LENGTH; i++) {
        mu_assert(init_msg, vs.items[i][0] == -1 && vs.items[i][1] == -1);
    }

    const char* search_msg = "FAILURE: test_vector_set__push";
    mu_assert(search_msg, !search_vector_set(&vs, 1, 1));

    push_vector_set(&vs, 1, 1);
    push_vector_set(&vs, 2, 2);
    push_vector_set(&vs, 3, 3);
    push_vector_set(&vs, 2, 2);
    const char* push_msg = "FAILURE: test_vector_set__push";
    mu_assert(push_msg, vs.length == 3);
    for (int i = 0; i < vs.length; i++) {
        mu_assert(push_msg, vs.items[i][0] == i + 1 && vs.items[i][1] == i + 1);
    }
    mu_assert(search_msg, search_vector_set(&vs, 1, 1));

    pop_vector_set(&vs, 1);
    const char* pop_msg = "FAILURE: test_vector_set__pop";
    mu_assert(pop_msg, vs.length == 2);
    mu_assert(pop_msg, vs.items[0][0] == 1 && vs.items[0][1] == 1);
    mu_assert(pop_msg, vs.items[1][0] == 3 && vs.items[1][1] == 3);

    return 0;
}

static const char* test_take_step() {
    valley v = parse_input("test_cases/test.txt");
    vector_set vs = init_vector_set();
    push_vector_set(&vs, v.map->entrance[0], v.map->entrance[1]);
    const char* init_msg = "FAILURE: test_take_step__init";
    mu_assert(init_msg, vs.length == 1);
    mu_assert(init_msg, vs.items[0][0] == 0 && vs.items[0][1] == 1);

    short optimal_positions[18][2] = {
        { 1, 1 }, { 2, 1 }, { 2, 1 }, { 1, 1 }, { 1, 2 }, { 1, 3 },
        { 2, 3 }, { 2, 2 }, { 1, 2 }, { 1, 3 }, { 1, 3 }, { 2, 3 },
        { 3, 3 }, { 3, 4 }, { 3, 5 }, { 3, 6 }, { 4, 6 }, { 5, 6 }
    };
    const char* fail_msg = "FAILURE: test_take_step";
    for (int i = 0; i < 18; i++) {
        take_step(&v, &vs);
        mu_assert(fail_msg, search_vector_set(&vs, optimal_positions[i][0], optimal_positions[i][1]));
    }

    free_valley(&v);
    return 0;
}

static const char* test_traverse_valley() {
    valley v = parse_input("test_cases/test.txt");

    const char* fail_msg = "FAILURE: test_traverse_valley";
    mu_assert(fail_msg, traverse_valley(&v) == 18);

    free_valley(&v);
    return 0;
}

static const char* test_backtrack_valley() {
    valley v = parse_input("test_cases/test.txt");

    const char* setup_msg = "FAILURE: test_backtrack_valley__setup";
    mu_assert(setup_msg, traverse_valley(&v) == 18);

    const char* backtrack_msg = "FAILURE: test_backtrack_valley";
    mu_assert(backtrack_msg, backtrack_valley(&v) == 23);

    const char* return_msg = "FAILURE: test_backtrack_valley__return";
    mu_assert(return_msg, traverse_valley(&v) == 13);

    free_valley(&v);
    return 0;
}

static const char* all_tests() {
    mu_run_test(test_parse_input);
    mu_run_test(test_move_blizzards);
    mu_run_test(test_vector_set);
    mu_run_test(test_take_step);
    mu_run_test(test_traverse_valley);
    mu_run_test(test_backtrack_valley);

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

