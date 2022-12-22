#ifndef AOC2022_17
#define AOC2022_17

extern char const I_BLOCK[4][4];
extern char const O_BLOCK[4][4];
extern char const J_BLOCK[4][4];
extern char const X_BLOCK[4][4];
extern char const L_BLOCK[4][4];

extern char const I_BLOCK__EXPECTED[7][7];
extern char const O_BLOCK__EXPECTED[7][7];
extern char const J_BLOCK__EXPECTED[7][7];
extern char const X_BLOCK__EXPECTED[7][7];
extern char const L_BLOCK__EXPECTED[7][7];

#define AOC_MAX_HEIGHT 65536

typedef struct {
    char well[AOC_MAX_HEIGHT][7];
    int anchor_row;
    int anchor_col;
    long long highest_rock;
    int blocked;
    int loop_start;
    int loop_blocks;
    int loop_height;
} well;
well init_well();

well spawn_rock(well w, char **block);
well move_hori(well w, char **block, int direction);
well move_down(well w, char **block);
char** load_block(const char block[4][4]);
well sim(char* filename, long long num_blocks, int check_loop);
long long simulate(char* filename, long long num_blocks);

#endif
