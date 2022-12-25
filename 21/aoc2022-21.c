#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc2022-21.h"

long hashcalc(char* index) {
    long hash = 0;
    for (int i = 0; i < 3; i++) {
        hash += (index[i] - 'a');
        hash <<= 5;
    }
    return hash + (index[3] - 'a');
}

hash_table init_hash_table() {
    hash_table ht;
    ht.items = malloc(sizeof(char *) * HASH_TABLE_SIZE);
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ht.items[i] = NULL;
    }
    return ht;
}

void free_hash_table(hash_table ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (ht.items[i] != NULL) {
            free(ht.items[i]);
        }
    }
    free(ht.items);
}

hash_table parse_input(char* filename) {
    hash_table ht = init_hash_table();
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return ht;
    }

    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    while ((read = getline(&line, &length, fp)) != -1) {
        char* key = strtok(line, ":");
        long hash = hashcalc(key);
        ht.items[hash] = malloc(sizeof(char) * 16);
        strcpy(ht.items[hash], (line + 6));
        char *newline = strchr(ht.items[hash], '\n');
        if (newline != NULL) {
            newline[0] = '\0';
        }
    }

    free(line);
    fclose(fp);
    return ht;
}

bt_node* search_tree(bt_node* root, char* key) {
    if (root == NULL) {
        return NULL;
    }
    if (!strcmp(root->name, key)) {
        return root;
    }
    bt_node* left = search_tree(root->left, key);
    if (left != NULL) {
        return left;
    }
    bt_node* right = search_tree(root->right, key);
    if (right != NULL) {
        return right;
    }
    return NULL;
}

void build_expr_tree(hash_table ht, bt_node* n, char* key) {
    n->name = key;

    char* value = ht.items[hashcalc(key)];
    long double num = atoi(value);
    if (num != 0) {
        n->op = 0;
        n->num = num;
        n->left = NULL;
        n->right = NULL;
        return;
    }

    n->num = -1;
    char* left_key = strtok(value, " ");
    n->op = strtok(NULL, " ")[0];
    char* right_key = strtok(NULL, " ");
    n->left = malloc(sizeof(bt_node));
    build_expr_tree(ht, n->left, left_key);
    n->right = malloc(sizeof(bt_node));
    build_expr_tree(ht, n->right, right_key);
}

void free_bt_node(bt_node* root) {
    if (root == NULL) {
        return;
    } else {
        free_bt_node(root->left);
        free_bt_node(root->right);
        free(root);
    }
}

long double eval_tree(bt_node* n) {
    if (n->op == 0) {
        return n->num;
    } else {
        switch (n->op) {
            case '+': return eval_tree(n->left) + eval_tree(n->right);
            case '-': return eval_tree(n->left) - eval_tree(n->right);
            case '*': return eval_tree(n->left) * eval_tree(n->right);
            case '/': return eval_tree(n->left) / eval_tree(n->right);
            default: return -1;
        }
    }
}

long double eval_monkey(char* filename) {
    hash_table ht = parse_input(filename);
    bt_node* root = malloc(sizeof(bt_node));
    build_expr_tree(ht, root, "root");

    long double result = eval_tree(root);

    free_bt_node(root);
    free_hash_table(ht);
    return result;
}

long double eval_algebra(bt_node* n, char* key, long double acc) {
    if (!strcmp(n->name, key)) {
        return acc;
    }

    bt_node* left = search_tree(n->left, key);
    bt_node* right = search_tree(n->right, key);
    bt_node* child;
    bt_node* eval;
    if (left == NULL) {
        eval = n->left;
        child = n->right;
        switch (n->op) {
            case '+': return eval_algebra(child, key, acc - eval_tree(eval));;
            case '-': return eval_algebra(child, key, eval_tree(eval) - acc);
            case '*': return eval_algebra(child, key, acc / eval_tree(eval));
            case '/': return eval_algebra(child, key, eval_tree(eval) / acc);
            default: return -1;
        }
    } else if (right == NULL) {
        eval = n->right;
        child = n->left;
        switch (n->op) {
            case '+': return eval_algebra(child, key, acc - eval_tree(eval));
            case '-': return eval_algebra(child, key, acc + eval_tree(eval));
            case '*': return eval_algebra(child, key, acc / eval_tree(eval));
            case '/': return eval_algebra(child, key, acc * eval_tree(eval));
            default: return -1;
        }
    } else {
        return -1;
    }
}

long double eval_human(char* filename) {
    hash_table ht = parse_input(filename);
    bt_node* root = malloc(sizeof(bt_node));
    build_expr_tree(ht, root, "root");

    bt_node* left = search_tree(root->left, "humn");
    bt_node* right = search_tree(root->right, "humn");
    bt_node* child;
    bt_node* eval;
    if (left == NULL) {
        eval = root->left;
        child = root->right;
    } else if (right == NULL) {
        eval = root->right;
        child = root->left;
    } else {
        return -1;
    }

    long double acc = eval_tree(eval);
    long double result = eval_algebra(child, "humn", acc);

    free_bt_node(root);
    free_hash_table(ht);
    return result;
}
