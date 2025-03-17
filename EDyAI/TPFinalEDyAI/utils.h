#ifndef __UTILS_H__
#define __UTILS_H__
#include "trie.h"

// Recibe un char y devuelve su indice en el intervalo
// [0,25] (los caracteres no se distinguen entre minuscula y mayuscula)
unsigned get_index(char);

/* Esta funcion toma un trie, una frase sin espacios y un puntero a entero
y devuelve la frase totalmente espaciada siguiendo las palabras del diccionario
que esta insertado en el trie, y cambia el valor del puntero a entero a 1 si fue
necesario recuperarse de errores*/
char* espaciar_frase(TrieNodo* trie, char* frase, int* errores);

/* Esta funcion toma un nombre de un archivo de diccionario
donde cada palabra ocupa una linea diferente y devuelve un trie
con todas las palabras en cada linea del diccionario */
TrieNodo* trie_diccionario(char*);

/* Esta funcion recibe un trie y dos nombres de archivos.
El primero con las frases sin espaciar y el segundo 
el archivo donde se guardaran las frases espaciadas*/
void espaciar_archivo(TrieNodo*, char*, char*);

#endif /* __UTILS_H__ */