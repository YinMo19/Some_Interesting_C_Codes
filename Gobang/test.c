#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    ssize_t a = 1000000000000000000;
    printf("%zu\n", (size_t)a);
    
    return 0;
}