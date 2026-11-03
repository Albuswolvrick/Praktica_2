#include <stdio.h>   /* printf, fgets, stdin, getchar, putchar */
#include <stdlib.h>  /* strtol */
#include <string.h>  /* strcspn */
#include <errno.h>   /* errno, ERANGE */
#include <limits.h>  /* INT_MAX, INT_MIN */

static int lese_zeile(char *puffer, size_t groesse)
{
    size_t laenge;
    int c;

    if (fgets(puffer, (int) groesse, stdin) == NULL) {
        return 0;
    }
    laenge = strcspn(puffer, "\n");
    if (puffer[laenge] == '\n') {
        puffer[laenge] = '\0';
    } else {
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    return 1;
}

static int text_zu_int(const char *text, int *wert)
{
    char *ende;
    long v;

    errno = 0;
    v = strtol(text, &ende, 10);
    if (ende == text) {
        return 0;
    }
    if (errno == ERANGE || v > INT_MAX || v < INT_MIN) {
        return 0;
    }
    while (*ende == ' ' || *ende == '\t') {
        ende++;
    }
    if (*ende != '\0') {
        return 0;
    }
    *wert = (int) v;
    return 1;
}

int main(void)
{
    char eingabe[64];
    int h = 0, zeile, i;

    do {
        printf("Hoehe (1-40): ");
        if (!lese_zeile(eingabe, sizeof(eingabe))) {
            return 1;
        }
        if (!text_zu_int(eingabe, &h) || h < 1 || h > 40) {
            printf("Ungueltig: Hoehe muss zwischen 1 und 40 liegen.\n");
            h = 0;
        }
    } while (h == 0);

    for (zeile = 1; zeile <= h; zeile++) {
        for (i = 0; i < h - zeile; i++) {      /* spaces */
            putchar(' ');
        }
        for (i = 0; i < 2 * zeile - 1; i++) {  /* stars */
            putchar('*');
        }
        putchar('\n');
    }
    return 0;
}
