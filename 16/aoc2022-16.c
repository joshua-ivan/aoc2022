#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "aoc2022-16.h"

graph init_graph(char* filename) {
    graph g;
    g.v = malloc(sizeof(vertex) * MAX_VERTICES);
    for (int i = 0; i < MAX_VERTICES; i++) {
        g.v[i].name = malloc(sizeof(char) * 4);
        g.v[i].flow = -1;
    }
    g.v_len = 0;
    g.e = malloc(sizeof(edge) * MAX_EDGES);
    for (int i = 0; i < MAX_EDGES; i++) {
        g.e[i].v_a = malloc(sizeof(char) * 4);
        g.e[i].v_b = malloc(sizeof(char) * 4);
    }
    g.e_len = 0;

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return g;
    }

    int read = 2;
    while (read == 2) {
        read = fscanf(fp, "Valve %s has flow rate=%d;",
                g.v[g.v_len].name, &g.v[g.v_len].flow);

        char *remaining_line = NULL;
        size_t remaining_length = 0;
        getline(&remaining_line, &remaining_length, fp);

        strtok(remaining_line, " ");
        for (int i = 0; i < 3; i++) {
            strtok(NULL, " ");
        }

        char* valve;
        while ((valve = strtok(NULL, " ")) != NULL) {
            char* cpy = malloc(sizeof(char) * strlen(valve) + 1);
            strcpy(cpy, valve);

            char* comma;
            if ((comma = strchr(cpy, ',')) != NULL) {
                comma[0] = '\0';
            }
            char* newline;
            if ((newline = strchr(cpy, '\n')) != NULL) {
                newline[0] = '\0';
            }

            g.e[g.e_len].v_a = g.v[g.v_len].name;
            g.e[g.e_len].v_b = cpy;
            g.e_len++;
        }

        if (read == 2) {
            g.v_len++;
        }
    }

    return g;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int* shortest_paths(graph g, char* start_name) {
    int* dists = malloc(sizeof(int) * g.v_len);
    int* queue = malloc(sizeof(int) * g.v_len);
    int head = 0;
    int tail = 0;
    int visited = 0;
    for (int i = 0; i < g.v_len; i++) {
        if (!strcmp(g.v[i].name, start_name)) {
            dists[i] = 0;
            queue[head++] = i;
            visited++;
        } else {
            dists[i] = INT_MAX;
        }
    }

    while ((head - tail) > 0) {
        int current = queue[tail++];

        for (int i = 0; i < g.e_len; i++) {
            if (!strcmp(g.e[i].v_a, g.v[current].name)) {
                int j = 0;
                while (j < g.v_len) {
                    if (!strcmp(g.e[i].v_b, g.v[j].name)) {
                        break;
                    }
                    j++;
                }

                int k = 0;
                while (k < visited) {
                    if (!strcmp(g.v[j].name, g.v[queue[k]].name)) {
                        break;
                    }
                    k++;
                }
                if (k == visited) {
                    dists[j] = min(dists[current] + 1, dists[j]);
                    queue[head++] = j;
                    visited++;
                }
            }
        }
    }

    free(queue);
    return dists;
}

dist_matrix build_dist_matrix(graph g) {
    dist_matrix dm;
    dm.matrix = malloc(sizeof(int *) * g.v_len);
    for (int i = 0; i < g.v_len; i++) {
        dm.matrix[i] = shortest_paths(g, g.v[i].name);
        if (!strcmp(g.v[i].name, "AA")) {
            dm.start = i;
        }
    }
    dm.size = g.v_len;

    for (int i = g.v_len - 1; i >= 0; i--) {
        if (strcmp(g.v[i].name, "AA") && g.v[i].flow <= 0) {
            dm.start = (i < dm.start) ? dm.start - 1 : dm.start;
            for (int j = i; j + 1 < dm.size; j++) {
                for (int k = 0; k < dm.size; k++) {
                    dm.matrix[k][j] = dm.matrix[k][j + 1];
                }
            }
            for (int j = i; j + 1 < dm.size; j++) {
                dm.matrix[j] = dm.matrix[j + 1];
            }

            dm.size -= 1;
        }
    }

    return dm;
}

long parttwo_hashcalc(int* remaining, int remaining_len) {
    long hash = 0;
    for (int i = 0; i < remaining_len; i++) {
        hash += (1 << remaining[i]);
    }
    return hash;
}

short* parttwo_hashtable_init(int flow_len) {
    long addresses = 0;
    for (int i = 0; i < flow_len; i++) {
        addresses = (addresses << 1) + 1;
    }
    addresses++;

    short *two_memo = malloc(sizeof(short) * addresses);
    for (long i = 0; i < addresses; i++) {
        two_memo[i] = -1;
    }

    return two_memo;
}

int part_two(int** dists, int* flow, int flow_len, short** flow_memo, short** two_memo, int start, int* human, int human_len) {
    long hash = parttwo_hashcalc(human, human_len);
    if (two_memo[0][hash] > -1) {
        return two_memo[0][hash];
    }

    /* printf("part_two called\n");
    printf("\thuman_len: %d\n", human_len);
    printf("\thuman: ");
    for (int i = 0; i < human_len; i++) {
        printf("%d ", human[i]);
    }
    printf("\n"); */

    int elephant_len = flow_len - human_len - 1;
    int* elephant = malloc(sizeof(int) * elephant_len);
    int k = 0;
    for (int i = 0; i < flow_len; i++) {
        if (i == start) {
            continue;
        }

        int j = 0;
        while (j < human_len) {
            if (i == human[j]) {
                break;
            }
            j++;
        }
        if (j == human_len) {
            elephant[k++] = i;
        }
    }

    /* printf("\telephant_len: %d\n", elephant_len);
    printf("\telephant: ");
    for (int i = 0; i < elephant_len; i++) {
        printf("%d ", elephant[i]);
    }
    printf("\n"); */

    int max = 0;
    if (human_len > (flow_len * 0.4) && elephant_len > (flow_len * 0.4)) {
        max = max_flow(4, dists, flow, flow_len, flow_memo, start, human, human_len)
            + max_flow(4, dists, flow, flow_len, flow_memo, start, elephant, elephant_len);
    }

    for (int i = 0; i < human_len; i++) {
        int* next = malloc(sizeof(int) * human_len - 1);
        int l = 0;
        for (int j = 0; j < human_len; j++) {
            if (j != i) {
                next[l++] = human[j];
            }
        }

        int candidate = part_two(dists, flow, flow_len, flow_memo, two_memo, start, next, human_len - 1);
        max = (candidate > max) ? candidate : max;

        free(next);
    }

    free(elephant);
    two_memo[0][hash] = max;
    return max;
}

long maxflow_hashcalc(int time_elapsed, int flow_len, int location, int* remaining, int remaining_len) {
    long hash = time_elapsed;
    for (int i = 1; i < flow_len; i = i << 1) {
        hash = hash << 1;
    }
    hash += location;
    for (int i = 0; i < flow_len; i++) {
        hash = hash << 1;
    }
    for (int i = 0; i < remaining_len; i++) {
        hash += (1 << remaining[i]);
    }
    return hash;
}

short* maxflow_hashtable_init(int time_limit, int flow_len) {
    long addresses = time_limit;
    for (int i = 1; i < flow_len; i = i << 1) {
        addresses = (addresses << 1) + 1;
    }
    for (int i = 0; i < flow_len; i++) {
        addresses = (addresses << 1) + 1;
    }

    short *flow_memo = malloc((sizeof(short) * addresses) + 1);
    for (long i = 0; i < addresses + 1; i++) {
        flow_memo[i] = -1;
    }

    return flow_memo;
}

int max_flow(int time_elapsed, int** dists, int* flow, int flow_len, short** flow_memo, int location, int* remaining, int remaining_len) {
    /* printf("max_flow called\n");
    printf("\ttime_elapsed: %d\n", time_elapsed);
    printf("\tlocation: %d\n", location);
    printf("\tremaining: ");
    for (int l = 0; l < count; l++) {
        printf("%d ", remaining[l]);
    }
    printf("\n\tcount: %d\n", count); */
    /* if (time_elapsed >= 10) {
        for (int i = 0; i < important_len; i++) {
            for (int j = 0; j < remaining_len; j++) {
                if (important[i] == remaining[j]) {
                    return 0;
                }
            }
        }
    } */

    if (time_elapsed >= 30 && remaining_len > 0) {
        return 0;
    } else if (remaining_len <= 0) {
        return 0;
    } else {
        long hash = maxflow_hashcalc(time_elapsed, flow_len, location, remaining, remaining_len);
        if (flow_memo[0][hash] > -1) {
            return flow_memo[0][hash];
        }

        int max = 0;

        for (int i = 0; i < remaining_len; i++) {
            int time = dists[location][remaining[i]];
            if (flow[remaining[i]] > 0) {
                time++;
            }
            int pressure = (30 - (time_elapsed + time)) * flow[remaining[i]];

            int* next = malloc(sizeof(int) * (remaining_len - 1));
            int k = 0;
            for (int j = 0; j < remaining_len; j++) {
                if (remaining[j] != remaining[i]) {
                    next[k++] = remaining[j];
                }
            }

            int candidate = max_flow(time_elapsed + time, dists, flow, flow_len, flow_memo, remaining[i], next, remaining_len - 1);
            candidate += pressure;
            max = (candidate > max) ? candidate : max;

            free(next);
        }

        flow_memo[0][hash] = max; 
        return max;
    }
}
