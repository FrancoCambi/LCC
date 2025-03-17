#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define N_SILLAS 5
#define LIMITE_CLIENTES 100

#define SEGUNDOS_ENTRE_CLIENTES 5
#define SEGUNDOS_DE_CORTE 1
#define SEGUNDOS_DE_PAGO 1
#define SEGUNDOS_DE_ESPERA_BARBERO 1

typedef struct _Semaforos {
    /**
     * Cantidad de sillas disponibles, comienza en N_SILLAS y cada vez que llega un
     * cliente decrece. Solo la hacen crecer los clientes que pueden ingresar, por 
     * lo que no excede N_SILLAS */
    sem_t cantidadSillasDisponibles;

    /**
     * Es el indicador de que el barbero esta dormido. Cuando la sala esta vacia 
     * entonces se pone en wait. Solo lo puede despertar un cliente que cuando 
     * llegue, vea que el barbero esta dormido entonces lo despierta con un post. 
     * Sirve adeamas de para despertar al barbero, como un EQUIVALENTE de 
     * clientesListos, hacen lo mismo, solo que este solo funciona para diferenciar 
     * el hecho de que el "barbero esta dormido".
    */
    sem_t barberoDormido;

    /**
     * Los siguientes son todos utilizados para coordinar las acciones entre el 
     * barbero y el cliente. Funcionan como true o false (0 o 1). */
    
    /**
     * Es la contra parte de cantidadSillasDisponibles (N_SILLAs - cant)
     * Si es 0 no hay clientes por lo que el barbero está durmiendo o va a 
     * dormirse apenas termine de realizar el corte de pelo. Cada vez que el 
     * barbero va a realizar un corte lo intenta decrecer. Y por otro lado, cada 
     * vez que un cliente llega, entonces se incrementa el valor. Sirve como un
     * indicador para saber si alguien se va o puede cortarse el pelo, o de cuanta  
     * gente hay en espera para cortarse el pelo. Unicamente se usa si el barbero 
     * esta/estaba dormido */
    sem_t clientesListos;

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

/**
 * Mutex de la variable estaElBarberoDormido. Ademas tambien funciona como mutex 
 * para saber si la sala esta vacia, asi no ocurre que la sala esta vacia, llega un 
 * cliente y el barbero se va a dormir con un cliente ya en la tienda. Sirve 
 * como separador entre el chequeo de que hay un cliente y que llega un cliente, 
 * asi no ocurre simlutaneamente. Sin esto, existiria un deadlock cuando: 
 * el barbero se va a dormir, pero antes el cliente vio que el barbero no estaba 
 * durmiendo, entonces el barbero se queda esperando que lo despierten y el cliente 
 * se quedaria esperando que el barbero termine de hacer un corte de pelo que no 
 * esta haciendo (pues esta durmiendo). Otro cliente despertaria al barbero despues, 
 * pero llevaria a un comportamiento indefinido. en el ej6x dormir es abstracto por 
 * lo que no existe este problema.
*/
pthread_mutex_t mutexEstaElBarberoDormido = PTHREAD_MUTEX_INITIALIZER;
int estaElBarberoDormido; // 1 si si, 0 si no

void *me_cortan(int idCliente) {
    printf("\t[C] Me estan cortando (Cliente [%d])\n", idCliente); // Concurrente con *cortando*
    return NULL;
}
void* cortando() {
    printf("\t[B] Cortando...\n"); // Concurrente con *me_cortan*
    sleep(random() % SEGUNDOS_DE_CORTE + 1); // TIEMPO DE CORTE
    return NULL;
}

void *me_pagan() {
    printf("\t[B] Me estan pagando.\n"); // Concurrente con *pagando*
    return NULL;
}
void* pagando(int idCliente) {
    printf("\t[C] Pagando... (Cliente [%d])\n", idCliente); // Concurrente con *me_pagan*
    sleep(random() % SEGUNDOS_DE_PAGO + 1); // TIEMPO DE PAGO
    return NULL;
}

int sala_vacia() {
    int cantidadSillasVacias;
    sem_getvalue(&sem.cantidadSillasDisponibles, &cantidadSillasVacias);
    return (N_SILLAS == cantidadSillasVacias);
}
int sala_llena() {
    int cantidadSillasVacias;
    sem_getvalue(&sem.cantidadSillasDisponibles, &cantidadSillasVacias);
    return (0 == cantidadSillasVacias);
}
int barbero_dormido() {
    return estaElBarberoDormido;
}

void * barbero(void * arg) {
    while(1) {
        pthread_mutex_lock(&mutexEstaElBarberoDormido);
        if(sala_vacia()) {
            printf("[B] Nadie en la sala, el barbero se va a dormir\n\n");
            estaElBarberoDormido = 1;
            pthread_mutex_unlock(&mutexEstaElBarberoDormido);
            sem_wait(&sem.barberoDormido);
            printf("[B] Me despertaron!\n");
        }
        else {
            pthread_mutex_unlock(&mutexEstaElBarberoDormido);
            sem_wait(&sem.clientesListos); // Espera a que el cliente, le de el OK
        }
        
        printf("[B] Hay un cliente listo y disponible para atender, le aviso y comenzamos YA.\n");

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
        sleep(random() % SEGUNDOS_DE_ESPERA_BARBERO + 1);
    }
    
    return NULL;
}

void * cliente(void * arg) {
    int idCliente = arg - (void*)0;
    pthread_mutex_lock(&mutexEstaElBarberoDormido);
    printf("[C] NUEVO CLIENTE! [%d] - ", idCliente);
    if(sala_llena()) {
        printf("No hay lugar, se va\n");
        pthread_mutex_unlock(&mutexEstaElBarberoDormido);
        return NULL;
    }
    if(sala_vacia() && barbero_dormido()) {
        printf("Hay lugar pero el barbero esta dormido! Le despierto y vamos directo a cortar\n"); // Sin ocupar silla
        estaElBarberoDormido = 0;
        sem_post(&sem.barberoDormido);
        pthread_mutex_unlock(&mutexEstaElBarberoDormido);
        sem_wait(&sem.puedoAtender);
    }
    else {
        if (sem_trywait(&sem.cantidadSillasDisponibles)) {
            perror("Nunca deberia pasar, ya que la sala no esta llena");
            exit(EXIT_FAILURE);
        }
        pthread_mutex_unlock(&mutexEstaElBarberoDormido);
        // Cuando el este listo me dice y me atiende
        printf("Hay lugar, se sentó en una silla. Le hace saber al barbero\n"); 
        sem_post(&sem.clientesListos);

        sem_wait(&sem.puedoAtender);
        /**
         * Apenas me atienden, me paro por lo que libero una silla de la sala de 
         * espera. Esto implica que puede haber simultaneamente hasta N_SILLAS + 1 
         * personas en la tienda: las que esperan y la que esta siendo atendida.
        */
        sem_post(&sem.cantidadSillasDisponibles); // libero la silla.
    }

    me_cortan(idCliente);

    sem_post(&sem.finCorteDePelo);
    sem_wait(&sem.comienzoPago);

    pagando(idCliente);

    printf("[C] Me cortaron el pelo genial (Cliente [%d]), me voy\n\n", idCliente);
    sem_post(&sem.finSesionCompletada); // Una vez le paga ya no coordinan acciones

    return NULL;
}

void inicializar_sem() {
    sem_init(&sem.cantidadSillasDisponibles ,0, N_SILLAS);
    sem_init(&sem.barberoDormido, 0, 0);
    sem_init(&sem.clientesListos, 0, 0);
    sem_init(&sem.puedoAtender, 0, 0);
    sem_init(&sem.finSesionCompletada, 0, 0);
    sem_init(&sem.finCorteDePelo, 0, 0);
    sem_init(&sem.comienzoPago, 0, 0);
}

int main() {

    inicializar_sem();
    estaElBarberoDormido = 0;

    pthread_t barberoPthread, clientePthread;
    pthread_create(&barberoPthread, NULL, barbero, NULL);

    for(int i = 0; i < LIMITE_CLIENTES; i++) {
        sleep(random() % SEGUNDOS_ENTRE_CLIENTES + 1);

        pthread_create(&clientePthread, NULL, cliente, i + (void*)0);
    }

    pthread_join(barberoPthread, NULL);

    return 0;
}