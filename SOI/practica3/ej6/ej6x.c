/**
 * En esta version se entiende al hecho de estar dormido como una situacion 
 * abstracta. Lo cual reduce la cantidad de semáforos y es un poco mas simple
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define N_SILLAS 5
#define LIMITE_CLIENTES 100

#define SEGUNDOS_ENTRE_CLIENTES 5
#define SEGUNDOS_DE_CORTE 2
#define SEGUNDOS_DE_PAGO 2

typedef struct _Semaforos {
    /**
     * Cantidad de sillas disponibles, comienza en N_SILLAS y cada vez que llega un
     * cliente decrece. Solo la hacen crecer los clientes que pueden ingresar, por 
     * lo que no excede N_SILLAS */
    sem_t cantidadSillasDisponibles;

    /**
     * Si es 0 no hay clientes por lo que el barbero está durmiendo o va a 
     * dormirse apenas termine de realizar el corte de pelo. Cada vez que el 
     * barbero va a realizar un corte lo intenta decrecer. Y por otro lado, cada 
     * vez que un cliente llega, entonces se incrementa el valor. Sirve como un
     * indicador para saber si alguien se va o puede cortarse el pelo, o de cuanta  
     * gente hay en espera para cortarse el pelo. */
    sem_t clientesListos;

    /**
     * Los siguientes son todos utilizados para coordinar las acciones entre el 
     * barbero y el cliente. Funcionan como true o false (0 o 1). */

    // El barbero le comunica al cliente que empieza a cortarle
    sem_t puedoAtender;

    // El cliente le avisa al barbero que ya termino de cortarle el pelo
    sem_t finCorteDePelo;

    // El barbero le dice al cliente que empieze a pagar
    sem_t comienzoPago;

    // Termino TODO (de pagar) el cliente le avisa al barbero que se va a casa
    sem_t finSesionCompletada;
} Semaforos;

Semaforos sem;

void *me_cortan(int idCliente) {
    printf("\tMe estan cortando (Cliente [%d])\n", idCliente); // Concurrente con *cortando*
    return NULL;
}
void* cortando() {
    printf("\tCortando...\n"); // [Concurrente con *me_cortan*
    sleep(random() % SEGUNDOS_DE_CORTE + 1); // TIEMPO DE CORTE
    return NULL;
}

void *me_pagan() {
    printf("\tMe estan pagando.\n"); // Concurrente con *pagando*
    return NULL;
}
void* pagando(int idCliente) {
    printf("\tPagando... (Cliente [%d])\n", idCliente); // Concurrente con *me_pagan*
    sleep(random() % SEGUNDOS_DE_PAGO + 1); // TIEMPO DE PAGO
    return NULL;
}

int sala_vacia() {
    int cantidadClientes;
    sem_getvalue(&sem.cantidadSillasDisponibles, &cantidadClientes);
    return !(N_SILLAS - cantidadClientes);
}
void * barbero(void * arg) {
    int dormido = 0;
    while(1) {
        if(sala_vacia()) {
            printf("Nadie en la sala, el barbero se va a dormir\n");
            dormido = 1;
            /* No importa si el wait nunca se bloquea porque JUSTO entre
             * esta linea y la de abajo llego alguien. La gracia es que por un 
             * momento no habia nadie y se durmio de forma abstracta, porque 
             * la idea es que siempre intenta dormirse haya o no alguien en la
             * sala. Se entiende por dormir a la accion de esperar sin consumir
             * CPU */
        }
        sem_wait(&sem.clientesListos); // Espera a que haya alguien listo para ser atendido
        if(dormido) {
            dormido = 0;
            printf("El barbero se ha despertado\n");
        }
        
        printf("Hay un cliente listo y disponible para atender, le aviso y comenzamos YA.\n");

        /* Podria ocurrir que JUSTO un cliente mas nuevo se meta de prepo en
         * la linea de codigo antes del wait del primer cliente (no dentro de
         * la cola del wait, que si se respeta, sino del codigo) lo que causaria
         * que el segundo se corte antes, pero la realidad es que el separador 
         * es sempuedoAtender.*/

        sem_post(&sem.puedoAtender);

        cortando();
        
        sem_wait(&sem.finCorteDePelo);
        sem_post(&sem.comienzoPago);

        me_pagan();

        sem_wait(&sem.finSesionCompletada);
    }
    
    return NULL;
}

void * cliente(void * arg) {
    int idCliente = arg - (void*)0;
    printf("NUEVO CLIENTE! [%d] - ", idCliente);
    if (sem_trywait(&sem.cantidadSillasDisponibles)) {
        printf("No hay lugar, se va\n");
        return NULL;
    }
    printf("Hay lugar, se sentó en una silla. Le hace saber al barbero\n");
    sem_post(&sem.clientesListos);
    sem_wait(&sem.puedoAtender);

    /**
     * Apenas me atienden, me paro por lo que libero una silla de la sala de 
     * espera. Esto implica que puede haber simultaneamente hasta N_SILLAS + 1 
     * personas en la tienda: las que esperan y la que esta siendo atendida.
    */
    sem_post(&sem.cantidadSillasDisponibles); // libero la silla.

    me_cortan(idCliente);

    sem_post(&sem.finCorteDePelo);
    sem_wait(&sem.comienzoPago);

    pagando(idCliente);

    sem_post(&sem.finSesionCompletada); // Una vez le paga ya no coordinan acciones
    printf("Me cortaron el pelo genial (Cliente [%d]), me voy\n", idCliente);

    return NULL;
}

void inicializar_sem() {
    sem_init(&sem.cantidadSillasDisponibles ,0, N_SILLAS);
    sem_init(&sem.clientesListos, 0, 0);
    sem_init(&sem.puedoAtender, 0, 0);
    sem_init(&sem.finSesionCompletada, 0, 0);
    sem_init(&sem.finCorteDePelo, 0, 0);
    sem_init(&sem.comienzoPago, 0, 0);
}

int main() {

    inicializar_sem();

    pthread_t barberoPthread;
    pthread_create(&barberoPthread, NULL, barbero, NULL);

    for(int i = 0; i < LIMITE_CLIENTES; i++) {
        pthread_t clientePthread;
        pthread_create(&clientePthread, NULL, cliente, i + (void*)0);
        
        sleep(random() % SEGUNDOS_ENTRE_CLIENTES + 1);
    }

    pthread_join(barberoPthread, NULL);

    return 0;
}