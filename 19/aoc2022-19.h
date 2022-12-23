#ifndef AOC2022_19
#define AOC2022_19

#define MAX_BPS 32
#define HASH_TABLE_SIZE 65536

typedef struct {
    int ore_cost[3];
    int clay_cost[3];
    int obsidian_cost[3];
    int geode_cost[3];
    int max_ore_cost;
} blueprint;
typedef struct {
    int time_elapsed;
    int num_resources[4];
    int num_robots[4];
} geode_state;
typedef struct {
    blueprint* list;
    int count;
} list_blueprint;
typedef struct ht_node {
    geode_state state;
    short max_geodes;
    struct ht_node* next;
} ht_node;
typedef struct {
    ht_node** list;
} hash_table;

list_blueprint parse_input(char* filename);
geode_state init_geode_state();
geode_state copy_geode_state(geode_state old_state);
int geode_state_equals(geode_state gsx, geode_state gsy);
unsigned int calculate_hash(geode_state gs);
hash_table init_hash_table();
hash_table insert_hash_table(hash_table ht, geode_state gs, short max_geodes);
short lookup_hash_table(hash_table ht, geode_state gs);
void free_hash_table(hash_table ht);
int sum_quality(char* filename);
int product_blueprints(char* filename);
int sufficient_resources(int robot, blueprint bp, geode_state gs);
int max_ore_cost(blueprint bp);
short potential_geodes(short time_limit, geode_state gs);
short max_geodes(short time_limit, blueprint bp, geode_state gs, hash_table* memo, short* global_max);

#endif
