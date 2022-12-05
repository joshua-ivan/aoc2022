#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc2022-05.h"

stack stack_init() {
    stack s;
    s.index = 0;
    s.items = malloc(sizeof(char) * AOC_STACK_SIZE);
    for (int i = 0; i < AOC_STACK_SIZE; i++) {
        s.items[i] = ' ';
    }
    return s;
}

void stack_push(stack *s, char c) {
    s->items[(s->index)++] = c;
}

char stack_pop(stack *s) {
    return s->items[--(s->index)];
}

stack* init_storage(FILE *fp, int num_stacks) {
    stack *reverse_temp = malloc(num_stacks * sizeof(*reverse_temp));
    for (int i = 0; i < num_stacks; i++) {
        reverse_temp[i] = stack_init();
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    while ((read = getline(&line, &length, fp)) != -1) {
        if (line[1] == '1') {
            // skip stack label line
            getline(&line, &length, fp);
            break;
        }
        for (int i = 0; i < num_stacks; i++) {
            int crate_index = (i * 4) + 1;
            if (line[crate_index] != ' ') {
                stack_push(&reverse_temp[i], line[crate_index]);
            }
        }
    }

    stack *storage = malloc(num_stacks * sizeof(*storage));
    for (int i = 0; i < num_stacks; i++) {
        storage[i] = stack_init();
        while (reverse_temp[i].index > 0) {
            stack_push(&storage[i], stack_pop(&reverse_temp[i]));
        }
    }

    return storage;
}

int* parse_instruction(char *c) {
    int len = strlen(c);
    char *inst = malloc(sizeof(char) * len);
    strcpy(inst, c);

    int *inst_nums = malloc(sizeof(int) * 3);
    strtok(inst, " "); // move
    inst_nums[0] = atoi(strtok(NULL, " "));

    strtok(NULL, " "); // from
    inst_nums[1] = atoi(strtok(NULL, " ")) - 1;

    strtok(NULL, " "); // to
    inst_nums[2] = atoi(strtok(NULL, " ")) - 1;

    free(inst);
    return inst_nums;
}

