#include <stdio.h>

int main(void)
{
    char eingabe[64];
    int h = 0, zeile, i;

    do {
        printf("Hoehe (1-40): ");
        if (fgets(eingabe, sizeof(eingabe), stdin) == NULL) {
            return 1;
        }
        if (sscanf(eingabe, "%d", &h) != 1 || h < 1 || h > 40) {
            printf("Ungueltig: Hoehe muss zwischen 1 und 40 liegen.\n");
            h = 0;
        }
    } while (h == 0);

    for (zeile = 1; zeile <= h; zeile++) {
        for (i = 0; i < h - zeile; i++) {        /* spaces */
            putchar(' ');
        }
        for (i = 0; i < 2 * zeile - 1; i++) {    /* stars */
            putchar('*');
        }
        putchar('\n');
    }
    return 0;
}
//
// Created by pierre on 03.11.26.
//