#include <stdio.h>
#include <stdlib.h>
#include "aoc2022-19.h"

list_blueprint parse_input(char* filename) {
    list_blueprint bps;
    bps.count = 0;
    bps.list = malloc(sizeof(blueprint) * MAX_BPS);
    for (int i = 0; i < MAX_BPS; i++) {
        for (int j = 0; j < 3; j++) {
            bps.list[i].ore_cost[j] = 0;
        }
        for (int j = 0; j < 3; j++) {
            bps.list[i].clay_cost[j] = 0;
        }
        for (int j = 0; j < 3; j++) {
            bps.list[i].obsidian_cost[j] = 0;
        }
        for (int j = 0; j < 3; j++) {
            bps.list[i].geode_cost[j] = 0;
        }
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return bps;
    }

    int num = 0;
    int read = 0;
    char *format = "Blueprint %d: Each ore robot costs %d ore. Each clay robot costs %d ore. Each obsidian robot costs %d ore and %d clay. Each geode robot costs %d ore and %d obsidian.\n";
    while ((read = fscanf(fp, format, &num,
                &bps.list[bps.count].ore_cost[2], &bps.list[bps.count].clay_cost[2],
                &bps.list[bps.count].obsidian_cost[2], &bps.list[bps.count].obsidian_cost[1],
                &bps.list[bps.count].geode_cost[2], &bps.list[bps.count].geode_cost[0])) == 7) {
        bps.list[bps.count].max_ore_cost = max_ore_cost(bps.list[bps.count]);
        bps.count++;
    }

    return bps;
}

geode_state init_geode_state() {
    geode_state gs;
    gs.time_elapsed = 0;
    for (int i = 0; i < 4; i++) {
        gs.num_resources[i] = 0;
        gs.num_robots[i] = 0;
    }
    gs.num_robots[3] = 1;
    return gs;
}

geode_state copy_geode_state(geode_state old_state) {
    geode_state gs = init_geode_state();
    gs.time_elapsed = old_state.time_elapsed;
    for (int i = 0; i < 4; i++) {
        gs.num_resources[i] = old_state.num_resources[i];
        gs.num_robots[i] = old_state.num_robots[i];
    }
    return gs;
}

int geode_state_equals(geode_state gsx, geode_state gsy) {
    if (gsx.time_elapsed != gsy.time_elapsed) {
        return 0;
    }
    for (int i = 0; i < 4; i++) {
        if (gsx.num_resources[i] != gsy.num_resources[i]) {
            return 0;
        }
        if (gsx.num_robots[i] != gsy.num_robots[i]) {
            return 0;
        }
    }
    return 1;
}

unsigned int calculate_hash(geode_state gs) {
    unsigned int hash = gs.time_elapsed << 10;
    for (int i = 0; i < 4; i++) {
        hash += gs.num_resources[i] * gs.num_robots[i];
    }
    return hash;
}

hash_table init_hash_table() {
    hash_table ht;
    ht.list = malloc(sizeof(ht_node *) * HASH_TABLE_SIZE);
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ht.list[i] = NULL;
    }
    return ht;
}

hash_table insert_hash_table(hash_table ht, geode_state gs, short max_geodes) {
    ht_node* node = malloc(sizeof(ht_node));
    node->state = copy_geode_state(gs);
    node->max_geodes = max_geodes;
    node->next = NULL;

    unsigned int hash = calculate_hash(gs);
    if (ht.list[hash] == NULL) {
        ht.list[hash] = node;
    } else {
        ht_node* current = ht.list[hash];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }

    return ht;
}

short lookup_hash_table(hash_table ht, geode_state gs) {
    unsigned int hash = calculate_hash(gs);
    ht_node* current = ht.list[hash];
    if (current == NULL) {
        return -1;
    } else {
        while (current != NULL) {
            if (geode_state_equals(gs, current->state)) {
                return current->max_geodes;
            }
            current = current->next;
        }
        return -1;
    }
}

void free_hash_table(hash_table ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (ht.list[i] != NULL) {
            ht_node* current = ht.list[i];
            while (current != NULL) {
                ht_node* previous = current;
                current = current->next;
                free(previous);
            }
        }
    }
    free(ht.list);
}

int sufficient_resources(int robot, blueprint bp, geode_state gs) {
    switch (robot) {
        case 0:
            if (bp.geode_cost[0] > gs.num_resources[1]) return 0;
            if (bp.geode_cost[2] > gs.num_resources[3]) return 0;
            break;
        case 1:
            if (bp.obsidian_cost[1] > gs.num_resources[2]) return 0;
            if (bp.obsidian_cost[2] > gs.num_resources[3]) return 0;
            break;
        case 2:
            if (bp.clay_cost[2] > gs.num_resources[3]) return 0;
            break;
        case 3:
            if (bp.ore_cost[2] > gs.num_resources[3]) return 0;
            break;
        default:
            return 0;
            break;
    }
    return 1;
}

int max_ore_cost(blueprint bp) {
    int max_ore_cost = bp.ore_cost[2];
    max_ore_cost = (bp.clay_cost[2] > max_ore_cost) ? bp.clay_cost[2] : max_ore_cost;
    max_ore_cost = (bp.obsidian_cost[2] > max_ore_cost) ? bp.obsidian_cost[2] : max_ore_cost;
    max_ore_cost = (bp.geode_cost[2] > max_ore_cost) ? bp.geode_cost[2] : max_ore_cost;
    return max_ore_cost;
}

short potential_geodes(short time_limit, geode_state gs) {
    short time_remaining = time_limit - gs.time_elapsed;
    short triangle_num = ((time_remaining - 1) * time_remaining) / 2;
    return gs.num_resources[0] + (gs.num_robots[0] * time_remaining) + triangle_num;
}

short max_geodes(short time_limit, blueprint bp, geode_state gs, hash_table* memo, short* global_max) {
    if (gs.time_elapsed >= time_limit) {
        return gs.num_resources[0];
    }

    short hash_max = lookup_hash_table(*memo, gs);
    if (hash_max > -1) {
        return hash_max;
    }

    short potential = potential_geodes(time_limit, gs);
    if (potential < *global_max) {
        return gs.num_resources[0];
    }

    short local_max = 0;
    int build_field = 0;
    if (sufficient_resources(0, bp, gs)) {
        build_field += 8;
        geode_state new_state = copy_geode_state(gs);
        new_state.time_elapsed++;

        new_state.num_resources[1] -= bp.geode_cost[0];
        new_state.num_resources[3] -= bp.geode_cost[2];

        for (int j = 0; j < 4; j++) {
            new_state.num_resources[j] += new_state.num_robots[j];
        }
        new_state.num_robots[0]++;
        short candidate = max_geodes(time_limit, bp, new_state, memo, global_max);
        local_max = (candidate > local_max) ? candidate : local_max;
    }
    if (!(build_field & 8) && (gs.num_robots[1] < bp.geode_cost[0]) && sufficient_resources(1, bp, gs)) {
        build_field += 4;
        geode_state new_state = copy_geode_state(gs);
        new_state.time_elapsed++;

        new_state.num_resources[2] -= bp.obsidian_cost[1];
        new_state.num_resources[3] -= bp.obsidian_cost[2];

        for (int j = 0; j < 4; j++) {
            new_state.num_resources[j] += new_state.num_robots[j];
        }
        new_state.num_robots[1]++;
        short candidate = max_geodes(time_limit, bp, new_state, memo, global_max);
        local_max = (candidate > local_max) ? candidate : local_max;
    }
    if (!(build_field & 8) && (gs.num_robots[2] < bp.obsidian_cost[1]) && sufficient_resources(2, bp, gs)) {
        build_field += 2;
        geode_state new_state = copy_geode_state(gs);
        new_state.time_elapsed++;

        new_state.num_resources[3] -= bp.clay_cost[2];

        for (int j = 0; j < 4; j++) {
            new_state.num_resources[j] += new_state.num_robots[j];
        }
        new_state.num_robots[2]++;
        short candidate = max_geodes(time_limit, bp, new_state, memo, global_max);
        local_max = (candidate > local_max) ? candidate : local_max;
    }
    if (!(build_field & 8) && (gs.num_robots[3] < bp.max_ore_cost) && sufficient_resources(3, bp, gs)) {
        build_field += 1;
        geode_state new_state = copy_geode_state(gs);
        new_state.time_elapsed++;

        new_state.num_resources[3] -= bp.ore_cost[2];

        for (int j = 0; j < 4; j++) {
            new_state.num_resources[j] += new_state.num_robots[j];
        }
        new_state.num_robots[3]++;
        short candidate = max_geodes(time_limit, bp, new_state, memo, global_max);
        local_max = (candidate > local_max) ? candidate : local_max;
    }
    if (!(build_field & 8) && (build_field != 15)) {
        geode_state new_state = copy_geode_state(gs);
        new_state.time_elapsed++;
        for (int j = 0; j < 4; j++) {
            new_state.num_resources[j] += new_state.num_robots[j];
        }
        short candidate = max_geodes(time_limit, bp, new_state, memo, global_max);
        local_max = (candidate > local_max) ? candidate : local_max;
    }

    if (local_max > *global_max) *global_max = local_max;
    insert_hash_table(*memo, gs, local_max);
    return local_max;
}

int sum_quality(char* filename) {
    list_blueprint bps = parse_input(filename);
    int quality = 0;
    short time_limit = 24;
    for (int i = 0; i < bps.count; i++) {
        hash_table memo = init_hash_table();
        short global_max = 0;

        quality += ((i + 1) * max_geodes(time_limit, bps.list[i], init_geode_state(), &memo, &global_max));

        free_hash_table(memo);
    }

    return quality;
}

int product_blueprints(char* filename) {
    list_blueprint bps = parse_input(filename);
    int geodes = 1;
    short time_limit = 32;
    for (int i = 0; i < 3; i++) {
        hash_table memo = init_hash_table();
        short global_max = 0;
        blueprint bp = (i < bps.count) ? bps.list[i] : bps.list[0];

        int g = max_geodes(time_limit, bp, init_geode_state(), &memo, &global_max);
        geodes *= g;

        free_hash_table(memo);
    }

    return geodes;
}
