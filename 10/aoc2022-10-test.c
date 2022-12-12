#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minunit.h"
#include "aoc2022-10.h"

int tests_run = 0;

static char const * test_parse_instruction() {
    int signal_graph[6];
    for (int i = 0; i < 6; i++) {
        signal_graph[i] = 1;
    }
    int past_cycles = 0;

    past_cycles = parse_instruction("noop", signal_graph, past_cycles);
    past_cycles = parse_instruction("addx 3", signal_graph, past_cycles);
    past_cycles = parse_instruction("addx -5", signal_graph, past_cycles);

    int expected_signal[6] = {1, 1, 1, 4, 4, -1};
    char const * failure_msg = "FAILURE: test_parse_instruction";
    for (int i = 0; i < 6; i++) {
        mu_assert(failure_msg, signal_graph[i] == expected_signal[i]);
    }

    return 0;
}

static char const * test_signal_strength() {
    int graph_size = 241;
    int signal_graph[graph_size];
    for (int i = 0; i < graph_size; i++) {
        signal_graph[i] = 1;
    }

    FILE *fp = fopen("test_cases/test.txt", "r");
    if (fp == NULL) {
        char const * failure_msg = "FAILURE: test_signal_strengths__test_input";
        mu_assert(failure_msg, 0 == 1);
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    int past_cycles = 0;
    while ((read = getline(&line, &length, fp)) != -1) {
        past_cycles = parse_instruction(line, signal_graph, past_cycles);
    }

    int nontrivial_signals[6] = {20, 60, 100, 140, 180, 220};
    int expected_strengths[6] = {420, 1140, 1800, 2940, 2880, 3960};
    char const * failure_msg = "FAILURE: test_signal_strengths";
    for (int i = 0; i < 6; i++) {
        int actual_strength = signal_strength(signal_graph, nontrivial_signals[i]);
        mu_assert(failure_msg, expected_strengths[i] == actual_strength);
    }

    fclose(fp);
    return 0;
}

static char const * test_generate_image() {
    int graph_size = 241;
    int signal_graph[graph_size];
    for (int i = 0; i < graph_size; i++) {
        signal_graph[i] = 1;
    }

    FILE *code_fp = fopen("test_cases/test.txt", "r");
    if (code_fp == NULL) {
        char const * failure_msg = "FAILURE: test_generate_image__test_input";
        mu_assert(failure_msg, 0 == 1);
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    int past_cycles = 0;
    while ((read = getline(&line, &length, code_fp)) != -1) {
        past_cycles = parse_instruction(line, signal_graph, past_cycles);
    }
    char **actual_image = generate_image(signal_graph, graph_size);

    FILE *image_fp = fopen("test_cases/test-image.txt", "r");
    if (image_fp == NULL) {
        char const * failure_msg = "FAILURE: test_generate_image__test_image";
        mu_assert(failure_msg, 0 == 1);
    }

    char const * failure_msg = "FAILURE: test_generate_image";
    int row = 0;
    while ((read = getline(&line, &length, image_fp)) != -1) {
        line[40] = '\0';
        mu_assert(failure_msg, !strcmp(line, actual_image[row++]));
    }

    for (int i = 0; i < row; i++) {
        free(actual_image[i]);
    }
    free(actual_image);
    return 0;
}

static char const * all_tests() {
    mu_run_test(test_parse_instruction);
    mu_run_test(test_signal_strength);
    mu_run_test(test_generate_image);

    return 0;
}

int main(int argc, char **argv) {
    char const *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}

