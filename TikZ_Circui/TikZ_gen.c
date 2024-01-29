/**
 * @file TikZ_gen.c
 * @author YinMo19 (YinMo19@proton.me)
 * @brief See in README.md
 * @version 0.1
 * @date 2024-01-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "TikZ_gen_func.h"


int main(int argc, char *argv[]) {
    kill_file("TikZ_Circuit.tex");

    // write the TikZ_head
    write_file_head("TikZ_Circuit.tex");

    // write the TikZ_body
    read_file("description.txt");

    // write the TikZ_end
    write_file_end("TikZ_Circuit.tex");
    return 0;
}
