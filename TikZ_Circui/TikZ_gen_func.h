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
typedef struct point {
    int x, y;
} point;

typedef struct circuit {
    int   start;
    char  name[10];
    char  direction;
    char  description[100];
    char  desc_dir;
    int   status;
    char  line_shape[4];
    point address;
    int   end;
} circuit;

// define a tree to calc the distance
typedef struct tree {
    struct tree *next[10];
    int          status;
    int          branch;
} tree;

// Global variables
extern circuit circuits[100];

_Noreturn void panic(char *msg);
void           kill_file(char *filename);
void           write_file_head(char *filename);
void           write_file_end(char *filename);
void           read_file(char *filename);
void           calc_address(tree *root);
void           calc_address_end(tree *root);
void           print_content(char *filename);
void           determine_tree_structure(tree *root, int status);

#endif
