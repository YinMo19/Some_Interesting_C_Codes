/**
 * @file TikZ_gen_func.h
 * @author YinMo19 (YinMo19@proton.me)
 * @brief functions in TikZ-generator
 * @version 0.1
 * @date 2024-01-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __TikZ_gen_func__
#define __TikZ_gen_func__

// define a basic struct
typedef struct circuit {
    int  start;
    char name[3];
    char direction;
    char description[100];
    char desc_dir;
} circuit;

void kill_file(char *filename);
void write_file_head (char *filename);
void write_file_end(char *filename);
void read_file (char *filename);

#endif
