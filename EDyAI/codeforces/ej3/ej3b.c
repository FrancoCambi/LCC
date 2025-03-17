#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXLENNAME 100000

char **moverFinal(char **pila, int longitud, int k);

int main(void) {

    int longitud, q;

    scanf("%d %d", &longitud, &q);
    char **pila = (char**)malloc(sizeof(char*) * longitud);

    for (int i = 0; i < longitud; i++) {
        pila[i] = malloc(sizeof(char) * MAXLENNAME + 1);
        scanf("%s", pila[i]);
        pila[i] = realloc(pila[i], sizeof(char) * strlen(pila[i]) + 1);
    }

    int k, kTotal = 0;
    for (int i = 0; i < q; i++) {
        scanf("%d", &k);
        kTotal += k;
    }

    kTotal %= longitud;

    pila = moverFinal(pila, longitud, kTotal);

    for (int i = 0; i < longitud; i++) {
        printf("%s\n", pila[i]);
        free(pila[i]);
    }

    free(pila);
    return 0;
}

char **moverFinal(char **pila, int longitud, int k) {

    if (k == 0)
        return pila;

    char **pilaCambiada = malloc(sizeof(char*) * longitud);

    for (int i = 0; i < longitud; i++) {

        if (i < k) {
            pilaCambiada[longitud - k + i] = malloc(sizeof(char) * strlen(pila[i]) + 1);
            strcpy(pilaCambiada[longitud - k + i], pila[i]);
        }
        else {
            pilaCambiada[i - k] = malloc(sizeof(char) * strlen(pila[i]) + 1);
            strcpy(pilaCambiada[i-k], pila[i]);
        }
        
    }
    return pilaCambiada;
}

