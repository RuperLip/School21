/*
Создать программу, которая принимает число n, массив Aцелых nчисел и число c, на которое все элементы массива должны сдвинуться влево.
Если значение cотрицательное, сдвиг массива должен быть выполнен вправо. На выходе ожидается изменённый массив.
Придерживайтесь рекомендуемой декомпозиции, как в предыдущих заданиях. Использование stdlib.h запрещено.
Передача массива в функцию только по указателю. Максимальный размер входного массива — 10. В случае ошибок выводить «n/a». ==

Вход	                           Выход
10
4 3 9 0 1 2 0 2 7 -1
2	                               9 0 1 2 0 2 7 -1 4 3
*/

/*
 *  gcc -std=c11 -Wall -Wextra -pedantic shift_array.c -o shift_array
 *  echo "5 1 2 3 4 5 2" | ./shift_array
 *  Ввод: n  a1 … an  c
 */

 #include <stdio.h>

 #define NMAX 10
 
 /* читает длину, массив и величину сдвига; возвращает 0 при успехе */
 int read_input(int *n, int *arr, int *shift)
 {
     if (scanf("%d", n) != 1 || *n <= 0 || *n > NMAX)
         return 1;
     for (int i = 0; i < *n; ++i)
         if (scanf("%d", &arr[i]) != 1)
             return 1;
     if (scanf("%d", shift) != 1)
         return 1;
     return 0;
 }
 
 /* выполняет циклический сдвиг вправо (если shift<0) или влево (shift>0) */
 void cyclic_shift(int *arr, int n, int shift)
 {
     if (n == 0) return;
     shift %= n;
     if (shift < 0) shift += n;   /* теперь сдвиг всегда ≥0, вправо */
     if (shift == 0) return;
 
     /* тройное реверсирование = циклический сдвиг без доп. памяти */
     /* 1. реверс всего массива */
     for (int i = 0, j = n - 1; i < j; ++i, --j) {
         int tmp = arr[i];
         arr[i] = arr[j];
         arr[j] = tmp;
     }
     /* 2. реверс первых shift элементов */
     for (int i = 0, j = shift - 1; i < j; ++i, --j) {
         int tmp = arr[i];
         arr[i] = arr[j];
         arr[j] = tmp;
     }
     /* 3. реверс остальных n-shift элементов */
     for (int i = shift, j = n - 1; i < j; ++i, --j) {
         int tmp = arr[i];
         arr[i] = arr[j];
         arr[j] = tmp;
     }
 }
 
 /* печать массива через пробел */
 void print_array(const int *arr, int n)
 {
     for (int i = 0; i < n; ++i) {
         printf("%d", arr[i]);
         if (i != n - 1) putchar(' ');
     }
     putchar('\n');
 }
 
 int main(void)
 {
     int n, arr[NMAX], shift;
 
     if (read_input(&n, arr, &shift)) {
         puts("n/a");
         return 1;
     }
 
     cyclic_shift(arr, n, shift);
     print_array(arr, n);
 
     return 0;
 } 