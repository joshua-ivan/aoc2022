#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minunit.h"
#include "aoc2022-07.h"

int tests_run = 0;

static char const * test_calculate_hash() {
    char const *failure_msg = "FAILURE: test_calculate_hash";
    mu_assert(failure_msg, calculate_hash("test") == 8);

    return 0;
}

static char const * test_hashtable() {
    hashtable ht;
    hashtable_init(&ht);
    directory *d = directory_init("D");
    hashtable_insert(&ht, d);
    directory *n = directory_init("N");
    hashtable_insert(&ht, n);
    directory *x = directory_init("X");
    hashtable_insert(&ht, x);

    char const *insert_failure_msg = "FAILURE: test_hashtable_insert";
    mu_assert(insert_failure_msg, !strcmp(d->name, ht.array[8]->dir->name));
    mu_assert(insert_failure_msg, !strcmp(n->name, ht.array[8]->next->dir->name));
    mu_assert(insert_failure_msg, !strcmp(x->name, ht.array[8]->next->next->dir->name));

    char const *search_failure_msg = "FAILURE: test_hashtable_search";
    mu_assert(search_failure_msg, !strcmp(d->name, hashtable_search(&ht, "D")->name));
    mu_assert(search_failure_msg, !strcmp(n->name, hashtable_search(&ht, "N")->name));
    mu_assert(search_failure_msg, !strcmp(x->name, hashtable_search(&ht, "X")->name));

    return 0;
}

static char const * test_stack() {
    stack s;
    stack_init(&s);

    stack_push(&s, "test");
    char const *push_failure_msg = "FAILURE: test_stack_push";
    mu_assert(push_failure_msg, !strcmp(s.str[s.index - 1], "test"));

    stack_push(&s, "beef");
    mu_assert(push_failure_msg, !strcmp(s.str[s.index - 1], "beef"));

    char *pop = stack_pop(&s);
    char const *pop_failure_msg = "FAILURE: test_stack_pop";
    mu_assert(pop_failure_msg, !strcmp(pop, "beef"));
    mu_assert(pop_failure_msg, s.index == 1);

    pop = stack_pop(&s);
    mu_assert(pop_failure_msg, !strcmp(pop, "test"));
    mu_assert(pop_failure_msg, s.index == 0);


    return 0;
}

static char const * test_build_absolute_path() {
    char *path[3] = {
        "/",
        "etc/",
        "test/"
    };
    char *expected = "/etc/test/";
    char const * failure_msg = "FAILURE: test_build_absolute_path";
    mu_assert(failure_msg, !strcmp(expected, build_absolute_path(path, 3)));

    return 0;
}

static char const * test_str_append() {
    char *m = "etc";
    char *n = "/";

    char *expected = "etc/";
    char const * failure_msg = "FAILURE: test_str_append";
    mu_assert(failure_msg, !strcmp(expected, str_append(m, n)));

    return 0;
}

static char const * test_str_strip() {
    char *s = "test\n";
    char *expected = "test";

    char const * failure_msg = "FAILURE: test_str_strip";
    mu_assert(failure_msg, !strcmp(expected, str_strip(s, '\n')));

    return 0;
}

static char const * test_parse_output_single_file() {
    FILE *fp = fopen("test_cases/single-file.txt", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    hashtable ht = parse_output(fp);

    directory *root = hashtable_search(&ht, "/");
    char const * failure_msg = "FAILURE: test_parse_output_single_file";
    mu_assert(failure_msg, root->size == 14848514);

    return 0;
}

static char const * test_parse_output() {
    FILE *fp = fopen("test_cases/aoc_test.txt", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    hashtable ht = parse_output(fp);
    char *all_dirs[4] = {
        "/a/e/",
        "/a/",
        "/d/",
        "/"
    };
    int expected[4] = {584, 94853, 24933642, 48381165};

    char const * aoc_msg = "FAILURE: test_parse_output_aoc_test";
    for (int i = 0; i < 4; i++) {
        directory *d = hashtable_search(&ht, all_dirs[i]);
        mu_assert(aoc_msg, d->size == expected[i]);
    }

    return 0;
}

static char const * test_solve_puzzle_one() {
    FILE *fp = fopen("test_cases/aoc_test.txt", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    hashtable ht = parse_output(fp);

    char const * failure_msg = "FAILURE: test_solve_puzzle_one";
    mu_assert(failure_msg, solve_puzzle_one(&ht) == 95437);

    return 0;
}

static char const * test_solve_puzzle_two() {
    FILE *fp = fopen("test_cases/aoc_test.txt", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    hashtable ht = parse_output(fp);

    char const * failure_msg = "FAILURE: test_solve_puzzle_two";
    mu_assert(failure_msg, solve_puzzle_two(&ht) == 24933642);

    return 0;
}

static char const * all_tests() {
    mu_run_test(test_calculate_hash);
    mu_run_test(test_hashtable);
    mu_run_test(test_stack);
    mu_run_test(test_build_absolute_path);
    mu_run_test(test_str_append);
    mu_run_test(test_str_strip);

    mu_run_test(test_parse_output_single_file);
    mu_run_test(test_parse_output);

    mu_run_test(test_solve_puzzle_one);
    mu_run_test(test_solve_puzzle_two);

    return 0;
}

int main(int argc, char **argv) {
    char const *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}

