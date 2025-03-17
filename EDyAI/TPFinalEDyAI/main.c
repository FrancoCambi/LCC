#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    if (argc < 4) {
        printf("ERROR! Faltan argumentos.\n");
        exit(EXIT_FAILURE);
    }

    char* nombreDiccionario = argv[1];
    char* nombreEntrada = argv[2];
    char* nombreSalida = argv[3];

    // TESTS
    //test_get_index();
    //test_espaciar_frase();

    TrieNodo* trie = trie_diccionario(nombreDiccionario);
    espaciar_archivo(trie, nombreEntrada, nombreSalida);

    trie_destruir(trie);
    return 0;
    
}


