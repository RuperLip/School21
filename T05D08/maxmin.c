//Внесите исправления в программу src/maxmin.c, чтобы она компилировалась и работала корректно
//(находила максимальное и минимальное значения из трёх целых чисел и выводила их на экран).
//Не изменяйте структуру программы. В случае некорректного ввода необходимо вывести n/a. ==

//Вход	   Выход
//1 2 3	     3 1

#include <stdio.h>


void maxmin(int prob1, int prob2, int prob3, int *max, int *min);

/* Find a max & min probabilities */
int main()
{
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);

    int max, min;

    maxmin(x, y, z, &max, &min);

    printf("%d %d", max, min);

    return 0;
}


/* This function should be kept !!! (Your AI) */
/* But errors & bugs should be fixed         */
void maxmin(int prob1, int prob2, int prob3, int *max, int *min)
{
    *max = *min = prob1;
    
    if(prob2 > *max)
        *max = prob2;
    if(prob2 < *min)
        *min = prob2;
    
    if(prob3 > *max)
        *max = prob3;
    if(prob3 < *min)
        *min = prob3;    
}
