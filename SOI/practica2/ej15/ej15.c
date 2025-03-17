#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <pthread.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include "list.h"

#define NUM_THREADS 4
#define MAX_EVENTS 5

SList list = NULL; // slist_crear()
pthread_mutex_t mutexList = PTHREAD_MUTEX_INITIALIZER;

/*
* Para probar, usar netcat. Ej:
*
*   $ nc localhost 3942
*
*   PUT k v
*   GET k
*   DEL k
*
*   Empty line for leaving
*/

void quit(char *s) {
	perror(s);
	abort();
}

int fd_readline(int fd, char *buf) {
	int rc;
	int i = 0;

	/*
	* Leemos de a un caracter (no muy eficiente...) hasta
	* completar una línea.
	*/
	while ((rc = read(fd, buf + i, 1)) > 0) {
		if (buf[i] == '\n')
			break;
		i++;
	}

	if (rc < 0)
		return rc;

	buf[i] = 0;
	return i;
}

void print_msg(int sock, char * msg) {
    write(sock, msg, strlen(msg) + 1);
}

void * handle_conn(void * csockPointer) {
	int csock = *(int *) csockPointer;
    
	char buf[255];
	int rc; // read(ed) characters
    char * command; // comando
    char * k; // key
    char * v; // value

    rc = fd_readline(csock, buf);
    if (rc < 0)
        quit("fd_readline");

    if (rc == 0) {
        /* linea vacia, se cerró la conexión: SI NO PONE NADA CORTA LA CONEX*/
        close(csock);
        return NULL;
    }

    command = strtok(buf, " ");
    k = strtok(NULL, " ");
    v = strtok(NULL, " ");

	pthread_mutex_lock(&mutexList); // lock list
    
    if(!command || !k || strtok(NULL, " ")) // si comomand es NULL, k es NULL o HAY MAS COSAS
        print_msg(csock, "EINVAL\n");
    else if(!strcmp(command, "PUT") && v) {
        list = slist_borrar_par(list, k);
        list = slist_agregar_inicio(list, k, v);
        print_msg(csock, "OK\n");
    }
    else if(!strcmp(command, "DEL") && !v) {
        list = slist_borrar_par(list, k);
        print_msg(csock, "OK\n"); // exista o no imprime OK igual
    }
    else if(!strcmp(command, "GET") && !v) {
        v = slist_buscar(list, k);
        if(v) {
            print_msg(csock, "OK ");
            print_msg(csock, v);
            print_msg(csock, "\n");
        }
        else
            print_msg(csock, "NOTFOUND\n");
    }
    else 
        print_msg(csock, "EINVAL\n");
	
    pthread_mutex_unlock(&mutexList); // unlock list

    return NULL;
}

void * wait_for_clients(void * lsockPointer) {
    int lsock = *(int *)lsockPointer;

    int csock;

    int epfd; // epoll file descriptor
    epfd = epoll_create1(0);
    if (epfd == -1)
        quit("epoll_create1");

    struct epoll_event ev; // que queremos que haga el epfd?
    ev.events = EPOLLIN; // que escuche
    ev.data.fd = lsock; // aca
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, lsock, &ev) == -1) // lo agregamos
        quit("epoll_ctl: lsock");

    int nfds; // number of file descriptors
    struct epoll_event events[MAX_EVENTS]; // array of info about every fd
    while(1) {
        nfds = epoll_wait(epfd, events, MAX_EVENTS, -1); // espera algo desde epfd y la guarda en events
        if (nfds == -1)
            quit("epoll_wait");

        for (int n = 0; n < nfds; n++) { // los recorre todos
            if (events[n].data.fd == lsock) { // si es new connection
                csock = accept(lsock, NULL, NULL);
                if (csock == -1)
                    quit("accept");

                ev.events = EPOLLIN | EPOLLOUT; // para leer y escribir
                ev.data.fd = csock;
                if (epoll_ctl(epfd, EPOLL_CTL_ADD, csock, &ev) == -1)
                    quit("epoll_ctl: csock");
            }
            else // si ya existian
                handle_conn((void *)&events[n].data.fd);
        }
    }
}

/* Crea un socket de escucha en puerto 3942 TCP */
int mk_lsock() {
	struct sockaddr_in sa;
	int lsock;
	int rc;
	int yes = 1;

	/* Crear socket */
	lsock = socket(AF_INET, SOCK_STREAM, 0);
	if (lsock < 0)
		quit("socket");

	/* Setear opción reuseaddr... normalmente no es necesario */
	if (setsockopt(lsock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == 1)
		quit("setsockopt");

	sa.sin_family = AF_INET;
	sa.sin_port = htons(3942);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	/* Bindear al puerto 3942 TCP, en todas las direcciones disponibles */
	rc = bind(lsock, (struct sockaddr *)&sa, sizeof sa);
	if (rc < 0)
		quit("bind");

	/* Setear en modo escucha */
	rc = listen(lsock, 10);
    if (rc < 0)
		quit("listen");

	return lsock;
}

void sigint_handler(int sig) {
    printf("\nSure you want to leave? y/n\n");
    
    fflush(stdout);
    char c;
    scanf(" %c", &c);

    if(c == 'y' || c == 'Y') {
        printf("Leaving...\n");
        exit(0);
    }
    printf("Staying...\n");
}

int main() {

	int lsock;
	lsock = mk_lsock();

    // list = slist_create();

    printf("Creating threads...\n");
    pthread_t threads[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; i++) {
        printf("Thread %d is listening...\n", i + 1);
        pthread_create(&threads[i], NULL, wait_for_clients, (void *)&lsock);
    }


    signal(SIGINT, sigint_handler);
    while(1)
        pause();

    return 0;
}
