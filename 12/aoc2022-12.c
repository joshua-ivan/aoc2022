#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "aoc2022-12.h"

int* get_matrix_bounds(char *filename) {
    int *dimensions = malloc(sizeof(int) * 2);
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        dimensions[0] = -1;
        dimensions[1] = -1;
        return dimensions;
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    int width = 0;
    if ((read = getline(&line, &length, fp)) != -1) {
        width = strlen(line) - 1;
    }
    int height = 1;
    while ((read = getline(&line, &length, fp)) != -1) {
        height++;
    }
    fclose(fp);

    dimensions[0] = width;
    dimensions[1] = height;
    return dimensions;
}

coords** init_coords_list(int width, int height) {
    int len = width * height;
    coords** list = malloc(sizeof(coords *) * len);

    for (int i = 0; i < len; i++) {
        list[i] = malloc(sizeof(coords));
        list[i]->x = -1;
        list[i]->y = -1;
    }

    return list;
}

void insert_coords_list(coords** list, coords* c, int max_size) {
    int i = 0;
    while (i < max_size && list[i]->x != -1 && list[i]->y != -1) {
        if (list[i]->x == c->x && list[i]->y == c->y) {
            return;
        }
        i++;
    }
    if (i < max_size) {
        list[i]->x = c->x;
        list[i]->y = c->y;
    }
}

int search_coords_list(coords** list, coords* c, int max_size) {
    int i = 0;
    while (i < max_size && list[i]->x != -1 && list[i]->y != -1) {
        if (list[i]->x == c->x && list[i]->y == c->y) {
            return i;
        }
        i++;
    }
    return -1;
}

void remove_coords_list(coords** list, coords* c, int max_size) {
    int i = search_coords_list(list, c, max_size);
    if (i < 0) {
        return;
    }
    while (i < max_size && list[i + 1]->x != -1 && list[i + 1]->y != -1) {
        list[i]->x = list[i + 1]->x;
        list[i]->y = list[i + 1]->y;
        i++;
    }
    list[i]->x = list[i + 1]->x;
    list[i]->y = list[i + 1]->y;
}

coords** get_waypoints(char *filename) {
    coords* start = malloc(sizeof(coords));
    start->x = -1;
    start->y = -1;
    coords* end = malloc(sizeof(coords));
    end->x = -1;
    end->y = -1;
    coords** waypoints = malloc(sizeof(coords *) * 2);
    waypoints[0] = start;
    waypoints[1] = end;

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return waypoints;
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    int i = 0;
    while ((read = getline(&line, &length, fp)) != -1) {
        for (int j = 0; j < length; j++) {
            switch (line[j]) {
                case 'S':
                    start->x = j;
                    start->y = i;
                    break;
                case 'E':
                    end->x = j;
                    end->y = i;
                    break;
            }
        }
        i++;
    }

    return waypoints;
}

int** init_heightmap(char *filename, int width, int height) {
    int** heightmap = malloc(sizeof(int *) * height);
    for (int i = 0; i < height; i++) {
        heightmap[i] = malloc(sizeof(int) * width);
        for (int j = 0; j < width; j++) {
            heightmap[i][j] = -1;
        }
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return heightmap;
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    for (int i = 0; i < height; i++) {
        if ((read = getline(&line, &length, fp)) == -1) {
            return heightmap;
        }
        for (int j = 0; j < width; j++) {
            char c = line[j];
            switch (c) {
                case 'S':
                    heightmap[i][j] = 0;
                    break;
                case 'E':
                    heightmap[i][j] = 'z' - 'a';
                    break;
                default:
                    heightmap[i][j] = c - 'a';
                    break;

            }
        }
    }

    return heightmap;
}

coords* get_closest_candidate(coords** candidates, int** distances, int max_size) {
    coords* closest = candidates[0];
    int i = 1;
    while (i < max_size && candidates[i]->x != -1 && candidates[i]->y != -1) {
        if (distances[candidates[i]->y][candidates[i]->x] < distances[closest->y][closest->x]) {
            closest = candidates[i];
        }
        i++;
    }
    return closest;
}

int traversible_not_visited(coords** visited, coords* src, coords* dest, int** heightmap, int map_rows, int map_cols) {
    if (src->y < 0 || src->y > map_rows - 1 || src->x < 0 || src->x > map_cols - 1) {
        return 0;
    }
    if (dest->y < 0 || dest->y > map_rows - 1 || dest->x < 0 || dest->x > map_cols - 1) {
        return 0;
    }
    if (search_coords_list(visited, dest, map_rows * map_cols) >= 0) {
        return 0;
    }
    int diff = heightmap[dest->y][dest->x] - heightmap[src->y][src->x];
    return diff <= 1;
}

int shortest_path(char* filename, int part2) {
    int* dims = get_matrix_bounds(filename);
    int** map = init_heightmap(filename, dims[0], dims[1]);
    coords** candidates = init_coords_list(dims[0], dims[1]);
    coords** visited = init_coords_list(dims[0], dims[1]);
    coords** waypoints = get_waypoints(filename);

    int** distances = malloc(sizeof(int *) * dims[1]);
    for (int i = 0; i < dims[1]; i++) {
        distances[i] = malloc(sizeof(int) * dims[0]);
        for (int j = 0; j < dims[0]; j++) {
            distances[i][j] = INT_MAX;
        }
    }
    distances[waypoints[1]->y][waypoints[1]->x] = 0;
    insert_coords_list(candidates, waypoints[1], dims[0] * dims[1]);

    coords* current = get_closest_candidate(candidates, distances, dims[0] * dims[1]);
    while (current->x != -1 && current->y != -1) {
        coords** directions = malloc(sizeof(coords *) * 4);
        int raw_dirs[4][2] = {
            {current->y - 1, current->x},
            {current->y, current->x - 1},
            {current->y, current->x + 1},
            {current->y + 1, current->x}
        };
        for (int i = 0; i < 4; i++) {
            directions[i] = malloc(sizeof(coords));
            directions[i]->y = raw_dirs[i][0];
            directions[i]->x = raw_dirs[i][1];

            if (traversible_not_visited(visited, directions[i], current, map, dims[1], dims[0])) {
                distances[directions[i]->y][directions[i]->x] = distances[current->y][current->x] + 1;
                insert_coords_list(candidates, directions[i], dims[0] * dims[1]);
            }
        }

        insert_coords_list(visited, current, dims[0] * dims[1]);
        remove_coords_list(candidates, current, dims[0] * dims[1]);

        for (int i = 0; i < 4; i++) {
            free(directions[i]);
        }
        free(directions);

        if (part2 && map[current->y][current->x] == 0) {
            return distances[current->y][current->x];
        }
        current = get_closest_candidate(candidates, distances, dims[0] * dims[1]);
    }

    return distances[waypoints[0]->y][waypoints[0]->x];
}

