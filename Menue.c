/*
 * Menue.c
 * Main menu that combines two programs:
 *   1) number guessing game   -> same logic as in Ratten.c
 *   2) prime number output    -> same logic as in primzahl.c
 *   3) quit
 * (The logic is copied into this file, so Menue.c compiles on its own.)
 * Created by pierre on 03.11.26.
 */

#include <stdio.h>
#include <stdlib.h>   /* strtol */
#include <errno.h>    /* errno, ERANGE */
#include <limits.h>   /* INT_MIN, INT_MAX */

/*
 * Converts a text to an int (replacement for sscanf).
 * Same helper as in Ratten.c, Pyramide.c and primzahl.c.
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
    char eingabe[64];               /* buffer for one line of user input */
    int auswahl = 0;                /* selected menu item */
    int zahl, ziel, versuche;       /* guessing game: guess, secret number, attempts */
    int n, kandidat, teiler, ist_prim;   /* prime output: limit, candidate, divisor, flag */
    unsigned int zufall = 12345u;   /* state of the random number generator */

    /* show the menu until the user chooses "3) Beenden" */
    do {
        printf("\n=== Hauptmenue ===\n");
        printf("1) Ratespiel starten\n");
        printf("2) Primzahlen ausgeben\n");
        printf("3) Beenden\n");
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
            /* --- guessing game (see Ratten.c) --- */
            /* simple linear congruential generator: new number each game */
            zufall = zufall * 1103515245u + 12345u;
            ziel = (int) ((zufall / 65536u) % 100u) + 1;   /* map to 1..100 */
            versuche = 0;

            printf("Mit \"exit\" kehrst du zum Menue zurueck.\n");

            while (1) {
                printf("Rate (1-100): ");
                if (fgets(eingabe, sizeof(eingabe), stdin) == NULL) {
                    break;
                }

                /* "exit" check without strcmp: compare character by character */
                if (eingabe[0] == 'e' && eingabe[1] == 'x' && eingabe[2] == 'i' &&
                    eingabe[3] == 't' && (eingabe[4] == '\n' || eingabe[4] == '\0')) {
                    break;   /* back to the menu */
                }

                /* the input must be exactly one integer */
                if (!parse_int(eingabe, &zahl)) {
                    printf("Ungueltige Eingabe\n");
                    continue;
                }
                if (zahl < 1 || zahl > 100) {
                    printf("Wert ausserhalb des Bereichs 1-100\n");
                    continue;
                }

                versuche++;   /* only valid guesses are counted */

                /* give a hint or finish the game */
                if (zahl < ziel) {
                    printf("zu klein\n");
                } else if (zahl > ziel) {
                    printf("zu gross\n");
                } else {
                    printf("Richtig! Du hast %d Versuche gebraucht.\n", versuche);
                    break;
                }
            }
            break;

        case 2:
            /* --- prime numbers up to N (see primzahl.c) --- */
            printf("N eingeben: ");
            if (fgets(eingabe, sizeof(eingabe), stdin) == NULL ||
                !parse_int(eingabe, &n)) {
                printf("Ungueltige Eingabe\n");
                break;
            }

            for (kandidat = 2; kandidat <= n; kandidat++) {
                ist_prim = 1;   /* assume prime until a divisor is found */

                /* trial division up to sqrt(kandidat) is enough */
                for (teiler = 2; teiler * teiler <= kandidat; teiler++) {
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
            break;

        case 3:
            printf("Auf Wiedersehen!\n");
            break;

        default:
            printf("Ungueltige Auswahl\n");
            break;
        }
    } while (auswahl != 3);

    return 0;
}