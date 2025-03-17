#include<stdio.h>
#include<stdlib.h>

size_t maxIndice(int *arr, size_t longitud);

int main(void) {

    size_t longitud;
    scanf("%ld", &longitud);
    int *arr = malloc(sizeof(int) * longitud);

    for (int i = 0; i < longitud; i++)
        scanf("%d", &arr[i]);
    
    printf("Index del maximo: %ld", maxIndice(arr, longitud));

    free(arr);

    return 0;
}

//O(n)
size_t maxIndice(int *arr, size_t longitud) {

    int max = arr[0], index = -1;

    for (int i = 0; i < longitud; i++) 
        if (arr[i] >= max) {
            max = arr[i];
            index = i;
        }

    return index;
}
