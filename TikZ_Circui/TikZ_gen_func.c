/**
 * @file TikZ_gen_func.c
 * @author YinMo19 (YinMo19@proton.me)
 * @brief functions in TikZ-generator
 * @version 1.0
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
 * @details This function is aimed to read the description.txt and
 *          get the information by special format
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

            // if is_multi or the start point is_multi,
            // it needs to input an anchor.
            if (circuits[status].is_multi ||
                circuits[circuits[status].start].is_multi) {
                fscanf(fp, "%s%*c", circuits[status].anchor);
                if (circuits[status].is_multi &&
                    circuits[circuits[status].start].is_multi) {
                    fscanf(fp, "%s%*c", circuits[status].next_anchor);
                }
            }

            // the tri-state point' input should be different
            if (circuits[status].is_multi) {
                fscanf(fp, "%*c%[^}]%*c", circuits[status].description);
            } else {

                // the normal input
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
 * @brief get the direction int for getting dir array
 *
 * @param direction
 * @return int
 */
int dirt(char direction) {
    for (int i = 0; i < 4; i++) {
        if (dir[i] == direction) {
            return i;
        }
    }
    return -1;
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

    // set the start point
    fprintf(fp, "\t(0,0) coordinate (0)\n");

    // set the status counter
    int status_cnt = 1;
    while (status_cnt < line_cnt - 1) {
        // if is ground
        if (strcmp(circuits[status_cnt].name, "gnd") == 0) {
            fprintf(fp, "\t(%d) node[ground]{}\n",
                    circuits[circuits[status_cnt].start].status);
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
        } else if (strcmp(circuits[status_cnt].name, "opa") == 0) {
            strcpy(name, "op amp");
        } else if (strcmp(circuits[status_cnt].name, "line") == 0) {
            strcpy(name, "short");
        } else {
            strcpy(name, circuits[status_cnt].name);
        }

        if (circuits[status_cnt].is_multi &&
            circuits[circuits[status_cnt].start].is_multi) {
            fprintf(fp,
                    "\t(%s.%s) node[%s, noinv input up, "
                    "anchor=%s](%s){\\texttt{%s}}\n",
                    circuits[circuits[status_cnt].start].description,
                    circuits[status_cnt].anchor, name,
                    circuits[status_cnt].next_anchor,
                    circuits[status_cnt].description,
                    circuits[status_cnt].description);
        } else if (circuits[status_cnt].is_multi) {
            fprintf(fp,
                    "\t(%d) node[%s, noinv input up, "
                    "anchor=%s](%s){\\texttt{%s}}\n",
                    circuits[circuits[status_cnt].start].status, name,
                    circuits[status_cnt].anchor,
                    circuits[status_cnt].description,
                    circuits[status_cnt].description);
        } else if (circuits[circuits[status_cnt].start].is_multi) {
            fprintf(fp, "\t(%s.%s) to[%s,%s] ++ (%d,%d) coordinate(%d)\n",
                    circuits[circuits[status_cnt].start].description,
                    circuits[status_cnt].anchor,
                    name,
                    circuits[status_cnt].line_shape,
                    dx[dirt(circuits[status_cnt].direction)],
                    dy[dirt(circuits[status_cnt].direction)],
                    circuits[status_cnt].status);
        } else if (circuits[status_cnt].end != 0) {
            fprintf(fp, "\t(%d) to [%s, %s %s] (%d)\n",
                    circuits[circuits[status_cnt].start].status, name, tmp,
                    circuits[status_cnt].line_shape,
                    circuits[circuits[status_cnt].end].status);
        } else {
            fprintf(fp, "\t(%d) to [%s, %s %s] ++ (%d,%d) coordinate (%d)\n",
                    circuits[circuits[status_cnt].start].status, name, tmp,
                    circuits[status_cnt].line_shape,
                    dx[dirt(circuits[status_cnt].direction)],
                    dy[dirt(circuits[status_cnt].direction)],
                    circuits[status_cnt].status);
        }
        status_cnt++;
    }

    fclose(fp);
}