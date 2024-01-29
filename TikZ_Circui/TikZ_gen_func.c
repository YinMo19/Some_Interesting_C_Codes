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
#include <stdio.h>

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
                "	\\draw[color=black, thick]\n");
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
                "\\end{document}\n;");
    fclose(fp);
}

