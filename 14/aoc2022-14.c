#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc2022-14.h"

coords to_coords(char *raw) {
    coords c;

    int separator = strcspn(raw, ",");
    c.x = atoi(raw);
    c.y = atoi(raw + separator + 1);

    return c;
}

cave init_cave(char *filename) {
    cave ca;
    ca.rocks = NULL;
    ca.formations = -1;
    ca.lowest = -1;

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return ca;
    }
    
    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    ca.formations = 0;
    int max_items = 256;
    ca.rocks = malloc(sizeof(coords_list) * max_items);
    while ((read = getline(&line, &length, fp)) != -1) {
        ca.rocks[ca.formations] = init_coords_list(max_items);

        char *rock = strtok(line, " ");
        coords co = to_coords(rock);
        insert_coords_list(ca.rocks[ca.formations], &co);
        if (ca.lowest < co.y) {
            ca.lowest = co.y;
        }

        while ((rock = strtok(NULL, " ")) != NULL) {
            if (!strcmp(rock, "->")) {
                continue;
            }

            co = to_coords(rock);
            insert_coords_list(ca.rocks[ca.formations], &co);
            if (ca.lowest < co.y) {
                ca.lowest = co.y;
            }
        }

        ca.formations++;
    }

    ca.rocks[ca.formations] = init_coords_list(max_items);

    coords floor;
    floor.x = 0;
    floor.y = ca.lowest + 2;
    insert_coords_list(ca.rocks[ca.formations], &floor);

    floor.x = 999;
    insert_coords_list(ca.rocks[ca.formations], &floor);

    ca.formations++;
    ca.lowest += 2;

    return ca;
}

int** build_terrain(cave c) {
    int **terrain = malloc(sizeof(int *) * 1000);
    for (int i = 0; i < 1000; i++) {
        terrain[i] = malloc(sizeof(int) * c.lowest + 1);
        for (int j = 0; j < c.lowest + 1; j++) {
            terrain[i][j] = '.';
        }
    }

    for (int i = 0; i < c.formations; i++) {
        coords_list current = c.rocks[i];

        int j = 0;
        terrain[current.list[j]->x][current.list[j]->y] = '#';
        j++;

        while (current.list[j]->x != -1 && current.list[j]->y != -1) {
            if (current.list[j]->y - current.list[j - 1]->y < 0) {
                for (int k = current.list[j]->y; k < current.list[j - 1]->y; k++) {
                    terrain[current.list[j]->x][k] = '#';
                }
            } else if (current.list[j]->x - current.list[j - 1]->x < 0) {
                for (int k = current.list[j]->x; k < current.list[j - 1]->x; k++) {
                    terrain[k][current.list[j]->y] = '#';
                }
            } else if (current.list[j]->x - current.list[j - 1]->x > 0) {
                for (int k = current.list[j]->x; k > current.list[j - 1]->x; k--) {
                    terrain[k][current.list[j]->y] = '#';
                }
            } else if (current.list[j]->y - current.list[j - 1]->y > 0) {
                for (int k = current.list[j]->y; k > current.list[j - 1]->y; k--) {
                    terrain[current.list[j]->x][k] = '#';
                }
            }
            j++;
        }
    }

    return terrain;
}

int pour_sand(int** terrain, int lowest) {
    int filled = 0;
    int num_units = 0;

    while (!filled) {
        coords c;
        c.x = 500;
        c.y = 0;
        terrain[c.x][c.y] = 'o';
        int at_rest = 0;

        while (!at_rest) {
            coords next;
            next.x = c.x;
            next.y = c.y;
            int raw[3][2] = { {c.x, c.y + 1}, {c.x - 1, c.y + 1}, {c.x + 1, c.y + 1} };
            int i = 0;

            while (i < 3) {
                if (terrain[raw[i][0]][raw[i][1]] == '.') {
                    next.x = raw[i][0];
                    next.y = raw[i][1];
                    break;
                }
                i++;
            }

            if (c.x == next.x && c.y == next.y) {
                at_rest = 1;
                if (c.x == 500 && c.y == 0) {
                    filled = 1;
                }
            } else {
                terrain[c.x][c.y] = '.';
                terrain[next.x][next.y] = 'o';
                c = next;
            }
        }

        num_units++;
    }

    return num_units;
}
