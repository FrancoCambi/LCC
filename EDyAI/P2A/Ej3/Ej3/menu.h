#ifndef __MENU__
#define __MENU__

#include "slist.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    CREAR,
    DESTRUIR,
    IMPRIMIR,
    AGREGAR_FINAL,
    AGREGAR_INICIO,
    AGREGAR_POS,
    LONGITUD,
    CONCATENAR,
    ELIMINAR,
    CONTIENE,
    INDICE,
    INTERSECAR,
    ORDENAR,
    REVERSO,
    SALIR,
    MENU,
    NONE
} Command;

/**
 * @brief Imprime por la salida estandar un dato pasado
 * 
 * @param dato 
 */
void imprimir_entero(int dato);

/**
 * @brief Compara dos enteros, devuelve 1 si dato1 es mayor a dato2 y -1 caso contrario
 * 
 * @param dato1 
 * @param dato2 
 * @return int 
 */
int comparar_enteros(int dato1, int dato2);

/**
 * @brief Get the enum command object
 * 
 * @param str 
 * @return Command 
 */
Command getEnumCommand(char* str);

/**
 * @brief Realiza el comando adecuado
 * 
 * @param slistArray 
 * @param slistArrayLongitud 
 * @param command 
 * @param args 
 */
void realizarComando(SList **slistArray, size_t *slistArrayLongitud, Command command, int *args);

/**
 * @brief Chequea que los datos pasados como argumentos para determinado comando sean correctos 
 * y devuelve 1 si lo son, 0 caso contrario.
 * 
 * @param command 
 * @param args 
 * @param argsLongitud 
 * @return int 
 */
int chequearArgs(Command command, size_t slistArrayLongitud, int* args, size_t argsLongitud);

/**
 * @brief Muestra el menu de opciones.
 * 
 */
void displayMenu();


#endif