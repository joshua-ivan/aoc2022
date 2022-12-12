#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc2022-08.h"

int* get_matrix_bounds(char *filename) {
    int *dimensions = malloc(sizeof(int) * 2);
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        dimensions[0] = -1;
        dimensions[1] = -1;
        return dimensions;
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    int width = 0;
    if ((read = getline(&line, &length, fp)) != -1) {
        width = strlen(line) - 1;
    }
    int height = 1;
    while ((read = getline(&line, &length, fp)) != -1) {
        height++;
    }
    fclose(fp);

    dimensions[0] = width;
    dimensions[1] = height;
    return dimensions;
}

int** build_matrix(char* filename, int width, int height) {
    if (width < 0 || height < 0) {
        int **matrix = malloc(sizeof(int*));
        matrix[0] = malloc(sizeof(int));
        matrix[0][0] = -1;
        return matrix;
    }

    int **matrix = malloc(sizeof(int*) * height);
    for (int i = 0; i < height; i++) {
        matrix[i] = malloc(sizeof(int) * width);
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            matrix[i][j] = -1;
        }
    }
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return matrix;
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    int i = 0;
    while ((read = getline(&line, &length, fp)) != -1 && i < height) {
        for (int j = 0; j < width; j++) {
            matrix[i][j] = line[j] - '0';
        }
        i++;
    }
    fclose(fp);

    return matrix;
}

int is_tree_visible(int **matrix, int width, int height, int row, int col) {
    if (row == 0 || col == 0 || row == (height - 1) || col == (width - 1)) {
        return 1;
    }

    int visible_top = 1;
    for (int i = 0; i < row; i++) {
        if (matrix[i][col] >= matrix[row][col]) {
            visible_top = 0;
            break;
        }
    }

    int visible_left = 1;
    for (int j = 0; j < col; j++) {
        if (matrix[row][j] >= matrix[row][col]) {
            visible_left = 0;
            break;
        }
    }

    int visible_right = 1;
    for (int j = col + 1; j < width; j++) {
        if (matrix[row][j] >= matrix[row][col]) {
            visible_right = 0;
            break;
        }
    }

    int visible_bottom = 1;
    for (int i = row + 1; i < height; i++) {
        if (matrix[i][col] >= matrix[row][col]) {
            visible_bottom = 0;
            break;
        }
    }

    return (visible_top || visible_left || visible_right || visible_bottom);
}

int scenic_score(int **matrix, int width, int height, int row, int col) {
    int top_distance = 0;
    for (int i = row - 1; i >= 0; i--) {
        top_distance++;
        if (matrix[i][col] >= matrix[row][col]) {
            break;
        }
    }

    int left_distance = 0;
    for (int j = col - 1; j >= 0; j--) {
        left_distance++;
        if (matrix[row][j] >= matrix[row][col]) {
            break;
        }
    }

    int right_distance = 0;
    for (int j = col + 1; j < width; j++) {
        right_distance++;
        if (matrix[row][j] >= matrix[row][col]) {
            break;
        }
    }

    int bottom_distance = 0;
    for (int i = row + 1; i < height; i++) {
        bottom_distance++;
        if (matrix[i][col] >= matrix[row][col]) {
            break;
        }
    }

    return top_distance * left_distance * right_distance * bottom_distance;
}

