#include <stdio.h>
#include <stdlib.h>

typedef struct Dada {
int niu;
float notes[5];
struct Dada * seg;
} Alu;

float mitjana(float[], int);
void imprimirllista(Alu * inici);
void inserir(Alu ** inici, Alu ** actual);
void esborrar(Alu ** inici, int niu_buscat);

int main() {
    FILE * dades;
    int n, i, lrg = 0;
    Alu * inicill = NULL, * actual = NULL;
    char continuar;

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
        inserir(&inicill, &actual);
    }
    fclose(dades);
    actual = inicill;
    printf("\nS'ha llegit informacio de %d linies.\n\n", lrg);
    printf("Vols afegir les dades d'algun altre alumne?(S/n):");
    continuar = getchar();
    while (continuar == 'S' || continuar == 's'){
        if ((actual = (Alu * ) malloc(sizeof(Alu))) == NULL) {
            printf("Problema assignant espai de memoria\n");
            return 2;
        }
        printf("Introdueix el niu:\n");
        scanf("%u", &n);
        actual -> niu = n;
        for (i = 0; i < 4; i++) {
            printf("Introdueix la nota %d:    ",i);
            scanf("%f", & actual -> notes[i]);
        }
        actual -> notes[4] = mitjana(actual -> notes, 4);
        inserir(&inicill, &actual);
        printf("Vols afegir les dades d'algun altre alumne?(S/n):");
        continuar = getchar();
    }
    esborrar(&inicill, 1000961);
    esborrar(&inicill, 1110847);
    esborrar(&inicill, 3900285);
    esborrar(&inicill, 3989795);
    imprimirllista(inicill);
    getchar();
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

void inserir(Alu ** inici, Alu ** actual){
    Alu *anterior = NULL;
    if ((*inici) == NULL) {
        (*actual) -> seg = NULL;
        (*inici) = (*actual);
    } else {
        if ((*actual) -> niu < (*inici) -> niu) {
            (*actual) -> seg = (*inici);
            (*inici) = (*actual);
        } else {
            anterior = (*inici);
            while (anterior -> seg != NULL && (anterior -> seg) -> niu < (*actual) -> niu) {
                anterior = anterior -> seg;
            }
            (*actual) -> seg = anterior -> seg;
            anterior -> seg = (*actual);
        }
    }
}

void esborrar(Alu ** inici, int niu_buscat){
    Alu *anterior=NULL, *actual = (*inici);
    
    while (actual && (actual->niu != niu_buscat)){
        anterior = actual;
        actual = actual->seg;
    }
    
    if (actual == NULL){
        return;
    }
    if (anterior == NULL){
        (*inici) = actual->seg;
    } else{
        anterior->seg = actual -> seg;
    }
    free(actual);
}