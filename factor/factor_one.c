#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma GCC optimize("Ofast")
#define MAX_LENGTH 500000

/**
 * @brief find the digit of an array
 *
 * @param Ptr
 * @param length
 * @return size_t
 */
static inline size_t find_digit_of_array(size_t *const Ptr,
                                         const size_t  length) {
    size_t digit = 0;
    for (size_t i = length; i > 0; i--) {
        if (Ptr[i] != 0) {
            digit = i + 1;
            break;
        }
    }
    return digit;
}

/**
 * @brief multiplies two numbers
 *
 * @details the one is number and the other is an array
 * @param a
 * @param b
 * @return size_t*  output should be an array
 */
static inline void multiply(size_t const a, size_t *const b) {
    static size_t tmp_length_of_b = 10;
    for (size_t j = 0; j < tmp_length_of_b; j++) {
        b[j] = a * b[j];
    }
    for (size_t i = 0; i < tmp_length_of_b; i++) {
        b[i + 1] += b[i] / 10;
        b[i] %= 10;
    } // do the carry

    tmp_length_of_b = find_digit_of_array(b, tmp_length_of_b) + 6;
}

int main() {
    clock_t start = clock();

    size_t input              = 0;
    size_t output[MAX_LENGTH] = {1};

    // get input and do some error checking
    do {
        printf("Enter a number: ");
        if (scanf("%zu", &input) != 1) {
            scanf("%*[^\n]%*c");
        }
    } while (input <= 0);

    FILE *fp = fopen("factor_one.txt", "w");

    for (size_t cnt = 1; cnt <= input; cnt++) {
        multiply(cnt, output);
    }
    fprintf(fp, "%zu! = ", input);

    bool start_ = false;
    for (int i = MAX_LENGTH - 1; i >= 0; i--) {
        if (output[i] != 0 || start_) {
            fprintf(fp, "%zu", output[i]);
            start_ = true;
        }
    }

    fprintf(fp, "\n");
    fclose(fp);

    // print the time taken
    clock_t end       = clock();
    double  time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_used);
    return 0;
}
