#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minunit.h"
#include "aoc2022-13.h"

int tests_run = 0;

static char const * test_packet_single_int() {
    packet p;
    char *st = "135";
    int chars = parse_packet(&p, st);

    int expected = 135;
    char const * parse_msg = "FAILURE: test_packet_single_int__parse";
    mu_assert(parse_msg, p.atom == expected);
    mu_assert(parse_msg, p.list == NULL);
    mu_assert(parse_msg, chars == 3);

    char *uv = to_string(p);
    char const * to_string_msg = "FAILURE: test_packet_single_int__to_string";
    mu_assert(to_string_msg, !strcmp(st, uv));

    return 0;
}

static char const * test_packet_empty_list() {
    packet p;
    char *st = "[]";
    int chars = parse_packet(&p, st);

    char const * parse_msg = "FAILURE: test_parse_packet_empty_list";
    mu_assert(parse_msg, p.atom == -1);
    mu_assert(parse_msg, p.list[0].atom == -1);
    mu_assert(parse_msg, chars == 2);

    char *uv = to_string(p);
    char const * to_string_msg = "FAILURE: test_packet_empty_list__to_string";
    mu_assert(to_string_msg, !strcmp(st, uv));

    return 0;
}

static char const * test_packet_flat_list() {
    packet p;
    char *st = "[1,1,3,1,1]";
    int chars = parse_packet(&p, st);

    int expected[5] = {1, 1, 3, 1, 1};
    char const * parse_msg = "FAILURE: test_parse_packet_flat_list";
    mu_assert(parse_msg, p.atom == -1);
    for (int i = 0; i < 5; i++) {
        mu_assert(parse_msg, p.list[i].atom == expected[i]);
    }
    mu_assert(parse_msg, chars == 11);

    char *uv = to_string(p);
    char const * to_string_msg = "FAILURE: test_packet_flat_list__to_string";
    mu_assert(to_string_msg, !strcmp(st, uv));

    return 0;
}

static char const * test_packet_nested_list() {
    packet p;
    char *st = "[1,[1],[[3]],[1,2],1]";
    int chars = parse_packet(&p, st);

    char const * parse_msg = "FAILURE: test_parse_packet_nested_list";
    mu_assert(parse_msg, chars == 21);
    mu_assert(parse_msg, p.list[0].atom == 1);
    mu_assert(parse_msg, p.list[1].list[0].atom == 1);
    mu_assert(parse_msg, p.list[2].list[0].list[0].atom == 3);
    mu_assert(parse_msg, p.list[3].list[0].atom == 1);
    mu_assert(parse_msg, p.list[3].list[1].atom == 2);
    mu_assert(parse_msg, p.list[4].atom == 1);

    char *uv = to_string(p);
    char const * to_string_msg = "FAILURE: test_packet_nested_list__to_string";
    mu_assert(to_string_msg, !strcmp(st, uv));

    return 0;
}

static char const * test_wrap_atom() {
    packet p = wrap_atom(5);
    char const * fail_msg = "FAILURE: test_wrap_atom";
    mu_assert(fail_msg, p.atom == -1);
    mu_assert(fail_msg, p.list[0].atom == 5);
    mu_assert(fail_msg, p.list[0].list == NULL);

    return 0;
}

static char const * test_wrap_list() {
    packet p = wrap_atom(5);
    packet q = wrap_list(p);
    char const * fail_msg = "FAILURE: test_wrap_list";
    mu_assert(fail_msg, q.atom == -1);
    mu_assert(fail_msg, q.list[0].atom == -1);
    mu_assert(fail_msg, q.list[0].list[0].atom == 5);

    return 0;
}

static char const * test_is_defined() {
    packet p;
    p.atom = 0;
    p.list = malloc(sizeof(packet));
    p.list->atom = -1;
    p.list->list = NULL;

    char const * fail_msg = "FAILURE: test_is_defined";
    mu_assert(fail_msg, is_defined(p));

    free(p.list);
    p.list = NULL;
    mu_assert(fail_msg, is_defined(p));

    p.atom = -1;
    p.list = malloc(sizeof(packet));
    p.list->atom = -1;
    p.list->list = NULL;
    mu_assert(fail_msg, is_defined(p));

    free(p.list);
    p.list = NULL;
    mu_assert(fail_msg, !is_defined(p));

    return 0;
}

static char const * test_compare_packets() {
    FILE *fp = fopen("test_cases/test.txt", "r");
    char const * input_msg = "FAILURE: test_compare_packets__input_file";
    mu_assert(input_msg, fp != NULL);

    char const * fail_msg = "FAILURE: test_compare_packets";
    char *expected = ">><><><<";
    char *line = NULL;
    size_t length = 0;
    for (int i = 0; i < 8; i++) {
        getline(&line, &length, fp);
        packet p;
        parse_packet(&p, line);

        getline(&line, &length, fp);
        packet q;
        parse_packet(&q, line);

        switch (expected[i]) {
            case '>':
                mu_assert(fail_msg, compare_packets(p, q) > 0);
                break;
            case '<':
                mu_assert(fail_msg, compare_packets(p, q) < 0);
                break;
        }

        getline(&line, &length, fp); // blank newline
    }

    return 0;
}

static char const * test_insert_packet() {
    packet *test = malloc(sizeof(packet) * 3);
    int raw[3] = {1, 4, 7};

    int expected[3][3] = {
        {1, 2, 6},
        {2, 4, 6},
        {2, 6, 7}
    };
    char const * fail_msg = "FAILURE: test_insert_packet";
    for (int i = 0; i < 3; i++) {
        test[i] = wrap_list(wrap_atom(raw[i]));
        packet *dest = malloc(sizeof(packet) * 3);
        dest[0] = wrap_list(wrap_atom(2));
        dest[1] = wrap_list(wrap_atom(6));
        insert_packet(dest, test[i], 2);
        for (int j = 0; j < 3; j++) {
            mu_assert(fail_msg, dest[j].list[0].list[0].atom == expected[i][j]);
        }
    }

    return 0;
}

static char const * test_sort_packets() {
    packet *ps = sort_packets("test_cases/test.txt");

    FILE *fp = fopen("test_cases/expected.txt", "r");
    char const * expected_msg = "FAILURE: test_compare_packets__input_file";
    mu_assert(expected_msg, fp != NULL);

    char const * fail_msg = "FAILURE: test_sort_packets";
    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    int i = 0;
    while ((read = getline(&line, &length, fp)) != -1) {
        char *actual = malloc(sizeof(char) * length);
        sprintf(actual, "%s\n", to_string(ps[i++]));
        mu_assert(fail_msg, !strcmp(actual, line));
        free(actual);
    }

    return 0;
}

static char const * test_search_packet() {
    packet *ps = sort_packets("test_cases/test.txt");
    packet p;
    parse_packet(&p, "[[2]]");
    char const * fail_msg = "FAILURE: test_search_packet";
    mu_assert(fail_msg, search_packet(ps, p) == 9);

    return 0;
}

static char const * test_get_decoder_key() {
    packet *ps = sort_packets("test_cases/test.txt");
    char const * fail_msg = "FAILURE: test_get_decoder_key";
    mu_assert(fail_msg, get_decoder_key(ps) == 140);

    return 0;
}

static char const * all_tests() {
    mu_run_test(test_packet_single_int);
    mu_run_test(test_packet_empty_list);
    mu_run_test(test_packet_flat_list);
    mu_run_test(test_packet_nested_list);
    mu_run_test(test_wrap_atom);
    mu_run_test(test_wrap_list);
    mu_run_test(test_is_defined);
    mu_run_test(test_compare_packets);
    mu_run_test(test_insert_packet);
    mu_run_test(test_sort_packets);
    mu_run_test(test_search_packet);
    mu_run_test(test_get_decoder_key);

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

