#include <stdio.h>
#include "aoc2022-20.h"

int main(int argc, char *argv[]) {
    long long* coords = grove_coords("input.txt", 0);
    long long sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += coords[i];
    }
    printf("Part 1: %lld\n", sum);

    coords = grove_coords("input.txt", 1);
    sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += coords[i];
    }
    printf("Part 2: %lld\n", sum);

    return 0;
}
