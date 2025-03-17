#ifndef __TRIE_H__
#define __TRIE_H__

#define TAMANIO 26

typedef struct _TrieNodo {

    struct _TrieNodo* childs[TAMANIO];

    // Es true si el nodo es el final de una palabra
    // valida.
    int esPalabra;

}TrieNodo;

/* Devuelve un nuevo nodo del trie */
TrieNodo* trie_crear_nodo();

/* Destruye el trie */
void trie_destruir(TrieNodo*);

/* Inserta una palabra en el trie */
void trie_insertar(TrieNodo*, const char*);

#endif /* __TRIE_H__ */