#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc2022-01.h"

void free_list(node *head) {
    if (head->next != NULL) {
        free_list(head->next);
    }
    free(head);
}

int* list_to_array(node *head, int *len) {
    int l = 0;
    node *current = head;
    while (current != NULL) {
        l++;
        current = current->next;
    }

    int *a = malloc(sizeof(int) * l);
    current = head;
    for (int i = 0; i < l; i++) {
        a[i] = current->cals;
        current = current->next;
    }

    *len = l;
    return a;
}

node* build_calorie_list(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    int current_total = 0;
    node *head = malloc(sizeof(node));
    node *current = head;

    while ((read = getline(&line, &length, fp)) != -1) {
        if (strcmp(line, "\n") == 0) {
            current->cals = current_total;
            current->next = malloc(sizeof(node));
            current = current->next;
            
            current_total = 0;
        } else {
            current_total += atoi(line);
        }
    }
    current->cals = current_total;
    current->next = NULL;

    fclose(fp);
    free(line);

    return head;
}

int max_value(node *head) {
    int max = 0;
    while (head != NULL) {
        if (head->cals > max) {
            max = head->cals;
        }
        head = head->next;
    }
    return max;
}

int comp(const void *a, const void *b) {
    int x = *((int *) a);
    int y = *((int *) b);
    if (x > y) return 1;
    if (y > x) return -1;
    return 0;
}

int top_n_sum(node *head, int n) {
    int len;
    int *arr = list_to_array(head, &len);

    qsort(arr, len, sizeof(int), comp);

    int sum = 0;
    for (int i = len - 1; i >= len - n; i--) {
        sum += arr[i];
    }
    return sum;
}

void count_calories() {
    exit(EXIT_SUCCESS);
}

