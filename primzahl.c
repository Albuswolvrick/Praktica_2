/*
 * primzahl.c
 * Reads a number N and prints all prime numbers from 2 to N.
 * Used by Menue.c (function primzahlen_ausgeben) and runnable on its own.
 * Created by pierre on 03.11.26.
 */

#include <stdio.h>
#include <stdlib.h>   /* strtol */
#include <errno.h>    /* errno, ERANGE */
#include <limits.h>   /* INT_MIN, INT_MAX */
#include "primzahl.h"

/*
 * Converts a text to an int (replacement for sscanf).
 * Returns 1 on success, 0 if the text is not exactly one valid integer.
 * Leading and trailing whitespace (e.g. the '\n' from fgets) is allowed.
 */
static int parse_int(const char *text, int *wert)
{
    char *ende;   /* first character strtol could not convert */
    long v;

    errno = 0;
    v = strtol(text, &ende, 10);

    if (ende == text) {                          /* no digits found */
        return 0;
    }
    if (errno == ERANGE || v < INT_MIN || v > INT_MAX) {   /* out of int range */
        return 0;
    }
    while (*ende == ' ' || *ende == '\t' || *ende == '\n' || *ende == '\r') {
        ende++;                                  /* skip trailing whitespace */
    }
    if (*ende != '\0') {                         /* extra characters after the number */
        return 0;
    }

    *wert = (int) v;
    return 1;
}

void primzahlen_ausgeben(void)
{
    char eingabe[64];   /* buffer for one line of user input */
    int n;              /* upper limit entered by the user */
    int kandidat;       /* number currently tested for primality */
    int teiler;         /* possible divisor of the candidate */
    int ist_prim;       /* flag: 1 = candidate is prime, 0 = it is not */

    printf("N eingeben: ");

    /* read a whole line safely (fgets cannot overflow the buffer) and convert it */
    if (fgets(eingabe, sizeof(eingabe), stdin) == NULL ||
        !parse_int(eingabe, &n)) {
        printf("Ungueltige Eingabe\n");
        return;
    }

    /* test every number from 2 up to n */
    for (kandidat = 2; kandidat <= n; kandidat++) {
        ist_prim = 1;   /* assume prime until a divisor is found */

        /* trial division: divisors only need to be checked up to sqrt(kandidat) */
        for (teiler = 2; teiler * teiler <= kandidat; teiler++) {
            if (kandidat % teiler == 0) {   /* divides evenly -> not prime */
                ist_prim = 0;
                break;
            }
        }

        if (ist_prim) {
            printf("%d ", kandidat);
        }
    }
    printf("\n");
}

/* main only exists when the file is compiled alone (not together with Menue.c) */
#ifndef AS_LIBRARY
int main(void)
{
    primzahlen_ausgeben();
    return 0;
}
#endif