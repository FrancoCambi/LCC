#include "slist.h"
#include "menu.h"

int main(void) {

  SList* slistArray = NULL;
  size_t slistArrrayLongitud = 0;
  int *args;
  int argsSize;
  char *token;
  char *comando;
  char *fullStringComando;
  size_t characters;
  size_t len = 32;
  Command comandoEnum;

  system("cls");
  displayMenu();

  do {
    
    args = NULL;
    fullStringComando = NULL;
    argsSize = 0;

    characters = getline(&fullStringComando, &len, stdin);
    token = strtok(fullStringComando, " ");
    comando = token;

    while (token = strtok(NULL, " ")) {
      args = realloc(args, sizeof(int) * (argsSize + 1));
      args[argsSize] = atoi(token);
      argsSize++;
    }

    comandoEnum = getEnumCommand(comando);

    if (chequearArgs(comandoEnum, slistArrrayLongitud, args, argsSize)) {
      realizarComando(&slistArray, &slistArrrayLongitud, comandoEnum, args);
    }
    else {
      printf("\nArgumentos invalidos.\n");
    }

    puts("");

  } while(comandoEnum != SALIR);
 


  return 0;
}

