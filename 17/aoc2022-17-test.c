#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minunit.h"
#include "aoc2022-17.h"

int tests_run = 0;
const int PRINT_SPAWN_ROCK = 0;
const int PRINT_MOVE_HORI = 0;
const int PRINT_MOVE_WALL = 0;
const int PRINT_MOVE_DOWN = 0;
const int PRINT_MOVE_FLOOR = 0;
const int PRINT_SPAWN_ROCK_OFFSET = 0;
const int PRINT_SIMULATE_WELL = 0;

char** load_expected_block(const char block[7][7]) {
    char **b = malloc(sizeof(char *) * 7);
    for (int i = 0; i < 7; i++) {
        b[i] = malloc(sizeof(char) * 7);
        strncpy(b[i], block[i], 7);
    }
    return b;
}

static char * test_spawn(char **block, char **expected, char *fail_msg) {
    well w = init_well();
    w = spawn_rock(w, block);

    mu_assert(fail_msg, w.anchor_row == 3 && w.anchor_col == 2);
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (PRINT_SPAWN_ROCK) printf("%c", w.well[6 - i][j]);
            mu_assert(fail_msg, w.well[6 - i][j] == expected[i][j]);
        }
        if (PRINT_SPAWN_ROCK) printf("\n");
    }
    if (PRINT_SPAWN_ROCK) printf("-------\n");

    return 0;
}

static char * test_spawn_rock() {
    char **all_blocks[5] = {
        load_block(I_BLOCK),
        load_block(O_BLOCK),
        load_block(J_BLOCK),
        load_block(X_BLOCK),
        load_block(L_BLOCK)
    };
    char **all_expected[5] = {
        load_expected_block(I_BLOCK__EXPECTED),
        load_expected_block(O_BLOCK__EXPECTED),
        load_expected_block(J_BLOCK__EXPECTED),
        load_expected_block(X_BLOCK__EXPECTED),
        load_expected_block(L_BLOCK__EXPECTED)
    };
    char *all_block_names = "iojxl";

    for (int i = 0; i < 5; i++) {
        char *fail_msg = malloc(sizeof(char *) * 64);
        sprintf(fail_msg, "FAILURE: test_spawn_rock__%c_block", all_block_names[i]);
        char *fail = test_spawn(all_blocks[i], all_expected[i], fail_msg);
        if (fail) return fail;
    }

    return 0;
}

static char * test_move(char **block, char **expected, int left_blocked[4][2], int right_blocked[4][2], int num_blocked, char *fail_msg) {
    for (int i = 0; i < num_blocked + 1; i++) {
        well w = init_well();
        w = spawn_rock(w, block);

        if (i > 0) {
            w.well[w.anchor_row + left_blocked[i - 1][0]][w.anchor_col + left_blocked[i - 1][1]] = '#';
        }
        w = move_hori(w, block, -1);
        mu_assert(fail_msg, w.blocked == (i > 0));
        mu_assert(fail_msg, w.anchor_col == 2 - !(i > 0));

        if (i > 0) {
            w.well[w.anchor_row + left_blocked[i - 1][0]][w.anchor_col + left_blocked[i - 1][1]] = '.';
        }
        for (int j = 0; j < 7; j++) {
            for (int k = 0; k < 7; k++) {
                if (PRINT_MOVE_HORI) printf("%c", w.well[6 - j][k]);
                int col = (k + !w.blocked) % 7;
                mu_assert(fail_msg, w.well[6 - j][k] == expected[j][col]);
            }
            if (PRINT_MOVE_HORI) printf("\n");
        }
        if (PRINT_MOVE_HORI) printf("-------\n");
    }

    for (int i = 0; i < num_blocked + 1; i++) {
        well w = init_well();
        w = spawn_rock(w, block);

        if (i > 0) {
            w.well[w.anchor_row + right_blocked[i - 1][0]][w.anchor_col + right_blocked[i - 1][1]] = '#';
        }
        w = move_hori(w, block, 1);
        mu_assert(fail_msg, w.blocked == (i > 0));
        mu_assert(fail_msg, w.anchor_col == 2 + !(i > 0));

        if (i > 0) {
            w.well[w.anchor_row + right_blocked[i - 1][0]][w.anchor_col + right_blocked[i - 1][1]] = '.';
        }
        for (int j = 0; j < 7; j++) {
            for (int k = 0; k < 7; k++) {
                if (PRINT_MOVE_HORI) printf("%c", w.well[6 - j][k]);
                int col = k - !w.blocked;
                if (col < 0) col = 6;
                mu_assert(fail_msg, w.well[6 - j][k] == expected[j][col]);
            }
            if (PRINT_MOVE_HORI) printf("\n");
        }
        if (PRINT_MOVE_HORI) printf("-------\n");
    }

    return 0;
}

static char * test_move_hori() {
    int left_blocked[5][4][2] = {
        { {3, -1}, {2, -1}, {1, -1}, {0, -1} },
        { {1, -1}, {0, -1}, {0, 0}, {0, 0} },
        { {2, 1}, {1, 1}, {0, -1}, {0, 0} },
        { {2, 0}, {1, -1}, {0, 0}, {0, 0} },
        { {0, -1}, {0, 0}, {0, 0}, {0, 0} }
    };
    int right_blocked[5][4][2] = {
        { {3, 1}, {2, 1}, {1, 1}, {0, 1} },
        { {1, 2}, {0, 2}, {0, 0}, {0, 0} },
        { {2, 3}, {1, 3}, {0, 3}, {0, 0} },
        { {2, 2}, {1, 3}, {0, 2}, {0, 0} },
        { {0, 4}, {0, 0}, {0, 0}, {0, 0} }
    };
    int num_dirs[5] = {4, 2, 3, 3, 1};
    char **all_blocks[5] = {
        load_block(I_BLOCK),
        load_block(O_BLOCK),
        load_block(J_BLOCK),
        load_block(X_BLOCK),
        load_block(L_BLOCK)
    };
    char **all_expected[5] = {
        load_expected_block(I_BLOCK__EXPECTED),
        load_expected_block(O_BLOCK__EXPECTED),
        load_expected_block(J_BLOCK__EXPECTED),
        load_expected_block(X_BLOCK__EXPECTED),
        load_expected_block(L_BLOCK__EXPECTED)
    };
    char *all_block_names = "iojxl";

    for (int i = 0; i < 5; i++) {
        char *fail_msg = malloc(sizeof(char *) * 64);
        sprintf(fail_msg, "FAILURE: test_move_hori__%c_block", all_block_names[i]);
        char *fail = test_move(all_blocks[i], all_expected[i], left_blocked[i], right_blocked[i], num_dirs[i], fail_msg);
        if (fail) return fail;
    }

    return 0;
}

static char* test_wall(char **block, char **expected, int right_num, char *fail_msg) {
    well w = init_well();
    w = spawn_rock(w, block);

    int left_num = 3;
    for (int i = 0; i < left_num - 1; i++) {
        w = move_hori(w, block, -1);
        mu_assert(fail_msg, w.blocked == 0);
        mu_assert(fail_msg, w.anchor_col == 1 - i);
    }
    w = move_hori(w, block, -1);
    mu_assert(fail_msg, w.blocked == 1);
    mu_assert(fail_msg, w.anchor_col == 0);

    for (int j = 0; j < 7; j++) {
        for (int k = 0; k < 7; k++) {
            if (PRINT_MOVE_WALL) printf("%c", w.well[6 - j][k]);
            int col = (k + (left_num - 1)) % 7;
            mu_assert(fail_msg, w.well[6 - j][k] == expected[j][col]);
        }
        if (PRINT_MOVE_WALL) printf("\n");
    }
    if (PRINT_MOVE_WALL) printf("-------\n");

    w = init_well();
    w = spawn_rock(w, block);

    for (int i = 0; i < right_num - 1; i++) {
        w = move_hori(w, block, 1);
        mu_assert(fail_msg, w.blocked == 0);
        mu_assert(fail_msg, w.anchor_col == 3 + i);
    }
    w = move_hori(w, block, 1);
    mu_assert(fail_msg, w.blocked == 1);
    mu_assert(fail_msg, w.anchor_col == 2 + (right_num - 1));

    for (int j = 0; j < 7; j++) {
        for (int k = 0; k < 7; k++) {
            if (PRINT_MOVE_WALL) printf("%c", w.well[6 - j][k]);
            int col = k - (right_num - 1);
            if (col < 0) col += 7;
            mu_assert(fail_msg, w.well[6 - j][k] == expected[j][col]);
        }
        if (PRINT_MOVE_WALL) printf("\n");
    }
    if (PRINT_MOVE_WALL) printf("-------\n");

    return 0;
}

static char* test_move_wall() {
    char **all_blocks[5] = {
        load_block(I_BLOCK),
        load_block(O_BLOCK),
        load_block(J_BLOCK),
        load_block(X_BLOCK),
        load_block(L_BLOCK)
    };
    char **all_expected[5] = {
        load_expected_block(I_BLOCK__EXPECTED),
        load_expected_block(O_BLOCK__EXPECTED),
        load_expected_block(J_BLOCK__EXPECTED),
        load_expected_block(X_BLOCK__EXPECTED),
        load_expected_block(L_BLOCK__EXPECTED)
    };
    char *all_block_names = "iojxl";
    int right_num[5] = {5, 4, 3, 3, 2};

    for (int i = 0; i < 5; i++) {
        char *fail_msg = malloc(sizeof(char *) * 64);
        sprintf(fail_msg, "FAILURE: test_move_wall__%c_block", all_block_names[i]);
        char *fail = test_wall(all_blocks[i], all_expected[i], right_num[i], fail_msg);
        if (fail) return fail;
    }

    return 0;
}

static char* test_down(char **block, char **expected, int blocked[4][2], int num_blocked, char* fail_msg) {
    for (int i = 0; i < num_blocked + 1; i++) {
        well w = init_well();
        w = spawn_rock(w, block);

        if (i > 0) {
            w.well[w.anchor_row + blocked[i - 1][0]][w.anchor_col + blocked[i - 1][1]] = '#';
        }
        w = move_down(w, block);
        mu_assert(fail_msg, w.blocked == (i > 0));
        mu_assert(fail_msg, w.anchor_row == 3 - !(i > 0));

        if (i > 0) {
            w.well[w.anchor_row + blocked[i - 1][0]][w.anchor_col + blocked[i - 1][1]] = '.';
        }
        for (int j = 0; j < 7; j++) {
            for (int k = 0; k < 7; k++) {
                if (PRINT_MOVE_DOWN) printf("%c", w.well[6 - j][k]);
                int row = j - !w.blocked;
                if (row < 0) row = 6;
                mu_assert(fail_msg, w.well[6 - j][k] == expected[row][k]);
            }
            if (PRINT_MOVE_DOWN) printf("\n");
        }
        if (PRINT_MOVE_DOWN) printf("-------\n");
    }

    return 0;
}

static char* test_move_down() {
    int blocked[5][4][2] = {
        { {-1, 0}, {0, 0}, {0, 0}, {0, 0} },
        { {-1, 0}, {-1, 1}, {0, 0}, {0, 0} },
        { {-1, 0}, {-1, 1}, {-1, 2}, {0, 0} },
        { {0, 0}, {-1, 1}, {0, 2}, {0, 0} },
        { {-1, 0}, {-1, 1}, {-1, 2}, {-1, 3} }
    };
    int num_dirs[5] = {1, 2, 3, 3, 4};
    char **all_blocks[5] = {
        load_block(I_BLOCK),
        load_block(O_BLOCK),
        load_block(J_BLOCK),
        load_block(X_BLOCK),
        load_block(L_BLOCK)
    };
    char **all_expected[5] = {
        load_expected_block(I_BLOCK__EXPECTED),
        load_expected_block(O_BLOCK__EXPECTED),
        load_expected_block(J_BLOCK__EXPECTED),
        load_expected_block(X_BLOCK__EXPECTED),
        load_expected_block(L_BLOCK__EXPECTED)
    };
    char *all_block_names = "iojxl";
   
    for (int i = 0; i < 5; i++) {
        char *fail_msg = malloc(sizeof(char *) * 64);
        sprintf(fail_msg, "FAILURE: test_move_down__%c_block", all_block_names[i]);
        char *fail = test_down(all_blocks[i], all_expected[i], blocked[i], num_dirs[i], fail_msg);
        if (fail) return fail;
    }

    return 0;
}

static char* test_floor(char **block, char **expected, int height, char *fail_msg) {
    well w = init_well();
    w = spawn_rock(w, block);

    int down_num = 4;
    for (int i = 0; i < down_num - 1; i++) {
        w = move_down(w, block);
        mu_assert(fail_msg, w.blocked == 0);
        mu_assert(fail_msg, w.anchor_row == 2 - i);
    }
    w = move_down(w, block);
    mu_assert(fail_msg, w.blocked == 1);
    mu_assert(fail_msg, w.anchor_row == 0);
    mu_assert(fail_msg, w.highest_rock == height);

    for (int j = 0; j < 7; j++) {
        for (int k = 0; k < 7; k++) {
            if (PRINT_MOVE_FLOOR) printf("%c", w.well[6 - j][k]);
            int row = (j - (down_num - 1));
            if (row < 0) row += 7;
            mu_assert(fail_msg, w.well[6 - j][k] == expected[row][k]);
        }
        if (PRINT_MOVE_FLOOR) printf("\n");
    }
    if (PRINT_MOVE_FLOOR) printf("-------\n");

    return 0;
}

static char* test_move_floor() {
    char **all_blocks[5] = {
        load_block(I_BLOCK),
        load_block(O_BLOCK),
        load_block(J_BLOCK),
        load_block(X_BLOCK),
        load_block(L_BLOCK)
    };
    char **all_expected[5] = {
        load_expected_block(I_BLOCK__EXPECTED),
        load_expected_block(O_BLOCK__EXPECTED),
        load_expected_block(J_BLOCK__EXPECTED),
        load_expected_block(X_BLOCK__EXPECTED),
        load_expected_block(L_BLOCK__EXPECTED)
    };
    char *all_block_names = "iojxl";
    int heights[5] = {4, 2, 3, 3, 1};

    for (int i = 0; i < 5; i++) {
        char *fail_msg = malloc(sizeof(char *) * 64);
        sprintf(fail_msg, "FAILURE: test_move_floor__%c_block", all_block_names[i]);
        char *fail = test_floor(all_blocks[i], all_expected[i], heights[i], fail_msg);
        if (fail) return fail;
    }

    return 0;
}

static char* test_offset(char **floor_block, char **spawn_block, char **expected, int height, char *fail_msg) {
    well w = init_well();
    w = spawn_rock(w, floor_block);

    for (int i = 0; i < 4; i++) {
        w = move_down(w, floor_block);
    }
    w = spawn_rock(w, spawn_block);

    mu_assert(fail_msg, w.anchor_row == 3 + height && w.anchor_col == 2);

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (PRINT_SPAWN_ROCK_OFFSET) printf("%c", w.well[6 - i + height][j]);
            mu_assert(fail_msg, w.well[6 - i + height][j] == expected[i][j]);
        }
        if (PRINT_SPAWN_ROCK_OFFSET) printf(" %d\n", 6 - i + height);
    }
    if (PRINT_SPAWN_ROCK_OFFSET) printf("-------\n");

    return 0;
}

static char* test_spawn_rock_offset() {
    char **all_blocks[5] = {
        load_block(I_BLOCK),
        load_block(O_BLOCK),
        load_block(J_BLOCK),
        load_block(X_BLOCK),
        load_block(L_BLOCK)
    };
    char **all_expected[5] = {
        load_expected_block(I_BLOCK__EXPECTED),
        load_expected_block(O_BLOCK__EXPECTED),
        load_expected_block(J_BLOCK__EXPECTED),
        load_expected_block(X_BLOCK__EXPECTED),
        load_expected_block(L_BLOCK__EXPECTED)
    };
    char *all_block_names = "iojxl";
    int heights[5] = {4, 2, 3, 3, 1};

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            char *fail_msg = malloc(sizeof(char *) * 64);
            sprintf(fail_msg, "FAILURE: test_spawn_rock_offset__%c_%c_block", all_block_names[i], all_block_names[j]);
            char *fail = test_offset(all_blocks[i], all_blocks[j], all_expected[j], heights[i], fail_msg);
            if (fail) return fail;
        }
    }

    return 0;
}

static char * test_sim_well() {
    char *fail_msg = "FAILURE: test_sim_well";
    well w = sim("test_cases/test.txt", 13, 0);

    FILE *expected_well = fopen("test_cases/expected-13.txt", "r");
    mu_assert(fail_msg, expected_well != NULL);
    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    for (int i = 0; i < 26; i++) {
        mu_assert(fail_msg, (read = getline(&line, &length, expected_well)) != 1);
        for (int j = 0; j < 7; j++) {
            if (PRINT_SIMULATE_WELL) printf("%c", w.well[19 - i][j]);
            mu_assert(fail_msg, w.well[25 - i][j] == line[j]);
        }
        if (PRINT_SIMULATE_WELL) printf("\n");
    }
    mu_assert(fail_msg, w.highest_rock == 23);

    return 0;
}

static char * test_sim() {
    char *fail_msg = "FAILURE: test_sim";
    int num_blocks = 2022;
    well w = sim("test_cases/test.txt", num_blocks, 0);
    mu_assert(fail_msg, w.highest_rock == 3068);

    return 0;
}

static char * test_simulate() {
    char *fail_msg = "FAILURE: test_simulate";

    long long v = simulate("test_cases/test.txt", 13);
    mu_assert(fail_msg, v == 23);

    long long w = simulate("test_cases/test.txt", 2022);
    mu_assert(fail_msg, w == 3068);

    long long x = simulate("test_cases/test.txt", 1000000000000);
    mu_assert(fail_msg, x == 1514285714288);

    return 0;
}

static char * all_tests() {
    mu_run_test(test_spawn_rock);
    mu_run_test(test_move_hori);
    mu_run_test(test_move_wall);
    mu_run_test(test_move_down);
    mu_run_test(test_move_floor);
    mu_run_test(test_spawn_rock_offset);
    mu_run_test(test_sim_well);
    mu_run_test(test_simulate);
    mu_run_test(test_sim);

    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}

