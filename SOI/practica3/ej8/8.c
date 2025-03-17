/*
Segun ChatGPT:
Este fragmento implementa una cola concurrente entre dos procesos de manera "lock-free" 
utilizando el algoritmo de Lamport. Funciona sin mutexes ni primitivas de sincronización al 
aprovechar la naturaleza atómica de ciertas operaciones y la consistencia secuencial de la 
memoria garantizada por la arquitectura subyacente y el compilador.

La función diff() calcula la diferencia entre las posiciones de escritura y lectura en la 
cola circular. Esta función garantiza que la cola no se desborde o subdesborde, manteniendo 
siempre un margen de al menos un elemento y no excediendo el tamaño máximo de la cola.

La función prod() es la función de producción, que se ejecuta en el proceso que agrega 
elementos a la cola. Funciona de la siguiente manera:

Espera hasta que haya espacio disponible en la cola (cuando la diferencia entre las posiciones 
de escritura y lectura no sea igual al tamaño de la cola).
Agrega un nuevo elemento al final de la cola circular.
Actualiza la posición de escritura (s) para apuntar al próximo índice de escritura en la cola.
La función cons() es la función de consumo, que se ejecuta en el proceso que lee elementos de 
la cola. Funciona de la siguiente manera:

Espera hasta que haya elementos disponibles en la cola (cuando la diferencia entre las posiciones 
de escritura y lectura no sea cero).
Lee el elemento en la posición actual de lectura (r) de la cola.
Actualiza la posición de lectura (r) para apuntar al próximo índice de lectura en la cola.
Imprime el elemento leído.
Este diseño funciona sin mutexes porque los accesos a las variables compartidas (s, r, buf) son 
atómicos. Es decir, cada operación de escritura o lectura de estas variables se ejecuta en su 
totalidad sin ser interrumpida por otro hilo, lo que evita condiciones de carrera. Además, el 
algoritmo garantiza que no se produzcan desbordamientos o subdesbordamientos de la cola.

Este enfoque se puede generalizar a más de dos procesos. Cada proceso de producción o consumo 
debe verificar si hay suficiente espacio o elementos disponibles en la cola antes de realizar 
la operación correspondiente. Mientras se mantenga la consistencia secuencial y los accesos a 
las variables compartidas sean atómicos, el algoritmo de Lamport seguirá funcionando sin necesidad 
de mutexes o primitivas de sincronización. Sin embargo, a medida que se agregan más procesos, puede 
aumentar la complejidad y la posibilidad de contención, por lo que se debe tener cuidado al diseñar 
el sistema para evitar cuellos de botella y garantizar la correctitud del algoritmo.

SEgun GEMINI:

Explicación del funcionamiento sin mutexes
El código implementa una cola sin bloqueos para dos procesos: un productor y un consumidor. 
La variable s mantiene la cantidad de elementos escritos en la cola, mientras que r indica la 
cantidad de elementos leídos. El valor K se utiliza para limitar el tamaño de la cola y evitar 
que las variables s y r crezcan demasiado.

La clave para que la cola funcione sin mutexes radica en la función diff(). Esta función calcula 
la diferencia entre el número de elementos escritos y leídos, pero lo hace de una manera modular, 
utilizando el valor K. Esto significa que la diferencia siempre estará entre 0 y K-1, 
independientemente del valor real de s y r.

El productor utiliza la función diff() para verificar si hay espacio disponible en la cola antes 
de escribir un nuevo elemento. Si la diferencia es B, significa que la cola está llena y el 
productor debe esperar. Una vez que hay espacio disponible, el productor escribe el elemento en 
la cola y actualiza la variable s.

El consumidor también utiliza la función diff() para verificar si hay elementos disponibles en la 
cola antes de leer uno. Si la diferencia es 0, significa que la cola está vacía y el consumidor 
debe esperar. Una vez que hay un elemento disponible, el consumidor lo lee de la cola y actualiza 
la variable r.

Razones por las que funciona sin mutexes:

Uso de la diferencia modular: La función diff() modula la diferencia entre s y r con K, lo que 
garantiza que la diferencia siempre esté entre 0 y K-1. Esto evita que se produzcan condiciones 
de carrera, ya que ambos procesos siempre tendrán una visión consistente del estado de la cola.
Operaciones atómicas: Las operaciones de lectura y escritura en las variables s y r se realizan 
de forma atómica, lo que significa que se completan en un solo paso sin que puedan ser 
interrumpidas por otro proceso. Esto evita que se produzcan conflictos al actualizar estas variables.
Generalización a n procesos
La cola sin bloqueos puede generalizarse a n procesos modificando la función diff() para 
que tenga en cuenta la cantidad de elementos escritos y leídos por cada proceso. Esto se 
puede lograr utilizando un vector o una matriz para almacenar las variables s y r, donde 
cada posición del vector o matriz corresponde a un proceso diferente. La función diff() entonces 
calcularía la diferencia entre la suma de los valores s de todos los procesos y la suma de los 
valores r de todos los procesos.

Es importante tener en cuenta que la generalización a n procesos puede ser más compleja y 
requerir más cuidado para evitar condiciones de carrera. Sin embargo, el principio básico 
de utilizar una diferencia modular y operaciones atómicas para coordinar el acceso a la cola 
sigue siendo el mismo.
*/

#define B 2
#define K (2 * B)

volatile int s, r, buf[B];
static inline int diff() { 
    return (K + s - r) % K;
}

void * prod(void *_arg) {
    int cur = 0;
    while (1) {
        while (diff() == B);
        buf[s % B] = cur++;
        s = (s + 1) % K;
    }
}

void * cons(void *_arg) {
    int cur;
    while (1) {
        while (diff() == 0);
        cur = buf[r % B];
        r = (r + 1) % K;
        printf("Lei %d\n", cur);
    }
}
