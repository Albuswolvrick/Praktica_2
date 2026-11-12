/*
 * Ratten.c
 * Number guessing game: the program picks a number between 1 and 100,
 * the player guesses and gets "zu klein" / "zu gross" as hints.
 * Typing "exit" ends the game.
 * Used by Menue.c (function ratespiel) and runnable on its own.
 * Created by pierre on 03.11.26.
 */

#include <stdio.h>
#include <stdlib.h>   /* strtol */
#include <errno.h>    /* errno, ERANGE */
#include <limits.h>   /* INT_MIN, INT_MAX */
#include "Ratten.h"

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

void ratespiel(void)
{
    char eingabe[64];                /* buffer for one line of user input */
    int zahl;                        /* the player's current guess */
    int versuche = 0;                /* number of valid guesses so far */
    int ziel;                        /* the secret number (1-100) */
    /* static: keeps its value between calls, so every new game gets a new number */
    static unsigned int zufall = 12345u;

    /* simple linear congruential generator instead of rand() */
    zufall = zufall * 1103515245u + 12345u;
    /* use the high bits (better quality) and map them to the range 1..100 */
    ziel = (int) ((zufall / 65536u) % 100u) + 1;

    printf("Ich habe mir eine Zahl zwischen 1 und 100 ausgedacht.\n");
    printf("Mit \"exit\" beendest du das Spiel.\n");

    /* game loop: runs until the number is guessed or the player quits */
    while (1) {
        printf("Rate (1-100): ");

        /* end of input (e.g. Ctrl+D) -> leave the game */
        if (fgets(eingabe, sizeof(eingabe), stdin) == NULL) {
            return;
        }

        /* "exit" check without strcmp: compare character by character */
        if (eingabe[0] == 'e' && eingabe[1] == 'x' && eingabe[2] == 'i' &&
            eingabe[3] == 't' && (eingabe[4] == '\n' || eingabe[4] == '\0')) {
            printf("Spiel beendet. Die Zahl war %d.\n", ziel);
            return;
        }

        /* the input must be exactly one integer and nothing else */
        if (!parse_int(eingabe, &zahl)) {
            printf("Ungueltige Eingabe (Zahl oder \"exit\" erwartet).\n");
            continue;   /* ask again, this does not count as an attempt */
        }

        /* guess must be inside the allowed range */
        if (zahl < 1 || zahl > 100) {
            printf("Wert ausserhalb des Bereichs 1-100, bitte erneut.\n");
            continue;
        }

        versuche++;     /* only valid guesses are counted */

        /* compare the guess with the secret number and give a hint */
        if (zahl < ziel) {
            printf("zu klein\n");
        } else if (zahl > ziel) {
            printf("zu gross\n");
        } else {
            printf("Richtig! Du hast %d Versuche gebraucht.\n", versuche);
            return;     /* correct guess -> game over */
        }
    }
}

/* main only exists when the file is compiled alone (not together with Menue.c) */
#ifndef AS_LIBRARY
int main(void)
{
    ratespiel();
    return 0;
}
#endif