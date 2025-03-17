#include "trie.h"
#include "utils.h"
#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<stddef.h>

/* Devuelve un nuevo nodo del trie */
TrieNodo* trie_crear_nodo() {
    
    TrieNodo* trie = malloc(sizeof(struct _TrieNodo));

    // Malloc falla.
    if (!trie)
        return NULL;
    
    trie->esPalabra = 0;

    // Llenamos el array de NULL para identificar que
    // esa casilla no se encuentra ocupada.
    for (int i = 0; i < TAMANIO; i++)
        trie->childs[i] = NULL;

    return trie;
}

/* Destruye el trie */
void trie_destruir(TrieNodo* trie) {

    for (int i = 0; i < TAMANIO; i++) {
        
        // Destruimos recursivamente cada sub-arbol
        // en caso de existir.
        if (trie->childs[i] != NULL)
            trie_destruir(trie->childs[i]);
    }

    // Liberamos la memoria del nodo
    free(trie);
}

/* Inserta una palabra en el trie */
void trie_insertar(TrieNodo* trie, const char* palabra) {

    TrieNodo* aux = trie;

    for (int i = 0; palabra[i] != '\0'; i++) {

        // Este if sirve para ignorar posibles saltos de linea que puedan estar
        // al final de la string.
        if (isalpha(palabra[i])) {
            unsigned idx = get_index(palabra[i]);

            // Si la casilla esta desocupada,
            // creamos un nodo en la posicion correspondiente
            // de la letra
            if (aux->childs[idx] == NULL)   
                aux->childs[idx] = trie_crear_nodo();
            
            aux = aux->childs[idx];
        }

    }

    // Al final si hubo una palabra valida para agregar, 
    // aux se parara en el nodo correspondiente a 
    // la ultima letra de nuestra palabra insertada
    // por lo tanto, seteamos esPalabra en true.
    if (aux != trie)
        aux->esPalabra = 1;
}