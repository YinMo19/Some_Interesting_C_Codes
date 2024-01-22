// Sudoku Solver v1.0
// Traversing all the grids,
// and this is the least efficient method.
// The DFS algorithm is used to realize
// the automatic solution of Sudoku.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma GCC optimize("Ofast")

// define a point structure
typedef struct point {
    int x;
    int y;
} point;

// four directions of searching
static const int dx[4] = {0, 1, 0, -1};
static const int dy[4] = {1, 0, -1, 0};

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
            if (tmp != '*') {
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
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fprintf(output, "%3d", sudoku[i][j]);
            if (j % 3 == 2 && j != 8) {
                fprintf(output, " |");
            }
        }
        fprintf(output, "\n");
        if (i % 3 == 2 && i != 8) {
            fprintf(output, "--------------------------------\n");
        }
    }
    fclose(output);
}

/**
 * @brief find the start point
 *
 * @param sudoku
 * @return point a struct that stores the start point
 *                of the x and y
 */
point find_start(int sudoku[9][9]) {
    point start;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] == 0) {
                start.x = i;
                start.y = j;
                return start;
            }
        }
    }
    return start;
}

/**
 * @brief check if the sudoku is solved
 *
 * @param pt_mark
 * @return true
 * @return false
 */
bool is_solved(int pt_mark[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (pt_mark[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Judge the fill in is legal or not
 *
 * @param sudoku
 * @param pt
 * @return true
 * @return false
 */
bool is_legal(int sudoku[9][9], point pt) {
    for (int i = 0; i < 9; i++) {
        if (sudoku[pt.x][i] == sudoku[pt.x][pt.y] && pt.y != i) {
            return false;
        }
        if (sudoku[i][pt.y] == sudoku[pt.x][pt.y] && pt.x != i) {
            return false;
        }
    }
    return true;
}

/**
 * @brief find the next point
 *
 * @param sudoku
 * @param start given point
 * @return point  the next point
 */
point find_next(int sudoku[9][9], point start) {
    point next;
    for (int i = 0; i < 81; i++) {
        next.x = (start.x + i / 9) % 9;
        next.y = (start.y + i % 9) % 9;
        if (sudoku[next.x][next.y] == 0) {
            return next;
        }
    }

    // if something wrong
    // you can't find the next point
    // so raise the panic point
    point panic = {-1, -1};
    return panic;
}

/**
 * @brief solve the sudoku in DFS algorithm
 *
 * @param sudoku
 * @param pt_mark
 * @param start the start point of the sudoku
 */
void solve_sudoku(int sudoku[9][9], int pt_mark[9][9], point start) {
    if (is_solved(pt_mark)) {
        write_sudoku(sudoku);
        printf("Solved!\n");
        return;
    }

    for (int i = 0; i < 4; i++) {
        point next = find_next(sudoku, start);

        if (next.x == -1) {
            printf("error!\n");
            exit(0);
        }

        // try all the numbers from 1 to 9
        // to make sure the sudoku is legal
        for (int j = 1; j <= 9; j++) {
            sudoku[next.x][next.y] = j;
            if (is_legal(sudoku, next)) {
                solve_sudoku(sudoku, pt_mark, next);
            }
        }

        // if the sudoku is not legal or  after DFS,
        // backtracking
        sudoku[next.x][next.y]  = 0;
        pt_mark[next.x][next.y] = 0;
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

int main(void) {
    clock_t _start = clock();

    // for debugging and next time
    // you generate a new sudoku
    kill_content("sudoku_ans.txt");

    // read the sudoku
    int sudoku[9][9]  = {0};
    int pt_mark[9][9] = {0};
    file_read(sudoku);

    // find the start point and mark
    point start               = find_start(sudoku);
    pt_mark[start.x][start.y] = 1;

    // solve the sudoku
    solve_sudoku(sudoku, pt_mark, start);

    // print the time taken
    clock_t end       = clock();
    double  time_used = ((double) (end - _start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_used);
    return 0;
}