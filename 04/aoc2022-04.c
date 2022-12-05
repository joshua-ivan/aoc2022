#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc2022-04.h"

int* parse_assignment(char *raw) {
    int raw_len = strlen(raw);
    char *copy = malloc(sizeof(char) * raw_len);
    strcpy(copy, raw);

    char delims[3] = "-,-";
    char *bound_str = strtok(copy, delims);
    int *bounds = malloc(sizeof(int) * 4);
    bounds[0] = atoi(bound_str);

    for (int i = 1; i < 4; i++) {
        bound_str = strtok(NULL, delims);
        bounds[i] = atoi(bound_str);
    }

    free(copy);
    return bounds;
}

int check_bounds(int *bounds) {
    return (bounds[0] <= bounds[2] && bounds[1] >= bounds[3])
        || (bounds[2] <= bounds[0] && bounds[3] >= bounds[1]);
}

int check_overlap(int *bounds) {
    return (bounds[2] <= bounds[1] && bounds[1] <= bounds[3])
        || (bounds[2] <= bounds[0] && bounds[0] <= bounds[3])
        || (bounds[0] <= bounds[3] && bounds[3] <= bounds[1])
        || (bounds[0] <= bounds[2] && bounds[2] <= bounds[1]);
}
