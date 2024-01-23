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

// global variable for solve_sudoku_method and undermined
static int  solve_method = 1;
static bool undermined   = false;

// define a point structure
typedef struct point {
    int x;
    int y;
    int content;
} point;

/**
 * @brief read the sudoku from a file
 *
 * @param fp file pointer
 * @param sudoku the two dimensional array
 *                that stores the sudoku
 */
void file_read(int sudoku[9][9]) {
    FILE *fp  = fopen("sudoku.txt", "r");
    char  tmp = 0;

    // read the sudoku , '*' means empty
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fscanf(fp, "%c", &tmp);
            if (tmp <= '9' && tmp > '0') {
                sudoku[i][j] = tmp - '0';
            }
        }
        fscanf(fp, "%*c");
    }

    fclose(fp);
}

/**
 * @brief write the sudoku to a file
 *
 * @param sudoku the sudoku(two dimensional array)
 */
void write_sudoku(int sudoku[9][9]) {
    FILE *output = fopen("sudoku_ans.txt", "a+");
    fprintf(output, "            Method:%d\n", solve_method);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fprintf(output, "%3d", sudoku[i][j]);
            if (j % 3 == 2 && j != 8) {
                fprintf(output, " |");
            }
        }
        fprintf(output, "\n");
        if (i % 3 == 2 && i != 8) {
            fprintf(output, "----------+----------+----------\n");
        }
    }
    fprintf(output, "\n");
    fclose(output);
}

/**
 * @brief Judge the fill in is legal or not
 *
 * @param sudoku
 * @param pt
 * @return true
 * @return false
 */
bool is_legal(const int sudoku[9][9], point pt) {

    // check the row and the col
    for (int i = 0; i < 9; i++) {
        if (sudoku[pt.x][i] == sudoku[pt.x][pt.y] && pt.y != i) {
            return false;
        }
        if (sudoku[i][pt.y] == sudoku[pt.x][pt.y] && pt.x != i) {
            return false;
        }
    }

    // check the 3*3 grid
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            if (sudoku[(pt.x / 3) * 3 + j][(pt.y / 3) * 3 + k] ==
                    sudoku[pt.x][pt.y] &&
                (pt.x / 3) * 3 + j != pt.x && (pt.y / 3) * 3 + k != pt.y) {
                return false;
            }
        }
    }

    return true;
}

/**
 * @brief check if the sudoku is solved
 *
 * @param sudoku
 * @return true
 * @return false
 */
bool is_solved(const int sudoku[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            point tmp = {i, j, 0};
            if (sudoku[i][j] == 0 || !is_legal(sudoku, tmp)) {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief find the largest possibility
 *
 * @param mark_row_or_col
 * @param largest_possibility
 */
void calc_possibility(int mark_row_or_col[9], int *largest_possibility) {
    int possibility = 0;
    for (int i = 0; i < 9; i++) {
        if (mark_row_or_col[i] == 0) {
            possibility++;
        }
    }
    if (possibility < *largest_possibility) {
        *largest_possibility = possibility;
    }
}

/**
 * @brief determine the content
 *
 * @param mark_row_or_col
 * @param x
 * @param y
 * @return int
 */
int determin_content(const int mark_row_or_col[9], const int x, const int y) {
    for (int i = 0; i < 9; i++) {
        if (mark_row_or_col[i] == 0) {
            return i + 1;
        }
    }
    undermined = true;
    return -1;
}

/**
 * @brief find the grid that has the largest
 *        possibility
 *
 * @param sudoku
 * @return point
 */
point find_start(int sudoku[9][9], int i, int j) {
    point      start               = {-1, -1, 0};
    static int mark_row_or_col[9]  = {0};
    int        largest_possibility = 9;
    // if the number is not empty, skip
    if (sudoku[i][j] != 0) {
        return start;
    }

    // find the largest possibility
    memset((void *) mark_row_or_col, 0, sizeof(int) * 9);
    for (int k = 0; k < 9; k++) {
        if (sudoku[i][k] != 0) {
            mark_row_or_col[sudoku[i][k] - 1] = 1;
        }
        if (sudoku[k][j] != 0) {
            mark_row_or_col[sudoku[k][j] - 1] = 1;
        }
        if (sudoku[(i / 3) * 3 + k / 3][(j / 3) * 3 + k % 3] != 0) {
            mark_row_or_col[sudoku[(i / 3) * 3 + k / 3][(j / 3) * 3 + k % 3] -
                            1] = 1;
        }
    }
    calc_possibility(mark_row_or_col, &largest_possibility);

    // if the largest possibility is 1,
    // which means there is determinable,
    // return the start point
    if (largest_possibility == 1) {
        point success = {
            i,
            j,
            determin_content(mark_row_or_col, i, j),
        };
        return success;
    }

    // if the largest possibility isn't 1,
    // which means there isn't determinable,
    // return un_find
    point un_find = {-1, -1, largest_possibility};
    return un_find;
}

/**
 * @brief find the start point of the sudoku
 *        which hasn't been filled
 *
 * @param sudoku
 * @return point
 */
point find_start_rest(int sudoku[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] == 0) {
                point start = {i, j, 0};
                return start;
            }
        }
    }

    // if not found, return un_find
    point un_find = {-1, -1, 0};
    return un_find;
}

/**
 * @brief By traversing all the grids, find the start point
 *
 * @param sudoku
 * @return point
 */
point find_start_all(int sudoku[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            point start = find_start(sudoku, i, j);
            if (start.x != -1) {
                return start;
            }
        }
    }

    // if the sudoku is undeterminable,
    // return a simple point
    point start = {0, 0, 0};
    while (true) {
        start.x = rand() % 9;
        start.y = rand() % 9;
        if (sudoku[start.x][start.y] == 0) {
            for (int i = 1; i <= 9; i++) {
                sudoku[start.x][start.y] = i;
                if (is_legal(sudoku, start)) {
                    start.content            = i;
                    sudoku[start.x][start.y] = 0;
                    return start;
                }
            }
        }
    }

    // else, raise an error
    printf("Error!\n");
    exit(0);
}

/**
 * @brief Solve the sudoku by DFS algorithm
 *
 * @param sudoku
 * @param start
 */
void solve_sudoku(int sudoku[9][9], point start) {

    // if the sudoku is solved, return
    static bool __is_solved__ = false;
    if (__is_solved__ || undermined) {
        return;
    }
    if (is_solved(sudoku)) {
        write_sudoku(sudoku);
        printf("Solved!Method:%d\n", solve_method++);

        // if the sudoku solve method up to 5, exit
        if (solve_method == 10) {
            __is_solved__ = true;
        }
        return;
    }

    // from the start point ,
    // search the col and the row
    // which the start point inside.
    point next;
    point tmp_next;
    bool  find                  = false;
    bool  haven_o_in_row_or_col = false;
    int   largest_possibility   = 9;
    for (int i = 0; i < 9; i++) {

        // search the col and row seperatedly,
        // to make sure the sudoku is legal
        __find_next__(i, start.y, start.x, i);
        __find_next__(start.x, i, start.y, i);
    }

    // if haven't found, search the rest
    if (haven_o_in_row_or_col == false) {
        point next_in_func = find_start_rest(sudoku);

        // if found, assign the tmp_next
        if (next_in_func.x != -1) {
            tmp_next.x       = next_in_func.x;
            tmp_next.y       = next_in_func.y;
            tmp_next.content = next_in_func.content;
        }
    }

    // then call the solve_sudoku to DFS
    if (find) {
        sudoku[next.x][next.y] = next.content;
        solve_sudoku(sudoku, next);
        sudoku[next.x][next.y] = 0;
    } else {
        for (int i = 0; i < 9; i++) {
            tmp_next.content               = i + 1;
            sudoku[tmp_next.x][tmp_next.y] = tmp_next.content;
            if (is_legal(sudoku, tmp_next)) {
                solve_sudoku(sudoku, tmp_next);
            }
            sudoku[tmp_next.x][tmp_next.y] = 0;
        }
    }
}

/**
 * @brief delete the content in a file
 *
 * @param filename
 */
void kill_content(char *filename) {
    FILE *fp = fopen(filename, "w");
    fclose(fp);
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