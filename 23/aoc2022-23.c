#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc2022-23.h"

grove parse_input(char* filename) {
    grove g;
    g.map = NULL;
    g.rows = -1;
    g.cols = -1;
    g.elves = -1;
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        return g;
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    if ((read = getline(&line, &length, fp)) != -1) {
        g.cols = read;
        if (line[g.cols - 1] == '\n') {
            g.cols--;
        }
    } else {
        return g;
    }
    g.rows = 1;
    while ((read = getline(&line, &length, fp)) != -1) {
        g.rows++;
    }

    int anchor_row = g.rows;
    int anchor_col = g.cols;
    g.rows *= 3;
    g.cols *= 3;

    rewind(fp);
    g.map = malloc(sizeof(char *) * g.rows);
    g.elves = 0;
    int current_row = 0;
    
    while (current_row < anchor_row) {
        g.map[current_row] = malloc(sizeof(char) * (g.cols + 1));
        int current_col = 0;
        while (current_col < g.cols) {
            g.map[current_row][current_col++] = '.';
        }
        g.map[current_row][current_col] = '\0';
        current_row++;
    }

    while ((read = getline(&line, &length, fp)) != -1) {
        g.map[current_row] = malloc(sizeof(char) * (g.cols + 1));
        int current_col = 0;
        while (current_col < anchor_col) {
            g.map[current_row][current_col++] = '.';
        }

        int current_char = 0;
        while (current_col < (anchor_col * 2)) {
            g.map[current_row][current_col] = line[current_char];
            if (line[current_char] == '#') {
                g.elves++;
            }
            current_col++;
            current_char++;
        }

        while (current_col < g.cols) {
            g.map[current_row][current_col++] = '.';
        }

        g.map[current_row][current_col] = '\0';
        current_row++;
    }

    while (current_row < g.rows) {
        g.map[current_row] = malloc(sizeof(char) * (g.cols + 1));
        int current_col = 0;
        while (current_col < g.cols) {
            g.map[current_row][current_col++] = '.';
        }
        g.map[current_row][current_col] = '\0';
        current_row++;
    }

    if (line != NULL) {
        free(line);
    }
    fclose(fp);
    return g;
}

void free_grove(grove* g) {
    for (int i = 0; i < g->rows; i++) {
        free(g->map[i]);
    }
    free(g->map);
    g->rows = -1;
    g->cols = -1;
}

int check_bounds(grove* g, int row, int col) {
    if (!(-1 < row && row < g->rows)) {
        return 0;
    }
    if (!(-1 < col && col < g->cols)) {
        return 0;
    }
    return 1;
}

int check_row(grove* g, int row, int col) {
    for (int i = col - 1; i <= col + 1; i++) {
        if (-1 < i && i < g->cols) {
            if (g->map[row][i] == '#') {
                return 0;
            }
        }
    }

    return 1;
}

int check_north(grove* g, int row, int col) {
    if (!check_bounds(g, row, col)) {
        return 0;
    }
    if (row == 0) {
        return 0;
    }

    return check_row(g, row - 1, col);
}

int check_south(grove* g, int row, int col) {
    if (!check_bounds(g, row, col)) {
        return 0;
    }
    if (row == g->rows - 1) {
        return 0;
    }

    return check_row(g, row + 1, col);
}

int check_col(grove* g, int row, int col) {
    for (int i = row - 1; i <= row + 1; i++) {
        if (-1 < i && i < g->rows) {
            if (g->map[i][col] == '#') {
                return 0;
            }
        }
    }

    return 1;

}

int check_west(grove* g, int row, int col) {
    if (!check_bounds(g, row, col)) {
        return 0;
    }
    if (col == 0) {
        return 0;
    }

    return check_col(g, row, col - 1);
}

int check_east(grove* g, int row, int col) {
    if (!check_bounds(g, row, col)) {
        return 0;
    }
    if (col == g->cols - 1) {
        return 0;
    }

    return check_col(g, row, col + 1);
}

int check_adjacent(grove* g, int row, int col) {
    if (!check_bounds(g, row, col)) {
        return 0;
    }

    for (int i = row - 1; i <= row + 1; i++) {
        if (!(-1 < i && i < g->rows)) {
            continue;
        }

        for (int j = col - 1; j <= col + 1; j++) {
            if (!(-1 < j && j < g->cols)) {
                continue;
            }

            if (i == row && j == col) {
                continue;
            }

            if (g->map[i][j] == '#') {
                return 0;
            }
        }
    }

    return 1;
}

order* init_orders() {
    int (*check_fns[4])(grove*,int,int) = {
        check_north, check_south, check_west, check_east
    };
    char* labels[4] = {
        "north", "south", "west", "east"
    };

    order* head;
    int i = 0;
    head = malloc(sizeof(order));
    head->fn = check_fns[i];
    head->label = labels[i++];
    head->next = malloc(sizeof(order));

    order* current = head->next;
    while (i < 3) {
        current->fn = check_fns[i];
        current->label = labels[i++];
        current->next = malloc(sizeof(order));
        current = current->next;
    }

    current->fn = check_fns[i];
    current->label = labels[i];
    current->next = NULL;

    return head;
}

void free_orders(order* o) {
    while (o != NULL) {
        order* next = o->next;
        free(o);
        o = next;
    }
}

moves propose_movements(grove* g, order* o) {
    moves m;
    m.list = malloc(sizeof(int *) * g->elves);
    m.list_len = g->elves;
    m.vect_len = 4;

    int current_elf = 0;
    for (int i = 0; i < g->rows; i++) {
        for (int j = 0; j < g->cols; j++) {
            if (g->map[i][j] == '.') {
                continue;
            }

            m.list[current_elf] = malloc(sizeof(int) * m.vect_len);
            if (check_adjacent(g, i, j)) {
                int vector[4] = { i, j, i, j };
                for (int i = 0; i < 4; i++) {
                    m.list[current_elf][i] = vector[i];
                }
                current_elf++;
                continue;
            }

            order* current = o;
            int move_proposed = 0;
            while (current != NULL && !move_proposed) {
                if (current->fn(g, i, j)) {
                    move_proposed = 1;
                    if (!strcmp(current->label, "north")) {
                        int vector[4] = { i, j, i - 1, j };
                        for (int i = 0; i < 4; i++) {
                            m.list[current_elf][i] = vector[i];
                        }
                    } else if (!strcmp(current->label, "south")) {
                        int vector[4] = { i, j, i + 1, j };
                        for (int i = 0; i < 4; i++) {
                            m.list[current_elf][i] = vector[i];
                        }
                    } else if (!strcmp(current->label, "west")) {
                        int vector[4] = { i, j, i, j - 1};
                        for (int i = 0; i < 4; i++) {
                            m.list[current_elf][i] = vector[i];
                        }
                    } else if (!strcmp(current->label, "east")) {
                        int vector[4] = { i, j, i, j + 1};
                        for (int i = 0; i < 4; i++) {
                            m.list[current_elf][i] = vector[i];
                        }
                    }
                    current_elf++;
                } else {
                    current = current->next;
                }
            }

            if (!move_proposed) {
                int vector[4] = { i, j, i, j };
                for (int i = 0; i < 4; i++) {
                    m.list[current_elf][i] = vector[i];
                }
                current_elf++;
            }
        }
    }

    return m;
}

void free_moves(moves* m) {
    for (int i = 0; i < m->list_len; i++) {
        free(m->list[i]);
    }
    free(m->list);
    m->list_len = -1;
    m->vect_len = -1;
}

void prune_duplicates(moves* m) {
    int* dupes = malloc(sizeof(int) * m->list_len);

    for (int i = 0; i < m->list_len; i++) {
        for (int j = 0; j < m->list_len; j++) {
            dupes[j] = -1;
        }

        int y = 0;
        for (int j = i + 1; j < m->list_len; j++) {
            if (m->list[i][2] == m->list[j][2] && m->list[i][3] == m->list[j][3]) {
                dupes[y++] = j;
            }
        }

        if (y > 0) {
            m->list[i][2] = m->list[i][0];
            m->list[i][3] = m->list[i][1];

            for (int x = 0; x < y; x++) {
                m->list[dupes[x]][2] = m->list[dupes[x]][0];
                m->list[dupes[x]][3] = m->list[dupes[x]][1];
            }
        }
    }

    free(dupes);
}

void move_elves(grove* g, moves* m) {
    for (int i = 0; i < m->list_len; i++) {
        g->map[m->list[i][0]][m->list[i][1]] = '.';
        g->map[m->list[i][2]][m->list[i][3]] = '#';
    }
}

void update_order(order** o) {
    order* old = *o;
    order* new = (*o)->next;
    order* end = *o;
    while (end->next != NULL) {
        end = end->next;
    }

    *o = new;
    end->next = old;
    old->next = NULL;
}

int diffusion_complete(moves m) {
    for (int i = 0; i < m.list_len; i++) {
        if (!(m.list[i][0] == m.list[i][2] && m.list[i][1] == m.list[i][3])) {
            return 0;
        }
    }

    return 1;
}

void diffuse(grove* g, order** o) {
    moves m = propose_movements(g, *o);
    update_order(o);
    prune_duplicates(&m);
    move_elves(g, &m);
    free_moves(&m);
}

int* align_bounds(grove g) {
    int* bounds = malloc(sizeof(int) * 4);

    int* start_row = &bounds[0];
    *start_row = -1;
    for (int i = 0; i < g.rows; i++) {
        for (int j = 0; j < g.cols; j++) {
            if (g.map[i][j] == '#') {
                *start_row = i;
                break;
            }
        }
        if (*start_row > -1) {
            break;
        }
    }

    int* end_row = &bounds[1];
    *end_row = g.rows;
    for (int i = g.rows - 1; i > -1; i--) {
        for (int j = 0; j < g.cols; j++) {
            if (g.map[i][j] == '#') {
                *end_row = i;
                break;
            }
        }
        if (*end_row < g.rows) {
            break;
        }
    }

    int* start_col = &bounds[2];
    *start_col = -1;
    for (int j = 0; j < g.cols; j++) {
        for (int i = 0; i < g.rows; i++) {
            if (g.map[i][j] == '#') {
                *start_col = j;
                break;
            }
        }
        if (*start_col > -1) {
            break;
        }
    }

    int* end_col = &bounds[3];
    *end_col = g.cols;
    for (int j = g.cols - 1; j > -1; j--) {
        for (int i = 0; i < g.rows; i++) {
            if (g.map[i][j] == '#') {
                *end_col = j;
                break;
            }
        }
        if (*end_col < g.cols) {
            break;
        }
    }

    return bounds;
}

int count_empty_tiles(grove g) {
    int* bounds = align_bounds(g);

    int count = 0;
    for (int i = bounds[0]; i <= bounds[1]; i++) {
        for (int j = bounds[2]; j <= bounds[3]; j++) {
            if (g.map[i][j] == '.') {
                count++;
            }
        }
    }

    free(bounds);
    return count;
}
