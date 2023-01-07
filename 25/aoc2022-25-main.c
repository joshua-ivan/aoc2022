#include <stdio.h>
#include <stdlib.h>
#include "aoc2022-25.h"

int main(int argc, char *argv[]) {
    char* sum = sum_file("input.txt");
    printf("%s\n", sum);
    free(sum);
    return 0;
}
