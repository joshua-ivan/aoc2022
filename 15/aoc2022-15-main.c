#include <stdio.h>
#include <stdlib.h>
#include "aoc2022-15.h"

int main(int argc, char *argv[]) {
    int part2 = 1;

    radar_arr ra = init_radar("input.txt");
    if (part2) {
        unsigned long long freq = tuning_frequency(ra, 4000000, 4000000);
        printf("\n%lld\n", freq);
    } else {
        printf("%d\n", positions_wo_beacons(ra, 2000000));
    }

    return 0;
}
