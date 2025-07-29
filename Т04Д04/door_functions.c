#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846
#define N  42          /* число точек */

/* ---------- реализации кривых ---------- */
static double agnesi(double x)
{
    return pow(1.0, 3)/(pow(1.0, 2) + pow(x,2));
}

static double bernoulli(double x)
{
    double z = sqrt((pow(1,4)) + (4* (pow(x,2)) * (pow(1,2))));
    
    double rezult = sqrt(z - (pow(x,2) - (pow(1,2))));

    if (rezult < 0.0)
    return NAN;

    return rezult;
}

static double hyperbola(double x)
{
    return 1.0 / pow(x, 2);
}

/* ---------- печать таблицы ---------- */
int main(void)
{
    const double dx = 2.0 * PI / (N - 1);   /* шаг по X */
    double x;

    /* заголовок */
    printf("       x |   Agnesi | Bernoulli | Hyperbola\n");
    printf("---------+----------+-----------+-----------\n");

    for (int i = 0; i < N; ++i) {
        x = -PI + i * dx;

        /* обрабатываем особенность 1/x в нуле */
        if (fabs(x) < 1e-12)
            printf("%8.7f | %8.7f | %9.7f |       inf\n",
                   x, agnesi(x), bernoulli(x));
             else 
            printf("%8.7f | %8.7f | %9.7f | %9.7f\n",
                   x, agnesi(x), bernoulli(x), hyperbola(x));
            
    }

    return 0;
}