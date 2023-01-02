#ifndef AOC2022_22
#define AOC2022_22

#define CUBE_MATRIX_ROWS 14
#define CUBE_MATRIX_COLS 9

typedef struct {
    char** map;
    int num_rows;
    int num_cols;
    char* directions;
    int avatar_row;
    int avatar_col;
    char facing;
} board;
typedef struct {
    int edges[CUBE_MATRIX_ROWS][CUBE_MATRIX_COLS];
} cube;

board parse_input(char* filename);
void free_board(board b);
void move_avatar(board* b, int steps, cube* c);
void turn_avatar(board* b, char direction);
void run_directions(board* b, cube* c);
int calc_pass(board* b);
cube load_cube(char* filename);
int is_along_edge(int* edge, int row, int col);
int calc_dest_offset(int* edge, int row, int col);
int* get_destination(int* edge, int offset, char facing);
void traverse_edge(board* b, cube* c);

#endif
