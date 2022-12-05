#include <stdio.h>
#include <stdlib.h>
#include "aoc2022-05.h"

int main(int argc, char *argv[]) {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    int num_stacks = 9;
    stack *storage = init_storage(fp, num_stacks + 1);

    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    while ((read = getline(&line, &length, fp)) != -1) {
        int *inst = parse_instruction(line);

        for (int i = 0; i < inst[0]; i++) {
            stack_push(&storage[num_stacks], stack_pop(&storage[inst[1]]));
        }

        for (int i = 0; i < inst[0]; i++) {
            stack_push(&storage[inst[2]], stack_pop(&storage[num_stacks]));
        }

        free(inst);
    }

    for (int i = 0; i < num_stacks; i++) {
        printf("%c", stack_pop(&storage[i]));
    }
    printf("\n");

    free(line);
    fclose(fp);

    return 0;
}

