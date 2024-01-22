#include <stdio.h>
#include <stdlib.h>

/**
 * @brief multiplies two numbers
 *
 * @details one is a number and the other is an array
 * @param a
 * @param b
 * @return int* output should be an array
 */
int *multiply(int const a, const int *const b, size_t length) {
    int *c = (int *) malloc(length * sizeof(int));
    for (size_t i = 0; i < length; i++) {
        c[i] = 0;
    }

    for (size_t j = 0; j < length; j++) {
        c[j] = a * b[j];
    }
    for (size_t i = 0; i < length - 1; i++) {
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    } // do the carry

    return c;
}

/**
 * @brief print the result
 *
 * @param input
 * @param output
 */
static inline void print_factor(int const input, int *const output,
                                size_t length) {
    printf("%d! = ", input);

    int start = 0;
    for (int i = length - 1; i >= 0; i--) {
        if (output[i] != 0 || start) {
            printf("%d", output[i]);
            start = 1;
        }
    }
    printf("\n");
    free(output); 
}

int main(int argc, char **argv) {
    int input = 0;
    printf("Enter a number: ");
    if (scanf("%d", &input) != 1) {
        scanf("%*[^\n]%*c");
    }

    if (input <= 0) {
        printf("Invalid input\n");
        return 1;
    }

    int *output = (int *) malloc(sizeof(int));
    output[0]   = 1;

    for (size_t cnt = 1; cnt <= input; cnt++) {
        int *temp = multiply(cnt, output, cnt);
        free(output); // free the previous memory allocation
        output = temp;
    }

    print_factor(input, output, input);
    return 0;
}