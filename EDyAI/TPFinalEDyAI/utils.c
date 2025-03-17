#include "utils.h"
#include "trie.h"
#include<stddef.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>

// Recibe un char y devuelve su indice en el intervalo
// [0,25] (los caracteres no se distinguen entre minuscula y mayuscula).
unsigned get_index(char c) {

    if (c >= 'a' && c <= 'z')
        return c - 'a';
    else if (c >= 'A' && c <= 'Z')
        return c - 'A';

    else return c;
}

/* Esta funcion toma un trie, una frase sin espacios y un puntero a entero
y devuelve la frase totalmente espaciada siguiendo las palabras del diccionario
que esta insertado en el trie, y cambia el valor del puntero a entero a 1 si fue
necesario recuperarse de errores. (En caso de no encontrar ninguna palabra valida
en la frase, se devolvera la string vacia.). */
char* espaciar_frase(TrieNodo* trie, char* frase, int* errores) {

    TrieNodo* raiz = trie;
    int len = strlen(frase);
    int lenActual = 0, k = 0;
    char* fraseEspaciada = malloc(sizeof(char) * len * 2);
    char auxPalabra[len + 1];

    for (int i = 0; i < len; i++) {

        // Este if sirve para ignorar posibles saltos de linea que puedan estar
        // al final de la string.
        if (isalpha(frase[i])) {
            // Guardamos el indice correspondiente
            // a la letra leida y su nodo si existe.
            unsigned idx = get_index(frase[i]);
            TrieNodo* nodoArray = trie->childs[idx];

            // Al encontrar un caracter con el cual no se puede formar
            // ninguna palabra valida, volvemos la iteración hasta
            // el siguiente de ese caracter dependiendo
            // de cuantos caracteres validos leimos antes de encontrar
            // el error.
            if (nodoArray == NULL && !trie->esPalabra) {
                *errores = 1;
                trie = raiz;
                if (k > 0) {
                    i -= k;
                    k = 0;
                }
            }

            // Si encontramos camino..
            else if (nodoArray != NULL) {
                // Llenamos la variable auxiliar y nos movemos
                // por el arbol.
                auxPalabra[k++] = frase[i];
                trie = nodoArray;

                // Si estamos en la ultima iteracion, sabemos que no hay siguiente
                // si no, guardamos los datos del siguiente.
                unsigned idxSiguiente = i < len - 1 ? get_index(frase[i + 1]) : 0;
                TrieNodo* nodoArraySiguiente = i < len - 1 ? trie->childs[idxSiguiente] : NULL;

                // Si nos encontramos en una palabra valida, y el caracter siguiente no continua
                // formando la palabra, la agregamos a la frase final
                // y comenzamos a buscar mas palabras.
                if (trie->esPalabra && nodoArraySiguiente == NULL) {
                    auxPalabra[k] = '\0';
                    strcpy(fraseEspaciada + lenActual, auxPalabra);
                    lenActual += k;
                    fraseEspaciada[lenActual++] = ' ';
                    k = 0;
                    trie = raiz;
                }
                
            }
        }

    }

    // Esto borra el espacio innecesario que se agrega junto con la ultima
    // palabra.
    if (fraseEspaciada[lenActual - 1] == ' ')
        lenActual--;

    // Ajustamos la memoria a la cantidad exacta necesaria.
    fraseEspaciada = realloc(fraseEspaciada, sizeof(char) * (lenActual + 1));
    fraseEspaciada[lenActual] = '\0';

    return fraseEspaciada;
}

/* Esta funcion toma un nombre de un archivo de diccionario
donde cada palabra ocupa una linea diferente y devuelve un trie
con todas las palabras en cada linea del diccionario */
TrieNodo* trie_diccionario(char* nombreDiccionario) {

    TrieNodo* trie = trie_crear_nodo();
    FILE* diccionario = fopen(nombreDiccionario, "r");

    // Si falla fopen, terminamos la ejecución con un mensaje de error.
    if (!diccionario) {
        printf("Error abriendo el diccionario.\n");
        exit(EXIT_FAILURE);
    }

    // Variables aux para getline
    char * linea = NULL;
    size_t len = 0;
    ssize_t cant;

    // Mientras encontremos una linea en el archivo, la insertamos en el trie
    while ((cant = getline(&linea, &len, diccionario)) != -1)
        trie_insertar(trie, linea);
    
    // Liberamos la memoria si fue usada
    if (linea)
        free(linea);
    fclose(diccionario);

    return trie;
}

/* Esta funcion recibe dos nombres de archivos
el primero con las frases sin espaciar y el segundo 
el archivo donde se guardaran las frases espaciadas */
void espaciar_archivo(TrieNodo* trie, char* nombreEntrada, char* nombreSalida) {

    FILE* entrada = fopen(nombreEntrada, "r");
    FILE* salida = fopen(nombreSalida, "w+");

    // Si falla fopen, terminamos la ejecución con un mensaje de error.
    if (!entrada || !salida) {
        printf("Error abriendo el archivo de entrada o de salida.\n");
        exit(EXIT_FAILURE);
    }

    // Variables auxiliares para getline
    char * linea = NULL;
    size_t len = 0;
    ssize_t cant;

    // Mientras leamos una linea en el archivo de entrada, la espaciamos
    // y la agregamos al archivo de salida
    while ((cant = getline(&linea, &len, entrada)) != -1) {
        int errores = 0;
        char* fraseEspaciada = espaciar_frase(trie, linea, &errores);

        char* outputError[2] = {"No se han recuperado errores.", "Se han recuperado errores."};
        char* outputMensaje = errores == 0 ? outputError[0] : outputError[1];

        fprintf(salida, "%s | %s\n", fraseEspaciada, outputMensaje);
        free(fraseEspaciada);
    }
    
    // Liberamos la memoria si fue usada
    if (linea)
        free(linea);
    fclose(entrada);
    fclose(salida);
}