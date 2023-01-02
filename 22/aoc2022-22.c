#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "aoc2022-22.h"

board parse_input(char* filename) {
    board b;

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        b.map = NULL;
        b.directions = NULL;
        b.num_rows = -1;
        b.num_cols = -1;
        b.avatar_row = -1;
        b.avatar_col = -1;
        b.facing = 0;
        return b;
    }

    b.num_rows = 0;
    b.num_cols = 0;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    while ((read = getline(&line, &length, fp)) != -1) {
        if ((read - 1) == 0) {
            break;
        }
        b.num_cols = ((read - 1) > b.num_cols) ? read - 1 : b.num_cols;
        b.num_rows++;
    }
    b.num_rows += 2;
    b.num_cols += 2;

    rewind(fp);
    int current_row = 0;
    b.map = malloc(sizeof(char *) * b.num_rows);
    b.map[current_row] = malloc(sizeof(char) * (b.num_cols + 1));
    for (int current_col = 0; current_col < b.num_cols; current_col++) {
        b.map[current_row][current_col] = ' ';
    }
    b.map[current_row][b.num_cols] = '\0';

    current_row++;
    while ((read = getline(&line, &length, fp)) != -1) {
        if ((read - 1) == 0) {
            break;
        }
        b.map[current_row] = malloc(sizeof(char) * (b.num_cols + 1));
        int current_col = 0;
        b.map[current_row][current_col++] = ' ';
        while (current_col < b.num_cols && line[current_col - 1] != '\n') {
            b.map[current_row][current_col] = line[current_col - 1];
            current_col++;
        }
        while (current_col < b.num_cols) {
            b.map[current_row][current_col++] = ' ';
        }
        b.map[current_row][current_col++] = '\0';
        current_row++;
    }

    b.map[current_row] = malloc(sizeof(char) * (b.num_cols + 1));
    for (int current_col = 0; current_col < b.num_cols; current_col++) {
        b.map[current_row][current_col] = ' ';
    }
    b.map[current_row][b.num_cols] = '\0';

    if ((read = getline(&line, &length, fp)) != -1) {
        b.directions = malloc(sizeof(char) * length);
        strcpy(b.directions, line);
        char* newline = strchr(b.directions, '\n');
        newline[0] = '\0';
    }

    b.avatar_row = 1;
    b.facing = 'R';
    for (int col = 1; col < b.num_cols - 1; col++) {
        if (b.map[1][col] == '.') {
            b.avatar_col = col;
            break;
        }
    }

    free(line);
    fclose(fp);
    return b;
}

void free_board(board b) {
    for (int current_row = 0; current_row < b.num_rows; current_row++) {
        free(b.map[current_row]);
    }
    free(b.map);
    free(b.directions);
    b.num_rows = -1;
    b.num_cols = -1;
}

void move_avatar(board* b, int steps, cube* c) {
    int i = 0;
    switch (b->facing) {
        case 'U':
            while (i < steps) {
                char direct_tile = b->map[b->avatar_row - 1][b->avatar_col];
                if (direct_tile == '.') {
                    b->avatar_row--;
                    i++;
                } else if (direct_tile == ' ' && c != NULL) {
                    traverse_edge(b, c);
                    move_avatar(b, steps - ++i, c);
                    break;
                } else if (direct_tile == ' ') {
                    int wrap_row = b->num_rows - 2;
                    while (b->map[wrap_row][b->avatar_col] == ' ') {
                        wrap_row--;
                    };
                    if (b->map[wrap_row][b->avatar_col] == '.') {
                        b->avatar_row = wrap_row;
                        i++;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            }
            break;
        case 'L':
            while (i < steps) {
                char direct_tile = b->map[b->avatar_row][b->avatar_col - 1];
                if (direct_tile == '.') {
                    b->avatar_col--;
                    i++;
                } else if (direct_tile == ' ' && c != NULL) {
                    traverse_edge(b, c);
                    move_avatar(b, steps - ++i, c);
                    break;
                } else if (direct_tile == ' ') {
                    int wrap_col = b->num_cols - 2;
                    while (b->map[b->avatar_row][wrap_col] == ' ') {
                        wrap_col--;
                    };
                    if (b->map[b->avatar_row][wrap_col] == '.') {
                        b->avatar_col = wrap_col;
                        i++;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            }
            break;
        case 'R':
            while (i < steps) {
                char direct_tile = b->map[b->avatar_row][b->avatar_col + 1];
                if (direct_tile == '.') {
                    b->avatar_col++;
                    i++;
                } else if (direct_tile == ' ' && c != NULL) {
                    traverse_edge(b, c);
                    move_avatar(b, steps - ++i, c);
                    break;
                } else if (direct_tile == ' ') {
                    int wrap_col = 1;
                    while (b->map[b->avatar_row][wrap_col] == ' ') {
                        wrap_col++;
                    };
                    if (b->map[b->avatar_row][wrap_col] == '.') {
                        b->avatar_col = wrap_col;
                        i++;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            }
            break;
        case 'D':
            while (i < steps) {
                char direct_tile = b->map[b->avatar_row + 1][b->avatar_col];
                if (direct_tile == '.') {
                    b->avatar_row++;
                    i++;
                } else if (direct_tile == ' ' && c != NULL) {
                    traverse_edge(b, c);
                    move_avatar(b, steps - ++i, c);
                    break;
                } else if (direct_tile == ' ') {
                    int wrap_row = 1;
                    while (b->map[wrap_row][b->avatar_col] == ' ') {
                        wrap_row++;
                    };
                    if (b->map[wrap_row][b->avatar_col] == '.') {
                        b->avatar_row = wrap_row;
                        i++;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            }
            break;
    }
}

void turn_avatar(board* b, char direction) {
    switch (b->facing) {
        case 'U':
            if (direction == 'R') { b->facing = 'R'; }
            else if (direction == 'L') { b->facing = 'L'; }
            break;
        case 'L':
            if (direction == 'R') { b->facing = 'U'; }
            else if (direction == 'L') { b->facing = 'D'; }
            break;
        case 'R':
            if (direction == 'R') { b->facing = 'D'; }
            else if (direction == 'L') { b->facing = 'U'; }
            break;
        case 'D':
            if (direction == 'R') { b->facing = 'L'; }
            else if (direction == 'L') { b->facing = 'R'; }
            break;
    }
}

void run_directions(board* b, cube* c) {
    int i = 0;
    int toggle = 0;
    char* num = malloc(sizeof(char) * 5);

    while (b->directions[i] != '\0') {
        if (!toggle) {
            int j = 0;
            while (j < 5) {
                num[j++] = '\0';
            }

            j = 0;
            while (isdigit(b->directions[i])) {
                num[j++] = b->directions[i++];
            }

            move_avatar(b, atoi(num), c);

            toggle = 1;
        } else {
            turn_avatar(b, b->directions[i++]);

            toggle = 0;
        }
    }

    free(num);
}

int calc_pass(board* b) {
    int facing = 0;
    switch (b->facing) {
        case 'R': facing = 0; break;
        case 'D': facing = 1; break;
        case 'L': facing = 2; break;
        case 'U': facing = 3; break;
    }
    return (1000 * b->avatar_row) + (4 * b->avatar_col) + facing;
}

cube load_cube(char* filename) {
    cube c;

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        for (int i = 0; i < CUBE_MATRIX_ROWS; i++) {
            for (int j = 0; j < CUBE_MATRIX_COLS; j++) {
                c.edges[i][j] = -1;
            }
        }

        fclose(fp);
        return c;
    }

    int row = 0;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    while ((read = getline(&line, &length, fp)) != -1) {
        char* num = strtok(line, ",");
        int col = 0;

        do {
            c.edges[row][col++] = atoi(num);
            num = strtok(NULL, ",");
        } while (num != NULL);

        row++;
    }

    free(line);
    fclose(fp);
    return c;
}

int is_along_edge(int* edge, int row, int col) {
    int edge_start_row;
    int edge_end_row;
    if (edge[0] <= edge[2]) {
        edge_start_row = edge[0];
        edge_end_row = edge[2];
    } else {
        edge_start_row = edge[2];
        edge_end_row = edge[0];
    }

    int edge_start_col;
    int edge_end_col;
    if (edge[1] <= edge[3]) {
        edge_start_col = edge[1];
        edge_end_col = edge[3];
    } else {
        edge_start_col = edge[3];
        edge_end_col = edge[1];
    }

    return edge_start_row <= row && row <= edge_end_row
            && edge_start_col <= col && col <= edge_end_col;
}

int calc_dest_offset(int* edge, int row, int col) {
    int offset = 0;
    int is_horizontal = edge[0] == edge[2];
    int is_vertical = edge[1] == edge[3];
    int count_up = (is_horizontal && edge[1] < edge[3])
            || (is_vertical && edge[0] < edge[2]);
    int count_down = (is_horizontal && edge[3] < edge[1])
            || (is_vertical && edge[2] < edge[0]);
    int acc;
    int end;

    if (is_horizontal) {
        acc = edge[1];
        end = col;
    } else if (is_vertical) {
        acc = edge[0];
        end = row;
    } else {
        return -1;
    }

    if (count_up) {
        while (acc++ < end) {
            offset++;
        }
    } else if (count_down) {
        while (acc-- > end) {
            offset++;
        }
    } else {
        return -1;
    }

    return offset;
}

int* get_destination(int* edge, int offset, char facing) {
    int* dest = malloc(sizeof(int) * 3);
    for (int i = 0; i < 3; i++) {
        dest[i] = -1;
    }

    int is_horizontal = edge[4] == edge[6];
    int is_vertical = edge[5] == edge[7];
    if (!(is_horizontal || is_vertical)) {
        return dest;
    }

    int count_up = (is_horizontal && edge[5] < edge[7])
            || (is_vertical && edge[4] < edge[6]);
    int count_down = (is_horizontal && edge[7] < edge[5])
            || (is_vertical && edge[6] < edge[4]);
    if (!(count_up || count_down)) {
        return dest;
    }

    if (is_horizontal) {
        dest[0] = edge[4];
        dest[1] = (count_up) ? edge[5] + offset : edge[5] - offset;
    } else {
        dest[0] = (count_up) ? edge[4] + offset : edge[4] - offset;
        dest[1] = edge[5];
    }

    char directions[4] = { 'L', 'U', 'R', 'D' };
    int start_index = 0;
    while (facing != directions[start_index]) {
        start_index++;
    }
    int end_index = start_index + edge[8];
    end_index = (end_index < 0) ? (-1 * ((-1 * end_index) % 4)) + 4 : end_index % 4;
    dest[2] = directions[end_index];

    return dest;
}

void traverse_edge(board* b, cube* c) {
    for (int i = 0; i < CUBE_MATRIX_ROWS; i++) {
        if (is_along_edge(c->edges[i], b->avatar_row, b->avatar_col)) {
            int offset = calc_dest_offset(c->edges[i], b->avatar_row, b->avatar_col);
            int* coords = get_destination(c->edges[i], offset, b->facing);

            if (b->map[coords[0]][coords[1]] == '.') {
                b->avatar_row = coords[0];
                b->avatar_col = coords[1];
                b->facing = coords[2];
            }

            free(coords);
            break;
        }
    }
}
