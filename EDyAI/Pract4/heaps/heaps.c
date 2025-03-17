#include"heaps.h"

BHeap bheap_crear(int capacidad, FuncionComparadora comparar) {

    BHeap heap = malloc(sizeof(struct _BHeap));

    heap->arr = malloc(sizeof(void*) * (capacidad + 1));
    heap->capacidad = capacidad;
    heap->ultimo = 0;
    heap->comparar = comparar;

    return heap;
}

void bheap_destruir(BHeap heap, FuncionDestructora destruir) {

    for (int i = 1; i <= heap->ultimo; i++) {
        destruir(heap->arr[i]);
    }

    free(heap->arr);
    free(heap);
}

int bheap_vacio(BHeap heap) {
    return heap->ultimo == 0;
}

void bheap_recorrer(BHeap heap, FuncionVisitante visit) {

    for (int i = 1; i <= heap->capacidad && i <= heap->ultimo; i++) 
        visit(heap->arr[i]);
    
}

static void bheap_insertar_aux(BHeap heap, void* dato, FuncionCopia copiar, FuncionComparadora comparar) {

    if (heap->ultimo >= heap->capacidad) {
        heap->arr = realloc(heap->arr, sizeof(void*) * (heap->capacidad * 2 + 1));
        heap->capacidad *= 2;
    }


    heap->arr[++(heap->ultimo)] = copiar(dato);

    int nuevoIndex = heap->ultimo;
    void* temp;

    for (; nuevoIndex > 1 && comparar(heap->arr[nuevoIndex], heap->arr[nuevoIndex / 2]) > 0; nuevoIndex /= 2) {

        temp = heap->arr[nuevoIndex];
        heap->arr[nuevoIndex] = heap->arr[nuevoIndex / 2];
        heap->arr[nuevoIndex / 2] = temp;
    }

}

void bheap_insertar(BHeap heap, void* dato, FuncionCopia copiar) {

    bheap_insertar_aux(heap, dato, copiar, heap->comparar);
}

static void bheap_eliminar_aux(BHeap heap, void* dato, FuncionDestructora destruir, FuncionComparadora comparar) {

    // Si es el ultimo solo se elimina
    if (comparar(heap->arr[heap->ultimo], dato) == 0) {
        destruir(heap->arr[(heap->ultimo)--]);
        return;
    }

    // Si no es el ultimo se elimina y se reacomoda el heap
    int encontrado = 0;

    for (int i = 1; i < heap->ultimo; i++) {
        if ((comparar(heap->arr[i], dato)) == 0) {
            destruir(heap->arr[i]);
            encontrado = 1;
        }
        if (encontrado)
            heap->arr[i] = heap->arr[i + 1];
    }

    heap->ultimo--;
}

void bheap_eliminar(BHeap heap, void* dato, FuncionDestructora destruir) {
    bheap_eliminar_aux(heap, dato, destruir, heap->comparar);
}


