#include<stdio.h>
#include<string.h>
#include<stdlib.h>


/// @brief Concatena las n cadenas del arreglo arreglo_strings, separandolos por la cadena sep y almacenandolos en res.
/// @param arreglo_strings arreglo de strings a concatenar
/// @param n longitud de arreglo_strings
/// @param sep separador entre strings al concatenar
/// @param res almacenamiento de la string final
void string_unir(char *arreglo_strings[], int n, char *sep, char *res);

/// @brief Concatena las n cadenas del arreglo arreglo_strings, separandolos por la cadena sep y almacenandolos en res.
/// @param arreglo_strings arreglo de strings a concatenar
/// @param n longitud de arreglo_strings
/// @param sep separador entre strings al concatenar
/// @param res almacenamiento de la string final
void string_unir_mejor(char *arreglo_strings[], int n, char *sep, char *res);

int main(void) {

    char res[255];
    char *arreglo_strings[11] = {"hola", "que", "hace", "hace", "hace", "hace", "hace", "hace", "hace", "hace", "hace"};
    int n = 11;
    char *sep = " ";

    string_unir_mejor(arreglo_strings, n, sep, res);

    printf("%s\n", res);

    return 0;
}

void string_unir(char *arreglo_strings[], int n, char *sep, char *res) {

    int operaciones = 0;

    int index = 0; // Index para ir concatenando en res
    for (int i = 0; i < n; i++) {
        // Agregamos la siguiente palabra
        for (int j = 0; j < strlen(arreglo_strings[i]); j++) {
            res[index] = arreglo_strings[i][j];
            index++;
            operaciones++;
        }
        // Agregamos el separador
        for (int z = 0; z < strlen(sep); z++) {
            res[index] = sep[z];
            index++;
            operaciones++;
        }
        
        
    }
    // Agregamos el barra cero antes de la colocacion del ultimo separador, el cual no es correcto
    res[index - strlen(sep)] = '\0';
    operaciones++;

    printf("Operaciones: %d\n", operaciones);
}

void string_unir_mejor(char *arreglo_strings[], int n, char *sep, char *res) {

    int index = 0, operaciones = 0;

    for (int i = 0; i < n; i++) {
        strcpy(res + index, arreglo_strings[i]);
        index += strlen(arreglo_strings[i]);
        operaciones++;
        
        if (i < n - 1) {
            strcpy(res + index, sep);
            index += strlen(sep);
            operaciones++;
        }
    }

    res[index] = '\0';
    operaciones++;

    printf("Operaciones: %d\n", operaciones);
}