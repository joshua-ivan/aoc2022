#include <stdio.h>
#include <stdlib.h>
#include "aoc2022-14.h"

int main(int argc, char *argv[]) {
    cave c = init_cave("input.txt");
    int** terrain = build_terrain(c);
    int units = pour_sand(terrain, c.lowest);
    printf("%d\n", units);

    return 0;
}
