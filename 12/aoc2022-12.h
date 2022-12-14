#ifndef AOC2022_12
#define AOC2022_12

typedef struct {
    int x;
    int y;
} coords;
coords** init_coords_list(int width, int height);
void insert_coords_list(coords** list, coords* c, int max_size);
int search_coords_list(coords** list, coords* c, int max_size);
void remove_coords_list(coords** list, coords* c, int max_size);

int* get_matrix_bounds(char *filename);
int** init_heightmap(char *filename, int width, int height);
coords** get_waypoints(char *filename);
coords* get_closest_candidate(coords** candidates, int** distances, int max_size);
int traversible_not_visited(coords** visited, coords* src, coords* dest, int** heightmap, int map_rows, int map_cols);
int shortest_path(char* filename, int part2);

#endif
