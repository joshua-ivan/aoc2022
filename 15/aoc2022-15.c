#include <stdio.h>
#include <stdlib.h>
#include "aoc2022-15.h"

radar_arr init_radar(char* filename) {
    radar_arr ra;
    ra.list = malloc(sizeof(radar *) * MAX_RADAR);
    for (int i = 0; i < MAX_RADAR; i++) {
        ra.list[i] = NULL;
    }
    ra.count = 0;

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return ra;
    }

    int read = 4;
    while (read == 4) {
        ra.list[ra.count] = malloc(sizeof(radar));
        read = fscanf(fp, "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d\n",
                &ra.list[ra.count]->sensor.x, &ra.list[ra.count]->sensor.y,
                &ra.list[ra.count]->beacon.x, &ra.list[ra.count]->beacon.y);
        ra.count++;
    }

    return ra;
}

int taxicab_dist(coords a, coords b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int leftover_range(coords sensor, int max_range, int y) {
    coords temp;
    temp.x = sensor.x;
    temp.y = y;

    return max_range - taxicab_dist(sensor, temp);
}

radar_range_arr calculate_ranges(radar_arr ra, int y) {
    radar_range_arr rra;
    rra.list = malloc(sizeof(radar_range *) * ra.count);
    for (int i = 0; i < ra.count; i++) {
        rra.list[i] = NULL;
    }
    rra.count = 0;

    for (int i = 0; i < ra.count; i++) {
        int max_range = taxicab_dist(ra.list[i]->sensor, ra.list[i]->beacon);
        int leftover;
        if ((leftover = leftover_range(ra.list[i]->sensor, max_range, y)) >= 0) {
            rra.list[rra.count] = malloc(sizeof(radar_range));
            rra.list[rra.count]->start.x = ra.list[i]->sensor.x - leftover;
            rra.list[rra.count]->start.y = y;
            rra.list[rra.count]->end.x = ra.list[i]->sensor.x + leftover;
            rra.list[rra.count]->end.y = y;
            rra.count++;
        }
    }

    return rra;
}

int is_overlapping(radar_range a, radar_range b) {
    return ((b.start.x <= a.start.x) && (a.start.x <= b.end.x))
            || ((b.start.x <= a.end.x) && (a.end.x <= b.end.x))
            || ((a.start.x <= b.start.x) && (b.start.x <= a.end.x))
            || ((a.start.x <= b.end.x) && (b.end.x <= a.end.x));
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void prune_overlap(radar_range_arr* rra) {
    if (rra->count < 2) {
        return;
    } else {
        int overlap = 0;
        for (int i = 0; i < rra->count; i++) {
            for (int j = i + 1; j < rra->count; j++) {
                if (is_overlapping(*(rra->list[i]), *(rra->list[j]))) {
                    overlap = 1;

                    rra->list[i]->start.x = min(rra->list[i]->start.x, rra->list[j]->start.x);
                    rra->list[i]->end.x = max(rra->list[i]->end.x, rra->list[j]->end.x);

                    for (int k = j + 1; k < rra->count; k++) {
                        rra->list[k - 1] = rra->list[k];
                    }
                    rra->count--;

                    break;
                }
            }

            if (overlap) {
                break;
            }
        }

        if (overlap) {
            prune_overlap(rra);
        }
    }
}

int positions_wo_beacons(radar_arr ra, int y) {
    radar_range_arr ranges = calculate_ranges(ra, y);
    prune_overlap(&ranges);

    int beacons_in_range = 0;
    coords_list beacons = init_coords_list(ra.count);
    for (int i = 0; i < ra.count; i++) {
        if (ra.list[i]->beacon.y == y && search_coords_list(beacons, &(ra.list[i]->beacon)) == -1) {
            beacons_in_range++;
            insert_coords_list(beacons, &(ra.list[i]->beacon));
        }
    }

    int positions = 0;
    for (int i = 0; i < ranges.count; i++) {
        positions += (abs(ranges.list[i]->start.x - ranges.list[i]->end.x) + 1);
    }

    return positions - beacons_in_range;
}

unsigned long long tuning_frequency(radar_arr ra, int search_x, int search_y) {
    for (int y = 0; y <= search_y; y++) {
        printf("Scanning y=%d\r", y);
        radar_range_arr ranges = calculate_ranges(ra, y);
        prune_overlap(&ranges);

        if (ranges.count == 1) {
            if (ranges.list[0]->start.x > 0) {
                unsigned long long y_coord = y;
                return y_coord;
            } else if (ranges.list[0]->end.x < search_x) {
                unsigned long long x_coord = search_x;
                return x_coord * 4000000 + y;
            }
        } else {
            for (int i = 0; i < ranges.count; i++) {
                for (int j = i + 1; j < ranges.count; j++) {
                    if ((ranges.list[i]->end.x + 2 == ranges.list[j]->start.x)
                            && (0 <= ranges.list[i]->end.x + 1 && ranges.list[i]->end.x + 1 <= search_x)) {
                        unsigned long long x_coord = ranges.list[i]->end.x + 1;
                        return x_coord * 4000000 + y;
                    }
                    if ((ranges.list[j]->end.x + 2 == ranges.list[i]->start.x)
                            && (0 <= ranges.list[j]->end.x + 1 && ranges.list[j]->end.x + 1 <= search_x)) {
                        unsigned long long x_coord = ranges.list[j]->end.x + 1;
                        return x_coord * 4000000 + y;
                    }
                }
            }
        }
    }

    return -1;
}
