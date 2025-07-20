#include <stdio.h>
#include <stdlib.h>

// Функция для вычисления числа Фибоначчи
int fibonacci(int n) {
    if (n < 0) {
        return -1; // Ошибка: отрицательное значение
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n;

    // Запрос ввода числа
    printf("enter a number: ");
    if (scanf("%d", &n) != 1) {
        printf("n/a\n");
        return 1; // Ошибка ввода
    }

    // Вычисление числа Фибоначчи
    int result = fibonacci(n);
    if (result == -1) {
        printf("n/a\n"); // Ошибка: отрицательное значение
    } else {
        printf("%d\n", result);
    }

    return 0;
}