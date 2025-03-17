#include "menu.h"

void imprimir_entero(int dato) {
  printf("%d ", dato);
}

int comparar_enteros(int dato1, int dato2) {

    return dato1 >= dato2 ? 1 : -1;

}

Command getEnumCommand(char* str) {

    Command command = NONE;

    /* Pasamos el comando a todo lowercase */
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }

    if (!strcmp(str, "crear")) command = CREAR;
    else if (!strcmp(str, "destruir")) command = DESTRUIR;
    else if (!strcmp(str, "imprimir")) command = IMPRIMIR;
    else if (!strcmp(str, "agregar_final")) command = AGREGAR_FINAL;
    else if (!strcmp(str, "agregar_inicio")) command = AGREGAR_INICIO;
    else if (!strcmp(str, "agregar_pos")) command = AGREGAR_POS;
    else if (!strcmp(str, "longitud")) command = LONGITUD;
    else if (!strcmp(str, "concatenar")) command = CONCATENAR;
    else if (!strcmp(str, "eliminar")) command = ELIMINAR;
    else if (!strcmp(str, "contiene")) command = CONTIENE;
    else if (!strcmp(str, "indice")) command = INDICE;
    else if (!strcmp(str, "intersecar")) command = INTERSECAR;
    else if (!strcmp(str, "ordenar")) command = ORDENAR;
    else if (!strcmp(str, "reverso")) command = REVERSO;
    else if (!strcmp(str, "salir") || !strcmp(str, "salir\n")) command = SALIR;
    else if (!strcmp(str, "menu") || !strcmp(str, "menu\n")) command = MENU;

    return command;

}

void realizarComando(SList **slistArray, size_t *slistArrayLongitud, Command command, int *args) {

    switch (command) {

        case CREAR:
            *slistArray = realloc(*slistArray, sizeof(SList*) * ((*slistArrayLongitud) + 1));
            SList list = slist_crear();
            (*slistArray)[*slistArrayLongitud] = list;
            printf("\n\tLista %d creada.\n", *slistArrayLongitud);
            (*slistArrayLongitud)++;
            break;

        case DESTRUIR:
            break;

        case IMPRIMIR:
            printf("\n\tImprimiendo lista %d...\n\n", args[0]);
            slist_recorrer((*slistArray)[args[0]], imprimir_entero);
            puts("");
            break;

        case AGREGAR_FINAL:
            (*slistArray)[args[0]] = slist_agregar_final((*slistArray)[args[0]], args[1]);
            printf("\n\t%d agregado al final de la lista %d.\n", args[1], args[0]);
            break;

        case AGREGAR_INICIO:
            (*slistArray)[args[0]] = slist_agregar_inicio((*slistArray)[args[0]], args[1]);
            printf("\n\t%d agregado al inicio de la lista %d.\n", args[1], args[0]);
            break;

        case AGREGAR_POS:;
            int pos = args[2];
            (*slistArray)[args[0]] = slist_insertar((*slistArray)[args[0]], args[1], args[2]);
            printf("\n\t%d agregado a la lista %d en la posicion %d.\n", args[1], args[0], pos);
            break;

        case LONGITUD:
            printf("\nLa longitud de la lista %d es: %d\n", args[0], slist_longitud((*slistArray)[args[0]]));
            break;

        case CONCATENAR:
            (*slistArray)[args[2]] = slist_concatenar((*slistArray)[args[0]], (*slistArray)[args[1]]);
            printf("\n\tlista %d y %d concatenadas en la lista %d.\n", args[0], args[1], args[2]);
            break;

        case ELIMINAR:
            (*slistArray)[args[0]] = slist_eliminar((*slistArray[args[0]]), args[1]);
            printf("\n\telemento en la posicion %d de la lista %d eliminado.\n", args[1], args[0]);
            break;

        case CONTIENE:;
            int contiene = slist_contiene((*slistArray)[args[0]], args[1]);
            char *mensaje = contiene ? "Lo contiene." : "No lo contiene.";
            printf("\n%s\n", mensaje);
            break;

        case INDICE:;
            size_t indice = slist_indice((*slistArray)[args[0]], args[1]);
            if (indice != -1)
                printf("\nEl indice de la primer ocurrencia de %d en la lista %d es: %d\n", args[1], args[0], indice);
            else 
                printf("\nNo se encontro %d en la lista %d.\n", args[1], args[0]);
            break;
        
        case INTERSECAR:
            (*slistArray)[args[2]] = slist_intersecar((*slistArray)[args[0]], (*slistArray)[args[1]]);
            printf("\n\tlista %d y %d intersecadas en la lista %d.\n", args[0], args[1], args[2]);
            break;

        case ORDENAR:
            (*slistArray)[args[0]] = slist_ordenar((*slistArray)[args[0]], comparar_enteros);
            printf("\n\tlista %d ordenada.\n", args[0]);
            break;

        case REVERSO:
            (*slistArray)[args[1]] = slist_reverso((*slistArray)[args[0]]);
            printf("\n\tlista %d reverso en lista %d.\n", args[0], args[1]);
            break;

        case SALIR:
            printf("\n\tSaliendo..\n");
            break;
        
        case MENU:
            break;
        default:
            printf("\nComando invalido.\n"); 
            break;
    }
    

}

int chequearArgs(Command command, size_t slistArrayLongitud, int* args, size_t argsLongitud) {
    
    int resultado = 1;

    switch (command) {

        case CREAR:
            if (argsLongitud != 1 || args[0] < 0 || args[0] < slistArrayLongitud)
                resultado = 0;
            break;

        case DESTRUIR:
            if (argsLongitud != 1 || args[0] < 0 || args[0] >= slistArrayLongitud)
                resultado = 0;
            break;
        
        case IMPRIMIR:
            if (argsLongitud != 1 || args[0] < 0 || args[0] >= slistArrayLongitud)
                resultado = 0;
            break;

        case AGREGAR_FINAL:
            if (argsLongitud != 2 || args[0] < 0 || args[0] >= slistArrayLongitud)
                resultado = 0;
            break;
        
        case AGREGAR_INICIO:
            if (argsLongitud != 2 || args[0] < 0 || args[0] >= slistArrayLongitud)
                resultado = 0;
            break;

        case AGREGAR_POS:
            if (argsLongitud != 3 || args[0] < 0 || args[0] >= slistArrayLongitud || args[2] < 0)
                resultado = 0;
            break;
        
        case LONGITUD:
            if (argsLongitud != 1 || args[0] < 0 || args[0] >= slistArrayLongitud)
                resultado = 0;
            break;
        
        case CONCATENAR:
            if (argsLongitud != 3 || args[0] < 0 || args[0] >= slistArrayLongitud || args[1] < 0 || args[1] >= slistArrayLongitud || args[2] < 0 || args[2] >= slistArrayLongitud)
                resultado = 0;
            break;
        
        case ELIMINAR:
            if (argsLongitud != 2 || args[0] < 0 || args[0] >= slistArrayLongitud || args[1] < 0)
                resultado = 0;
            break;
        
        case CONTIENE:
            if (argsLongitud != 2 || args[0] < 0 || args[0] >= slistArrayLongitud)
                resultado = 0;
            break;
        
        case INDICE:
            if (argsLongitud != 2 || args[0] < 0 || args[0] >= slistArrayLongitud)
                resultado = 0;
            break;

        case INTERSECAR:
            if (argsLongitud != 3 || args[0] < 0 || args[0] >= slistArrayLongitud || args[1] < 0 || args[1] >= slistArrayLongitud || args[2] < 0 || args[2] >= slistArrayLongitud)
                resultado = 0;
            break;
        
        case ORDENAR:
            if (argsLongitud != 1 || args[0] < 0 || args[0] >= slistArrayLongitud)
                resultado = 0;
            break;
        
        case REVERSO:
            if (argsLongitud != 2 || args[0] < 0 || args[0] >= slistArrayLongitud || args[1] < 0 || args[1] >= slistArrayLongitud)
                resultado = 0;
            break;
        
        case MENU:
            displayMenu();
            break;
            
        default:
            break;
    }

    return resultado;
    
}

void displayMenu() {

    printf("\t\t\tOPCIONES\n\n\n");
    printf("COMANDO\t\t\tARGUMENTOS\n\n");
    printf("CREAR\t\t\tint lista\n");
    printf("DESTRUIR\t\tint lista\n");
    printf("IMPRIMIR\t\tint lista\n");
    printf("AGREGAR_FINAL\t\tint lista, int dato\n");
    printf("AGREGAR_INICIO\t\tint lista, int dato\n");
    printf("AGREGAR_POS\t\tint lista, int dato, int pos\n");
    printf("LONGITUD\t\tint lista\n");
    printf("CONCATENAR\t\tint lista1, int lista2, int listaResultado\n");
    printf("ELIMINAR\t\tint lista, int pos\n");
    printf("CONTIENE\t\tint lista, int dato\n");
    printf("INDICE\t\t\tint lista, int dato\n");
    printf("INTERSECAR\t\tint lista1, int lista2, int listaResultado\n");
    printf("ORDENAR\t\t\tint lista\n");
    printf("REVERSO\t\t\tint lista, int listaResultado\n");
    printf("SALIR\t\t\n\n");
}

