#include <stdio.h>
#include <stdlib.h>
#include "aoc2022-18.h"

cube init_cube() {
    cube c;
    for (int i = 0; i < MAX_DIM_SIZE; i++) {
        for (int j = 0; j < MAX_DIM_SIZE; j++) {
            for (int k = 0; k < MAX_DIM_SIZE; k++) {
                c.matrix[i][j][k] = 0;
            }
        }
    }

    return c;
}

cube insert_cube(cube c, int x, int y, int z) {
    c.matrix[x][y][z] = 1;
    return c;
}

cube parse_input(char* filename) {
    cube c = init_cube();
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return c;
    }

    int x = 0;
    int y = 0;
    int z = 0;
    int read = 3;
    while ((read = fscanf(fp, "%d,%d,%d\n", &x, &y, &z)) == 3) {
        c = insert_cube(c, x, y, z);
    }

    fclose(fp);
    return c;
}

int is_reachable(cube *c, cube *visited, int x, int y, int z) {
    if (x < 0 || x >= MAX_DIM_SIZE || y < 0 || y >= MAX_DIM_SIZE || z < 0 || z >= MAX_DIM_SIZE) {
        return 1;
    }
    if (visited->matrix[x][y][z]) {
        return 0;
    }
    visited->matrix[x][y][z] = 1;
    if (c->matrix[x][y][z]) {
        return 0;
    }
    return is_reachable(c, visited, x - 1, y, z)
        || is_reachable(c, visited, x + 1, y, z)
        || is_reachable(c, visited, x, y - 1, z)
        || is_reachable(c, visited, x, y + 1, z)
        || is_reachable(c, visited, x, y, z - 1)
        || is_reachable(c, visited, x, y, z + 1);
}

int surface_area(char* filename, int part2) {
    int sa = -1;

    cube c = parse_input(filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return sa;
    }

    int x = 0;
    int y = 0;
    int z = 0;
    int read = 3;
    sa = 0;
    while ((read = fscanf(fp, "%d,%d,%d\n", &x, &y, &z)) == 3) {
        int coords[6][3] = {
            {x - 1, y, z},
            {x + 1, y, z},
            {x, y - 1, z},
            {x, y + 1, z},
            {x, y, z - 1},
            {x, y, z + 1},
        };
        for (int i = 0; i < 6; i++) {
            if (part2) {
                cube visited = init_cube();
                sa += is_reachable(&c, &visited, coords[i][0], coords[i][1], coords[i][2]);
            } else {
                sa += !c.matrix[coords[i][0]][coords[i][1]][coords[i][2]];
            }
        }
    }

    return sa;
}
