# TP Final Estructuras de Datos y Algoritmos I. 
# Franco Cambiaso.

# Analizador sintáctico rudimentario.

Este programa recibe 3 nombres de archivos por el método main. Un diccionario de palabras, un archivo de entrada y un archivo de salida.

-> El diccionario debe tener palabras solo conteniendo letras minúsculas y mayúsculas separadas por una nueva línea.\
-> El archivo de entrada debe tener frases solo conteniendo letras minúsculas y mayúsculas separadas por una nueva línea.\
-> Si el archivo de salida no existe, se creará otro. En caso de existir, se borrará su contenido para luego usarse.

Como primera medida, el programa almacena todas las palabras del diccionario. Estas palabras son las que se considerarán válidas para el análisis de las frases. (Las palabras no se distinguen entre maýusculas y minúsculas.)
Luego, por cada frase del archivo de entrada, encuentra las posiciones de los espacios necesarios para que la frase este compuesta de todas palabras válidas y guarda la frase espaciada en una nueva línea del archivo de salida. Indicando a su vez, si el programa detectó letras que no llevaban a la composición de ninguna palabra válida y tuvo que recuperarse de las mismas.
En caso de que una frase no contenga ninguna palabra válida, se le correspondrá la string vacía.

# DETALLES DE LA IMPLEMENTACIÓN.

El diccionario se almacena en una estructura llamada `Trie`.

La implementación de Trie que se propone en este programa es: un arbol cuyos nodos contienen un `array de nodos` de longitud 26 donde cada nodo representa un hijo del nodo que los contiene, y un entero que será igual a 1 si el mismo corresponde a la terminación de una palabra válida de nuestro diccionario o 0 en caso contrario.
Cada hijo de un nodo representa una posible letra de nuestro alfabeto según la posición que ocupe en el array.

Se decidió usar Trie por su velocidad en la inserción y búsqueda de palabras ya que ambos cuestan O(N) donde N es la longitud de la palabra.

Luego de insertar todo el diccionario, a medida que se va leyendo el archivo de entrada, se van guardando los resultados en el archivo de salida.

Para espaciar una frase, se itera por la misma buscando palabras contenidas en el Trie y salteando carácteres que no lleven a nada. Una vez se encuentra una palabra válida la cual no puede ser maximizada, se agrega la misma y un espacio a una nueva string que será el resultado del algoritmo.
Como solo debemos calcular la longitud e iterar por la frase, la complejidad de tiempo para espaciar una palabra es O(2N) donde N es la longitud de la frase.

# DETALLES DE EJECUCIÓN. 

Primero compilamos haciendo uso del makefile.

$ make\
o\
$ make all

Esto nos creará dos ejecutables, `programa` y `tests`.

El primero correrá el programa y el segundo los tests.

$ ./programa `NombreDiccionario` `NombreEntrada` `NombreSalida`

IMPORTANTE: Los nombres deberán incluir la extensión .txt para el funcionamiento correcto del programa.

$ ./tests
