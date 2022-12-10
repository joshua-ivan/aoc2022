#ifndef AOC2022_07
#define AOC2022_07

#define AOC_HASHTABLE_SIZE 10
#define AOC_STACK_SIZE 32

typedef struct directory {
    char *name;
    int size;
} directory;
directory* directory_init(char *s);

typedef struct hashnode {
    directory *dir;
    struct hashnode *next;
} hashnode;

typedef struct hashtable {
    hashnode *array[AOC_HASHTABLE_SIZE];
} hashtable;
void hashtable_init(hashtable *ht);
int calculate_hash(char *name);
void hashtable_insert(hashtable *ht, directory *d);
directory* hashtable_search(hashtable *ht, char *key);

typedef struct stack {
    char *str[AOC_STACK_SIZE];
    int index;
} stack;
void stack_init(stack *s);
void stack_push(stack *s, char *str);
char* stack_pop(stack *s);

char* build_absolute_path(char **path, int num_strings);
char* str_append(char *m, char *n);
char* str_strip(char *s, char x);

hashtable parse_output(FILE *output_text);
int solve_puzzle_one(hashtable *ht);
int solve_puzzle_two(hashtable *ht);

#endif
