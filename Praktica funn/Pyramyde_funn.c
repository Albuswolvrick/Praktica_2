#include <stdio.h>

int main(void)
{
    static const int farben[] = {31, 33, 32, 36, 34, 35};
    char buf[64];
    int h = 0, stil = 0, zeilen, zeile, k, laenge, i;

    while (h == 0) {
        printf("Hoehe (1-40): ");
        if (fgets(buf, sizeof(buf), stdin) == NULL) return 1;
        if (sscanf(buf, "%d", &h) != 1 || h < 1 || h > 40) {
            printf("Ungueltig, bitte 1-40.\n");
            h = 0;
        }
    }
    while (stil == 0) {
        printf("Stil: 1) gefuellt  2) hohl  3) Raute: ");
        if (fgets(buf, sizeof(buf), stdin) == NULL) return 1;
        if (sscanf(buf, "%d", &stil) != 1 || stil < 1 || stil > 3) {
            printf("Ungueltige Auswahl\n");
            stil = 0;
        }
    }

    zeilen = (stil == 3) ? 2 * h - 1 : h;
    for (zeile = 1; zeile <= zeilen; zeile++) {
        k = (zeile <= h) ? zeile : 2 * h - zeile;   /* "level" of this row */
        laenge = 2 * k - 1;

        printf("\033[%dm", farben[(zeile - 1) % 6]);
        for (i = 0; i < h - k; i++) putchar(' ');
        for (i = 0; i < laenge; i++) {
            if (stil == 2 && k < h && i > 0 && i < laenge - 1) {
                putchar(' ');                        /* hollow inside */
            } else {
                putchar('*');
            }
        }
        printf("\033[0m\n");
    }
    return 0;
}
//
// Created by pierre on 03.11.26.
//