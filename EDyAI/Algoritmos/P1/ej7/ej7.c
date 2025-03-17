#include<stdio.h>
#include<stdlib.h>

int **crearMatriz(int n, int m);
void llenarFila(int ***matriz, int n, int m, int *fila, int pos);
int minimo(int x, int y);
int peajeAux(int i, int j, int n, int m, int **mat, int **calculado, int**memo, int***caminoOptimo, int* contadorCamino);
int peaje(int** mat, int n, int m, int ***caminoOptimo);

int main(void) {

    int n, m;
    scanf("%d %d", &n, &m);
    int **matriz = crearMatriz(n , m);
    int **caminoOptimo = crearMatriz(n + m, 2);

    for (int i = 0; i < n; i++) {
        int *fila = malloc(sizeof(int) * m);
        for (int j = 0; j < m; j++) {
            scanf("%d", &fila[j]);
        }
        llenarFila(&matriz, n, m, fila, i);
        free(fila);

    }

    printf("Min: %d\n", peaje(matriz, n, m, &caminoOptimo));

    for (int i = 0; i < 4; i++) {
        printf("(%d, %d)\n", caminoOptimo[i][0], caminoOptimo[i][1]);
    }

    return 0;
}

int peajeAux(int i, int j, int n, int m, int **mat, int **calculado, int**memo, int ***caminoOptimo, int *contadorCamino) {

    if (calculado[i][j])
        return memo[i][j];
    
    else {

        int costoCasilla = mat[i][j];

        int resultado;

        if (i == n - 1 && j == m - 1)  {
            resultado = costoCasilla;
            (*caminoOptimo)[*contadorCamino][0] = i;
            (*caminoOptimo)[*contadorCamino][1] = j;
            (*contadorCamino)++;
        }
        else if (i == n - 1) {
            resultado = costoCasilla + peajeAux(i, j + 1, n, m, mat, calculado, memo, caminoOptimo, contadorCamino);
            (*caminoOptimo)[*contadorCamino][0] = i;
            (*caminoOptimo)[*contadorCamino][1] = j;
            (*contadorCamino)++;
        }
        else if (j == m - 1) {
            resultado = costoCasilla + peajeAux(i + 1, j, n, m, mat, calculado, memo, caminoOptimo, contadorCamino);
            (*caminoOptimo)[*contadorCamino][0] = i;
            (*caminoOptimo)[*contadorCamino][1] = j;
            (*contadorCamino)++;
        }
        else {
            int resultado1 = peajeAux(i + 1, j, n, m, mat, calculado, memo, caminoOptimo, contadorCamino);
            int resultado2 = peajeAux(i, j + 1, n, m, mat, calculado, memo, caminoOptimo, contadorCamino);
            int min = minimo(resultado1, resultado2);
            if (min == resultado1) {
                (*caminoOptimo)[*contadorCamino][0] = i + 1;
                (*caminoOptimo)[*contadorCamino][1] = j;
                (*contadorCamino)++;
                resultado = costoCasilla + min;
            }
            else {
                (*caminoOptimo)[*contadorCamino][0] = i;
                (*caminoOptimo)[*contadorCamino][1] = j + 1;
                (*contadorCamino)++;
                resultado = costoCasilla + min;
            }
        }

        calculado[i][j] = 1;
        memo[i][j] = resultado;

        return resultado;
    }
}

int peaje(int** mat, int n, int m, int ***caminoOptimo) {

    int **calculado = crearMatriz(n, m);
    int **memo = crearMatriz(n, m);
    int contadorCamino = 0;

    int resultado = peajeAux(0, 0, n, m, mat, calculado, memo, caminoOptimo, &contadorCamino);

    return resultado;
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