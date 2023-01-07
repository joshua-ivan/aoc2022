#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc2022-25.h"

int int_pow(int base, int exp) {
    int acc = 1;
    for (int i = 0; i < exp; i++) {
        acc *= base;
    }
    return acc;
}

int sna_to_dec(char* sna) {
    int len = strlen(sna);
    int acc = 0;
    char* digits = "=-012";
    for (int i = 0; i < len; i++) {
        char current[1] = { sna[i] };
        int val = strcspn(digits, current) - 2;
        acc += (val * int_pow(5, len - 1 - i));
    }

    return acc;
}

int digit_to_hash(char digit) {
    switch (digit) {
        case '2': return 4;
        case '1': return 3;
        case '0': return 2;
        case '-': return 1;
        case '=': return 0;
        default: return -1;
    }
}

char* snafu_addition(char* x, char* y) {
    int x_len = strlen(x);
    int y_len = strlen(y);
    int result_len = (x_len > y_len) ? x_len + 1 : y_len + 1;

    char* result = malloc(sizeof(char) * result_len + 1);
    result[result_len] = '\0';
    for (int i = 0; i < result_len; i++) {
        result[i] = ' ';
    }

    char addition_tables[3][5][5][2] = {
        {
            {"00","01","02","1=","1-"},
            {"01","02","1=","1-","10"},
            {"02","1=","1-","10","11"},
            {"1=","1-","10","11","12"},
            {"1-","10","11","12","2="}
        },
        {
            {"01","02","1=","1-","10"},
            {"02","1=","1-","10","11"},
            {"1=","1-","10","11","12"},
            {"1-","10","11","12","2="},
            {"10","11","12","2=","2-"}
        },
        {
            {"02","1=","1-","10","11"},
            {"1=","1-","10","11","12"},
            {"1-","10","11","12","2="},
            {"10","11","12","2=","2-"},
            {"11","12","2=","2-","20"}
        }
    };

    int i = 0;
    int carry = 1;
    while ((x_len - 1 - i) > -1 && (y_len - 1 - i) > -1) {
        int x_hash = digit_to_hash(x[x_len - 1 - i]);
        int y_hash = digit_to_hash(y[y_len - 1 - i]);

        result[result_len - 1 - i] = addition_tables[carry][x_hash][y_hash][1];
        carry = addition_tables[carry][x_hash][y_hash][0] - '0';

        i++;
    }
    while ((x_len - 1 - i) > -1) {
        int x_hash = digit_to_hash(x[x_len - 1 - i]);
        int y_hash = 2;

        result[result_len - 1 - i] = addition_tables[carry][x_hash][y_hash][1];
        carry = addition_tables[carry][x_hash][y_hash][0] - '0';

        i++;
    }
    while ((y_len - 1 - i) > -1) {
        int x_hash = 2;
        int y_hash = digit_to_hash(y[y_len - 1 - i]);

        result[result_len - 1 - i] = addition_tables[carry][x_hash][y_hash][1];
        carry = addition_tables[carry][x_hash][y_hash][0] - '0';

        i++;
    }
    switch (carry) {
        case 1:
            char* temp = malloc(sizeof(char) * result_len);
            for (int i = 0; i < result_len; i++) {
                temp[i] = result[i + 1];
            }
            free(result);
            result = temp;
            break;
        case 0: result[0] = '-'; break;
        case 2: result[0] = '1'; break;
    }

    return result;
}

char* sum_file(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        return "";
    }

    char* line = NULL;
    size_t length = 0;
    ssize_t read;
    char* result;

    if ((read = getline(&line, &length, fp)) != -1) {
        result = malloc(sizeof(char) * (read + 1));
        strcpy(result, line);
        char* newline = strchr(result, '\n');
        if (newline != NULL) newline[0] = '\0';
    }

    while ((read = getline(&line, &length, fp)) != -1) {
        char* temp = malloc(sizeof(char) * (read + 1));
        strcpy(temp, line);
        char* newline = strchr(temp, '\n');
        if (newline != NULL) newline[0] = '\0';

        char* next = snafu_addition(result, temp);

        free(result);
        free(temp);
        result = next;
    }

    free(line);
    fclose(fp);
    return result;
}
