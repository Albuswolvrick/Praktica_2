/*
 * Pyramide.c
 * Reads a height (1-40) and prints a centered pyramid made of '*'.
 * Used by Menue.c (function pyramide_zeichnen) and runnable on its own.
 * Created by pierre on 03.11.26.
 */

#include <stdio.h>
#include <stdlib.h>   /* strtol */
#include <errno.h>    /* errno, ERANGE */
#include <limits.h>   /* INT_MIN, INT_MAX */
#include "Pyramide.h"

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

void pyramide_zeichnen(void)
{
    char eingabe[64];   /* buffer for one line of user input */
    int h = 0;          /* pyramid height; 0 means "no valid value yet" */
    int zeile;          /* current row, counted from 1 (top) to h (bottom) */
    int i;              /* loop counter for spaces and stars */

    /* keep asking until the user enters a valid height */
    do {
        printf("Hoehe (1-40): ");
        if (fgets(eingabe, sizeof(eingabe), stdin) == NULL) {
            return;     /* end of input (e.g. Ctrl+D) -> abort */
        }
        if (!parse_int(eingabe, &h) || h < 1 || h > 40) {
            printf("Ungueltig: Hoehe muss zwischen 1 und 40 liegen.\n");
            h = 0;      /* reset so the loop asks again */
        }
    } while (h == 0);

    /* print the pyramid row by row */
    for (zeile = 1; zeile <= h; zeile++) {
        /* leading spaces: fewer in every row, so the pyramid is centered */
        for (i = 0; i < h - zeile; i++) {
            putchar(' ');
        }
        /* stars: 1, 3, 5, ... -> row n has 2*n - 1 stars */
        for (i = 0; i < 2 * zeile - 1; i++) {
            putchar('*');
        }
        putchar('\n');   /* end of this row */
    }
}

/* main only exists when the file is compiled alone (not together with Menue.c) */
#ifndef AS_LIBRARY
int main(void)
{
    pyramide_zeichnen();
    return 0;
}
#endif