#ifndef __AD_H__
#define __AD_H__

#include<stdio.h>
#include<stdlib.h>

/// @brief Estructura que representa un array de enteros dinámico.
typedef struct {
    int *direccion;
    int capacidad;
    int cantidad;
} ArregloEnteros;

/// @brief Crea un ArregloEnteros con la capacidad dada
/// @param capacidad Tamaño del array.
/// @return Puntero al ArregloEnteros creado.
ArregloEnteros *arreglo_enteros_crear(int capacidad);

/// @brief Libera la memoria de un ArregloEnteros
/// @param arreglo Objeto a destruir.
void arreglo_enteros_destruir(ArregloEnteros *arreglo);

/// @brief Lee el arreglo en al posicion asignada
/// @param arreglo  Arreglo a leer
/// @param pos Posición a leer
/// @return Entero en esa posición o basura en caso de haber un error
int arreglo_enteros_leer(ArregloEnteros *arreglo, int pos);

/// @brief Escribe dato en pos de arreglo
/// @param arreglo Arreglo a escribir
/// @param pos Posición a escribir
/// @param dato Entero a escribir en arr[pos]
void arreglo_enteros_escribir(ArregloEnteros *arreglo, int pos, int dato);

/// @brief Devuelve la capacidad del arregloEnteros
/// @param arreglo ArregloEntero: 
/// @return int: capacidad de arreglo
int arreglo_enteros_capacidad(ArregloEnteros *arreglo);

/// @brief Imprime en la salida estandar el arreglo de enteros
/// @param arreglo Arreglo a imprimir
void arreglo_enteros_imprimir(ArregloEnteros *arreglo);

/// @brief Ajusta el tamaño del arreglo
/// @param arreglo Arreglo a ajustar
/// @param capacidad Nueva capacidad
void arreglo_enteros_ajustar(ArregloEnteros *arreglo, int capacidad);

void arreglo_enteros_agregar(ArregloEnteros *arreglo, int pos, int dato);

/// @brief Inserta un dato en una posicion dada incrementando el tamaño del arreglo
/// @param arreglo Areglo a modificar
/// @param pos Index 
/// @param dato dato
void arreglo_enteros_insertar(ArregloEnteros *arreglo, int pos, int dato);

/// @brief Elimina un dato en la posición dada
/// @param arreglo Arreglo a modificar
/// @param pos Index
void arreglo_enteros_eliminar(ArregloEnteros *arreglo, int pos);

#endif