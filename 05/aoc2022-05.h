#ifndef AOC2022_05
#define AOC2022_05

#define AOC_STACK_SIZE 128
typedef struct stack {
    int index;
    char *items;
} stack;
stack stack_init();
void stack_push(stack *s, char c);
char stack_pop(stack *s);

stack* init_storage(FILE *fp, int num_stacks);
int* parse_instruction(char *c);

#endif

