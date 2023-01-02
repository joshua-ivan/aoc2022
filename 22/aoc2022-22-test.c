#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../minunit.h"
#include "aoc2022-22.h"

int tests_run = 0;

static const char* test_parse_input() {
    board b = parse_input("test_cases/test.txt");

    const char* test_msg = "FAILURE: test_parse_input__expected_map";
    FILE* expected_map = fopen("test_cases/expected_map.txt", "r");
    mu_assert(test_msg, expected_map != NULL);

    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    const char* bounds_msg = "FAILURE: test_parse_input__bounds";
    mu_assert(bounds_msg, b.num_rows == 14); 
    mu_assert(bounds_msg, b.num_cols == 18); 
    const char* map_msg = "FAILURE: test_parse_input__map";
    for (int i = 0; i < b.num_rows; i++) {
        read = getline(&line, &length, expected_map);
        char* newline = strchr(line, '\n');
        newline[0] = '\0';
        mu_assert(test_msg, read != -1); 
        mu_assert(map_msg, !strcmp(b.map[i], line));
    }

    const char* dirs_msg = "FAILURE: test_parse_input__directions";
    char* expected_directions = "10R5L5R10L4R5L5";
    mu_assert(dirs_msg, !strcmp(b.directions, expected_directions));

    const char* avatar_msg = "FAILURE: test_parse_input__avatar";
    mu_assert(avatar_msg, b.avatar_row == 1 && b.avatar_col == 9 && b.facing == 'R');

    free(line);
    fclose(expected_map);
    free_board(b);
    return 0;
}

static const char* test_move_avatar() {
    board b = parse_input("test_cases/test.txt");
    char dirs[4] = { 'R', 'D', 'L', 'U' };

    const char* fail_msg = "FAILURE: test_move_avatar";
    const char* wall_msg = "FAILURE: test_move_avatar__wall";
    int normal_coords[4][2] = { { 1, 9 }, { 5, 11 }, { 7, 11 }, { 9, 9 } };
    int expected_normal[4][2] = { { 1, 11 }, { 7, 11 }, { 7, 9 }, { 7, 9 } };
    for (int i = 0; i < 4; i++) {
        b.avatar_row = normal_coords[i][0];
        b.avatar_col = normal_coords[i][1];
        b.facing = dirs[i];
        move_avatar(&b, 2, NULL);
        mu_assert(fail_msg, b.avatar_row == expected_normal[i][0]);
        mu_assert(fail_msg, b.avatar_col == expected_normal[i][1]);
        move_avatar(&b, 1, NULL);
        mu_assert(wall_msg, b.avatar_row == expected_normal[i][0]);
        mu_assert(wall_msg, b.avatar_col == expected_normal[i][1]);
    }

    const char* wrap_msg = "FAILURE: test_move_avatar__wrap";
    int wrap_coords[4][2] = { { 2, 12 }, { 12, 9 }, { 4, 9 }, { 5, 5 } };
    int expected_wrap[4][2] = { { 2, 9 }, { 1, 9 }, { 4, 12 }, { 8, 5 } };
    for (int i = 0; i < 4; i++) {
        b.avatar_row = wrap_coords[i][0];
        b.avatar_col = wrap_coords[i][1];
        b.facing = dirs[i];
        move_avatar(&b, 1, NULL);
        mu_assert(wrap_msg, b.avatar_row == expected_wrap[i][0]);
        mu_assert(wrap_msg, b.avatar_col == expected_wrap[i][1]);
    }

    const char* wrap_wall_msg = "FAILURE: test_move_avatar__wrap_wall";
    int wrap_wall_coords[4][2] = { { 3, 12 }, { 12, 12 }, { 5, 1 }, { 9, 15} };
    for (int i = 0; i < 4; i++) {
        b.avatar_row = wrap_wall_coords[i][0];
        b.avatar_col = wrap_wall_coords[i][1];
        b.facing = dirs[i];
        move_avatar(&b, 1, NULL);
        mu_assert(wrap_wall_msg, b.avatar_row == wrap_wall_coords[i][0]);
        mu_assert(wrap_wall_msg, b.avatar_col == wrap_wall_coords[i][1]);
    }

    free_board(b);
    return 0;
}

static const char* test_turn_avatar() {
    board b = parse_input("test_cases/test.txt");

    char clockwise_dirs[4] = { 'D', 'L', 'U', 'R' };
    const char* clockwise_msg = "FAILURE: test_turn_avatar__clockwise";
    for (int i = 0; i < 4; i++) {
        turn_avatar(&b, 'R');
        mu_assert(clockwise_msg, b.facing == clockwise_dirs[i]);
    }

    char counterwise_dirs[4] = { 'U', 'L', 'D', 'R' };
    const char* counterwise_msg = "FAILURE: test_turn_avatar__counterwise";
    for (int i = 0; i < 4; i++) {
        turn_avatar(&b, 'L');
        mu_assert(counterwise_msg, b.facing == counterwise_dirs[i]);
    }

    free_board(b);
    return 0;
}

static const char* test_run_directions() {
    board b = parse_input("test_cases/test.txt");
    run_directions(&b, NULL);
    const char* fail_msg = "FAILURE: test_run_directions";
    mu_assert(fail_msg, b.avatar_row == 6 && b.avatar_col == 8 && b.facing == 'R');

    free_board(b);
    return 0;
}

static const char* test_calc_pass() {
    board b = parse_input("test_cases/test.txt");

    const char* fail_msg = "FAILURE: test_calc_pass";
    for (int i = 0; i < 4; i++) {
        mu_assert(fail_msg, calc_pass(&b) == ((1000 * 1) + (4 * 9) + i));
        turn_avatar(&b, 'R');
    }

    run_directions(&b, NULL);
    mu_assert(fail_msg, calc_pass(&b) == ((1000 * 6) + (4 * 8) + 0));

    free_board(b);
    return 0;
}

static const char* test_load_cube() {
    cube c = load_cube("test_cases/cube.txt");
    int expected[14][9] = {
        { 1, 9, 4, 9, 5, 5, 5, 8, -1 }, 
        { 5, 5, 5, 8, 1, 9, 4, 9, 1 }, 
        { 8, 5, 8, 8, 12, 9, 9, 9, -1 }, 
        { 12, 9, 9, 9, 8, 5, 8, 8, 1 }, 
        { 5, 12, 8, 12, 9, 16, 9, 13, 1 }, 
        { 9, 16, 9, 13, 5, 12, 8, 12, -1 }, 
        { 1, 9, 1, 12, 5, 4, 5, 1, -2 },
        { 5, 4, 5, 1, 1, 9, 1, 12, 2 },
        { 1, 12, 4, 12, 12, 16, 9, 16, 2 },
        { 12, 16, 9, 16, 1, 12, 4, 12, -2 },
        { 8, 1, 8, 4, 12, 12, 12, 9, -2 },
        { 12, 12, 12, 9, 8, 1, 8, 4, 2 },
        { 5, 1, 8, 1, 12, 16, 12, 13, -3 },
        { 12, 16, 12, 13, 5, 1, 8, 1, 3 }
    };

    const char* fail_msg = "FAILURE: test_load_cube";
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 9; j++) {
            mu_assert(fail_msg, c.edges[i][j] == expected[i][j]);
        }
    }

    return 0;
}

static const char* test_is_along_edge() {
    cube c = load_cube("test_cases/cube.txt");

    int test_params[16][4] = {
        { 0, 1, 9, 1 }, { 0, 4, 9, 1 },
        { 0, 0, 9, 0 }, { 0, 5, 9, 0 },

        { 1, 5, 5, 1 }, { 1, 5, 8, 1 },
        { 1, 5, 4, 0 }, { 1, 5, 9, 0 },

        { 3, 12, 9, 1 }, { 3, 9, 9, 1 },
        { 3, 13, 9, 0 }, { 3, 8, 9, 0 },

        { 5, 9, 16, 1 }, { 5, 9, 13, 1 },
        { 5, 9, 17, 0 }, { 5, 9, 12, 0 }
    };

    const char* fail_msg = "FAILURE: test_is_along_edge";
    for (int i = 0; i < 16; i++) {
        mu_assert(fail_msg,
            is_along_edge(
                c.edges[test_params[i][0]], test_params[i][1], test_params[i][2])
                == test_params[i][3]);
    }

    return 0;
}

static const char* test_calc_dest_offset() {
    cube c = load_cube("test_cases/cube.txt");

    int test_params[8][4] = {
        { 0, 1, 9, 0 }, { 0, 4, 9, 3 },
        { 1, 5, 5, 0 }, { 1, 5, 8, 3 },
        { 3, 12, 9, 0 }, { 3, 9, 9, 3 },
        { 5, 9, 16, 0 }, { 5, 9, 13, 3 }
    };

    const char* fail_msg = "FAILURE: test_calc_dest_offset";
    for (int i = 0; i < 8; i++) {
        mu_assert(fail_msg,
            calc_dest_offset(
                c.edges[test_params[i][0]], test_params[i][1], test_params[i][2])
                == test_params[i][3]);
    }

    return 0;
}

static const char* test_transform_coordinates() {
    cube c = load_cube("test_cases/cube.txt");
    char test_facing[14][2] = {
        { 'L', 'D' }, { 'U', 'R' },
        { 'D', 'R' }, { 'L', 'U' },
        { 'R', 'D' }, { 'U', 'L' },
        { 'U', 'D' }, { 'U', 'D' },
        { 'R', 'L' }, { 'R', 'L' },
        { 'D', 'U' }, { 'D', 'U' },
        { 'L', 'U' }, { 'D', 'R' }
    };

    int edge_size = 4;
    const char* fail_msg = "FAILURE: test_transform_coordinates";
    for (int i = 0; i < CUBE_MATRIX_ROWS; i++) {
        int is_horizontal = c.edges[i][4] == c.edges[i][6];
        int is_vertical = c.edges[i][5] == c.edges[i][7];
        mu_assert(fail_msg, is_horizontal || is_vertical);

        int count_up = (is_horizontal && c.edges[i][5] < c.edges[i][7])
                || (is_vertical && c.edges[i][4] < c.edges[i][6]);
        int count_down = (is_horizontal && c.edges[i][7] < c.edges[i][5])
                || (is_vertical && c.edges[i][6] < c.edges[i][4]);
        mu_assert(fail_msg, count_up || count_down);

        for (int j = 0; j < edge_size; j++) {
            int* coords = get_destination(c.edges[i], j, test_facing[i][0]);
            if (is_horizontal) {
                int expected = (count_up) ? c.edges[i][5] + j : c.edges[i][5] - j;
                mu_assert(fail_msg, coords[0] == c.edges[i][4] && coords[1] == expected && coords[2] == test_facing[i][1]);
            } else {
                int expected = (count_up) ? c.edges[i][4] + j : c.edges[i][4] - j;
                mu_assert(fail_msg, coords[0] == expected && coords[1] == c.edges[i][5] && coords[2] == test_facing[i][1]);
            }
            free(coords);
        }
    }

    return 0;
}

static const char* test_traverse_edge() {
    board b = parse_input("test_cases/test.txt");
    cube c = load_cube("test_cases/cube.txt");

    b.avatar_row = 1;
    b.avatar_col = 9;
    b.facing = 'L';
    traverse_edge(&b, &c);

    const char* normal_msg = "FAILURE: test_traverse_edge";
    mu_assert(normal_msg, b.avatar_row == 5 && b.avatar_col == 5 && b.facing == 'D');

    b.avatar_row = 5;
    b.avatar_col = 7;
    b.facing = 'U';
    traverse_edge(&b, &c);

    const char* wall_msg = "FAILURE: test_traverse_edge__wall";
    mu_assert(wall_msg, b.avatar_row == 5 && b.avatar_col == 7 && b.facing == 'U');

    free_board(b);
    return 0;
}


static const char* test_move_cube() {
    board b = parse_input("test_cases/test.txt");
    cube c = load_cube("test_cases/cube.txt");

    b.avatar_row = 4;
    b.avatar_col = 9;
    b.facing = 'L';
    move_avatar(&b, 2, &c);

    const char* fail_msg = "FAILURE: test_move_cube";
    mu_assert(fail_msg, b.avatar_row == 6 && b.avatar_col == 8 && b.facing == 'D');

    free_board(b);
    return 0;
}

static const char* test_cube_directions() {
    board b = parse_input("test_cases/test.txt");
    cube c = load_cube("test_cases/cube.txt");

    run_directions(&b, &c);

    const char* fail_msg = "FAILURE: test_run_directions";
    mu_assert(fail_msg, b.avatar_row == 5 && b.avatar_col == 7 && b.facing == 'U');

    free_board(b);
    return 0;

}

static const char* all_tests() {
    mu_run_test(test_parse_input);
    mu_run_test(test_move_avatar);
    mu_run_test(test_turn_avatar);
    mu_run_test(test_run_directions);
    mu_run_test(test_calc_pass);
    mu_run_test(test_load_cube);
    mu_run_test(test_is_along_edge);
    mu_run_test(test_calc_dest_offset);
    mu_run_test(test_transform_coordinates);
    mu_run_test(test_traverse_edge);
    mu_run_test(test_move_cube);
    mu_run_test(test_cube_directions);

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

