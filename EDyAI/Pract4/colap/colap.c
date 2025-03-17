#include"colap.h"

ColaP cola_prioridad_crear(int capacidad, FuncionComparadoraDato comparar) {

    ColaP cola = malloc(sizeof(struct _ColaP));
    cola->arr = malloc(sizeof(struct _Dato) * (capacidad + 1));
    cola->ultimo = 0;
    cola->capacidad = capacidad;
    cola->comparar = comparar;

    return cola;
}

void cola_prioridad_destruir(ColaP cola, FuncionDestructora destruir) {

    for (int i = 1; i <= cola->ultimo; i++) {
        destruir(cola->arr[i]->val);
        free(cola->arr[i]);
    }

    free(cola->arr);
    free(cola);
}

int cola_prioridad_es_vacia(ColaP cola) {
    return cola->ultimo == 0;
}

void cola_prioridad_recorrer(ColaP cola, FuncionVisitante visit) {

    if (cola_prioridad_es_vacia(cola))
        return;

    for (int i = 1; i <= cola->ultimo; i++)
        visit(cola->arr[i]->val);
    
}

void* cola_prioridad_maximo(ColaP cola) {

    if (cola_prioridad_es_vacia(cola))
        return NULL;

    return cola->arr[1]->val;
}

static void cola_prioridad_eliminar_maximo_aux(ColaP cola , FuncionDestructora destruir, FuncionComparadoraDato comparar) {

    Dato datoALiberar = cola->arr[1];

    cola->arr[1] = cola->arr[(cola->ultimo)--];
    int indexDatoSubido = 1, indexHijoIzq, esMayor = 1;

    while ((indexDatoSubido * 2) <= cola->ultimo && esMayor) {

        indexHijoIzq = indexDatoSubido * 2;

        if (indexHijoIzq + 1 <= cola->ultimo && comparar(cola->arr[indexHijoIzq + 1], cola->arr[indexHijoIzq]) > 0)
            indexHijoIzq++; // hijo derecho el mayor
        if (comparar(cola->arr[indexDatoSubido], cola->arr[indexHijoIzq]) > 0)
            esMayor = 0;
        else {

            Dato temp = cola->arr[indexDatoSubido];
            cola->arr[indexDatoSubido] = cola->arr[indexHijoIzq];
            cola->arr[indexHijoIzq] = temp;
            indexDatoSubido = indexHijoIzq;
        }
    }

    destruir(datoALiberar->val);
    free(datoALiberar);

}
void cola_prioridad_eliminar_maximo(ColaP cola , FuncionDestructora destruir) {
    cola_prioridad_eliminar_maximo_aux(cola, destruir, cola->comparar);
}

static void cola_prioridad_insertar_aux(ColaP cola, void* val, int prioridad, FuncionCopia copiar, FuncionComparadoraDato comparar) {

    if (cola->ultimo == cola->capacidad) {
        cola->capacidad *= 2;
        cola->arr = realloc(cola->arr, sizeof(struct _Dato) * cola->capacidad);
    }

    Dato dato = malloc(sizeof(struct _Dato));
    dato->val = copiar(val);
    dato->prioridad = prioridad;

    cola->arr[++(cola->ultimo)] = dato;
    int index;
    Dato temp;

    for (index = cola->ultimo; index > 1 && comparar(cola->arr[index], cola->arr[index / 2]) > 0; index /= 2) {

        temp = cola->arr[index];
        cola->arr[index] = cola->arr[index / 2];
        cola->arr[index / 2] = temp;
    }

}
void cola_prioridad_insertar(ColaP cola, void* dato, int prioridad, FuncionCopia copiar) {
    cola_prioridad_insertar_aux(cola, dato, prioridad, copiar, cola->comparar);
}