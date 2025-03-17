#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b);
int partition(int *arr, size_t low, size_t high, int *pivotCont);
void quickSort(int *arr,  int low,  int high);

int main(void) {

    size_t longitud;
    scanf("%ld", &longitud);

    int *arr = malloc(sizeof(int) * longitud);

    for (int i = 0; i < longitud; i++) {
        scanf("%d", &arr[i]);
    }


    printf("Array: ");
    for (int i = 0; i < longitud; i++) {
        printf("%d ", arr[i]);
    }

    quickSort(arr, 0, longitud - 1);
    printf("\nArray ordenado: ");
    for (int i = 0; i < longitud; i++) {
        printf("%d ", arr[i]);
    }

    free(arr);

    return 0;
}

void swap (int *a, int *b) {

    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int *arr, size_t low, size_t high, int *pivotCont) {

    int pivot = arr[high];

    int i = low - 1;

    for (int j = low; j < high; j++) {

        if (arr[j] < pivot) {

            i++;
            swap(&arr[i], &arr[j]);
        }
        else if (arr[j] == pivot) (*pivotCont)++;
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int *arr,  int low,  int high) {

    int pivotCont = 1;
    if (low < high) {

        size_t pivotPosicionado = partition(arr, low, high, &pivotCont);

        quickSort(arr, low, pivotPosicionado - pivotCont);
        quickSort(arr, pivotPosicionado + 1, high); 
    }

}