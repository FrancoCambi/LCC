#include<stdio.h>

typedef void (*VisitorFunc)(int);
void imprimir(int);
void recorre(VisitorFunc, int[], int);

int main(void) {

    int arr[5] = {1,2,3,4,5};

    recorre(imprimir, arr, 5);

    return 0;
}

void imprimir(int num) {
    printf("%d \n", num);
}

void recorre(VisitorFunc func, int arr[], int n) {

    for (int i = 0; i < n; i++) {

        func(arr[i]);
    }

}