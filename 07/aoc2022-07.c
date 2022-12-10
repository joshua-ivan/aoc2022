#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc2022-07.h"

directory* directory_init(char *s) {
    directory *d = malloc(sizeof(directory));

    int len = strlen(s) + 1;
    char *name = malloc(sizeof(char) * len);
    for (int i = 0; i < len; i++) {
        name[i] = '\0';
    }

    strcpy(name, s);
    d->name = name;
    d->size = 0;
    return d;
}

void hashtable_init(hashtable *ht) {
    for (int i = 0; i < AOC_HASHTABLE_SIZE; i++) {
        ht->array[i] = NULL;
    }
}

int calculate_hash(char *name) {
    int len = strlen(name);
    int sum = 0;
    int i = 0;
    while (i < len) {
        sum += name[i++];
    }
    return sum % AOC_HASHTABLE_SIZE;
}

void hashtable_insert(hashtable *ht, directory *d) {
    hashnode *hn = malloc(sizeof(hashnode));
    hn->dir = d;

    int hash = calculate_hash(d->name);
    if (ht->array[hash] == NULL) {
        ht->array[hash] = hn;
    } else {
        hashnode *current = ht->array[hash];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = hn;
    }
}

directory* hashtable_search(hashtable *ht, char *key) {
    int hash = calculate_hash(key);
    if (ht->array[hash] == NULL) {
        return NULL;
    } else {
        hashnode *current = ht->array[hash];
        while (strcmp(current->dir->name, key) && current->next != NULL) {
            current = current->next;
        }
        return current->dir;
    }
}

void stack_init(stack *s) {
    for (int i = 0; i < AOC_STACK_SIZE; i++) {
        s->str[i] = NULL;
    }
    s->index = 0;
}

void stack_push(stack *s, char *str) {
    int len = strlen(str) + 1;
    char *cpy = malloc(sizeof(char) * len);
    for (int i = 0; i < len; i++) {
        cpy[i] = '\0';
    }

    strcpy(cpy, str);
    s->str[s->index++] = cpy;
}

char* stack_pop(stack *s) {
    int len = strlen(s->str[s->index - 1]) + 1;
    char *cpy = malloc(sizeof(char) * len);
    for (int i = 0; i < len; i++) {
        cpy[i] = '\0';
    }

    strcpy(cpy, s->str[--(s->index)]);
    return cpy;
}

char *build_absolute_path(char **path, int num_strings) {
    int dest_len = 0;
    for (int i = 0; i < num_strings; i++) {
        dest_len += strlen(path[i]);
    }
    dest_len++;
    char *absolute_path = malloc(sizeof(char) * dest_len);
    for (int i = 0; i < dest_len; i++) {
        absolute_path[i] = '\0';
    }

    for (int i = 0; i < num_strings; i++) {
        strcat(absolute_path, path[i]);
    }

    return absolute_path;
}

char* str_append(char *m, char *n) {
    int len = strlen(m) + strlen(n) + 1;
    char *str = malloc(sizeof(char) * len);
    for (int i = 0; i < len; i++) {
        str[i] = '\0';
    }

    strcpy(str, m);
    strcat(str, n);
    return str;
}

char* str_strip(char *s, char x) {
    int len = strlen(s) + 1;
    char *strip = malloc(sizeof(char) * len);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] != x) {
            strip[j++] = s[i];
        }
    }
    while (j < len) {
        strip[j++] = '\0';
    }
    return strip;
}

hashtable parse_output(FILE *output_text) {
    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    getline(&line, &length, output_text); // skip root
    hashtable ht;
    hashtable_init(&ht);
    directory *root = directory_init("/");
    hashtable_insert(&ht, root);

    stack abs_path;
    stack_init(&abs_path);
    stack_push(&abs_path, "/");

    while ((read = getline(&line, &length, output_text)) != -1) {
        printf("Output: %s", line);
        char *cmd[3];
        int i = 0;
        cmd[i] = strtok(line, " ");
        while (cmd[i] != NULL && i++ < 3) {
            cmd[i] = strtok(NULL, " ");
        }

        if (!strcmp(cmd[0], "$")) {
            if (!strcmp(cmd[1], "cd")) {
                if (!strcmp(cmd[2], "..\n")) {
                    stack_pop(&abs_path);
                } else {
                    char *strip = str_strip(cmd[2], '\n');
                    char *dir = str_append(strip, "/");
                    stack_push(&abs_path, dir);
                    free(dir);
                }
                printf("CWD: %s\n", build_absolute_path(abs_path.str, abs_path.index));
            } else {
                // may need to use an "ls"'d flag
            }
        } else if (!strcmp(cmd[0], "dir")) {
            char *strip = str_strip(cmd[1], '\n');
            char *dir = str_append(strip, "/");
            stack_push(&abs_path, dir);
            free(dir);

            char *cwd = build_absolute_path(abs_path.str, abs_path.index);
            printf("Path: %s\n", cwd);
            directory *dir_struct = directory_init(cwd);
            hashtable_insert(&ht, dir_struct);

            free(cwd);
            stack_pop(&abs_path);
        } else {
            for (int i = 0; i < abs_path.index; i++) {
                char *path = build_absolute_path(abs_path.str, i + 1);
                directory *d = hashtable_search(&ht, path);
                d->size += atoi(cmd[0]);
            }
        }
    }

    return ht;
}

int solve_puzzle_one(hashtable *ht) {
    int total = 0;
    for (int i = 0; i < AOC_HASHTABLE_SIZE; i++) {
        hashnode *hn = ht->array[i];
        while (hn != NULL) {
            directory *d = hn->dir;
            if (d->size <= 100000) {
                total += d->size;
            }
            hn = hn->next;
        }
    }
    return total;
}

int solve_puzzle_two(hashtable *ht) {
    directory *root = hashtable_search(ht, "/");
    int used_space = root->size;

    int unused_space = 70000000 - used_space;
    int min_size = 30000000 - unused_space;

    int smallest_dir = 70000000;
    for (int i = 0; i < AOC_HASHTABLE_SIZE; i++) {
        hashnode *hn = ht->array[i];
        while (hn != NULL) {
            directory *d = hn->dir;
            if (d->size < smallest_dir && d->size >= min_size) {
                smallest_dir = d->size;
            }
            hn = hn->next;
        }
    }

    return smallest_dir;
}
