#ifndef AOC2022_13
#define AOC2022_13

typedef struct packet {
    int atom;
    struct packet* list;
} packet;
int parse_packet(packet* pt, char* raw);
char* to_string(packet p);
packet wrap_atom(int a);
packet wrap_list(packet p);
int is_defined(packet p);
int compare_packets(packet p, packet q);
void insert_packet(packet *ps, packet p, int num_packets);
packet* sort_packets(char* raw);
int search_packet(packet* ps, packet p);
int get_decoder_key(packet* ps);

#endif

