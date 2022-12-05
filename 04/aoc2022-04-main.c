#include <stdio.h>
#include <stdlib.h>
#include "aoc2022-04.h"

int main(int argc, char *argv[]) {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    int pairs = 0;
    while ((read = getline(&line, &length, fp)) != -1) {
        int *bounds = parse_assignment(line);
        pairs += check_overlap(bounds);
        free(bounds);
    }
    printf("%d\n", pairs);

    free(line);
    fclose(fp);

    return 0;
}

