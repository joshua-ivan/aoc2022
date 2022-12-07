#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include "aoc2022-06.h"

int tests_run = 0;

static char const * test_queue() {
    int queue_size = 4;
    queue q = queue_init(queue_size);

    char const *init_failure_msg = "FAILURE: test_queue_init";
    mu_assert(init_failure_msg, q.head_index == 0);
    mu_assert(init_failure_msg, q.tail_index == 0);
    mu_assert(init_failure_msg, q.num_items == 0);
    for (int i = 0; i < queue_size; i++) {
        mu_assert(init_failure_msg, q.items[i] == '\0');
    }
    mu_assert(init_failure_msg, is_empty(&q));

    int results[queue_size + 1];
    for (int i = 0; i < queue_size + 1; i++) {
        results[i] = enqueue(&q, 'A' + i);
    }

    char const *enqueue_failure_msg = "FAILURE: test_enqueue";
    for (int i = 0; i < queue_size; i++) {
        mu_assert(enqueue_failure_msg, q.items[i] == ('A' + i));
        mu_assert(enqueue_failure_msg, results[i] == 0);
    }
    mu_assert(enqueue_failure_msg, results[4] == -1);

    char c = dequeue(&q);
    char const *dequeue_failure_msg = "FAILURE: test_dequeue";
    mu_assert(dequeue_failure_msg, c == 'A');

    enqueue(&q, 'E');
    char const *looping_index_failure_msg = "FAILURE: test_queue_looping_index";
    mu_assert(looping_index_failure_msg, q.head_index == 1);
    mu_assert(looping_index_failure_msg, q.tail_index == 1);
    mu_assert(looping_index_failure_msg, q.num_items == 4);

    queue_free(&q);

    return 0;
}

static char const * test_is_queue_unique() {
    int queue_size = 4;
    queue q = queue_init(queue_size);
    char const *queue_not_unique_msg = "FAILURE: test_queue_not_unique";
    mu_assert(queue_not_unique_msg, !is_queue_unique(&q));

    for (int i = 0; i < queue_size; i++) {
        enqueue(&q, 'A' + i);
    }
    char const *queue_unique_msg = "FAILURE: test_queue_unique";
    mu_assert(queue_unique_msg, is_queue_unique(&q));

    dequeue(&q);
    enqueue(&q, 'E');
    mu_assert(queue_unique_msg, is_queue_unique(&q));

    return 0;
}

static char const * test_get_start_marker() {
    char *test_arr[] = {
        "mjqjpqmgbljsphdztnvjfqwrcgsmlb",
        "bvwbjplbgvbhsrlpgdmjqwftvncz",
        "nppdvjthqldpwncqszvftbrmjlhg",
        "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg",
        "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"
    };

    char const *packet_start_msg = "FAILURE: test_get_packet_start_marker";
    int packet_expected[] = {7, 5, 6, 10, 11};
    for (int i = 0; i < 5; i++) {
        mu_assert(packet_start_msg, get_start_marker(test_arr[i], 4) == packet_expected[i]);
    }

    int message_expected[] = {19, 23, 23, 29, 26};
    for (int i = 0; i < 5; i++) {
        mu_assert(packet_start_msg, get_start_marker(test_arr[i], 14) == message_expected[i]);
    }

    return 0;
}

static char const * all_tests() {
    mu_run_test(test_queue);
    mu_run_test(test_is_queue_unique);
    mu_run_test(test_get_start_marker);

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

