#include "sudoku_func.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main (int argc, char *argv[]) {
    int sudoku[9][9] = {0};
    file_read_ans_format(sudoku);
    write_sudoku(sudoku);

    return 0;
}