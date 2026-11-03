#include <stdio.h>

int main(void)
{
    char eingabe[64];
    char rest;
    int zahl;
    int versuche = 0;
    int ziel;
    unsigned int zufall = 12345u;      /* change this number for a different target */

    /* simple linear congruential generator instead of rand() */
    zufall = zufall * 1103515245u + 12345u;
    ziel = (int) ((zufall / 65536u) % 100u) + 1;

    printf("Ich habe mir eine Zahl zwischen 1 und 100 ausgedacht.\n");
    printf("Mit \"exit\" beendest du das Spiel.\n");

    while (1) {
        printf("Rate (1-100): ");
        if (fgets(eingabe, sizeof(eingabe), stdin) == NULL) {
            break;
        }

        /* "exit" check without strcmp */
        if (eingabe[0] == 'e' && eingabe[1] == 'x' && eingabe[2] == 'i' &&
            eingabe[3] == 't' && (eingabe[4] == '\n' || eingabe[4] == '\0')) {
            printf("Spiel beendet. Die Zahl war %d.\n", ziel);
            break;
            }

        /* exactly one integer and nothing after it */
        if (sscanf(eingabe, "%d %c", &zahl, &rest) != 1) {
            printf("Ungueltige Eingabe (Zahl oder \"exit\" erwartet).\n");
            continue;
        }
        if (zahl < 1 || zahl > 100) {
            printf("Wert ausserhalb des Bereichs 1-100, bitte erneut.\n");
            continue;
        }

        versuche++;
        if (zahl < ziel) {
            printf("zu klein\n");
        } else if (zahl > ziel) {
            printf("zu gross\n");
        } else {
            printf("Richtig! Du hast %d Versuche gebraucht.\n", versuche);
            break;
        }
    }
    return 0;
}
//
// Created by pierre on 03.11.26.
//