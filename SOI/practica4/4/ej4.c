#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#include "../timing.h"

#define LARGO_ARRAYS 39
#define ITERACIONES 1000

float tiempo_que_consume(int (*funcion)(long), long arr[]);

/**
 * En esta version los procesos empiezan todos desde el menor valor posible e
 * incrementan de a cantidad_de_threads (prioriza divisores bajos)
 */
int es_primo_optimizada_v1(long n) {
    if(n <= 1)
        return 0;
    if(n <= 3)
        return 1;
    if(n % 2 == 0 || n % 3 == 0)
        return 0;

    long nSqrt = sqrtl(n);    
    int esPrimo = 1;

    #pragma omp parallel
    {
        int numThreads = omp_get_num_threads();
        int idThread = (omp_get_thread_num() + 1) * 6 - 1; // 5, 11, 17, 23, ...

        int delta = 6 * numThreads;

        for (long i = idThread; i <= nSqrt && esPrimo; i += delta)
            if(n % i == 0 || n % (i + 2) == 0)
                esPrimo = 0; // break
    }
    return esPrimo;
}

/**
 * En esta version los procesos se reparten el rango en secciones iguales
 * (de [5..nSqrt/cantidad_de_threads] de largo) (prioriza divisores aleatorios)
 */
int es_primo_optimizada_v2(long n) {
    if(n <= 1)
        return 0;
    if(n <= 3)
        return 1;
    if(n % 2 == 0 || n % 3 == 0)
        return 0;

    long nSqrt = sqrtl(n);    
    int esPrimo = 1;

    #pragma omp parallel for
    for (long i = 5; i <= nSqrt; i += 6) {
        if(!esPrimo) continue;
        if(n % i == 0 || n % (i + 2) == 0)
            esPrimo = 0;
    }
    return esPrimo;
}

/**
 * En esta version no se utiliza omp
 */
int es_primo_optimizada_secuencial(long n) {
    if(n <= 1)
        return 0;
    if(n <= 3)
        return 1;
    if(n % 2 == 0 || n % 3 == 0)
        return 0;

    long nSqrt = sqrtl(n);   
    int esPrimo = 1;

    for (int i = 5; i < nSqrt; i += 5) {
        if(n % i == 0 || n % (i + 2) == 0) {
            esPrimo = 0;
            break;
        }
    }
    return esPrimo;
}

/**
 * Esta version es super ineficiente ya que hat threads chequeando pares y 
 * multiplos de 3 constantemente (4 de cada 6 chequeos!!). Incluso, si 
 * los threads son pares, exactamente la mitad solamente está chequeando si 
 * el numero no es primo dividiendolo por un nro par.
 */
int es_primo_v1(long n) {
    if(n <= 1)
        return 0;

    long nSqrt = sqrtl(n);    
    int esPrimo = 1;

    #pragma omp parallel
    {
        int numThreads = omp_get_num_threads();
        int idThread = omp_get_thread_num() + 2; // 2, 3, 4, 5, ...

        for (long i = idThread; i <= nSqrt && esPrimo; i += numThreads)
            if(n % i == 0)
                esPrimo = 0; // break
    }
    return esPrimo;
}

/**
 * Esta es la peor de todas las versiones porque tiene que iterar todas las 
 * veces si o si.
 */
int es_primo_v2(long n) {
    if(n <= 1)
        return 0;

    long nSqrt = sqrtl(n);    
    int esPrimo = 1;

    #pragma omp parallel for
    for (long i = 2; i <= nSqrt; i++) {
        if(!esPrimo) continue; // break inválido en omp for
        if(n % i == 0)
            esPrimo = 0;
    }
    return esPrimo;
}

int main () {
    // Array de primos > 999.999.000
    long arrPrimosChicos[LARGO_ARRAYS] = {999999103, 999999107, 999999113, 999999131, 999999137, \
    999999181, 999999191, 999999193, 999999197, 999999223, 999999229, 999999323, 999999337, \
    999999391, 999999433, 999999487, 999999491, 999999503, 999999527, 999999541, 999999587, \
    999999607, 999999613, 999999667, 999999677, 999999733, 999999739, 999999751, 999999757, \
    999999797, 999999883, 999999893, 999999929, 999999937, 999999163, 999999353, 999999599, \
    999999151, 999999761};
    // Array de primos > 1.900.000.000
    long arrPrimosGrandes[LARGO_ARRAYS] = {1900045463, 1900045471, 1900045501, 1900045513, \
    1900045621, 1900045639, 1900045649, 1900045661, 1900045699, 1900045753, 1900045787, \
    1900045897, 1900045907, 1900045909, 1900045921, 1900045943, 1900045949, 1900045951, \
    1900046051, 1900046081, 1900046087, 1900046101, 1900046129, 1900046147, 1900046167, \
    1900046177, 1900046179, 1900046243, 1900046249, 1900046257, 1900045541, 1900045549, \
    1900045517, 1900045811, 1900045883, 1900045957, 1900046023, 1900046171, 1900046173};
    // Array de Semiprimos: 10000 < lowest divisor
    long arrSemiprimosChicos[LARGO_ARRAYS] = {100140049, 100160063, 100180081, 100440259, 100460273, \
    100680427, 100700549, 100740469, 100741369, 100760483, 100760603, 100761443, 100780621, \
    100860553, 100880711, 100980637, 100982257, 101000651, 101000819, 101002379, 101020837, \
    101060693, 101062553, 101062613, 101080891, 101082691, 101100721, 101120927, 101162923, \
    101183081, 101200999, 101223721, 101283367, 101284087, 100480351, 100781521, 101042479, \
    100460333, 101180777};
    // Array de Semiprimos: 40000 < lowest divisor
    long arrSemiprimosGrandes[LARGO_ARRAYS] = {1900010591, 1900011371, 1900014803, 1900016047, \
    1900022441, 1900024883, 1900026169, 1900026221, 1900031377, 1900031801, 1900033997, \
    1900036207, 1900036937, 1900037099, 1900040239, 1900040587, 1900041191, 1900041713, \
    1900042939, 1900043707, 1900045843, 1900046557, 1900048499, 1900050851, 1900051619, \
    1900053577, 1900054579, 1900055477, 1900058753, 1900059197, 1900019929, 1900020839, \
    1900035563, 1900036027, 1900042223, 1900042379, 1900052191, 1900018079, 1900053131};
    // Array de pares
    long arrPares[LARGO_ARRAYS] = {123456780, 234567892, 345678904, 456789016, 567890128, 678901240, \
    890123464, 901234576, 123456788, 234567900, 345678912, 456789024, 567890136, 678901248, \
    890123472, 901234584, 102345678, 213456790, 324567802, 435678914, 546789026, 657890138, \
    879012362, 990123474, 101234586, 112345698, 223456710, 334567822, 445678934, 556789046, \
    778901270, 889012382, 990123494, 101234506, 112345618, 789012352, 789012360, 768901250,
    667890158};

    float promedio;

    printf("es_primo_optimizada_v1:\n");
    promedio = tiempo_que_consume(es_primo_optimizada_v1, arrPrimosChicos);
    printf("Calcular los Primos > 999.999.000 tarda en promedio:    %f\n", promedio);
    promedio = tiempo_que_consume(es_primo_optimizada_v1, arrPrimosGrandes);
    printf("Calcular los Primos > 1.900.000.000 tarda en promedio:  %f\n", promedio);
    promedio = tiempo_que_consume(es_primo_optimizada_v1, arrSemiprimosChicos);
    printf("Calcular los Semiprimos: lwd > 10000 tarda en promedio: %f\n", promedio);
    promedio = tiempo_que_consume(es_primo_optimizada_v1, arrSemiprimosGrandes);
    printf("Calcular los Semiprimos: lwd > 40000 tarda en promedio: %f\n", promedio);
    promedio = tiempo_que_consume(es_primo_optimizada_v1, arrPares);
    printf("Calcular los Pares tarda en promedio:                   %f\n", promedio);
    puts("");

    printf("es_primo_optimizada_v2:\n");
    promedio = tiempo_que_consume(es_primo_optimizada_v2, arrPrimosChicos);
    printf("Calcular los Primos > 999.999.000 tarda en promedio:    %f\n", promedio);
    promedio = tiempo_que_consume(es_primo_optimizada_v2, arrPrimosGrandes);
    printf("Calcular los Primos > 1.900.000.000 tarda en promedio:  %f\n", promedio);
    promedio = tiempo_que_consume(es_primo_optimizada_v2, arrSemiprimosChicos);
    printf("Calcular los Semiprimos: lwd > 10000 tarda en promedio: %f\n", promedio);
    promedio = tiempo_que_consume(es_primo_optimizada_v2, arrSemiprimosGrandes);
    printf("Calcular los Semiprimos: lwd > 40000 tarda en promedio: %f\n", promedio);
    promedio = tiempo_que_consume(es_primo_optimizada_v2, arrPares);
    printf("Calcular los Pares tarda en promedio:                   %f\n", promedio);
    puts("");

    printf("es_primo_optimizada_secuencial:\n");
    promedio = tiempo_que_consume(es_primo_optimizada_secuencial, arrPrimosChicos);
    printf("Calcular los Primos > 999.999.000 tarda en promedio:    %f\n", promedio);
    promedio = tiempo_que_consume(es_primo_optimizada_secuencial, arrPrimosGrandes);
    printf("Calcular los Primos > 1.900.000.000 tarda en promedio:  %f\n", promedio);
    promedio = tiempo_que_consume(es_primo_optimizada_secuencial, arrSemiprimosChicos);
    printf("Calcular los Semiprimos: lwd > 10000 tarda en promedio: %f\n", promedio);
    promedio = tiempo_que_consume(es_primo_optimizada_secuencial, arrSemiprimosGrandes);
    printf("Calcular los Semiprimos: lwd > 40000 tarda en promedio: %f\n", promedio);
    promedio = tiempo_que_consume(es_primo_optimizada_secuencial, arrPares);
    printf("Calcular los Pares tarda en promedio:                   %f\n", promedio);
    puts("");

    printf("es_primo_v1:\n");
    promedio = tiempo_que_consume(es_primo_v1, arrPrimosChicos);
    printf("Calcular los Primos > 999.999.000 tarda en promedio:    %f\n", promedio);
    promedio = tiempo_que_consume(es_primo_v1, arrPrimosGrandes);
    printf("Calcular los Primos > 1.900.000.000 tarda en promedio:  %f\n", promedio);
    promedio = tiempo_que_consume(es_primo_v1, arrSemiprimosChicos);
    printf("Calcular los Semiprimos: lwd > 10000 tarda en promedio: %f\n", promedio);
    promedio = tiempo_que_consume(es_primo_v1, arrSemiprimosGrandes);
    printf("Calcular los Semiprimos: lwd > 40000 tarda en promedio: %f\n", promedio);
    promedio = tiempo_que_consume(es_primo_v1, arrPares);
    printf("Calcular los Pares tarda en promedio:                   %f\n", promedio);
    puts("");

    printf("es_primo_v2:\n");
    promedio = tiempo_que_consume(es_primo_v2, arrPrimosChicos);
    printf("Calcular los Primos > 999.999.000 tarda en promedio:    %f\n", promedio);
    promedio = tiempo_que_consume(es_primo_v2, arrPrimosGrandes);
    printf("Calcular los Primos > 1.900.000.000 tarda en promedio:  %f\n", promedio);
    promedio = tiempo_que_consume(es_primo_v2, arrSemiprimosChicos);
    printf("Calcular los Semiprimos: lwd > 10000 tarda en promedio: %f\n", promedio);
    promedio = tiempo_que_consume(es_primo_v2, arrSemiprimosGrandes);
    printf("Calcular los Semiprimos: lwd > 40000 tarda en promedio: %f\n", promedio);
    promedio = tiempo_que_consume(es_primo_v2, arrPares);
    printf("Calcular los Pares tarda en promedio:                   %f\n", promedio);
    puts("");

    return 0;
}

float tiempo_que_consume(int (*funcion)(long), long arr[]) {
    float tiempo, promedio = 0.0;
    for (int i = 0; i < LARGO_ARRAYS; i++) {
        TIMEREP(ITERACIONES, funcion(arr[i]), &tiempo);
        promedio += (tiempo/ITERACIONES);
    }
    return promedio /= (float) LARGO_ARRAYS;
}