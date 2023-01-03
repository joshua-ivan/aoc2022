#ifndef AOC2022_23
#define AOC2022_23

typedef struct {
    char** map;
    int rows;
    int cols;
    int elves;
} grove;
grove parse_input(char* filename);
void free_grove(grove* g);

int check_bounds(grove* g, int row, int col);
int check_row(grove* g, int row, int col);
int check_col(grove* g, int row, int col);
int check_north(grove* g, int row, int col);
int check_south(grove* g, int row, int col);
int check_west(grove* g, int row, int col);
int check_east(grove* g, int row, int col);
int check_adjacent(grove* g, int row, int col);

typedef struct order {
    int (*fn)(grove*,int,int);
    char* label;
    struct order* next;
} order;
order* init_orders();
void free_orders(order* o);

typedef struct {
    int** list;
    int list_len;
    int vect_len;
} moves;
moves propose_movements(grove* g, order* o);
void free_moves(moves* m);

void prune_duplicates(moves* m);
void move_elves(grove* g, moves* m);
void update_order(order** o);
int diffusion_complete(moves m);
void diffuse(grove* g, order** o);
int* align_bounds(grove g);
int count_empty_tiles(grove g);

#endif
