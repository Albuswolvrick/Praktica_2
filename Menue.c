#include <stdio.h>

int main(void)
{
    char eingabe[64];
    char rest;
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

        if (fgets(eingabe, sizeof(eingabe), stdin) == NULL) {
            break;
        }
        if (sscanf(eingabe, "%d %c", &auswahl, &rest) != 1) {
            auswahl = 0;                        /* not a number -> invalid */
        }

        switch (auswahl) {
        case 1:
            zufall = zufall * 1103515245u + 12345u;   /* new number each game */
            ziel = (int) ((zufall / 65536u) % 100u) + 1;
            versuche = 0;
            printf("Mit \"exit\" kehrst du zum Menue zurueck.\n");
            while (1) {
                printf("Rate (1-100): ");
                if (fgets(eingabe, sizeof(eingabe), stdin) == NULL) {
                    break;
                }
                if (eingabe[0] == 'e' && eingabe[1] == 'x' && eingabe[2] == 'i' &&
                    eingabe[3] == 't' && (eingabe[4] == '\n' || eingabe[4] == '\0')) {
                    break;
                }
                if (sscanf(eingabe, "%d %c", &zahl, &rest) != 1) {
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
            if (fgets(eingabe, sizeof(eingabe), stdin) == NULL ||
                sscanf(eingabe, "%d", &n) != 1) {
                printf("Ungueltige Eingabe\n");
                break;
            }
            for (kandidat = 2; kandidat <= n; kandidat++) {
                ist_prim = 1;
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
//
// Created by pierre on 03.11.26.
//