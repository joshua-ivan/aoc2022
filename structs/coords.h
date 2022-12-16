#ifndef AOC_COORDS
#define AOC_COORDS

typedef struct {
    int x;
    int y;
} coords;
typedef struct {
    coords **list;
    int max_len;
} coords_list;

coords_list init_coords_list(int max_len);
void insert_coords_list(coords_list li, coords* c);
int search_coords_list(coords_list li, coords* c);
void remove_coords_list(coords_list li, coords* c);

#endif

