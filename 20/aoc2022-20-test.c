#include <stdio.h>
#include <stdlib.h>
#include "../minunit.h"
#include "aoc2022-20.h"

int tests_run = 0;

static const char* test_array_list() {
    array_list al = init_array_list();
    const char* init_msg = "FAILURE: test_array_list__init";
    for (int i = 0; i < AL_SIZE; i++) {
        mu_assert(init_msg, al.items[i] == NULL);
    }
    mu_assert(init_msg, al.count == 0);
    return 0;
}

static const char* test_parse_input() {
    array_list al = parse_input("test_cases/test.txt");
    const char* count_msg = "FAILURE: test_parse_input__count";
    mu_assert(count_msg, al.count == 7);
    short expected[7] = {1, 2, -3, 3, -2, 0, 4};
    const char* items_msg = "FAILURE: test_parse_input__items";
    mu_assert(items_msg, al.head->val == 0);
    mu_assert(items_msg, al.items[5] == al.head);
    for (int i = 0; i < al.count; i++) {
        mu_assert(items_msg, al.items[i]->val == expected[i]);
        mu_assert(items_msg, al.items[i]->prev == al.items[modulo(i - 1, 7)]);
        mu_assert(items_msg, al.items[i]->next == al.items[(i + 1) % 7]);
    }

    return 0;
}

static const char* test_modulo() {
    const char* fail_msg = "FAILURE: test_modulo";
    mu_assert(fail_msg, modulo(-2, 7) == 5);
    mu_assert(fail_msg, modulo(-9, 7) == 5);
    mu_assert(fail_msg, modulo(2, 7) == 2);
    mu_assert(fail_msg, modulo(9, 7) == 2);

    return 0;
}

static const char* test_modulo_huge() {
    const char* fail_msg = "FAILURE: test_modulo_huge";
    mu_assert(fail_msg, modulo(811589153, 6) == 5);
    mu_assert(fail_msg, modulo(1623178306, 6) == 4);
    mu_assert(fail_msg, modulo(-2434767459, 6) == 3);

    return 0;
}

static const char* test_pop_list() {
    array_list al = parse_input("test_cases/test.txt");
    al_node* pop = pop_list(al.items[3]);
    const char* fail_msg = "FAILURE: test_pop_list";
    mu_assert(fail_msg, pop->val == 3);
    short expected[7] = {0, 4, 1, 2, -3, -2, 0};
    al_node* current = al.head;
    for (int i = 0; i < 7; i++) {
        mu_assert(fail_msg, current->val == expected[i]);
        current = current->next;
    }

    return 0;
}

static const char* test_insert_list() {
    array_list al = parse_input("test_cases/test.txt");
    al_node* item = malloc(sizeof(al_node));
    item->val = 5;
    insert_list(al.head, item, al.head->next);
    short expected[9] = {0, 5, 4, 1, 2, -3, 3, -2, 0};
    const char* fail_msg = "FAILURE: test_insert_list";
    al_node* current = al.head;
    for (int i = 0; i < 9; i++) {
        mu_assert(fail_msg, current->val == expected[i]);
        current = current->next;
    }

    return 0;
}

static const char* test_move_list() {
    array_list al = parse_input("test_cases/test.txt");

    short expected[7][7] = {
        {0, 4, 2, 1, -3, 3, -2},
        {0, 4, 1, -3, 2, 3, -2},
        {0, 4, 1, 2, 3, -2, -3},
        {0, 3, 4, 1, 2, -2, -3},
        {0, 3, 4, -2, 1, 2, -3},
        {0, 3, 4, -2, 1, 2, -3},
        {0, 3, -2, 1, 2, -3, 4}
    };
    const char* fail_msg = "FAILURE: test_move_list";
    for (int i = 0; i < 7; i++) {
        move_list(al, i);
        al_node* current = al.head;
        for (int j = 0; j < 7; j++) {
            mu_assert(fail_msg, current->val == expected[i][j]);
            current = current->next;
        }
    }

    return 0;
}

static const char* test_move_list_overlap() {
    array_list al = parse_input("test_cases/overlap.txt");

    short expected[7][7] = {
        { 0, 11, 44, 22, -33, 33, -22 },
        { 0, 22, 11, 44, -33, 33, -22 },
        { 0, -33, 22, 11, 44, 33, -22 },
        { 0, -33, 33, 22, 11, 44, -22 },
        { 0, -33, -22, 33, 22, 11, 44 },
        { 0, -33, -22, 33, 22, 11, 44 },
        { 0, -33, 44, -22, 33, 22, 11 }
    };

    const char* fail_msg = "FAILURE: test_move_list_overlap";
    for (int i = 0; i < 7; i++) {
        move_list(al, i);
        al_node* current = al.head;
        for (int j = 0; j < 7; j++) {
            mu_assert(fail_msg, current->val == expected[i][j]);
            current = current->next;
        }
    }

    return 0;
}

static const char* test_mix_list() {
    array_list al = parse_input("test_cases/test.txt");
    al = mix_list(al);
    const char* fail_msg = "FAILURE: test_mix_list";
    short expected[7] = {0, 3, -2, 1, 2, -3, 4};
    al_node* current = al.head;
    for (int i = 0; i < 7; i++) {
        mu_assert(fail_msg, current->val == expected[i]);
        current = current->next;
    }

    return 0;
}

static const char* test_grove_coords() {
    const char* fail_msg = "FAILURE: test_grove_coords";
    long long expected[3] = {4, -3, 2};
    long long* actual = grove_coords("test_cases/test.txt", 0);
    for (int i = 0; i < 3; i++) {
        mu_assert(fail_msg, expected[i] == actual[i]);
    }

    return 0;
}

static const char* test_apply_key() {
    array_list al = parse_input("test_cases/test.txt");
    apply_key(al);

    long long expected[7] = {0, 3246356612, 811589153, 1623178306, -2434767459, 2434767459, -1623178306};
    al_node* current = al.head;
    const char* fail_msg = "FAILURE: test_apply_key";
    for (int i = 0; i < 7; i++) {
        mu_assert(fail_msg, expected[i] == current->val);
        current = current->next;
    }

    return 0;
}

static const char* test_mix_part2() {
    array_list al = parse_input("test_cases/test.txt");
    apply_key(al);
    al = mix_list(al);

    long long expected[7] = { 0, -2434767459, 3246356612, -1623178306, 2434767459, 1623178306, 811589153 };
    al_node* current = al.head;
    const char* fail_msg = "FAILURE: test_mix_part2";
    for (int i = 0; i < 7; i++) {
        mu_assert(fail_msg, expected[i] == current->val);
        current = current->next;
    }

    return 0;
}

static const char* test_part_two() {
    const char* fail_msg = "FAILURE: test_part_two";
    long long expected[3] = {811589153, 2434767459, -1623178306};
    long long* actual = grove_coords("test_cases/test.txt", 1);
    for (int i = 0; i < 3; i++) {
        mu_assert(fail_msg, expected[i] == actual[i]);
    }

    return 0;
}

static const char* all_tests() {
    mu_run_test(test_array_list);
    mu_run_test(test_parse_input);
    mu_run_test(test_modulo);
    mu_run_test(test_pop_list);
    mu_run_test(test_insert_list);
    mu_run_test(test_move_list);
    mu_run_test(test_mix_list);
    mu_run_test(test_grove_coords);
    mu_run_test(test_apply_key);
    mu_run_test(test_move_list_overlap);
    mu_run_test(test_modulo_huge);
    mu_run_test(test_mix_part2);
    mu_run_test(test_part_two);

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

