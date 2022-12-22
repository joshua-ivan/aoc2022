#ifndef AOC2022_18
#define AOC2022_18

#define MAX_DIM_SIZE 32

typedef struct {
    int matrix[MAX_DIM_SIZE][MAX_DIM_SIZE][MAX_DIM_SIZE];
} cube;
cube init_cube();
cube insert_cube(cube c, int x, int y, int z);
int surface_area(char* filename, int part2);
cube parse_input(char* filename);
int is_reachable(cube *c, cube *visited, int x, int y, int z);

#endif

