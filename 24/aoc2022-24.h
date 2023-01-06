#ifndef AOC2022_24
#define AOC2022_24

#define VECTOR_SET_LENGTH 65536

typedef struct blizzard {
    short* position;
    short* direction;
    struct blizzard* next;
} blizzard;
typedef struct map {
    short rows;
    short cols;
    short** spaces;
    short* entrance;
    short* exit;
} map;
typedef struct {
    blizzard* blizzard_list;
    map* map;
} valley;
valley parse_input(char* filename);
void free_valley(valley* v);

typedef struct {
    int length;
    short items[VECTOR_SET_LENGTH][2];
} vector_set;
vector_set init_vector_set();
int search_vector_set(vector_set* vs, int row, int col);
void push_vector_set(vector_set* al, int row, int col);
void pop_vector_set(vector_set* al, int index);

void take_step(valley* v, vector_set* vs);
void move_blizzards(valley* v);
int traverse_valley(valley* v);
int backtrack_valley(valley* v);

#endif
