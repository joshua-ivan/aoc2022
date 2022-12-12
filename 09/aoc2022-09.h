#ifndef AOC2022_09
#define AOC2022_09

typedef struct {
    int x;
    int y;
} coords;

void move_head(coords* head, char direction);
void move_tail(coords* head, coords* tail);
void append_position_list(coords** list, coords *tail);
int count_positions_one(char *filename);
int count_positions_two(char *filename);

#endif

