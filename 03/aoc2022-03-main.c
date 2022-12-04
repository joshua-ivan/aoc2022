#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc2022-03.h"

int main(int argc, char *argv[]) {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    char *rucksacks[3];
    for (int i = 0; i < 3; i++) {
        rucksacks[i] = malloc(sizeof(char));
    }
    int priority_sum = 0;
    int order = 0;
    while ((read = getline(&line, &length, fp)) != -1) {
        free(rucksacks[order]);
        rucksacks[order] = malloc(sizeof(char) * strlen(line));
        strcpy(rucksacks[order], line);

        if (order == 2) {
            char badge = group_intersect(rucksacks[0], rucksacks[1], rucksacks[2]);
            priority_sum += get_priority(badge);
        }
        order = (order + 1) % 3;
    }
    printf("%d\n", priority_sum);

    for (int i = 0; i < 3; i++) {
        free(rucksacks[i]);
    }
    free(line);
    fclose(fp);

    return 0;
}

