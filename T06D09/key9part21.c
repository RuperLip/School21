//НЕ РАБОТАЕТ...

/*
 *  gcc -std=c11 -Wall -Wextra -pedantic big_calc.c -o big_calc
 *  echo "3 1 2 3 2 9 8" | ./big_calc
 *  Ввод: длина1 цифры1...  длина2 цифры2...
 *  Пример выше: 123 + 98 = 221, 123 - 98 = 25
 */

/*Измените программу src/key9part2.c так, чтобы она возвращала результат сложения и вычитания двух очень больших чисел,
переданных программе на вход в виде массивов. Максимальная длина числа: 100 элементов типа int. Вводимые целые числа
являются десятичными. Если вычитаемое больше уменьшаемого, вместо разности должно быть выведено «n/a».
Придерживайтесь разложения, как в предыдущих заданиях. Использование stdlib.h запрещено.
Передача массива в функцию только по указателю. В случае ошибок выводите «n/a». ==

Вход	                                            Выход
1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 6 1
2 9	                                                1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 9 0
                                                    1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 3 2
0 1 0
0 0 1	                                            1 1
                                                    9
*/

 #include <stdio.h>

 #define MAXN 100          /* максимальное количество десятичных цифр */
 
 /* ---------- чтение одного большого числа ---------- */
 static int read_big(int *digits, int *len)
 {
     if (scanf("%d", len) != 1 || *len <= 0 || *len > MAXN)
         return 1;
 
     for (int i = 0; i < *len; ++i) {
         if (scanf("%1d", &digits[i]) != 1)   /* читаем ровно одну цифру */
             return 1;
     }
     return 0;
 }
 
 /* ---------- сложение: a + b = res ---------- */
 static void add(const int *a, int alen,
                 const int *b, int blen,
                 int *res, int *rlen)
 {
     int carry = 0, k = 0;
     int i = alen - 1, j = blen - 1;
 
     while (i >= 0 || j >= 0 || carry) {
         int da = (i >= 0) ? a[i--] : 0;
         int db = (j >= 0) ? b[j--] : 0;
         int sum = da + db + carry;
         res[k++] = sum % 10;
         carry    = sum / 10;
     }
     *rlen = k;
 }
 
 /* ---------- вычитание: a - b = res ---------- */
 /* возвращает 0 – успех, 1 – b > a */
 static int sub(const int *a, int alen,
                const int *b, int blen,
                int *res, int *rlen)
 {
     if (blen > alen) return 1;
     if (blen == alen) {
         for (int i = 0; i < alen; ++i) {
             if (a[i] < b[i]) return 1;
             if (a[i] > b[i]) break;
         }
     }
 
     int borrow = 0, k = 0;
     int i = alen - 1, j = blen - 1;
 
     while (i >= 0) {
         int da = a[i--];
         int db = (j >= 0) ? b[j--] : 0;
         int diff = da - db - borrow;
         if (diff < 0) {
             diff += 10;
             borrow = 1;
         } else {
             borrow = 0;
         }
         res[k++] = diff;
     }
     /* убираем ведущие нули */
     while (k > 1 && res[k - 1] == 0) --k;
     *rlen = k;
     return 0;
 }
 
 /* ---------- печать цифр в прямом порядке ---------- */
 static void print_big(const int *digits, int len)
 {
     if (len == 0) { puts("0"); return; }
     for (int i = len - 1; i >= 0; --i)
         printf("%d", digits[i]);
 }
 
 int main(void)
 {
     int a[MAXN], b[MAXN], sum[MAXN + 1], diff[MAXN];
     int alen, blen, sumlen, difflen;
 
     if (read_big(a, &alen) || read_big(b, &blen)) {
         puts("n/a");
         return 1;
     }
 
     add(a, alen, b, blen, sum, &sumlen);
     print_big(sum, sumlen);
     putchar(' ');
 
     if (sub(a, alen, b, blen, diff, &difflen))
         printf("n/a");
     else
         print_big(diff, difflen);
 
     putchar('\n');
     return 0;
 }
 
 
 
 
 
 
 
 