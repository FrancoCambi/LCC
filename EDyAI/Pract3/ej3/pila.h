#ifndef __PILA_H__
#define __PILA_H__
#include"glist.h"
#include<stdlib.h>

struct _Pila {
    GNode *inicio;
};

typedef struct _Pila *Pila;

void imprimir(void* dato);

Pila pila_crear();

void pila_destruir(Pila pila, FuncionDestructora destruir);

int pila_es_vacia(Pila pila);

void *pila_tope(Pila pila);

void pila_apilar(Pila pila, void *dato, FuncionCopia copia);

void pila_desapilar(Pila pila);

void pila_imprimir(Pila pila, FuncionVisitante visit);

#endif