#include <stdio.h>
#include <stdlib.h>
#include "aoc2022-23.h"

int main(int argc, char *argv[]) {
    grove g = parse_input("input.txt");
    order* o = init_orders();

    int count = 1;
    for (int i = 0; i < 10; i++) {
        diffuse(&g, &o);
        count++;
    }
    printf("Part 1: %d\n", count_empty_tiles(g));

    int complete = 0;
    while (!complete) {
        diffuse(&g, &o);
        moves m = propose_movements(&g, o);
        complete = diffusion_complete(m);
        free_moves(&m);
        count++;
    }
    printf("Part 2: %d\n", count);

    free_orders(o);
    free_grove(&g);
    return 0;
}
