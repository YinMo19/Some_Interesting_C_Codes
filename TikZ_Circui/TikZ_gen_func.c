/**
 * @file TikZ_gen_func.c
 * @author YinMo19 (YinMo19@proton.me)
 * @brief functions in TikZ-generator
 * @version 0.1
 * @date 2024-01-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "TikZ_gen_func.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// define a movement and a direction array
static int  dx[4]    = {0, 1, 0, -1};
static int  dy[4]    = {1, 0, -1, 0};
static char dir[4]   = {'u', 'r', 'd', 'l'};
static int  line_cnt = 0;

/**
 * @brief raise a error
 *
 * @param msg error message
 * @return _Noreturn
 */
_Noreturn void panic(char *msg) {
    fprintf(stderr, "panic: %s\n", msg);
    exit(1);
}

/**
 * @brief kill the file content
 *
 * @param filename
 */
void kill_file(char *filename) {
    FILE *fp = fopen(filename, "w");
    fclose(fp);
}

/**
 * @brief write the TikZ_head,such as "documentclass" etc.
 *
 * @param filename
 */
void write_file_head(char *filename) {
    FILE *fp = fopen(filename, "a+");
    fprintf(fp, "\\documentclass[margin=10pt]{standalone}\n"
                "\\usepackage[siunitx]{circuitikz}\n"
                "\\begin{document}\n"
                "\\begin{tikzpicture}[scale=2]\n"
                "	\\draw[color=black]\n");
    // if you think it's not so thick,uncomment this
    //  and comment the upper line
    // "	\\draw[color=black,thick]\n");
    fclose(fp);
}

/**
 * @brief write the TikZ_end
 *
 * @param filename
 */
void write_file_end(char *filename) {
    FILE *fp = fopen(filename, "a+");
    fprintf(fp, "    ;\n"
                "\\end{tikzpicture}\n"
                "\\end{document}\n");
    fclose(fp);
}

/**
 * @brief read the descriptions and write the curcuit array
 *
 * @param filename
 */
void read_file(char *filename) {
    FILE *fp = fopen(filename, "r");

    // do some error checking
    if (fp == NULL) {
        panic("Can't open file.Do you forgot something?");
    }

    // line count
    int status = 1;

    // when not the end of the file
    while (!feof(fp)) {
        do {

            // read the data by special format
            fscanf(fp, "%d%*c", &circuits[status].start);
            fscanf(fp, "%s%*c", circuits[status].name);

            // if is ground or tri-state
            if (strcmp(circuits[status].name, "gnd") == 0) {
                break;
            } else if (strcmp(circuits[status].name, "opa") == 0) {
                circuits[status].is_multi = true;
            }

            if (circuits[status].is_multi ||) {
                fscanf(fp, "%s", circuits[status].anchor);
            }

            fscanf(fp, "%c%*c", &circuits[status].direction);
            fscanf(fp, "%s", circuits[status].line_shape);

            char tmp = (char) fgetc(fp);
            if (tmp == '\n') {
                break;
            }

            // the part can be chosen
            tmp = (char) fgetc(fp);
            if (tmp == '[') {
                fscanf(fp, "%d%*c", &circuits[status].end);
                tmp = (char) fgetc(fp);
                if (tmp == '\n') {
                    break;
                } else if (tmp == ' ') {
                    tmp = (char) fgetc(fp);
                }
            }
            if (tmp == '{') {
                fscanf(fp, "%[^}]%*c", circuits[status].description);
                tmp = (char) fgetc(fp);
                if (tmp == '\n') {
                    break;
                }
                if (tmp == ' ') {
                    fscanf(fp, "%*c%c%*c", &circuits[status].desc_dir);
                }
            }
        } while (0);

        // set the status
        circuits[status].status = status;
        status++;
    }

    line_cnt = status;
    fclose(fp);
}

/**
 * @brief calculate the address by tree structure
 *
 * @param circuits
 */
void calc_address(tree *root) {

    // calculate the address
    int branch_cnt = 0;
    while (branch_cnt < root->branch) {
        for (int i = 0; i < 4; i++) {
            if (circuits[root->next[branch_cnt]->status].direction == dir[i]) {
                circuits[root->next[branch_cnt]->status].address.x =
                    circuits[root->status].address.x + dx[i];
                circuits[root->next[branch_cnt]->status].address.y =
                    circuits[root->status].address.y + dy[i];
            }
        }

        // calc the next branch
        calc_address(root->next[branch_cnt]);
        branch_cnt++;
    }
}

/**
 * @brief calc the ones which have end
 *
 * @param root
 */
void calc_address_end(tree *root) {

    int branch_cnt = 0;
    while (branch_cnt < root->branch) {
        if (circuits[root->next[branch_cnt]->status].end != 0) {
            circuits[root->next[branch_cnt]->status].address.x =
                circuits[circuits[root->next[branch_cnt]->status].end]
                    .address.x;
            circuits[root->next[branch_cnt]->status].address.y =
                circuits[circuits[root->next[branch_cnt]->status].end]
                    .address.y;
        }

        // calc the next branch
        calc_address_end(root->next[branch_cnt]);
        branch_cnt++;
    }
}

/**
 * @brief determine the tree structure
 *
 * @param root
 */
void determine_tree_structure(tree *root, int status) {

    // do some error checking
    if (root == NULL) {
        panic("root is NULL");
    }

    // set the root status
    root->status = circuits[status].status;

    // determine the next branch
    int branch_cnt = 0;
    for (int i = 0; i < line_cnt; i++) {

        // skip when root is counting
        if (i == root->status) {
            continue;
        }

        // search the next branch
        if (circuits[i].start == root->status) {
            root->next[branch_cnt] = (tree *) malloc(sizeof(tree));
            determine_tree_structure(root->next[branch_cnt], i);
            branch_cnt++;
        }
    }

    // set the branch number
    root->branch = branch_cnt;
}

/**
 * @brief print the content of the circuit
 *
 */
void print_content(char *filename) {
    FILE *fp = fopen(filename, "a+");

    // do some error checking
    if (fp == NULL) {
        panic("Can't open file.");
    }

    // set the status counter
    int status_cnt = 1;
    while (status_cnt < line_cnt - 1) {
        // if is ground
        if (strcmp(circuits[status_cnt].name, "gnd") == 0) {
            fprintf(fp, "\t(%d,%d) node[ground]{}\n",
                    circuits[circuits[status_cnt].start].address.x,
                    circuits[circuits[status_cnt].start].address.y);
            status_cnt++;
            continue;
        }

        // if is line
        if (strcmp(circuits[status_cnt].name, "line") == 0) {
            fprintf(fp, "\t(%d,%d) to [short,%s] (%d,%d)\n",
                    circuits[circuits[status_cnt].start].address.x,
                    circuits[circuits[status_cnt].start].address.y,
                    circuits[status_cnt].line_shape,
                    circuits[status_cnt].address.x,
                    circuits[status_cnt].address.y);
            status_cnt++;
            continue;
        }

        // standard output
        char tmp[100] = {0};
        if (strcmp(circuits[status_cnt].description, "\0") != 0) {
            strcpy(tmp, "l");
            if (circuits[status_cnt].desc_dir == '_') {
                strcat(tmp, "_");
            }
            strcat(tmp, "=$");
            strcat(tmp, circuits[status_cnt].description);
            strcat(tmp, "$,");
        }

        // Judge the name,and replace it.
        char name[100] = {0};
        if (strcmp(circuits[status_cnt].name, "bat") == 0) {
            strcpy(name, "battery2");
        } else if (strcmp(circuits[status_cnt].name, "iso") == 0) {
            strcpy(name, "isource");
        } else if (strcmp(circuits[status_cnt].name, "pbu") == 0) {
            strcpy(name, "push button");
        } else if (strcmp(circuits[status_cnt].name, "fld") == 0) {
            strcpy(name, "full led");
        } else {
            strcpy(name, circuits[status_cnt].name);
        }

        fprintf(fp, "\t(%d,%d) to [%s, %s %s] (%d,%d)\n",
                circuits[circuits[status_cnt].start].address.x,
                circuits[circuits[status_cnt].start].address.y, name, tmp,
                circuits[status_cnt].line_shape, circuits[status_cnt].address.x,
                circuits[status_cnt].address.y);
        status_cnt++;
    }

    fclose(fp);
}