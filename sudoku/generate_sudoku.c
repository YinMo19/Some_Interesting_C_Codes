/**
 * @file generate_sudoku.c
 * @author YinMo (YinMo19@proton.me)
 * @brief Automatically generate a Sudoku and its solution. Enter them into two
 * txt files in the same folder. Compile with sudoku_func.c.
 *  
 * @version 1.0
 * @date 2024-01-24
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

#define max_generate_solution 1

int main(int argc, char *argv[]) {
    clock_t _start = clock();
    srand(time(0));

    // for debugging and next time
    // you generate a new sudoku
    kill_content("sudoku_ans.txt");

    // initialize the sudoku
    int sudoku[9][9] = {0};

    // initialize the time taken
    clock_t end       = clock();
    double  time_used = ((double) (end - _start)) / CLOCKS_PER_SEC;

    // find the start point and mark
    // generate the solved sudoku into
    // the ans file:
    // sukoku_ans.txt
    while (solve_method < 2) {
        point start              = find_start_all(sudoku);
        sudoku[start.x][start.y] = start.content;
        solve_sudoku(sudoku, start, max_generate_solution);
        sudoku[start.x][start.y] = 0;

        // calculate the time taken
        // to provide a judge element
        end       = clock();
        time_used = ((double) (end - _start)) / CLOCKS_PER_SEC;
        if (time_used > 1 && solve_method == 1) {
            exit(0);
        }
    }

    // delete the sudoku for random choice
    // and output the sudoku in ans format
    int ans[9][9] = {0};
    delete_sudoku_for_least_num_and_one_solution(sudoku);
    file_read_ans_format(ans, "sudoku_ans_format.txt");
    solve_method = 1;

    // output the sudoku
    kill_content("sudoku_ans.txt");
    kill_content("sudoku_ans_format.txt");
    write_sudoku(ans, "sudoku_ans.txt","output1");
    write_sudoku(sudoku, "sudoku_ans_format.txt", "puz");

    // print the time taken
    end       = clock();
    time_used = ((double) (end - _start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_used);
    return 0;
}