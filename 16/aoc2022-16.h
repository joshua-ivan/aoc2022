#ifndef AOC2022_16
#define AOC2022_16

#define MAX_VERTICES 100
#define MAX_EDGES 1000
typedef struct {
    char* name;
    int flow;
} vertex;
typedef struct {
    char* v_a;
    char* v_b;
} edge;
typedef struct {
    vertex* v;
    int v_len;
    edge* e;
    int e_len;
} graph;
typedef struct {
    int** matrix;
    int start;
    int size;
} dist_matrix;
typedef struct {
    int index;
    int pressure;
} valve;
graph init_graph(char* filename);
int* shortest_paths(graph g, char* start_name);
long maxflow_hashcalc(int time_elapsed, int flow_len, int location, int* remaining, int remaining_len);
short* maxflow_hashtable_init(int time_limit, int flow_len);
int max_flow(int time_elapsed, int** dists, int* flow, int flow_len, short** flow_memo, int location, int* remaining, int remaining_len);
dist_matrix build_dist_matrix(graph g);
long parttwo_hashcalc(int* remaining, int remaining_len);
short* parttwo_hashtable_init(int flow_len);
int part_two(int** dists, int* flow, int flow_len, short** flow_memo, short** two_memo, int start, int* human, int human_len);

#endif

