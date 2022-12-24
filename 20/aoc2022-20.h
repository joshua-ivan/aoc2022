#ifndef AOC2022_20
#define AOC2022_20

#define AL_SIZE 5000

typedef struct al_node {
    long long val;
    struct al_node* prev;
    struct al_node* next;
} al_node;
typedef struct {
    al_node** items;
    al_node* head;
    short count;
} array_list;

array_list init_array_list();
array_list parse_input(char* filename);
long long modulo(long long n, long long mod);
al_node* pop_list(al_node* al);
void insert_list(al_node* a, al_node* b, al_node* c);
void move_list(array_list al, int index);
array_list mix_list(array_list al);
void apply_key(array_list al);
long long* grove_coords(char* filename, int part2);

#endif
