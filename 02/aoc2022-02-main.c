#include <stdio.h>
#include <stdlib.h>
#include "aoc2022-02.h"

int main(int argc, char *argv[]) {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    int score = 0;
    while ((read = getline(&line, &length, fp)) != -1) {
        score += final_score(line[0], line[2]);
    }
    printf("%d\n", score);

    free(line);
    fclose(fp);

    return 0;
}
