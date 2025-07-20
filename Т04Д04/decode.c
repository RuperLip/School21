#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encode(void) {
    int c;                       /* int, а не char, чтобы корректно ловить EOF */
    int first = 1;               /* флаг «первый символ» — чтобы не ставить лишний пробел перед первым кодом */

    while ((c = getchar()) != EOF && (c == '\n' || c == '\r'));

do {
    if (!first && c != EOF)
        putchar(' ');
    if (c != EOF) {
        printf("%02x", c);
        first = 0;
    }
} while ((c = getchar()) != EOF);
}

   void decode(void) {
    char hex[3]; // для хранения двух символов и завершающего нуля
    while (scanf("%2s", hex) == 1) {
        // Преобразуем шеснадцатеричное значение в символ
        char *endptr;
        long int value = strtol(hex, &endptr, 16);
        if (*endptr != '\0') {
            printf("n/a\n");
            return;
        }
        if (value < 0 || value > 255) {
            printf("n/a\n");
            return;
        }
        putchar((char)value);
        putchar(' '); // выводим пробел после символа
    }
}

        int main(void) {
            char mode[16];                 // буфер под строку
            if (scanf("%15s", mode) != 1)  // читаем не более 15 символов + '\0'
                return 0;
        
            if (strcmp(mode, "0") == 0) {
                encode();
            } else if (strcmp(mode, "1") == 0) {
                decode();
            }
            return 0;
        }