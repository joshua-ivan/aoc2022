#include <stdio.h>
#include <stdlib.h>
#include "aoc2022-20.h"

array_list init_array_list() {
    array_list al;
    al.items = malloc(sizeof(al_node *) * AL_SIZE);
    for (int i = 0; i < AL_SIZE; i++) {
        al.items[i] = NULL;
    }
    al.count = 0;
    return al;
}

array_list parse_input(char* filename) {
    array_list al = init_array_list();

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return al;
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    while ((read = getline(&line, &length, fp)) != -1) {
        al_node *an = malloc(sizeof(al_node));
        an->val = atoi(line);
        al.items[al.count] = an;
        if (an->val == 0) {
            al.head = al.items[al.count];
        }

        if (al.count > 0) {
            al.items[al.count - 1]->next = al.items[al.count];
            al.items[al.count]->prev = al.items[al.count - 1];
        }
        al.count++;
    }
    al.items[al.count - 1]->next = al.items[0];
    al.items[0]->prev = al.items[al.count - 1];

    return al;
}

long long modulo(long long n, long long mod) {
    return (n < 0) ? (-1 * ((-1 * n) % mod)) + mod : n % mod;
}

al_node* pop_list(al_node* al) {
    al_node* prev = al->prev;
    al_node* next = al->next;
    prev->next = next;
    next->prev = prev;
    return al;
}

void insert_list(al_node* a, al_node* b, al_node* c) {
    a->next = b;
    b->prev = a;
    b->next = c;
    c->prev = b;
}

void move_list(array_list al, int index) {
    long long num_steps = modulo(al.items[index]->val, al.count - 1);
    if (num_steps == 0) {
        return;
    }

    al_node* item = pop_list(al.items[index]);
    al_node* target = item->next;
    int steps = 0;
    while (steps++ < num_steps - 1) {
        target = target->next;
    }

    insert_list(target, item, target->next);
}

array_list mix_list(array_list al) {
    for (short i = 0; i < al.count; i++) {
        move_list(al, i);
    }
    return al;
}

void apply_key(array_list al) {
    for (short i = 0; i < al.count; i++) {
        al.items[i]->val *= 811589153;
    }
}

long long* grove_coords(char* filename, int part2) {
    long long* coords = malloc(sizeof(long long) * 3);
    for (int i = 0; i < 3; i++) {
        coords[i] = 0;
    }

    array_list al = parse_input(filename);
    int num_mixes = 1;
    if (part2) {
        apply_key(al);
        num_mixes = 10;
    }
    for (int i = 0; i < num_mixes; i++) {
        al = mix_list(al);
    }

    int num_steps[3] = { 1000 % al.count, 2000 % al.count, 3000 % al.count };
    for (int i = 0; i < 3; i++) {
        al_node* current = al.head;
        int steps = 0;
        while (steps++ < num_steps[i]) {
            current = current->next;
        }
        coords[i] = current->val;
    }

    return coords;
}

