#include<stdio.h>
#include<stdlib.h>

#define STARTSIZE 5
#define INCREMENT 1.75


int main(void) {

    int *arr = malloc(sizeof(int) * STARTSIZE), dato, cantidad = 0, arrSize = STARTSIZE;

    do {

        printf("Ingrese un entero: ");
        scanf("%d", &dato);

        // Una vez usada toda la memoria designada, se aumenta.
        if (cantidad == arrSize) {
            arrSize *= INCREMENT;
            arrSize = (int) arrSize;
            arr = realloc(arr, sizeof(int) * arrSize);
        }

        arr[cantidad] = dato;
        cantidad++;

        puts("");


    } while (dato != 0);

    // Se trunca el array a la longitud resultante exacta.
    arr = realloc(arr, sizeof(int) * cantidad);

    for (int i = 0; i < cantidad - 1; i++) 
        printf("%d ", arr[i]);

    return 0;
}