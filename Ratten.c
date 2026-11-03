#include <stdio.h>   /* printf, fgets, stdin, getchar */
#include <stdlib.h>  /* strtol */
#include <string.h>  /* strcspn, strcmp */
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
    int zahl;
    int versuche = 0;
    int ziel;
    unsigned int zufall = 12345u;   /* change this number for a different target */

    /* simple linear congruential generator instead of rand() */
    zufall = zufall * 1103515245u + 12345u;
    ziel = (int) ((zufall / 65536u) % 100u) + 1;

    printf("Ich habe mir eine Zahl zwischen 1 und 100 ausgedacht.\n");
    printf("Mit \"exit\" beendest du das Spiel.\n");

    while (1) {
        printf("Rate (1-100): ");
        if (!lese_zeile(eingabe, sizeof(eingabe))) {
            break;
        }

        if (strcmp(eingabe, "exit") == 0) {
            printf("Spiel beendet. Die Zahl war %d.\n", ziel);
            break;
        }

        if (!text_zu_int(eingabe, &zahl)) {
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
