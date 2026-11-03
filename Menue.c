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
    int auswahl = 0;
    int zahl, ziel, versuche;
    int n, kandidat, teiler, ist_prim;
    unsigned int zufall = 12345u;

    do {
        printf("\n=== Hauptmenue ===\n");
        printf("1) Ratespiel starten\n");
        printf("2) Primzahlen ausgeben\n");
        printf("3) Beenden\n");
        printf("Auswahl: ");

        if (!lese_zeile(eingabe, sizeof(eingabe))) {
            break;
        }
        if (!text_zu_int(eingabe, &auswahl)) {
            auswahl = 0;                /* not a number -> invalid */
        }

        switch (auswahl) {
        case 1:
            zufall = zufall * 1103515245u + 12345u;   /* new number each game */
            ziel = (int) ((zufall / 65536u) % 100u) + 1;
            versuche = 0;
            printf("Mit \"exit\" kehrst du zum Menue zurueck.\n");
            while (1) {
                printf("Rate (1-100): ");
                if (!lese_zeile(eingabe, sizeof(eingabe))) {
                    break;
                }
                if (strcmp(eingabe, "exit") == 0) {
                    break;
                }
                if (!text_zu_int(eingabe, &zahl)) {
                    printf("Ungueltige Eingabe\n");
                    continue;
                }
                if (zahl < 1 || zahl > 100) {
                    printf("Wert ausserhalb des Bereichs 1-100\n");
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
            break;

        case 2:
            printf("N eingeben: ");
            if (!lese_zeile(eingabe, sizeof(eingabe)) || !text_zu_int(eingabe, &n)) {
                printf("Ungueltige Eingabe\n");
                break;
            }
            for (kandidat = 2; kandidat <= n; kandidat++) {
                ist_prim = 1;
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
