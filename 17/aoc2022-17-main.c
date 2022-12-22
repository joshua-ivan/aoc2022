#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc2022-17.h"

int main(int argc, char *argv[]) {
    well v = sim("input.txt", 2022, 0);
    printf("%lld\n", v.highest_rock);
    long long w = simulate("input.txt", 1000000000000);
    printf("%lld\n", w);

    return 0;
}
