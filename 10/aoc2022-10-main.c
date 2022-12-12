#include <stdio.h>
#include <stdlib.h>
#include "aoc2022-10.h"

int main(int argc, char *argv[]) {
    int graph_size = 241;
    int signal_graph[graph_size];
    for (int i = 0; i < graph_size; i++) {
        signal_graph[i] = 1;
    }

    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    int past_cycles = 0;
    while ((read = getline(&line, &length, fp)) != -1) {
        past_cycles = parse_instruction(line, signal_graph, past_cycles);
    }

    int nontrivial_signals[6] = {20, 60, 100, 140, 180, 220};
    int strength = 0;
    for (int i = 0; i < 6; i++) {
        strength += signal_strength(signal_graph, nontrivial_signals[i]);
    }
    printf("%d\n", strength);

    char **image = generate_image(signal_graph, graph_size);
    for (int i = 0; i < 6; i++) {
        printf("%s\n", image[i]);
    }

    for (int i = 0; i < 6; i++) {
        free(image[i]);
    }
    free(image);
    fclose(fp);
    return 0;
}
