#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char rucksack_intersect(char *former, char *latter, int len) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (former[i] == latter[j]) {
                return former[i];
            }
        }
    }

    return -1;
}

char group_intersect(char *first, char *second, char* third) {
    int len_i = strlen(first);
    int len_j = strlen(second);
    int len_k = strlen(third);

    for (int i = 0; i < len_i; i++) {
        for (int j = 0; j < len_j; j++) {
            for (int k = 0; k < len_k; k++) {
                if (first[i] == second[j] && second[j] == third[k]) {
                    return first[i];
                }
            }
        }
    }

    return -1;
}

int get_compartment_length(char *rucksack) {
    int len = strlen(rucksack);
    if (rucksack[len - 1] == '\n') {
        len -= 1;
    }
    return len / 2;
}

int get_priority(char c) {
    if (islower(c)) {
        return c - 'a' + 1;
    } else {
        return c - 'A' + 27;
    }
}

int process_rucksack(char *rucksack) {
    int len = get_compartment_length(rucksack);

    char i = rucksack_intersect(rucksack, rucksack + len, len);

    return get_priority(i);
}
