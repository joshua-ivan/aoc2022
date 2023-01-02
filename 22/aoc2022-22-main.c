#include <stdio.h>
#include "aoc2022-22.h"

int main(int argc, char *argv[]) {
    board b1 = parse_input("input.txt");
    run_directions(&b1, NULL);
    printf("Part 1: %d\n", calc_pass(&b1));
    free_board(b1);

    board b2 = parse_input("input.txt");
    cube c = load_cube("cube.txt");
    run_directions(&b2, &c);
    printf("Part 2: %d\n", calc_pass(&b2));
    free_board(b2);

    return 0;
}
