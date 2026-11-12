/*
 * Menue.c
 * Main menu that starts the other programs of this project:
 *   1) number guessing game   -> Ratten.c    (ratespiel)
 *   2) prime number output    -> primzahl.c  (primzahlen_ausgeben)
 *   3) pyramid                -> Pyramide.c  (pyramide_zeichnen)
 *   4) quit
 *
 * Build (all files together, AS_LIBRARY removes the main() of the other files):
 *   gcc -DAS_LIBRARY Menue.c Ratten.c primzahl.c Pyramide.c -o Menue
 *
 * Created by pierre on 03.11.26.
 */

#include <stdio.h>
#include <stdlib.h>   /* strtol */
#include <errno.h>    /* errno, ERANGE */
#include <limits.h>   /* INT_MIN, INT_MAX */

/* header files of the other parts: they declare the functions used below */
#include "Ratten.h"
#include "primzahl.h"
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

int main(void)
{
    char eingabe[64];   /* buffer for one line of user input */
    int auswahl = 0;    /* selected menu item */

    /* show the menu until the user chooses "4) Beenden" */
    do {
        printf("\n=== Hauptmenue ===\n");
        printf("1) Ratespiel starten\n");
        printf("2) Primzahlen ausgeben\n");
        printf("3) Pyramide zeichnen\n");
        printf("4) Beenden\n");
        printf("Auswahl: ");

        /* end of input (e.g. Ctrl+D) -> leave the program */
        if (fgets(eingabe, sizeof(eingabe), stdin) == NULL) {
            break;
        }

        /* convert the input; anything that is not a number counts as invalid */
        if (!parse_int(eingabe, &auswahl)) {
            auswahl = 0;
        }

        switch (auswahl) {
        case 1:
            ratespiel();             /* defined in Ratten.c */
            break;
        case 2:
            primzahlen_ausgeben();   /* defined in primzahl.c */
            break;
        case 3:
            pyramide_zeichnen();     /* defined in Pyramide.c */
            break;
        case 4:
            printf("Auf Wiedersehen!\n");
            break;
        default:
            printf("Ungueltige Auswahl\n");
            break;
        }
    } while (auswahl != 4);

    return 0;
}