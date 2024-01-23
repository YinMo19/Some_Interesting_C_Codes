#ifndef __SUDOKU_FUNC_H__
#define __SUDOKU_FUNC_H__

#include <stdbool.h>


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

extern int  solve_method ;
extern bool undermined   ;

void file_read(int sudoku[9][9]);
void write_sudoku(int sudoku[9][9]);
bool is_legal(const int sudoku[9][9], point pt);
bool is_solved(const int sudoku[9][9]);
void calc_possibility(int mark_row_or_col[9], int *largest_possibility);
int determin_content(const int mark_row_or_col[9], const int x, const int y);
point find_start(int sudoku[9][9], int i, int j);
point find_start_rest(int sudoku[9][9]);
point find_start_all(int sudoku[9][9]);
void solve_sudoku(int sudoku[9][9], point start);
void kill_content(char *filename);

#endif