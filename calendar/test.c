#include <stdbool.h>
#include <stdio.h>

int main() {
    int a = 0;

    do {
        printf("Enter a number: ");
        if (scanf("%d", &a) != 1) scanf("%*[^\n]");// clear the buffer
    } while (a < 0);

    char ch  = 0;
    scanf("%c", &ch);
    printf("%c", ch);
    printf("%d", a);
    return 0;
}