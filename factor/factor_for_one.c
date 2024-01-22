#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma GCC optimize("Ofast")

/**
 * @brief if an error happens, free the memory
 *
 * @param Ptr1
 * @param Ptr2
 * @return _Noreturn
 */
static inline _Noreturn void panic_2(int *const Ptr1, int *const Ptr2) {
    free(Ptr1);
    free(Ptr2);
    exit(0);
}

/**
 * @brief if an error happens, free the memory
 *
 * @param Ptr1
 * @return _Noreturn
 */
static inline _Noreturn void panic_1(int *const Ptr1) {
    free(Ptr1);
    exit(0);
}

/**
 * @brief find the digit of an array
 *
 * @param Ptr
 * @param length
 * @return size_t
 */
static inline size_t find_digit_of_array(int *const Ptr, const size_t length) {
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
 * @details two arrays multiply each other
 * @param a
 * @param b
 * @return int*  output should be an array
 */
static inline int *multiply(const int *const a, int *const b,
                            const int MAX_LENGTH, const int digit) {
    int          *tmp_array       = malloc(sizeof(int) * MAX_LENGTH);
    static size_t tmp_length_of_b = 1;
    if (tmp_array == NULL) {
        panic_1(tmp_array);
    }
    memset(tmp_array, 0, sizeof(int) * MAX_LENGTH);

    for (size_t i = 0; i < digit; i++) {
        for (size_t j = 0; j < tmp_length_of_b; j++) {
            tmp_array[j + i] += a[i] * b[j];
        }
    }
    for (size_t i = 0; i < tmp_length_of_b + digit; i++) {
        tmp_array[i + 1] += tmp_array[i] / 10;
        tmp_array[i] %= 10;
    } // do the carry

    memcpy(b, tmp_array, MAX_LENGTH * sizeof(int));
    tmp_length_of_b = find_digit_of_array(b, tmp_length_of_b) + digit;
    free(tmp_array);
    return b;
}

/**
 * @brief print the result
 *
 * @param input
 * @param output
 */
static inline void print_factor(int const input, int *const output,
                                const int MAX_LENGTH) {
    FILE *fp = fopen("factor_for_one.txt", "w");
    fprintf(fp,"%d! = ", input);

    bool start = false;
    for (int i = MAX_LENGTH - 1; i >= 0; i--) {
        if (output[i] != 0 || start) {
            fprintf(fp,"%d", output[i]);
            start = true;
        }
    }
    fprintf(fp,"\n");
    fclose(fp);
}

/**
 * @brief add 1 to a array
 *
 * @param Ptr
 * @param digit
 */
static inline void array_add_1(int *const Ptr, const int digit) {
    for (int i = 0; i < digit; i++) {
        if (Ptr[i] == 9) {
            Ptr[i] = 0;
        } else {
            Ptr[i]++;
            break;
        }
    }
}

/**
 * @brief find the digit of input
 *
 * @param input
 * @return int
 */
int find_digit_of_input(int input) {
    int digit = 0;
    while ((input /= 10) > 0) {
        digit++;
    }
    return digit + 1;
}

int main() {
    clock_t start = clock();
    // get input and do some error checking
    int input = 0;
    do {
        printf("Enter a number: ");
        if (scanf("%d", &input) != 1) {
            scanf("%*[^\n]%*c");
        }
    } while (input < 0);

    if (input == 0) {
        printf("0! = 1\n");
        return 0;
    }

    // The length of output should be input * digit
    // Log[n!] < n Log[n]
    const int digit       = find_digit_of_input(input);
    const int MAX_LENGTH  = input * digit;
    int      *output      = malloc(MAX_LENGTH * sizeof(int));
    int      *calc_factor = malloc(digit * sizeof(int));

    // do some error checking
    if (output == NULL || calc_factor == NULL) {
        panic_2(output, calc_factor);
    }

    // initialize
    memset(output, 0, sizeof(int) * MAX_LENGTH);
    memset(calc_factor, 0, sizeof(int) * digit);
    output[0] = 1;

    // calculate the factorial
    for (size_t cnt = 1; cnt <= input; cnt++) {
        array_add_1(calc_factor, digit);
        memcpy(output, multiply(calc_factor, output, MAX_LENGTH, digit),
               sizeof(int) * MAX_LENGTH);
    }
    print_factor(input, output, MAX_LENGTH);

    free(output);
    free(calc_factor);

    // print the time taken
    clock_t end       = clock();
    double  time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_used);
    return 0;
}
