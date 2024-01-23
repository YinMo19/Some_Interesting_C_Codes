/**
 * @file sudoku_func.h
 * @author YinMo (YinMo19@proton.me)
 * @brief sudoku_functions for sudoku
 * @version 1.0
 * @date 2024-01-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __SUDOKU_FUNC_H__
#define __SUDOKU_FUNC_H__

#include <stdbool.h>

// for memcpy
#include <string.h>

// define a function to find the next point
// use define to achieve the same format for
// col and row.
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

// define a point structure
typedef struct point {
    int x;
    int y;
    int content;
} point;

// global variables
extern int  solve_method;
extern bool undermined;
extern bool __is_solved__;

// functions defined in sudoku_func.c
void  file_read(int sudoku[9][9]);
void  write_sudoku(int sudoku[9][9], char *filename);
bool  is_legal(const int sudoku[9][9], point pt);
bool  is_solved(const int sudoku[9][9]);
void  calc_possibility(int mark_row_or_col[9], int *largest_possibility);
int   determin_content(const int mark_row_or_col[9], const int x, const int y);
point find_start(int sudoku[9][9], int i, int j);
point find_start_rest(int sudoku[9][9]);
point find_start_all(int sudoku[9][9]);
void  solve_sudoku(int sudoku[9][9], point start,
                   const int max_generate_solution);
void  kill_content(char *filename);
void  file_read_ans_format(int (*sudoku)[9], char *filename);
void  delete_sudoku_for_least_num_and_one_solution(int sudoku[9][9]);

#endif