#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 10000

/**
 * @brief multiplies two numbers
 *
 * @details the one is number and the other is an array
 * @param a
 * @param b
 * @return int*  output should be an array
 */
int *multiply(int const a, const int *const b) {
    static int c[MAX_LENGTH] = {0};
    memset(c, 0, sizeof(int) * MAX_LENGTH);

    for (int j = 0; j < MAX_LENGTH; j++) {
        c[j] = a * b[j];
    }
    for (size_t i = 0; i < MAX_LENGTH - 1; i++) {
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    } // do the carry

    return c;
}

int main() {
    clock_t start = clock();

    int input              = 0;
    int output[MAX_LENGTH] = {1};

    do {
        printf("Enter a number: ");
        if (scanf("%d", &input) != 1) {
            scanf("%*[^\n]%*c");
        }
    } while (input <= 0);

    for (size_t cnt = 1; cnt <= input; cnt++) {
        memcpy(output, multiply(cnt, output), sizeof(int) * MAX_LENGTH);
        printf("%zu! = ", cnt);

        bool start = false;
        for (int i = MAX_LENGTH - 1; i >= 0; i--) {
            if (output[i] != 0 || start) {
                printf("%d", output[i]);
                start = true;
            }
        }

        printf("\n");
    }

    // print the time taken
    clock_t end       = clock();
    double  time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_used);
    return 0;
}
