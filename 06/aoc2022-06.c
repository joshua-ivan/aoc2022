#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc2022-06.h"

queue queue_init(int queue_size) {
    queue q;
    q.head_index = 0;
    q.tail_index = 0;
    q.num_items = 0;
    q.queue_size = queue_size;
    q.items = malloc(sizeof(char) * q.queue_size);
    for (int i = 0; i < queue_size; i++) {
        q.items[i] = '\0';
    }
    return q;
}

int is_empty(queue *q) {
    return q->num_items == 0;
}

int is_full(queue *q) {
    return q->num_items == q->queue_size;
}

int enqueue(queue *q, char c) {
    if (is_full(q)) {
        printf("queue is full\n");
        return -1;
    }

    q->items[q->head_index] = c;
    q->head_index = (q->head_index + 1) % q->queue_size;
    q->num_items++;
    return 0;
}

char dequeue(queue *q) {
    if (is_empty(q)) {
        printf("queue is empty\n");
        return -1;
    }

    char c = q->items[q->tail_index];
    q->tail_index = (q->tail_index + 1) % q->queue_size;
    q->num_items--;
    return c;
}

void queue_free(queue *q) {
    free(q->items);
}

int is_queue_unique(queue *q) {
    for (int i = 0; i < q->queue_size; i++) {
        for (int j = i + 1; j < q->queue_size; j++) {
            if (q->items[i] == q->items[j]) {
                return 0;
            }
        }
    }
    return 1;
}

int get_start_marker(char *signal, int queue_size) {
    queue q = queue_init(queue_size);

    int i = 0;
    while (!is_full(&q)) {
        enqueue(&q, signal[i++]);
    }

    int len = strlen(signal);
    while (i < len && !is_queue_unique(&q)) {
        dequeue(&q);
        enqueue(&q, signal[i++]);
    }

    queue_free(&q);
    return i;
}
