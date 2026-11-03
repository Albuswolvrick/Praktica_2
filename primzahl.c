#include <stdio.h>   /* printf, fgets, stdin, getchar, putchar */
#include <stdlib.h>  /* strtol */
#include <string.h>  /* strcspn */
#include <errno.h>   /* errno, ERANGE */
#include <limits.h>  /* INT_MAX, INT_MIN */

/* Reads one line from stdin into puffer. Removes the '\n'.
   Returns 1 on success, 0 on end of input (EOF). */
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
        /* line was longer than the buffer: throw away the rest */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    return 1;
}

/* Converts text to int. Only one whole number (optional spaces around it)
   is accepted. Returns 1 if valid, otherwise 0. */
static int text_zu_int(const char *text, int *wert)
{
    char *ende;
    long v;

    errno = 0;
    v = strtol(text, &ende, 10);
    if (ende == text) {
        return 0;                       /* no digits at all */
    }
    if (errno == ERANGE || v > INT_MAX || v < INT_MIN) {
        return 0;                       /* number too big */
    }
    while (*ende == ' ' || *ende == '\t') {
        ende++;
    }
    if (*ende != '\0') {
        return 0;                       /* garbage after the number */
    }
    *wert = (int) v;
    return 1;
}

int main(void)
{
    char eingabe[64];
    int n, kandidat, teiler, ist_prim;

    printf("N eingeben: ");
    if (!lese_zeile(eingabe, sizeof(eingabe)) || !text_zu_int(eingabe, &n)) {
        printf("Ungueltige Eingabe\n");
        return 1;
    }

    for (kandidat = 2; kandidat <= n; kandidat++) {
        ist_prim = 1;
        /* teiler <= kandidat / teiler is the same as teiler*teiler <= kandidat
           but cannot overflow for large numbers */
        for (teiler = 2; teiler <= kandidat / teiler; teiler++) {
            if (kandidat % teiler == 0) {
                ist_prim = 0;
                break;
            }
        }
        if (ist_prim) {
            printf("%d ", kandidat);
        }
    }
    printf("\n");
    return 0;
}
