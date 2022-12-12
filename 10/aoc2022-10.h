#ifndef AOC2022_10
#define AOC2022_10

int parse_instruction(char* inst, int* signal_graph, int past_cycles);
int signal_strength(int* signal_graph, int cycle);
char** generate_image(int* signal_graph, int graph_size);

#endif

