#include <stdio.h>
#include <stdlib.h>
#include "aoc2022-07.h"

int main(int argc, char *argv[]) {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    hashtable ht = parse_output(fp);
    printf("%d\n", solve_puzzle_one(&ht));
    printf("%d\n", solve_puzzle_two(&ht));

    return 0;
}
