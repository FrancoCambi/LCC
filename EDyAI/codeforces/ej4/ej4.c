#include<stdio.h>
#include<stdlib.h>

int **crearMatriz(int n, int m);
void llenarFila(int ***matriz, int n, int m, int *fila, int pos);
int minimo(int x, int y);
int ladronAux(int i, int j, int n, int m, int **mat, int **calculado, int**memo);

int main(void) {

    int n, m;
    scanf("%d %d", &n, &m);
    int **matriz = crearMatriz(n , m);

    for (int i = 0; i < n; i++) {
        int *fila = malloc(sizeof(int) * m);
        for (int j = 0; j < m; j++) {
            scanf("%d", &fila[j]);
        }
        llenarFila(&matriz, n, m, fila, i);
        free(fila);

    }

    int **calculado = crearMatriz(n , m);
    int **memo = crearMatriz(n, m);

    int resultado = ladronAux(0, 0, n, m, matriz, calculado, memo);

    printf("%d", resultado);

    for (int i = 0; i < n; i++) {
        free(matriz[i]);
        free(memo[i]);
        free(calculado[i]);
    }

    free(matriz);
    free(memo);
    free(calculado);


    return 0;
}

int ladronAux(int i, int j, int n, int m, int **mat, int **calculado, int **memo) {

    if (calculado[i][j])
        return memo[i][j];

    else {
        int costoCastilla = mat[i][j];

        int resultado;

        if (i == n - 1 && j == m - 1) {
            resultado = costoCastilla;
        }
        else if (i == n - 1) {
            resultado = costoCastilla + ladronAux(i, j + 1, n, m, mat, calculado, memo);
        }
        else if (j == m - 1) {
            resultado = costoCastilla + ladronAux(i + 1, j, n, m, mat, calculado, memo);
        }
        else {
            int opcion1 = ladronAux(i, j + 1, n, m, mat, calculado, memo);
            int opcion2 = ladronAux(i + 1, j, n, m, mat, calculado, memo);
            resultado = costoCastilla + minimo(opcion1, opcion2);
        }

        calculado[i][j] = 1;
        memo[i][j] = resultado;

        return resultado;
    }
}

void llenarFila(int ***matriz, int n, int m, int *fila, int pos) {

    for (int i = 0; i < m; i++)
        (*matriz)[pos][i] = fila[i];
}

int **crearMatriz(int n, int m) {

    int **matriz = calloc(n, sizeof(int*));

    for (int i = 0; i < n; i++) {
        matriz[i] = calloc(m, sizeof(int*));
    }

    return matriz;
}

int minimo(int x, int y) {
    return x < y ? x : y;
}