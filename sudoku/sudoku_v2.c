/**
 * @file sudoku_v2.c
 * @author YinMo (YinMo19@proton.me)
 * @brief Sudoku Solver v2.0
 *        Find the largest possibility grid to fill in.
 *        The DFS algorithm is used to realize
 *        the automatic solution of Sudoku.
 * @version 2.0
 * @date 2024-01-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "sudoku_func.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define max_generate_solution 9

// if you want to optimize the code,
// uncomment the following line
// #pragma GCC optimize("Ofast")

int main(int argc, char *argv[]) {
    clock_t _start = clock();
    srand(time(0));

    // for debugging and next time
    // you generate a new sudoku
    kill_content("sudoku_ans.txt");

    // read the sudoku
    int sudoku[9][9] = {0};
    file_read(sudoku);

    // initialize the time taken
    clock_t end       = clock();
    double  time_used = ((double) (end - _start)) / CLOCKS_PER_SEC;

    // find the start point and mark
    // solve the sudoku
    while (solve_method < 2) {
        point start              = find_start_all(sudoku);
        sudoku[start.x][start.y] = start.content;
        solve_sudoku(sudoku, start, max_generate_solution);
        sudoku[start.x][start.y] = 0;

        // calculate the time taken
        // to provide a judge element
        end       = clock();
        time_used = ((double) (end - _start)) / CLOCKS_PER_SEC;
        if (time_used > 5) {
            break;
        }
    }

    // if the sudoku can't be solved in 5 seconds
    // print the error message
    if (solve_method == 1) {
        printf("No solution(in 5 seconds).\n");
    }

    // if the sudoku has only one solution
    if (solve_method == 2) {
        printf("Only one solution.\n");
    } else if (solve_method >= 3) {
        printf("Totally %d solutions.\n", solve_method - 1);
    }

    // print the time taken
    end       = clock();
    time_used = ((double) (end - _start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_used);
    return 0;
}