#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../minunit.h"
#include "aoc2022-23.h"

int tests_run = 0;
const int debug_diffuse = 0;

static const char* test_parse_input() {
    grove g = parse_input("test_cases/small.txt");

    const char* fail_msg = "FAILURE: test_parse_input";
    mu_assert(fail_msg, g.rows == 18);
    mu_assert(fail_msg, g.cols == 15);
    mu_assert(fail_msg, g.elves == 5);

    const char* input_msg = "FAILURE: test_parse_input__expected";
    FILE* fp = fopen("test_cases/small__expected.txt", "r");
    mu_assert(input_msg, fp != NULL);

    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    for (int i = 0; i < g.rows; i++) {
        read = getline(&line, &length, fp);
        mu_assert(input_msg, read != -1);

        for (int j = 0; j < g.cols; j++) {
            mu_assert(fail_msg, g.map[i][j] == line[j]);
        }
    }

    free(line);
    fclose(fp);
    free_grove(&g);
    return 0;
}

static const char* test_move_checks() {
    grove g;
    g.rows = 3;
    g.cols = 3;
    g.map = malloc(sizeof(char *) * g.rows);
    for (int i = 0; i < g.rows; i++) {
        g.map[i] = malloc(sizeof(char) * g.cols + 1);
        int j = 0;
        while (j < g.cols) {
            g.map[i][j++] = '.';
        }
        g.map[i][j] = '\0';
    }

    int bounds_checks[5][2] = {
        {-1, 0}, {3, 0}, {0, -1}, {0, 3}, {0, 0}
    };
    const char* bounds_msg = "FAILURE: test_move_checks__bounds";
    int i = 0;
    while (i < 4) {
        mu_assert(bounds_msg, !check_bounds(&g, bounds_checks[i][0], bounds_checks[i][1]));
        i++;
    }
    mu_assert(bounds_msg, check_bounds(&g, bounds_checks[i][0], bounds_checks[i][1]));

    char* test_vectors[4] = {
        "...",
        "#..",
        ".#.",
        "..#"
    };
    int expected[3][4] = {
        { 1, 0, 0, 1 },
        { 1, 0, 0, 0 },
        { 1, 1, 0, 0 }
    };
    const char* row_msg = "FAILURE: test_move_checks__row";
    const char* north_msg = "FAILURE: test_move_checks__north";
    const char* south_msg = "FAILURE: test_move_checks__south";
    const char* col_msg = "FAILURE: test_move_checks__col";
    const char* west_msg = "FAILURE: test_move_checks__west";
    const char* east_msg = "FAILURE: test_move_checks__east";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            strcpy(g.map[0], test_vectors[j]);
            strcpy(g.map[2], test_vectors[j]);

            mu_assert(row_msg, (check_row(&g, 0, i) == expected[i][j]));
            mu_assert(north_msg, (check_north(&g, 1, i) == expected[i][j]));

            mu_assert(row_msg, (check_row(&g, 2, i) == expected[i][j]));
            mu_assert(south_msg, (check_south(&g, 1, i) == expected[i][j]));

            strcpy(g.map[0], test_vectors[0]);
            strcpy(g.map[2], test_vectors[0]);

            for (int k = 0; k < 3; k++) {
                g.map[k][0] = test_vectors[j][k];
                g.map[k][2] = test_vectors[j][k];
            }

            mu_assert(col_msg, (check_col(&g, i, 0) == expected[i][j]));
            mu_assert(west_msg, (check_west(&g, i, 1) == expected[i][j]));

            mu_assert(col_msg, (check_col(&g, i, 2) == expected[i][j]));
            mu_assert(east_msg, (check_east(&g, i, 1) == expected[i][j]));

            for (int k = 0; k < 3; k++) {
                g.map[k][0] = test_vectors[0][k];
                g.map[k][2] = test_vectors[0][k];
            }
        }
    }

    int (*check_fns[4])(grove*,int,int) = {
        check_north, check_south, check_west, check_east
    };
    int border_checks[4][2] = {
        {0, 1}, {2, 1}, {1, 0}, {1, 2}
    };
    const char* borders_msg = "FAILURE: test_move_checks__borders";
    i = 0;
    while (i < 4) {
        mu_assert(borders_msg, !check_fns[i](&g, border_checks[i][0], border_checks[i][1]));
        i++;
    }

    free_grove(&g);
    return 0;
}

static const char* test_check_adjacent() {
    grove g;
    g.rows = 3;
    g.cols = 3;
    g.map = malloc(sizeof(char *) * g.rows);
    for (int i = 0; i < g.rows; i++) {
        g.map[i] = malloc(sizeof(char) * g.cols + 1);
        int j = 0;
        while (j < g.cols) {
            g.map[i][j++] = '.';
        }
        g.map[i][j] = '\0';
    }
    g.map[1][1] = '#';

    const char* fail_msg = "FAILURE: test_check_adjacent";
    mu_assert(fail_msg, check_adjacent(&g, 1, 1));

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 1 && j == 1) {
                continue;
            }

            g.map[i][j] = '#';
            mu_assert(fail_msg, !check_adjacent(&g, 1, 1));
            g.map[i][j] = '.';
        }
    }

    free_grove(&g);
    return 0;
}

static const char* test_init_orders() {
    order* o = init_orders();
    const char* fail_msg = "FAILURE: test_init_orders";
    mu_assert(fail_msg, o != NULL);
    int i = 0;
    int (*expected_fns[4])(grove*,int,int) = {
        check_north, check_south, check_west, check_east
    };
    char *expected_labels[4] = {
        "north", "south", "west", "east"
    };

    order* current = o;
    while (current != NULL) {
        mu_assert(fail_msg, expected_fns[i] == current->fn);
        mu_assert(fail_msg, !strcmp(expected_labels[i++], current->label));
        current = current->next;
    }

    free_orders(o);
    return 0;
}

static const char* test_propose_movements() {
    grove g = parse_input("test_cases/small.txt");
    order* o = init_orders();
    moves m = propose_movements(&g, o);
    int expected[5][4] = {
        { 7, 7, 6, 7 },
        { 7, 8, 6, 8 },
        { 8, 7, 9, 7 },
        { 10, 7, 9, 7 },
        { 10, 8, 9, 8 }
    };

    const char* fail_msg = "FAILURE: test_propose_movements";
    mu_assert(fail_msg, m.list_len == 5);
    mu_assert(fail_msg, m.vect_len == 4);
    for (int i = 0; i < m.list_len; i++) {
        for (int j = 0; j < m.vect_len; j++) {
            mu_assert(fail_msg, expected[i][j] == m.list[i][j]);
        }
    }

    free_moves(&m);
    free_orders(o);
    free_grove(&g);
    return 0;
}

static const char* test_prune_duplicates() {
    grove g = parse_input("test_cases/small.txt");
    order* o = init_orders();
    moves m = propose_movements(&g, o);

    prune_duplicates(&m);
    int expected[5][4] = {
        { 7, 7, 6, 7 },
        { 7, 8, 6, 8 },
        { 8, 7, 8, 7 },
        { 10, 7, 10, 7 },
        { 10, 8, 9, 8 }
    };

    const char* fail_msg = "FAILURE: test_prune_duplicates";
    for (int i = 0; i < m.list_len; i++) {
        for (int j = 0; j < m.vect_len; j++) {
            mu_assert(fail_msg, expected[i][j] == m.list[i][j]);
        }
    }

    free_moves(&m);
    free_orders(o);
    free_grove(&g);
    return 0;
}

static const char* test_move_elves() {
    grove g = parse_input("test_cases/small.txt");
    order* o = init_orders();
    moves m = propose_movements(&g, o);
    prune_duplicates(&m);
    move_elves(&g, &m);

    const char* input_msg = "FAILURE: test_move_elves__expected_move";
    FILE* fp = fopen("test_cases/small__expected_move.txt", "r");
    mu_assert(input_msg, fp != NULL);

    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    const char* fail_msg = "FAILURE: test_move_elves";
    for (int i = 0; i < g.rows; i++) {
        read = getline(&line, &length, fp);
        mu_assert(input_msg, read != -1);

        for (int j = 0; j < g.cols; j++) {
            mu_assert(fail_msg, g.map[i][j] == line[j]);
        }
    }

    free(line);
    fclose(fp);
    free_moves(&m);
    free_orders(o);
    free_grove(&g);
    return 0;
}

static const char* test_update_order() {
    grove g = parse_input("test_cases/small.txt");
    order* o = init_orders();
    moves m = propose_movements(&g, o);

    update_order(&o);
    int (*expected_fns[4])(grove*,int,int) = {
        check_south, check_west, check_east, check_north
    };
    char *expected_labels[4] = {
        "south", "west", "east", "north"
    };
    order* current = o;
    const char* fail_msg = "FAILURE: test_update_order";
    for (int i = 0; i < 4; i++) {
        mu_assert(fail_msg, expected_fns[i] == current->fn);
        mu_assert(fail_msg, !strcmp(expected_labels[i], current->label));
        current = current->next;
    }

    free_moves(&m);
    free_orders(o);
    free_grove(&g);
    return 0;
}

static const char* test_diffusion_complete() {
    grove g = parse_input("test_cases/small.txt");
    order* o = init_orders();

    for (int i = 0; i < 3; i++) {
        moves m = propose_movements(&g, o);
        update_order(&o);
        prune_duplicates(&m);
        move_elves(&g, &m);
        free_moves(&m);
    }

    moves m = propose_movements(&g, o);
    const char* fail_msg = "FAILURE: test_diffusion_complete";
    mu_assert(fail_msg, diffusion_complete(m));

    free_moves(&m);
    free_orders(o);
    free_grove(&g);
    return 0;
}

static const char* test_diffuse() {
    grove g = parse_input("test_cases/test/0.txt");
    order* o = init_orders();

    for (int i = 0; i < 10; i++) {
        diffuse(&g, &o);

        const char* input_msg = "FAILURE: test_diffuse__expected";
        char filename[32];
        sprintf(filename, "test_cases/test/%d.txt", i + 1);
        FILE* fp = fopen(filename, "r");
        if (fp == NULL) {
            continue;
        }

        char *line = NULL;
        size_t length = 0;
        ssize_t read;
        const char* fail_msg = "FAILURE: test_diffuse";
        if (debug_diffuse) printf("== Round %d ==\n", i + 1);
        for (int i = 0; i < g.rows; i++) {
            read = getline(&line, &length, fp);
            mu_assert(input_msg, read != -1);

            for (int j = 0; j < g.cols; j++) {
                if (debug_diffuse) printf("%c", g.map[i][j]);
                mu_assert(fail_msg, g.map[i][j] == line[j]);
            }
            if (debug_diffuse) printf("\n");
        }

        free(line);
        fclose(fp);
    }

    free_orders(o);
    free_grove(&g);
    return 0;
}

static const char* test_align_bounds() {
    grove g = parse_input("test_cases/test/10.txt");
    int* actual = align_bounds(g);

    int expected[4] = { 26, 36, 26, 37 };
    const char* fail_msg = "FAILURE: test_align_bounds";
    for (int i = 0; i < 4; i++) {
        mu_assert(fail_msg, expected[i] == actual[i]);
    }

    free(actual);
    free_grove(&g);
    return 0;
}

static const char* test_count_empty_tiles() {
    grove g = parse_input("test_cases/test/10.txt");
    const char* fail_msg = "FAILURE: test_count_empty_tiles";
    mu_assert(fail_msg, count_empty_tiles(g) == 110);

    free_grove(&g);
    return 0;
}

static const char* test_count_rounds() {
    grove g = parse_input("test_cases/test/0.txt");
    order* o = init_orders();

    int complete = 0;
    int count = 1;
    while (!complete) {
        diffuse(&g, &o);
        moves m = propose_movements(&g, o);
        complete = diffusion_complete(m);
        free_moves(&m);
        count++;
    }

    const char* fail_msg = "FAILURE: test_count_rounds";
    mu_assert(fail_msg, count == 20);

    free_orders(o);
    free_grove(&g);
    return 0;
}

static const char* all_tests() {
    mu_run_test(test_parse_input);
    mu_run_test(test_move_checks);
    mu_run_test(test_init_orders);
    mu_run_test(test_check_adjacent);
    mu_run_test(test_propose_movements);
    mu_run_test(test_prune_duplicates);
    mu_run_test(test_move_elves);
    mu_run_test(test_update_order);
    mu_run_test(test_diffusion_complete);
    mu_run_test(test_diffuse);
    mu_run_test(test_align_bounds);
    mu_run_test(test_count_empty_tiles);
    mu_run_test(test_count_rounds);

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

