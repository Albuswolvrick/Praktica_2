#include <stdio.h>

enum { ENDE, UNGUELTIG, HILFE, ZAHL };

static unsigned int zustand = 2463534242u;

static void seed_init(void)
{
    FILE *f = fopen("/dev/urandom", "rb");
    unsigned int s = 0;
    int i;
    if (f != NULL) {
        for (i = 0; i < 4; i++) {
            s = (s << 8) | (unsigned int) (fgetc(f) & 0xFF);
        }
        fclose(f);
        if (s != 0) {
            zustand = s;
        }
    }
}

static int zufall(int von, int bis)             /* xorshift32 */
{
    zustand ^= zustand << 13;
    zustand ^= zustand >> 17;
    zustand ^= zustand << 5;
    return von + (int) (zustand % (unsigned int) (bis - von + 1));
}

static int gleich(const char *s, const char *wort)
{
    while (*wort != '\0') {
        if (*s != *wort) {
            return 0;
        }
        s++;
        wort++;
    }
    return *s == '\n' || *s == '\0';
}

static int lies_eingabe(int *zahl)
{
    char buf[64], rest;
    printf("Rate (1-100): ");
    if (fgets(buf, sizeof(buf), stdin) == NULL || gleich(buf, "exit")) {
        return ENDE;
    }
    if (gleich(buf, "hilfe")) {
        return HILFE;
    }
    if (sscanf(buf, "%d %c", zahl, &rest) != 1) {
        return UNGUELTIG;
    }
    return ZAHL;
}

int main(void)
{
    char buf[16];
    int beste = 0, weiter = 1;

    seed_init();
    printf("Zahlenraten! Befehle: exit, hilfe\n");

    while (weiter) {
        int ziel = zufall(1, 100);
        int lo = 1, hi = 100, versuche = 0, fertig = 0, zahl = 0;

        printf("\nNeue Runde: Zahl zwischen 1 und 100.\n");
        while (!fertig) {
            switch (lies_eingabe(&zahl)) {
            case ENDE:
                printf("Die Zahl war %d.\n", ziel);
                weiter = 0;
                fertig = 1;
                break;
            case HILFE:
                printf("Tipp: probiere %d (Bereich %d-%d)\n", (lo + hi) / 2, lo, hi);
                break;
            case UNGUELTIG:
                printf("Ungueltige Eingabe\n");
                break;
            default:
                if (zahl < 1 || zahl > 100) {
                    printf("Wert ausserhalb des Bereichs 1-100\n");
                    break;
                }
                versuche++;
                if (zahl < ziel) {
                    printf("zu klein\n");
                    if (zahl + 1 > lo) lo = zahl + 1;
                } else if (zahl > ziel) {
                    printf("zu gross\n");
                    if (zahl - 1 < hi) hi = zahl - 1;
                } else {
                    printf("Richtig! Du hast %d Versuche gebraucht.\n", versuche);
                    if (beste == 0 || versuche < beste) beste = versuche;
                    printf("Rekord: %d (optimal sind maximal 7 Versuche)\n", beste);
                    fertig = 1;
                }
            }
        }
        if (weiter) {
            printf("Nochmal? (j/n): ");
            if (fgets(buf, sizeof(buf), stdin) == NULL || buf[0] != 'j') {
                weiter = 0;
            }
        }
    }
    return 0;
}
//
// Created by pierre on 03.11.26.
//