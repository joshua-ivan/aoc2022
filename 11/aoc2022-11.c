#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc2022-11.h"

char** load_base_strings() {
    FILE *fp = fopen("base.txt", "r");
    if (fp == NULL) exit(EXIT_FAILURE);

    char **base_strings = malloc(sizeof(char *) * NUM_BASE_STRINGS);

    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    int i = 0;
    while ((read = getline(&line, &length, fp)) != -1) {
        char* cpy = malloc(sizeof(char) * length);
        strcpy(cpy, line);

        char* newline = strchr(cpy, '\n');
        newline[0] = '\0';

        base_strings[i++] = cpy;
    }

    fclose(fp);
    return base_strings;
}

void free_base_strings(char **str) {
    for (int i = 0; i < NUM_BASE_STRINGS; i++) {
        free(str[i]);
    }
    free(str);
}

int get_significant_index(char* input_str, char* base_str) {
    int i = 0;
    while (input_str[i] == base_str[i]) i++;
    return i;
}

void set_items(monkey *m, char *item_str) {
    for (int i = 0; i < MAX_ITEMS; i++) {
        m->items[i] = -1;
    }

    int len = strlen(item_str) + 1;
    char *cpy = malloc(sizeof(char) * len);
    strcpy(cpy, item_str);

    m->num_items = 0;
    char *current = strtok(cpy, " ");
    while (current != NULL && m->num_items < MAX_ITEMS) {
        int worry = atoi(current);
        m->items[m->num_items++] = worry;
        current = strtok(NULL, " ");
    }

    free(cpy);
}

long compute_operand(long old, char* raw) {
    long operand = (!strcmp(raw, "old")) ? old : atoi(raw);
    return operand;
}

void add(long* old, char* raw, long modulo) {
    *old = (*old + compute_operand(*old, raw)) % modulo;
}

void multiply(long* old, char* raw, long modulo) {
    *old = (*old * compute_operand(*old, raw)) % modulo;
}

void set_operation(monkey *m, char *op_str) {
    int len = strlen(op_str) + 1;
    char *cpy = malloc(sizeof(char) * len);
    strcpy(cpy, op_str);

    char *current = strtok(cpy, " ");
    switch (current[0]) {
        case '+':
            m->op = &add;
            break;
        case '*':
            m->op = &multiply;
            break;
    }

    current = strtok(NULL, " ");
    char* newline = strchr(current, '\n');
    if (newline != NULL) newline[0] = '\0';
    char* op = malloc(sizeof(char) * strlen(current) + 1);
    strcpy(op, current);
    m->operand = op;
    
    free(cpy);
}

void throw_item(monkey *from, monkey *to) {
    to->items[to->num_items++] = from->items[0];
    int i = 0;
    while (i < from->num_items - 1) {
        from->items[i] = from->items[i + 1];
        i++;
    }
    from->items[i] = -1;
    from->num_items--;
}

monkey init_monkey(char **raw) {
    monkey m;
    set_items(&m, raw[1]);
    set_operation(&m, raw[2]);
    m.test = atoi(raw[3]);
    m.monkey_t = atoi(raw[4]);
    m.monkey_f = atoi(raw[5]);
    return m;
}

long* simulate_monkeys(monkey *m, int monkeys, int rounds, int part1) {
    long *inspections = malloc(sizeof(long) * monkeys);
    for (int i = 0; i < monkeys; i++) {
        inspections[i] = 0;
    }

    long modulo_cap = 1;
    for (int i = 0; i < monkeys; i++) {
        modulo_cap *= m[i].test;
    }

    for (int i = 0; i < rounds; i++) {
        for (int j = 0; j < monkeys; j++) {
            while (m[j].items[0] >= 0) {
                inspections[j]++;
                (m[j].op)(&m[j].items[0], m[j].operand, modulo_cap);
                if (part1) m[j].items[0] /= 3;
                int test = m[j].items[0] % m[j].test == 0;
                int target = test ? m[j].monkey_t : m[j].monkey_f;
                throw_item(&m[j], &m[target]);
            }
        }
    }

    return inspections;
}

int comp(const void *a, const void *b) {
    long x = *((long *) a);
    long y = *((long *) b);
    if (x > y) return -1;
    if (y > x) return 1;
    return 0;
}

long calculate_monkey_business(long* inspections, int monkeys) {
    qsort(inspections, monkeys, sizeof(long), comp);
    return inspections[0] * inspections[1];
}

