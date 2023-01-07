#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../minunit.h"
#include "aoc2022-25.h"

int tests_run = 0;

static const char* test_sna_to_dec() {
    const char* fail_msg = "FAILURE: test_sna_to_dec";
    mu_assert(fail_msg, sna_to_dec("1=-0-2") == 1747);
    mu_assert(fail_msg, sna_to_dec("20012") == 1257);
    return 0;
}

static const char* test_digit_to_hash() {
    const char* fail_msg = "FAILURE: test_digit_to_hash";
    char digits[5] = "=-012";
    for (int i = 0; i < 5; i++) {
        mu_assert(fail_msg, digit_to_hash(digits[i]) == i);
    }

    return 0;
}

static const char* test_snafu_addition() {
    const char* fail_msg = "FAILURE: test_snafu_addition";

    char *result = snafu_addition("2", "2");
    mu_assert(fail_msg, !strcmp(result, "1-"));
    free(result);

    result = snafu_addition("02", "02");
    mu_assert(fail_msg, !strcmp(result, "1-"));
    free(result);

    result = snafu_addition("===", "===");
    mu_assert(fail_msg, !strcmp(result, "-001"));
    free(result);

    result = snafu_addition("222", "222");
    mu_assert(fail_msg, !strcmp(result, "100-"));
    free(result);

    result = snafu_addition("1=-0-2", "20012");
    mu_assert(fail_msg, !strcmp(result, "10-01-"));
    free(result);

    return 0;
}

static const char* test_sum_file() {
    const char* fail_msg = "FAILURE: test_process_input";

    char* sum = sum_file("test_cases/test.txt");
    mu_assert(fail_msg, !strcmp(sum, "2=-1=0"));
    free(sum);

    return 0;
}

static const char* all_tests() {
    mu_run_test(test_sna_to_dec);
    mu_run_test(test_digit_to_hash);
    mu_run_test(test_snafu_addition);
    mu_run_test(test_sum_file);

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

