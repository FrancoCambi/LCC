#include<stdio.h>
#include<stdlib.h>

typedef enum {
    FINAL,
    INICIO
}DONDE;
void realizarOperacion(int **mazo, int n, int op, int posCarta);
int getIndex(int *mazo, int n, int num);
void insertarMazoFI(int **mazo, int n, int posCarta, DONDE donde);


int main(void) {

    int n, q;
    scanf("%d %d", &n, &q);

    int ops[q][2];
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &ops[i][0], &ops[i][1]);
    }

    int *mazo = malloc(sizeof(int) * n);
    for (int i = 1; i <= n; i++) {
        mazo[i - 1] = i;
    }

    for (int i = 0; i < q; i++) {

        realizarOperacion(&mazo, n, ops[i][0], ops[i][1]);
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", mazo[i]);
    }

    free(mazo);

    return 0;
}


void realizarOperacion(int **mazo, int n, int op, int posCarta) {

    switch (op) {

        case 1:
            insertarMazoFI(mazo, n, posCarta, INICIO);
            break;
        
        case 2:
            insertarMazoFI(mazo, n, posCarta, FINAL);
            break;
        
        case 3:;
            int buffer = (*mazo)[posCarta - 1];
            (*mazo)[posCarta - 1] = (*mazo)[posCarta];
            (*mazo)[posCarta] = buffer;
            break;
    }
}


void insertarMazoFI(int **mazo, int n, int posCarta, DONDE donde) {

    int dato;
    if (donde == INICIO) {

        dato = (*mazo)[posCarta];
        for (int i = posCarta - 1; i >= 0; i--) {
            (*mazo)[i + 1] = (*mazo)[i];
        }

        (*mazo)[0] = dato;
    }

    else {

        dato = (*mazo)[posCarta];

        for (int i = posCarta + 1; i < n; i++) {
            (*mazo)[i - 1] = (*mazo)[i];
        }

        (*mazo)[n - 1] = dato;
    }

}
