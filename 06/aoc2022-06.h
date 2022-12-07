#ifndef AOC2022_06
#define AOC2022_06

typedef struct queue {
    int head_index;
    int tail_index;
    int num_items;
    int queue_size;
    char *items;
} queue;
queue queue_init(int queue_size);
int is_empty(queue *q);
int is_full(queue *q);
int enqueue(queue *q, char c);
char dequeue(queue *q);
void queue_free(queue *q);

int is_queue_unique(queue *q);
int get_start_marker(char *signal, int queue_size);

#endif

