#include <stdio.h>
#include <stdlib.h>
#include "aoc2022-08.h"

int main(int argc, char *argv[]) {
    char *filename = "input.txt";
    int* dims = get_matrix_bounds(filename);
    int width = dims[0];
    int height = dims[1];

    int **matrix = build_matrix(filename, width, height);
    int trees_visible = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            trees_visible += is_tree_visible(matrix, width, height, i, j);
        }
    }
    printf("Visible trees: %d\n", trees_visible);

    int max_scenic_score = -1;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int score = scenic_score(matrix, width, height, i, j);
            if (score > max_scenic_score) {
                max_scenic_score = score;
            }
        }
    }
    printf("Max scenic score: %d\n", max_scenic_score);

    for (int i = 0; i < height; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(dims);
    return 0;
}
