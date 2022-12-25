#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../minunit.h"
#include "aoc2022-21.h"

int tests_run = 0;

static const char* test_hashcalc() {
    long hash = hashcalc("root");
    long expected = (
        (('r' - 'a') << 15) +
        (('o' - 'a') << 10) +
        (('o' - 'a') << 5) +
        ('t' - 'a')
    );
    const char* fail_msg = "FAILURE: test_hashcalc";
    mu_assert(fail_msg, hash == expected);
    return 0;
}

static const char* test_init_hash_table() {
    hash_table ht = init_hash_table();
    const char* fail_msg = "FAILURE: init_hash_table";
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        mu_assert(fail_msg, ht.items[i] == NULL);
    }
    free_hash_table(ht);

    return 0;
}

static const char* test_parse_input() {
    hash_table ht = parse_input("test_cases/test.txt");

    char *keys[15] = {
        "root", "dbpl", "cczh", "zczc", "ptdq",
        "dvpt", "lfqf", "humn", "ljgn", "sjmn",
        "sllz", "pppw", "lgvd", "drzm", "hmdt"
    };
    char *values[15] = {
        "pppw + sjmn", "5", "sllz + lgvd", "2", "humn - dvpt",
        "3", "4", "5", "2", "drzm * dbpl",
        "4", "cczh / lfqf", "ljgn * ptdq", "hmdt - zczc", "32"
    };
    const char* fail_msg = "FAILURE: test_parse_input";
    for (int i = 0; i < 15; i++) {
        mu_assert(fail_msg, !strcmp(ht.items[hashcalc(keys[i])], values[i]));
    }
    free_hash_table(ht);

    return 0;
}

static const char* test_search_tree() {
    hash_table ht = parse_input("test_cases/test.txt");
    bt_node* root = malloc(sizeof(bt_node));
    build_expr_tree(ht, root, "root");

    const char* fail_msg = "FAILURE: test_search_tree";
    mu_assert(fail_msg, search_tree(root, "humn") != NULL);
    mu_assert(fail_msg, search_tree(root, "miss") == NULL);

    free_bt_node(root);
    free_hash_table(ht);
    return 0;
}

static const char* test_build_expr_tree() {
    hash_table ht = parse_input("test_cases/test.txt");
    bt_node* root = malloc(sizeof(bt_node));
    build_expr_tree(ht, root, "root");

    char* keys[15] = {
        "root", "dbpl", "cczh", "zczc", "ptdq",
        "dvpt", "lfqf", "humn", "ljgn", "sjmn",
        "sllz", "pppw", "lgvd", "drzm", "hmdt"
    };
    char ops[15] = {
        '+', 0, '+', 0, '-',
        0, 0, 0, 0, '*',
        0, '/', '*', '-', 0
    };
    int expected_children[15][2] = {
        { 11, 9 }, { -1, -1 }, { 10, 12 }, { -1, -1 }, { 7, 5 },
        { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { 13, 1 },
        { -1, -1 }, { 2, 6 }, { 8, 4 }, { 14, 3 }, { -1, -1 }
    };
    const char* fail_msg = "FAILURE: test_build_expr_tree";
    for (int i = 0; i < 15; i++) {
        bt_node* n = search_tree(root, keys[i]);
        mu_assert(fail_msg, !strcmp(n->name, keys[i]));
        mu_assert(fail_msg, n->op == ops[i]);
        if (expected_children[i][0] > -1) {
            int child = expected_children[i][0];
            mu_assert(fail_msg, !strcmp(n->left->name, keys[child]));
        }
        if (expected_children[i][1] > -1) {
            int child = expected_children[i][1];
            mu_assert(fail_msg, !strcmp(n->right->name, keys[child]));
        }
    }

    free_bt_node(root);
    free_hash_table(ht);
    return 0;
}

static const char* test_eval_tree() {
    hash_table ht = parse_input("test_cases/test.txt");
    bt_node* root = malloc(sizeof(bt_node));
    build_expr_tree(ht, root, "root");

    const char* fail_msg = "FAILURE: test_eval_tree";
    mu_assert(fail_msg, eval_tree(root) == 152);

    free_bt_node(root);
    free_hash_table(ht);
    return 0;
}

static const char* test_eval_monkey() {
    const char* fail_msg = "FAILURE: test_eval_monkey";
    mu_assert(fail_msg, eval_monkey("test_cases/test.txt") == 152);

    return 0;
}

static const char* test_eval_algebra() {
    hash_table ht = parse_input("test_cases/test.txt");
    bt_node* root = malloc(sizeof(bt_node));
    build_expr_tree(ht, root, "root");

    const char* search_msg = "FAILURE: test_eval_algebra__search";
    bt_node* left = search_tree(root->left, "humn");
    mu_assert(search_msg, left != NULL);
    bt_node* right = search_tree(root->right, "humn");
    mu_assert(search_msg, right == NULL);

    const char* fail_msg = "FAILURE: test_eval_algebra";
    long double acc = eval_tree(root->right);
    mu_assert(fail_msg, eval_algebra(root->left, "humn", acc) == 301);

    free_bt_node(root);
    free_hash_table(ht);
    return 0;
}

static const char* test_eval_human() {
    const char* fail_msg = "FAILURE: test_eval_human";
    mu_assert(fail_msg, eval_human("test_cases/test.txt") == 301);

    return 0;
}

static const char* all_tests() {
    mu_run_test(test_hashcalc);
    mu_run_test(test_init_hash_table);
    mu_run_test(test_parse_input);
    mu_run_test(test_search_tree);
    mu_run_test(test_build_expr_tree);
    mu_run_test(test_eval_tree);
    mu_run_test(test_eval_monkey);
    mu_run_test(test_eval_algebra);
    mu_run_test(test_eval_human);

    return 0;
}

int main(int argc, char **argv) {
    const char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}

