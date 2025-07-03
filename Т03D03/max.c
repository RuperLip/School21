#include <stdio.h>

int couple (int a, int b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

int main(void)
{
        int a, b;
        char c;
    
        if (scanf("%d%d%c", &a, &b, &c) != 2 && (c != '\n')) {
            printf("n/a\n");
        } else {
            printf ("%d\n", couple(a,b));
        }
    return 0;
}