#ifndef AOC2022_08
#define AOC2022_08

int *get_matrix_bounds(char *filename);
int** build_matrix(char* filename, int width, int height);
int is_tree_visible(int **matrix, int width, int height, int row, int col);
int scenic_score(int **matrix, int width, int height, int row, int col);

#endif

