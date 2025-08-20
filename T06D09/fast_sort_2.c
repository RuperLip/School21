//Создайте программу src/fast_sort.c, которая сортирует массив из 10 целочисленных элементов по возрастанию,
//используя два разных алгоритма сортировки с теоретическими оценками вычислительной сложности не более nlog(n)
//(например, быстрая сортировка и пирамидальная сортировка). В первой строке стандартного вывода выведите массив,
//отсортированный первым алгоритмом; во второй строке – вторым. Использование stdlib.h или сторонних библиотек запрещено.
//Следуйте принципам структурного программирования. Передача массива в функцию только по указателю. В случае ошибок выведите «n/a»

/*
 *  Два алгоритма со сложностью ≤ n log n:
 *  1) Heapsort   – O(n log n)
 *  2) Merge sort – O(n log n)*/


 #include <stdio.h>

 #define N 10
 
 /* ---------- Heapsort ---------- */
 static void sift_down(int *a, int root, int bottom)
 {
     while (1) {
         int max = root;
         int left  = 2 * root + 1;
         int right = 2 * root + 2;
 
         if (left  <= bottom && a[left]  > a[max]) max = left;
         if (right <= bottom && a[right] > a[max]) max = right;
 
         if (max == root) break;
 
         int tmp   = a[root];
         a[root]   = a[max];
         a[max]    = tmp;
         root      = max;
     }
 }
 
 static void heapsort(int *a, int n)
 {
     /* построение кучи */
     for (int i = n / 2 - 1; i >= 0; --i)
         sift_down(a, i, n - 1);
 
     /* извлечение максимумов */
     for (int end = n - 1; end > 0; --end) {
         int tmp = a[0];
         a[0]    = a[end];
         a[end]  = tmp;
         sift_down(a, 0, end - 1);
     }
 }
 
 /* ---------- Merge sort ---------- */
 static void merge(int *a, int *tmp, int left, int mid, int right)
 {
     int i = left, j = mid, k = left;
     while (i < mid && j <= right) {
         if (a[i] <= a[j])
             tmp[k++] = a[i++];
         else
             tmp[k++] = a[j++];
     }
     while (i < mid)  tmp[k++] = a[i++];
     while (j <= right) tmp[k++] = a[j++];
     for (i = left; i <= right; ++i) a[i] = tmp[i];
 }
 
 static void merge_sort_rec(int *a, int *tmp, int left, int right)
 {
     if (left >= right) return;
     int mid = left + (right - left) / 2;
     merge_sort_rec(a, tmp, left, mid);
     merge_sort_rec(a, tmp, mid + 1, right);
     merge(a, tmp, left, mid + 1, right);
 }
 
 static void merge_sort(int *a, int n)
 {
     int tmp[N];
     merge_sort_rec(a, tmp, 0, n - 1);
 }
 
 /* ---------- чтение ---------- */
 static int read_array(int *a)
 {
     for (int i = 0; i < N; ++i)
         if (scanf("%d", &a[i]) != 1) return 1;
     return 0;
 }
 
 /* ---------- вывод ---------- */
 static void print_array(const int *a)
 {
     for (int i = 0; i < N; ++i) {
         printf("%d", a[i]);
         if (i != N - 1) putchar(' ');
     }
     putchar('\n');
 }
 
 /* ---------- main ---------- */
 int main(void)
 {
     int data1[N], data2[N];
 
     if (read_array(data1)) return 1;
     for (int i = 0; i < N; ++i) data2[i] = data1[i];
 
     heapsort(data1, N);
     merge_sort(data2, N);
 
     print_array(data1);   /* первая строка – Heapsort   */
     print_array(data2);   /* вторая строка – Merge sort */
     return 0;
 }