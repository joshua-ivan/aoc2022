#include <stdio.h>
#include "aoc2022-24.h"

int main(int argc, char *argv[]) {
    valley v = parse_input("input.txt");

    int trips[3];
    trips[0] = traverse_valley(&v);
    printf("Part 1: %d\n", trips[0]);

    trips[1] = backtrack_valley(&v);
    trips[2] = traverse_valley(&v);
    printf("Part 2: %d\n", trips[0] + trips[1] + trips[2]);

    free_valley(&v);
    return 0;
}
