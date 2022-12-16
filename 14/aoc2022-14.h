#ifndef AOC2022_14
#define AOC2022_14

#include "../structs/coords.h"

coords to_coords(char *raw);
typedef struct {
    coords_list* rocks;
    int formations;
    int lowest;
} cave;
cave init_cave(char *filename);
int** build_terrain(cave c);
int pour_sand(int** terrain, int lowest);

#endif

