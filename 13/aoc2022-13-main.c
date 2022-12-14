#include <stdio.h>
#include <stdlib.h>
#include "aoc2022-13.h"

int main(int argc, char *argv[]) {
    int part2 = 1;

    if (part2) {
        packet *ps = sort_packets("input.txt");
        printf("%d\n", get_decoder_key(ps));
        return 0;
    } else {
        FILE *fp = fopen("input.txt", "r");
        if (fp == NULL) {
            exit(EXIT_FAILURE);
        }

        char *line = NULL;
        size_t length = 0;
        ssize_t read;
        int sum = 0;
        int index = 1;
        while ((read = getline(&line, &length, fp)) != -1) {
            packet p;
            parse_packet(&p, line);
            if ((read = getline(&line, &length, fp)) == -1) {
                break;
            }
            packet q;
            parse_packet(&q, line);

            if (compare_packets(p, q) > 0) {
                sum += index;
            }

            getline(&line, &length, fp); // newline
            index++;
        }
        printf("%d\n", sum);

        fclose(fp);
        return 0;
    }
}
