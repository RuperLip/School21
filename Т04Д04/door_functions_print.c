#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846
#define N  42          /* число точек */
#define H   21          /* строк (отсчётов) по Y */

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
static void print_table(void)
{
    const double dx = 2.0 * PI / (N - 1);
    printf("x        |   Agnesi | Bernoulli | Hyperbola\n");
    printf("---------+----------+-----------+-----------\n");
    for (int i = 0; i < N; ++i) {
        double x = -PI + i * dx;
        printf("%8.5f | %8.5f | ", x, agnesi(x));

        double yb = bernoulli(x);
        if (isnan(yb))
            printf("    -     | ");
        else
            printf("%9.5f | ", yb);

        if (isinf(hyperbola(x)))
            printf("       inf\n");
        else
            printf("%9.5f\n", hyperbola(x));
    }
}

/* ---------- рисование графиков ---------- */
static void draw_plots(void)
{
    const double x0 = -PI, x1 = PI;
    const double y0 = -1.0, y1 = 1.0;   /* вертикальный диапазон 21 строка */

    /* массивы значений */
    double ag[N], be[N], hy[N];
    const double dx = (x1 - x0) / (N - 1);

    for (int i = 0; i < N; ++i) {
        double x = x0 + i * dx;
        ag[i] = agnesi(x);
        be[i] = isnan(bernoulli(x)) ? NAN : bernoulli(x);
        hy[i] = isinf(hyperbola(x)) ? NAN : hyperbola(x);
    }

    /* нарисуем три графика подряд */
    const char *names[3] = { "Agnesi", "Bernoulli", "Hyperbola" };
    const double *curves[3] = { ag, be, hy };

    for (int g = 0; g < 3; ++g) {
        printf("\n%s:\n", names[g]);
        for (int row = 0; row < H; ++row) {
            double y = y1 - row * (y1 - y0) / (H - 1); /* сверху вниз */
            for (int col = 0; col < N; ++col) {
                double val = curves[g][col];
                if (isnan(val)) {
                    putchar(' ');
                    continue;
                }
                /* попадает ли значение в строку row? */
                if (fabs(val - y) < (y1 - y0) / (H - 1) / 2.0)
                    putchar('*');
                else
                    putchar(' ');
            }
            putchar('\n');
        }
    }
}

/* ---------- main ---------- */
int main(void)
{
    print_table();
    draw_plots();
    return 0;
}