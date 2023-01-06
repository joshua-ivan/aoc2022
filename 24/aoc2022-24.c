#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "aoc2022-24.h"

valley parse_input(char* filename) {
    valley v;
    v.blizzard_list = NULL;
    v.map = malloc(sizeof(map));
    v.map->rows = -1;
    v.map->cols = -1;
    v.map->spaces = NULL;
    v.map->entrance = NULL;
    v.map->exit = NULL;

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        return v;
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    v.map->rows = 0;
    v.map->cols = 0;
    if ((read = getline(&line, &length, fp)) == -1) {
        return v;
    }
    v.map->rows = 1;
    v.map->cols = (line[read - 1] == '\n') ? read - 1 : read;
    while ((read = getline(&line, &length, fp)) != -1) {
        v.map->rows++;
    }

    v.map->entrance = malloc(sizeof(short) * 2);
    v.map->entrance[0] = 0; v.map->entrance[1] = 1;
    v.map->exit = malloc(sizeof(short) * 2);
    v.map->exit[0] = v.map->rows - 1; v.map->exit[1] = v.map->cols - 2;

    rewind(fp);
    v.map->spaces = malloc(sizeof(short *) * v.map->rows);
    int row = 0;
    while ((read = getline(&line, &length, fp)) != -1) {
        v.map->spaces[row] = malloc(sizeof(short) * v.map->cols);
        for (int col = 0; col < v.map->cols; col++) {
            if (line[col] == '#') {
                v.map->spaces[row][col] = -1;
            } else if (line[col] == '.') {
                v.map->spaces[row][col] = 0;
            } else {
                v.map->spaces[row][col] = 1;

                blizzard* b = malloc(sizeof(blizzard));
                b->position = malloc(sizeof(short) * 2);
                b->position[0] = row; b->position[1] = col;
                b->direction = malloc(sizeof(short) * 2);
                switch(line[col]) {
                    case '^':
                        b->direction[0] = -1; b->direction[1] = 0;
                        break;
                    case '<':
                        b->direction[0] = 0; b->direction[1] = -1;
                        break;
                    case '>':
                        b->direction[0] = 0; b->direction[1] = 1;
                        break;
                    case 'v':
                        b->direction[0] = 1; b->direction[1] = 0;
                        break;
                }
                b->next = v.blizzard_list;
                v.blizzard_list = b;
            }
        }
        row++;
    }

    free(line);
    fclose(fp);
    return v;
}

void free_valley(valley* v) {
    if (v == NULL) {
        return;
    }

    blizzard* b_list = v->blizzard_list;
    while (b_list != NULL) {
        blizzard* temp = b_list->next;
        if (b_list->position != NULL) free(b_list->position);
        if (b_list->direction != NULL) free(b_list->direction);
        free(b_list);
        b_list = temp;
    }

    map* m = v->map;
    if (m != NULL) {
        if (m->spaces != NULL) {
            for (int i = 0; i < m->rows; i++) {
                if (m->spaces[i] != NULL) free(m->spaces[i]);
            }
            free(m->spaces);
        }
        if (m->exit != NULL) free(m->exit);
        if (m->entrance != NULL) free(m->entrance);
        free(m);
    }
}

void move_blizzards(valley* v) {
    blizzard* list = v->blizzard_list;
    while (list != NULL) {
        v->map->spaces[list->position[0]][list->position[1]]--;

        list->position[0] += list->direction[0];
        if (list->position[0] == 0) {
            list->position[0] = v->map->rows - 2;
        } else if (list->position[0] == v->map->rows - 1) {
            list->position[0] = 1;
        }

        list->position[1] += list->direction[1];
        if (list->position[1] == 0) {
            list->position[1] = v->map->cols - 2;
        } else if (list->position[1] == v->map->cols - 1) {
            list->position[1] = 1;
        }

        v->map->spaces[list->position[0]][list->position[1]]++;

        list = list->next;
    }
}

vector_set init_vector_set() {
    vector_set vs;
    vs.length = 0;
    for (int i = 0; i < VECTOR_SET_LENGTH; i++) {
        vs.items[i][0] = -1;
        vs.items[i][1] = -1;
    }
    return vs;
}

int search_vector_set(vector_set* vs, int row, int col) {
    for (int i = 0; i < vs->length; i++) {
        if (vs->items[i][0] == row && vs->items[i][1] == col) {
            return 1;
        }
    }
    return 0;
}

void push_vector_set(vector_set* vs, int row, int col) {
    if (search_vector_set(vs, row, col)) {
        return;
    }

    vs->items[vs->length][0] = row;
    vs->items[vs->length][1] = col;
    vs->length++;
}

void pop_vector_set(vector_set* vs, int index) {
    vs->items[index][0] = -1;
    vs->items[index][1] = -1;
    for (int i = index + 1; i < vs->length; i++) {
        vs->items[i - 1][0] = vs->items[i][0];
        vs->items[i - 1][1] = vs->items[i][1];
    }
    vs->length--;
}

void take_step(valley* v, vector_set* vs) {
    int preop_len = vs->length;
    short directions[5][2] = {
        { 0, 0 }, { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }
    };
    for (int i = 0; i < preop_len; i++) {
        for (int j = 0; j < 5; j++) {
            int row = vs->items[i][0] + directions[j][0];
            int col = vs->items[i][1] + directions[j][1];

            if ((-1 < row && row < v->map->rows) && (-1 < col && col < v->map->cols)) {
                push_vector_set(vs, row, col);
            }
        }
    }

    move_blizzards(v);

    preop_len = vs->length;
    for (int i = preop_len - 1; i >= 0; i--) {
        if (v->map->spaces[vs->items[i][0]][vs->items[i][1]] != 0) {
            pop_vector_set(vs, i);
        }
    }
}

int move_valley(valley* v, vector_set* vs, int dest_row, int dest_col) {
    int steps = 0;
    int dest_found = 0;
    while (!dest_found) {
        take_step(v, vs);
        steps++;

        if (search_vector_set(vs, dest_row, dest_col)) {
            dest_found = 1;
        }
    }

    return steps;
}

int traverse_valley(valley* v) {
    vector_set vs = init_vector_set();
    push_vector_set(&vs, v->map->entrance[0], v->map->entrance[1]);
    return move_valley(v, &vs, v->map->exit[0], v->map->exit[1]);
}

int backtrack_valley(valley* v) {
    vector_set vs = init_vector_set();
    push_vector_set(&vs, v->map->exit[0], v->map->exit[1]);
    return move_valley(v, &vs, v->map->entrance[0], v->map->entrance[1]);
}
