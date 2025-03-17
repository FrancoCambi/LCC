#include "tests.h"
#include "trie.h"
#include<stdlib.h>
#include <assert.h>
#include<stdio.h>
#include<string.h>

/* Testeo de la funcion get_index */
void test_get_index() {

    assert(get_index('a') == 0);
    assert(get_index('b') == 1);
    assert(get_index('y') == 24);
    assert(get_index('z') == 25);
    assert(get_index('A') == 0);
    assert(get_index('B') == 1);
    assert(get_index('Y') == 24);
    assert(get_index('Z') == 25);

    printf("Get Index Test Passed!\n");
}

/* Testeo de la función espaciar_frase */
void test_espaciar_frase() {

    int errores = 0;

    TrieNodo* trie = trie_crear_nodo();

    trie_insertar(trie, "quien");
    trie_insertar(trie, "deposito");
    trie_insertar(trie, "dolares");
    trie_insertar(trie, "recibira");
    trie_insertar(trie, "es");
    trie_insertar(trie, "en");
    trie_insertar(trie, "dolar");
    trie_insertar(trie, "franco");
    trie_insertar(trie, "cambiaso");

    char* frase;

    frase = espaciar_frase(trie, "quiendepositodolaresrecibiradolares", &errores);
    assert(!strcmp(frase, "quien deposito dolares recibira dolares"));
    free(frase);

    frase = espaciar_frase(trie, "quienxxderdepositozzzdolaresrecibiradolareszz", &errores);
    assert(!strcmp(frase, "quien deposito dolares recibira dolares"));
    free(frase);

    printf("Espaciar Frase Test Passed!\n");
    trie_destruir(trie);

}