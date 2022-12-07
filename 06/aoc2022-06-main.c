#include <stdio.h>
#include <stdlib.h>
#include "aoc2022-06.h"

int main(int argc, char *argv[]) {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    int num_chars = 0;
    while ((read = getline(&line, &length, fp)) != -1) {
        num_chars = get_start_marker(line, 14);
    }
    printf("%d\n", num_chars);

    free(line);
    fclose(fp);

    return 0;
}

