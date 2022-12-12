#include <stdio.h>
#include <stdlib.h>
#include "aoc2022-09.h"

void move_head(coords* head, char direction) {
    switch (direction) {
        case 'U':
            head->y++;
            break;
        case 'L':
            head->x--;
            break;
        case 'R':
            head->x++;
            break;
        case 'D':
            head->y--;
            break;
    }
}

void move_tail(coords* head, coords* tail) {
    // check touching
    for (int x = (head->x - 1); x <= (head->x + 1); x++) {
        for (int y = (head->y - 1); y <= (head->y + 1); y++) {
            if (tail->x == x && tail->y == y) {
                return;
            }
        }
    }

    // check straight
    if (head->x == tail->x && head->y >= tail->y + 2) {
        tail->y++;
        return;
    }
    if (head->x == tail->x && head->y <= tail->y - 2) {
        tail->y--;
        return;
    }
    if (head->y == tail->y && head->x <= tail->x - 2) {
        tail->x--;
        return;
    }
    if (head->y == tail->y && head->x >= tail->x + 2) {
        tail->x++;
        return;
    }

    // check diagonal
    if (head->x < tail->x && head->y > tail->y) {
        tail->x--;
        tail->y++;
        return;
    }
    if (head->x > tail->x && head->y > tail->y) {
        tail->x++;
        tail->y++;
        return;
    }
    if (head->x < tail->x && head->y < tail->y) {
        tail->x--;
        tail->y--;
        return;
    }
    if (head->x > tail->x && head->y < tail->y) {
        tail->x++;
        tail->y--;
        return;
    }
}

void append_position_list(coords** list, coords *tail) {
    int i = 0;
    while (list[i] != NULL) {
        if (list[i]->x == tail->x && list[i]->y == tail->y) {
            return;
        }
        i++;
    }
    list[i] = malloc(sizeof(coords));
    list[i]->x = tail->x;
    list[i]->y = tail->y;
}

int count_positions_one(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return -1;
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    coords head;
    head.x = 0;
    head.y = 0;
    coords tail;
    tail.x = 0;
    tail.y = 0;
    coords **list = malloc(sizeof(coords *) * 65536);
    for (int i = 0; i < 65536; i++) {
        list[i] = NULL;
    }

    while ((read = getline(&line, &length, fp)) != -1) {
        char direction = line[0];
        int steps = atoi(line + 2);

        for (int i = 0; i < steps; i++) {
            move_head(&head, direction);
            move_tail(&head, &tail);
            append_position_list(list, &tail);
        }
    }

    int len = -1;
    while (list[++len] != NULL) ;

    for (int i = 0; i < len; i++) {
        free(list[i]);
    }
    free(list);
    fclose(fp);
    return len;
}

int count_positions_two(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return -1;
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    coords rope[10];
    for (int i = 0; i < 10; i++) {
        rope[i].x = 0;
        rope[i].y = 0;
    }
    coords **list = malloc(sizeof(coords *) * 65536);
    for (int i = 0; i < 65536; i++) {
        list[i] = NULL;
    }

    while ((read = getline(&line, &length, fp)) != -1) {
        char direction = line[0];
        int steps = atoi(line + 2);

        for (int i = 0; i < steps; i++) {
            move_head(&rope[0], direction);
            for (int j = 1; j < 10; j++) {
                move_tail(&rope[j - 1], &rope[j]);
            }
            append_position_list(list, &rope[9]);
        }
    }

    int len = -1;
    while (list[++len] != NULL) ;

    for (int i = 0; i < len; i++) {
        free(list[i]);
    }
    free(list);
    fclose(fp);
    return len;
}
