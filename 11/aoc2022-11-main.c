#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc2022-11.h"

int main(int argc, char *argv[]) {
    char **base = load_base_strings();
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) exit(EXIT_FAILURE);

    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    monkey m[8];
    for (int i = 0; i < 8; i++) {
        char *input[6];
        for (int j = 0; j < 6; j++) {
            read = getline(&line, &length, fp);
            if (read == -1) exit(EXIT_FAILURE);
            int actual = get_significant_index(line, base[j]);

            char *sig_line = malloc(sizeof(char) * strlen(line + actual) + 1);
            strcpy(sig_line, line + actual);
            input[j] = sig_line;
        }
        m[i] = init_monkey(input);
        read = getline(&line, &length, fp);
    }

    long* inspections = simulate_monkeys(m, 8, 10000, 0);
    printf("%ld\n", calculate_monkey_business(inspections, 8));

    return 0;
}
