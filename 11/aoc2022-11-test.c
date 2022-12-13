#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minunit.h"
#include "aoc2022-11.h"

int tests_run = 0;

static char const * test_load_base_strings() {
    char **base = load_base_strings();
    char *expected[6] = {
        "Monkey ",
        "  Starting items: ",
        "  Operation: new = old ",
        "  Test: divisible by ",
        "    If true: throw to monkey ",
        "    If false: throw to monkey "
    };

    char const * failure_msg = "FAILURE: test_load_base_strings";
    for (int i = 0; i < NUM_BASE_STRINGS; i++) {
        mu_assert(failure_msg, !strcmp(expected[i], base[i]));
    }

    free_base_strings(base);
    return 0;
}

static char const * test_get_significant_index() {
    char **base = load_base_strings();
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) exit(EXIT_FAILURE);

    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    int expected[6] = {7, 18, 23, 21, 29, 30};
    char const * failure_msg = "FAILURE: test_get_significant_index";
    for (int i = 0; i < 6; i++) {
        read = getline(&line, &length, fp);
        if (read == -1) mu_assert(failure_msg, 1 == 0);
        int actual = get_significant_index(line, base[i]);
        mu_assert(failure_msg, expected[i] == actual);
    }

    fclose(fp);
    free_base_strings(base);
    return 0;
}

static char const * test_set_items() {
    monkey m;
    char *test_str = "52, 78, 79, 63, 51, 94\n";
    set_items(&m, test_str);

    int len = 6;
    int expected[6] = {52, 78, 79, 63, 51, 94};
    char const * failure_msg = "FAILURE: test_set_items";
    for (int i = 0; i < len; i++) {
        mu_assert(failure_msg, expected[i] == m.items[i]);
    }

    return 0;
}

static char const * test_set_operation() {
    monkey m;
    m.items[0] = 0;

    char *test_ops[4] = {
        "+ 2\n",
        "+ old\n",
        "* 2\n",
        "* old\n"
    };
    char const * failure_msgs[4] = {
        "FAILURE: test_set_operation__add_const",
        "FAILURE: test_set_operation__add_old",
        "FAILURE: test_set_operation__multiply_const",
        "FAILURE: test_set_operation__multiply_old"
    };
    int expected[4] = {2, 4, 8, 64};

    for (int i = 0; i < 4; i++) {
        set_operation(&m, test_ops[i]);
        (m.op)(&m.items[0], m.operand, 100);
        mu_assert(failure_msgs[i], m.items[0] == expected[i]);
        free(m.operand);
    }

    return 0;
}

static char const * test_init_monkey() {
    char **base = load_base_strings();
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) exit(EXIT_FAILURE);

    char const * failure_msg = "FAILURE: test_init_monkey";
    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    char *input[6];
    for (int i = 0; i < 6; i++) {
        read = getline(&line, &length, fp);
        if (read == -1) mu_assert(failure_msg, 1 == 0);
        int actual = get_significant_index(line, base[i]);

        char *sig_line = malloc(sizeof(char) * strlen(line + actual) + 1);
        strcpy(sig_line, line + actual);
        input[i] = sig_line;
    }

    monkey m = init_monkey(input);
    mu_assert(failure_msg, m.test == 5);
    mu_assert(failure_msg, m.monkey_t == 1);
    mu_assert(failure_msg, m.monkey_f == 6);

    return 0;
}

static char const * test_throw_item() {
    char *m_str[6] = {
        "0", "2, 4", "* 2", "2", "0", "1"
    };
    monkey m = init_monkey(m_str);
    char *n_str[6] = {
        "1", "", "* 2", "2", "0", "1"
    };
    monkey n = init_monkey(n_str);

    throw_item(&m, &n);

    char const * failure_msg = "FAILURE: test_throw";
    mu_assert(failure_msg, m.items[0] == 4);
    mu_assert(failure_msg, m.num_items == 1);
    mu_assert(failure_msg, n.items[0] == 2);
    mu_assert(failure_msg, n.num_items == 1);

    return 0;
}

static char const * test_simulate_monkeys() {
    char **base = load_base_strings();
    FILE *fp = fopen("test_cases/test.txt", "r");
    if (fp == NULL) exit(EXIT_FAILURE);

    char const * failure_msg = "FAILURE: test_simulate_monkeys";
    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    monkey m[4];
    for (int i = 0; i < 4; i++) {
        char *input[6];
        for (int j = 0; j < 6; j++) {
            read = getline(&line, &length, fp);
            if (read == -1) mu_assert(failure_msg, 1 == 0);
            int actual = get_significant_index(line, base[j]);

            char *sig_line = malloc(sizeof(char) * strlen(line + actual) + 1);
            strcpy(sig_line, line + actual);
            input[j] = sig_line;
        }
        m[i] = init_monkey(input);
        read = getline(&line, &length, fp);
    }

    long* inspections = simulate_monkeys(m, 4, 20, 1);
    int expected_items[4][5] = {
        {10, 12, 14, 26, 34},
        {245, 93, 53, 199, 115},
        {-1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1}
    };
    int expected_num_items[4] = {5, 5, 0, 0};
    int expected_inspections[4] = {101, 95, 7, 105};
    for (int i = 0; i < 4; i++) {
        mu_assert(failure_msg, m[i].num_items == expected_num_items[i]); 
        for (int j = 0; j < m[i].num_items; j++) {
            mu_assert(failure_msg, m[i].items[j] == expected_items[i][j]); 
        }
        mu_assert(failure_msg, inspections[i] == expected_inspections[i]); 
    }
    return 0;
}

static char const * test_part_two() {
    char **base = load_base_strings();
    FILE *fp = fopen("test_cases/test.txt", "r");
    if (fp == NULL) exit(EXIT_FAILURE);

    char const * failure_msg = "FAILURE: test_part_two";
    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    monkey m[4];
    for (int i = 0; i < 4; i++) {
        char *input[6];
        for (int j = 0; j < 6; j++) {
            read = getline(&line, &length, fp);
            if (read == -1) mu_assert(failure_msg, 1 == 0);
            int actual = get_significant_index(line, base[j]);

            char *sig_line = malloc(sizeof(char) * strlen(line + actual) + 1);
            strcpy(sig_line, line + actual);
            input[j] = sig_line;
        }
        m[i] = init_monkey(input);
        read = getline(&line, &length, fp);
    }

    long* inspections = simulate_monkeys(m, 4, 10000, 0);
    int expected[4] = {52166, 47830, 1938, 52013};
    for (int i = 0; i < 4; i++) {
        mu_assert(failure_msg, inspections[i] == expected[i]); 
    }
    long expected_business = 2713310158;
    mu_assert(failure_msg, expected_business == calculate_monkey_business(inspections, 4));

    return 0;
}

static char const * test_calculate_monkey_business() {
    long test_ins[4] = {101, 95, 7, 105};
    char const * failure_msg = "FAILURE: test_calculate_monkey_business";
    mu_assert(failure_msg, calculate_monkey_business(test_ins, 4) == 10605);

    return 0;
}

static char const * all_tests() {
    mu_run_test(test_get_significant_index);
    mu_run_test(test_load_base_strings);
    mu_run_test(test_set_items);
    mu_run_test(test_set_operation);
    mu_run_test(test_init_monkey);
    mu_run_test(test_throw_item);
    mu_run_test(test_simulate_monkeys);
    mu_run_test(test_calculate_monkey_business);
    mu_run_test(test_part_two);

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

