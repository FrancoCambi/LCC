#include<stdio.h>

int binsearch(int *arr, int len, int v);
int binsearchAux(int *arr, int len, int v, int low, int high);

int main(void) {

    int arr[] = {1,2,3,4,5,6,7,8,9};
    int len = 9;

    printf("%d", binsearch(arr, len, 5));

    return 0;
}

int binsearchAux(int *arr, int len, int v, int low, int high) {

    if (low > high) return -1;

    int mid = (low + high) / 2;
    if (arr[mid] == v) return mid;

    if (v > arr[mid]) return binsearchAux(arr, len, v, mid + 1, high);
    if (v < arr[mid]) return binsearchAux(arr, len, v, low, mid - 1);
}

int binsearch(int *arr, int len, int v) {

    return binsearchAux(arr, len, v, 0, len);

}