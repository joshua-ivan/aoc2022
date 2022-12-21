#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc2022-16.h"

int main(int argc, char *argv[]) {
    graph g = init_graph("input.txt");
    dist_matrix dm = build_dist_matrix(g);
    int** dists = dm.matrix;
    int* flow = malloc(sizeof(int) * dm.size);
    int location = dm.start;
    int* remaining = malloc(sizeof(int) * dm.size - 1);
    short* flow_memo = maxflow_hashtable_init(30, dm.size);
    short* two_memo = parttwo_hashtable_init(dm.size);

    int j = 0;
    for (int i = 0; i < g.v_len; i++) {
        if (!strcmp(g.v[i].name, "AA") || g.v[i].flow > 0) {
            flow[j++] = g.v[i].flow;
        }
    }
    
    int k = 0;
    for (j = 0; j < dm.size; j++) {
        if (j != dm.start) {
            remaining[k++] = j;
        }
    }

    int max = part_two(dists, flow, dm.size, &flow_memo, &two_memo, location, remaining, dm.size - 1);
    printf("%d\n", max);
}
