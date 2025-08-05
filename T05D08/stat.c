//Добавьте реализации необходимых функций в программу src/stat.c, чтобы она компилировалась и работала корректно
//(получала массив целых чисел через stdin, отображала его, вычисляла и выводила на новой строке набор статистических метрик –
//максимумы и минимумы, математическое ожидание и дисперсию, предполагая, что мы имеем дело с дискретным равномерным распределением).
//В случае некорректного ввода необходимо вывести n/a. Уменьшение разложения не допускается – можно добавлять функции при необходимости,
//но нельзя их удалять. Придерживайтесь рекомендуемой структуры программы. Выводите числа с плавающей точкой с точностью до 6 знаков после запятой. ==

//Вход	        Выход
//4            1 2 3 4
//1 2 3 4	   4 1 2.500000 1.250000

//Расчёт дисперсии для выборки из шести элементов (например, оценок группы с дополнительных занятий: [5, 2, 3, 5, 4, 5]):
//Найти среднее арифметическое: (5 + 2 + 3 + 5 + 4 + 5) / 6 = 24 / 6 = 4.
//Найти квадраты отклонения от среднего: (5 – 4)² = 1, (2 – 4)² = 4, (3 – 4)² = 1, (5 – 4)² = 1, (4 – 4)² = 0, (5 – 4)² = 1.
//Сложить получившиеся квадраты: 1 + 4 + 1 + 1 + 0 + 1 = 8.
//Разделить сумму на количество элементов: 8 / 6 = 1,33 — это и есть дисперсия.

//Математическое ожидание: сумма всех элементов массива, поделенная на их количество

#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    if (input(data, &n)) {
        printf("n/a");
        return 1;
    }
    output(data, n);
    output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));

    return 0;
}

int input(int *a, int *n) {
    if ((scanf("%d", n) != 1) || (*n <= 0) || (*n > NMAX)) {
        return 1;
    } else {
        char c;
        for (int *p = a; p - a < *n; p++) {
            if ((scanf("%d%c", p, &c) != 1) && (c != ' ' && c != '\n')) {
                return 1;
            }
        }
    }
    return 0;
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        printf("%d", *p);
        if (p - a != n - 1) {
            printf(" ");
        }
    }
}

int max(int *a, int n) {
    int max = *a;
    for (int *p = a; p - a < n; p++) {
        if (*p > max) {
            max = *p;
        }
    }
    return max;
}

int min(int *a, int n) {
    int min = *a;
    for (int *p = a; p - a < n; p++) {
        if (*p < min) {
            min = *p;
        }
    }
    return min;
}

double mean(int *a, int n) {                               //double mean(int *a, int n)
                                                           //Цель – найти среднее арифметическое (математическое ожидание дискретной равномерной случайной величины).
                                                           //probability = 1.0 / n – вес одного элемента.
                                                        //Цикл по указателю p от a до a+n-1.
                                                         //Каждое значение *p умножается на probability и добавляется к аккумулятору mean.
                                                         //В результате mean = (1/n) * Σ a[i] – классическое среднее.
    double mean = 0;
    double probability = 1 / (double)n;
    for (int *p = a; p - a < n; p++) {
        mean += (double)*p * probability;
    }
    return mean;
}

double variance(int *a, int n) {                                     //Цель – найти дисперсию по формуле
                                                                     //Var(X) = E[X²] – (E[X])².
                                                                     //Одним проходом считаются сразу два аккумулятора:
                                                                     //– mean = Σ a[i]·(1/n) → E[X]
                                                                     //– square_mean = Σ a[i]²·(1/n) → E[X²]
                                                                     //После цикла дисперсия получается как square_mean – mean².
                                                                     //Это эквивалентно формуле Σ (a[i] – mean)² / n (несмещённая оценка при делении на n, а не n-1).
    double mean = 0, square_mean = 0, variance = 0;
    double probability = 1 / (double)n;
    for (int *p = a; p - a < n; p++) {
        mean += (double)*p * probability;
        square_mean += (double)(*p * *p) * probability;
    }
    variance = square_mean - mean * mean;
    return variance;
}

//mean возвращает среднее значение.
//variance возвращает дисперсию (с делением на n).

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("\n%d %d %.6f %.6f", max_v, min_v, mean_v, variance_v);
}
