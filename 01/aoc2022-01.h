#ifndef AOC2022_01
#define AOC2022_01

typedef struct node {
    int cals;
    struct node *next;
} node;

void free_list(node *head);
int* list_to_array(node *head, int* len);
node* build_calorie_list(char *filename);
int max_value(node *head);
int top_n_sum(node *head, int n);
void count_calories();

#endif

