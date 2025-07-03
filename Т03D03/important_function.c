#include <stdio.h>
#include <math.h>

int main(void)
{
    float x;
    char c;
    if (scanf("%f%c", &x, &c) != 1 && (c != '\n')){
        printf("n/a\n");
    } else {
    float y = 7e-3 * pow(x, 4) + ((22.8 * pow(x, 1/3) - 1e3) * x + 3) / (x * x/2) - x * pow((10+x), (2/x)) - 1.01;
    printf("%.1f", y);
    }
    return 0;
}