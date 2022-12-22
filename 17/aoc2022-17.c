#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc2022-17.h"

const int DEBUG_MOVE_DOWN = 0;
const int DEBUG_SIMULATE = 0;

well init_well() {
    well w;
    for (int row = 0; row < AOC_MAX_HEIGHT; row++) {
        for (int col = 0; col < 7; col++) {
            w.well[row][col] = '.';
        }
    }
    w.anchor_row = -1;
    w.anchor_col = -1;
    w.highest_rock = 0;
    w.loop_start = -1;
    w.loop_blocks = -1;
    w.loop_height = -1;

    return w;
}

well spawn_rock(well w, char **block) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (block[row][col] == '#') {
                w.well[w.highest_rock + 6 - row][2 + col] = '#';
            }
        }
    }

    w.anchor_row = w.highest_rock + 3;
    w.anchor_col = 2;
    return w;
}

well move_hori(well w, char **block, int direction) {
    int blocked = 0;
    for (int row = 0; row < 4; row++) {
        for (int col = (direction < 0) ? 0 : 3; 0 <= col && col < 4; col -= direction) {
            if (block[row][col] != '#') {
                continue;
            }

            if (direction < 0 && w.anchor_col + col + direction < 0) {
                blocked = 1;
                break;
            }

            if (direction > 0 && w.anchor_col + col + direction > 6) {
                blocked = 1;
                break;
            }

            if (w.well[w.anchor_row + 3 - row][w.anchor_col + col + direction] == '#') {
                blocked = 1;
            }
            break;
        }

        if (blocked) {
            break;
        }
    }

    if (!blocked) {
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                if (block[row][col] == '#') {
                    w.well[w.anchor_row + 3 - row][w.anchor_col + col] = '.';
                }
            }
        }

        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                if (block[row][col] == '#') {
                    w.well[w.anchor_row + 3 - row][w.anchor_col + col + direction] = '#';
                }
            }
        }
       
        w.anchor_col += direction;
    }

    w.blocked = blocked;
    return w;
}

well move_down(well w, char **block) {
    int blocked = 0;
    for (int col = 0; col < 4; col++) {
        for (int row = 3; row >= 0; row--) {
            if (block[row][col] != '#') {
                continue;
            }

            if (w.anchor_row + 2 - row < 0) {
                blocked = 1;
                break;
            }

            if (w.well[w.anchor_row + 2 - row][w.anchor_col + col] == '#') {
                blocked = 1;
            }
            break;
        }

        if (blocked) {
            break;
        }
    }


    if (!blocked) {
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                if (block[row][col] == '#') {
                    w.well[w.anchor_row + 3 - row][w.anchor_col + col] = '.';
                }
            }
        }

        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                if (block[row][col] == '#') {
                    w.well[w.anchor_row + 2 - row][w.anchor_col + col] = '#';
                }
            }
        }

        w.anchor_row -= 1;
    } else {
        int current_row = w.anchor_row;
        int next_height_found = 0;
        while (!next_height_found) {
            if (DEBUG_MOVE_DOWN) {
                printf("Checking row %d\n", current_row);
                for (int i = 0; i < 7; i++) {
                    printf("%c", w.well[current_row][i]);
                }
                printf("\n");
            }

            int col = 0;
            while (col < 7) {
                if (w.well[current_row][col] == '#') {
                    break;
                }
                col++;
            }
            if (col == 7) {
                next_height_found = 1;
            }
            current_row++;
        }

        w.highest_rock = current_row - 1;
    }

    w.blocked = blocked;
    return w;
}

char** load_block(const char block[4][4]) {
    char **b = malloc(sizeof(char *) * 4);
    for (int i = 0; i < 4; i++) {
        b[i] = malloc(sizeof(char) * 4);
        strncpy(b[i], block[i], 4);
    }
    return b;
}

void free_block(char **block) {
    for (int i = 0; i < 4; i++) {
        free(block[i]);
    }
    free(block);
}

long long simulate(char* filename, long long num_blocks) {
    well w = sim(filename, num_blocks, 1);
    if (w.loop_start > -1) {
        int height = w.loop_height;
        int blocks = w.loop_blocks;
        long long counter = (w.loop_start - (w.loop_start - w.loop_blocks)) + ((num_blocks + w.loop_blocks) % w.loop_blocks);
        well w = sim(filename, counter, 0);
        long long offset = height * ((num_blocks - counter) / blocks);

        return w.highest_rock + offset;
    }
    return w.highest_rock;
}

well sim(char* filename, long long num_blocks, int check_loop) {
    well w = init_well();
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return w;
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    if ((read = getline(&line, &length, fp)) == -1) {
        return w;
    }

    int num_loops = 0;
    int jet = 0;
    int num_rocks[3] = {-1, -1, -1};
    int heights[3] = {-1, -1, -1};
    for (int i = 0; i < num_blocks; i++) {
        char **block;
        switch (i % 5) {
            case 0:
                block = load_block(L_BLOCK);
                break;
            case 1:
                block = load_block(X_BLOCK);
                break;
            case 2:
                block = load_block(J_BLOCK);
                break;
            case 3:
                block = load_block(I_BLOCK);
                break;
            case 4:
                block = load_block(O_BLOCK);
                break;
        }
        w = spawn_rock(w, block);

        int lock = 0;
        while (!lock) {
            switch (line[jet]) {
                case '<':
                    w = move_hori(w, block, -1);
                    break;
                case '>':
                    w = move_hori(w, block, 1);
                    break;
            }
            w = move_down(w, block);
            jet = (jet + 1) % (read - 1);
            if (check_loop && jet == 0) {
                num_loops++;
                if (num_loops == 5) {
                    num_rocks[0] = num_rocks[1];
                    heights[0] = heights[1];
                    num_rocks[1] = num_rocks[2];
                    heights[1] = heights[2];
                    num_rocks[2] = i + 1;
                    heights[2] = w.highest_rock;

                    if (heights[0] > 0 && heights[1] > 0 && heights[2] > 0) {
                        if ((heights[2] - heights[1]) == (heights[1] - heights[0])) {
                            w.loop_start = num_rocks[0];
                            w.loop_blocks = num_rocks[2] - num_rocks[1];
                            w.loop_height = heights[2] - heights[1];
                            return w;
                        }
                    }

                    num_loops = 0;
                }
            }
            lock = w.blocked;
        }

        if (DEBUG_SIMULATE) {
            for (int i = 0; i < 50; i++) {
                for (int j = 0; j < 7; j++) {
                    printf("%c", w.well[49 - i][j]);
                }
                printf("\n");
            }
        }

        free(block);
    }

    return w;
}
