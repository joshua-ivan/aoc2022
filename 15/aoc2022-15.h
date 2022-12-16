#ifndef AOC2022_15
#define AOC2022_15

#include "../structs/coords.h"
#define MAX_RADAR 64

typedef struct {
    coords sensor;
    coords beacon;
} radar;
typedef struct {
    radar** list;
    int count;
} radar_arr;
typedef struct {
    coords start;
    coords end;
} radar_range;
typedef struct {
    radar_range** list;
    int count;
} radar_range_arr;
radar_arr init_radar(char* filename);
int taxicab_dist(coords a, coords b);
radar_range_arr calculate_ranges(radar_arr ra, int y);
int is_overlapping(radar_range a, radar_range b);
void prune_overlap(radar_range_arr* rra);
int positions_wo_beacons(radar_arr ra, int y);
unsigned long long tuning_frequency(radar_arr ra, int search_x, int search_y);

#endif

