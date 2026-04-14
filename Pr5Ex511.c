#include <stdio.h>
#include <stdlib.h>

typedef struct Dada {
    int niu;
    float notes[5];
    struct Dada * seg;
} Alu;

float mitjana(float[], int);
void imprimirllista(Alu * inici);

int main() {
    FILE * dades;
    int n, i, lrg = 0;
    Alu * inicill = NULL, * actual = NULL, * anterior;

    dades = fopen("Llista.txt", "r");
    if (dades == NULL) {
        printf("\nNo s'ha accedit al fitxer de dades\n");
        return 1;
    }
    while (!(fscanf(dades, "%i;", & n) == EOF)) {
    if ((actual = (Alu * ) malloc(sizeof(Alu))) == NULL) {
        printf("Problema assignant espai de memoria\n");
        return 2;
    }
    lrg++;
    actual -> niu = n;
    for (i = 0; i < 4; i++) {
        fscanf(dades, "%f", & actual -> notes[i]);
        fgetc(dades); //llegeix i descarta els ; i el \n
    }
    actual -> notes[4] = mitjana(actual -> notes, 4);
    if (inicill == NULL) {
        actual -> seg = NULL;
        inicill = actual;
    } else {
        if (actual -> niu < inicill -> niu) {
            actual -> seg = inicill;
            inicill = actual;
        } else {
            anterior = inicill;
            while (anterior -> seg != NULL && (anterior -> seg) -> niu < actual -> niu) {
                anterior = anterior -> seg;
            }
            actual -> seg = anterior -> seg;
            anterior -> seg = actual;
        }
    }
    }
    fclose(dades);
    actual = inicill;
    imprimirllista(actual);
    printf("\nS'ha llegit informacio de %d linies.\n\n", lrg);
    return 0;
}

float mitjana(float dades[], int n) {
    int i;
    float m = 0.;
    for (i = 0; i < n; i++) {
        m += dades[i];
    }
    return m / n;
}

void imprimirllista(Alu * inici){
    Alu * actual = inici;
    while (actual) {
        printf("%d | ", actual -> niu);
        for (unsigned i = 0; i < 4; i++) {
            printf("%5.1f", actual -> notes[i]);
        }
        printf(" |%6.2f", actual -> notes[4]);
        printf("\n");
        actual = actual -> seg;
    }
}