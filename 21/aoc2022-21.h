#ifndef AOC2022_21
#define AOC2022_21

#define HASH_TABLE_SIZE 1048576

typedef struct bt_node {
    char* name;
    char op;
    long double num;
    struct bt_node* left;
    struct bt_node* right;
} bt_node;
typedef struct {
    char** items;
} hash_table;

long hashcalc(char* index);
hash_table init_hash_table();
void free_hash_table(hash_table ht);
hash_table parse_input(char* filename);
void build_expr_tree(hash_table ht, bt_node* n, char* key);
bt_node* search_tree(bt_node* root, char* key);
void free_bt_node(bt_node* root);
long double eval_tree(bt_node* n);
long double eval_monkey(char* filename);
long double eval_algebra(bt_node* n, char* key, long double acc);
long double eval_human(char* filename);

#endif
