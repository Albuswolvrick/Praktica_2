#include <stdio.h>

#define MAX 10000000

static char zusammengesetzt[MAX + 1];

int main(void)
{
    char eingabe[64];
    int n, i, j, anzahl = 0;

    printf("N eingeben (2-%d): ", MAX);
    if (fgets(eingabe, sizeof(eingabe), stdin) == NULL ||
        sscanf(eingabe, "%d", &n) != 1 || n < 2 || n > MAX) {
        printf("Ungueltige Eingabe\n");
        return 1;
        }

    for (i = 2; i <= n / i; i++) {
        if (!zusammengesetzt[i]) {
            for (j = i * i; j <= n; j += i) {
                zusammengesetzt[j] = 1;
            }
        }
    }

    for (i = 2; i <= n; i++) {
        if (!zusammengesetzt[i]) {
            printf("%d%c", i, (++anzahl % 10 == 0) ? '\n' : ' ');
        }
    }
    printf("\n%d Primzahlen bis %d\n", anzahl, n);
    return 0;
}
//
// Created by pierre on 03.11.26.
//