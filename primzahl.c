#include <stdio.h>

int main(void)
{
    char eingabe[64];
    int n, kandidat, teiler, ist_prim;

    printf("N eingeben: ");
    if (fgets(eingabe, sizeof(eingabe), stdin) == NULL ||
        sscanf(eingabe, "%d", &n) != 1) {
        printf("Ungueltige Eingabe\n");
        return 1;
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
    return 0;
}//
// Created by pierre on 03.11.26.
//