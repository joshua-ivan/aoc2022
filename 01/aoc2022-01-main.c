#include <stdio.h>
#include "aoc2022-01.h"

int main(int argc, char *argv[]) {
    node *head = build_calorie_list("input.txt");
    int max = max_value(head);
    printf("%d\n", max);
    int sum = top_n_sum(head, 3);
    printf("%d\n", sum);
}

