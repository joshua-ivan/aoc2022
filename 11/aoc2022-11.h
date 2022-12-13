#ifndef AOC2022_11
#define AOC2022_11

#define NUM_BASE_STRINGS 6
#define MAX_ITEMS 36
typedef struct {
    long items[36];
    int num_items;
    void (*op)(long*,char*,long);
    char *operand;
    int test;
    int monkey_t;
    int monkey_f;
} monkey;

char** load_base_strings();
void free_base_strings(char **str);
int get_significant_index(char* input_str, char* base_str);
void set_items(monkey *m, char *item_str);
void set_operation(monkey *m, char *op_str);
monkey init_monkey(char **raw);
void throw_item(monkey *from, monkey *to);
long* simulate_monkeys(monkey *m, int monkeys, int rounds, int part1);
long calculate_monkey_business(long* inspections, int monkeys);

#endif

