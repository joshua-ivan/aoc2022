#include <stdio.h>
#include <stdlib.h>
#include "aoc2022-10.h"

int parse_instruction(char* inst, int* signal_graph, int past_cycles) {
    int cycles = past_cycles;
    signal_graph[cycles + 1] = signal_graph[cycles];
    cycles++;
    switch (inst[0]) {
        case 'a': // addx
            signal_graph[cycles + 1] = signal_graph[cycles] + atoi(inst + 4);
            cycles++;
            break;
        case 'n': // noop
            break;
    }
    return cycles;
}

int signal_strength(int* signal_graph, int cycle) {
    return cycle * signal_graph[cycle - 1];
}

char** generate_image(int* signal_graph, int graph_size) {
    char **image = malloc(sizeof(char *) * 6);
    for (int i = 0; i < 6; i++) {
        image[i] = malloc(sizeof(char) * 41);
        image[i][40] = '\0';
    }

    for (int i = 0; i < graph_size - 1; i++) {
        int row = i / 40;
        int col = i % 40;
        int drawing = (signal_graph[i] >= col - 1 && signal_graph[i] <= col + 1);
        image[row][col] = (drawing) ? '#' : '.';
    }

    return image;
}
