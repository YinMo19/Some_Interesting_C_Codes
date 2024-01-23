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

// if you want to optimize the code,
// uncomment the following line
// #pragma GCC optimize("Ofast")

#define __find_next__(place_1, place_2, place_3, place_4)                      \
    if (place_3 != place_4 && sudoku[place_1][place_2] == 0) {                 \
        haven_o_in_row_or_col = true;                                          \
        point next_in_func    = find_start(sudoku, place_1, place_2);          \
        next.x                = next_in_func.x;                                \
        next.y                = next_in_func.y;                                \
        next.content          = next_in_func.content;                          \
        if (next.y != -1) {                                                    \
            find = true;                                                       \
            break;                                                             \
        } else {                                                               \
            if (largest_possibility >= start.content) {                        \
                largest_possibility = start.content;                           \
                tmp_next.x          = place_1;                                 \
                tmp_next.y          = place_2;                                 \
            }                                                                  \
        }                                                                      \
    }

int main(int argc, char *argv[]) {
    clock_t _start = clock();
    srand(time(0));

    // for debugging and next time
    // you generate a new sudoku
    kill_content("sudoku_ans.txt");

    // read the sudoku
    int sudoku[9][9] = {0};
    file_read(sudoku);

    // find the start point and mark
    // solve the sudoku
    undermined = true;
    while (undermined || solve_method < 2) {
        undermined               = false;
        point start              = find_start_all(sudoku);
        sudoku[start.x][start.y] = start.content;
        solve_sudoku(sudoku, start);
        sudoku[start.x][start.y] = 0;
    }

    // if the sudoku has only one solution
    if (solve_method == 2) {
        printf("Only one solution.\n");
    }
    // print the time taken
    clock_t end       = clock();
    double  time_used = ((double) (end - _start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_used);
    return 0;
}