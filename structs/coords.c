#include <stdlib.h>
#include "coords.h"

coords_list init_coords_list(int max_len) {
    coords_list li;
    li.list = malloc(sizeof(coords *) * max_len);
    li.max_len = max_len;

    for (int i = 0; i < li.max_len; i++) {
        li.list[i] = malloc(sizeof(coords));
        li.list[i]->x = -1;
        li.list[i]->y = -1;
    }

    return li;
}

void insert_coords_list(coords_list li, coords* c) {
    int i = 0;
    while (i < li.max_len && li.list[i]->x != -1 && li.list[i]->y != -1) {
        if (li.list[i]->x == c->x && li.list[i]->y == c->y) {
            return;
        }
        i++;
    }
    if (i < li.max_len) {
        li.list[i]->x = c->x;
        li.list[i]->y = c->y;
    }
}

int search_coords_list(coords_list li, coords* c) {
    int i = 0;
    while (i < li.max_len && li.list[i]->x != -1 && li.list[i]->y != -1) {
        if (li.list[i]->x == c->x && li.list[i]->y == c->y) {
            return i;
        }
        i++;
    }
    return -1;
}

void remove_coords_list(coords_list li, coords* c) {
    int i = search_coords_list(li, c);
    if (i < 0) {
        return;
    }
    while (i < li.max_len && li.list[i + 1]->x != -1 && li.list[i + 1]->y != -1) {
        li.list[i]->x = li.list[i + 1]->x;
        li.list[i]->y = li.list[i + 1]->y;
        i++;
    }
    li.list[i]->x = li.list[i + 1]->x;
    li.list[i]->y = li.list[i + 1]->y;
}

