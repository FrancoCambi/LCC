# Grupo10
---
## Práctica 1

### Dar dos razones de por qué los caches son útiles. ¿Qué problemas resuleven? ¿Qué problemas causan?

Los caches son utiles pues:

+ **Mejoran el rendimiento:** Los caches almacenan datos en un lugar al que se puede acceder muy rapidamente y no es necesario ir a la fuente original de los datos cada vez que se los solicitan.
+ **Reduce el uso de los demas recursos de almacenamiento:** Al almacenar datos en un cache, se reduce la carga en los recursos subyacentes, como el disco duro o la red. Esto es especialmente útil en entornos donde la velocidad de acceso a los datos es crítica y donde la fuente de datos subyacente puede ser costosa en términos de tiempo o recursos.

En general, los caches resuelven problemas de rendimiento.

+ El almacenamiento en caché de base de datos le permite aumentar drásticamente el rendimiento y reducir la latencia del recuperación de datos asociada a las bases de datos de backend, lo que, como resultado, mejora el rendimiento general de las aplicaciones.

Pueden causar problemas: 

+ **Consistencia de los datos:** Si los datos en la fuente original cambian, es posible que los datos en el cache no se actualicen inmediatamente, lo que puede provocar inconsistencias.
+ **Uso ineficiente de la memoria:** Si el cache almacena una gran cantidad de datos que rara vez se utilizan, puede llevar a un uso ineficiente de la memoria, ya que estos datos ocupan espacio en el cache que podría ser utilizado para almacenar datos más útiles.
---
## Práctica 2

### Mini guía de estilo.
+ **Nombre Variables**: camelCase.
+ **Nombre Funciones**: underscores minúsculas.
+ **Indexación (Sangría)**: 4 Espacios.
+ **Nombre Constantes**: underscore mayúsculas.
+ **Esqueleto de función**:  Las variables y los operadores de una expresión deben estar separados por un elemento en blanco. Las lista de definición de variables, y las listas de parámetros de una función se deben separar por un espacio en blanco. La llave de apertura va en la misma línea que el paréntesis de cierre.
+ Ejemplo:
```
    #define BUFF_SIZE 255
    for(int i = 0; i < numberOfArrays; i++) {
        function_name(var1, var2, *(int *) &var3);
    }
```