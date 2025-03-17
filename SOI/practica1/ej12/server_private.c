#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include <sys/mman.h>

#include "list.h"

/*
 * Para probar, usar netcat. Ej:
 *
 *      $ nc localhost 3942
 *      NUEVO
 *      0
 *      NUEVO
 *      1
 *      CHAU
 */

void quit(char *s)
{
	perror(s);
	abort();
}

int fd_readline(int fd, char *buf)
{
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

void imprimir_msg(int sock, char * msg) {
  write(sock, msg, strlen(msg) + 1);
}

void handle_conn(int csock)
{
	char buf[200];
	int rc;
  SList lista = slist_crear();
  char * command;
  char * k;
  char * v;

	while (1) {
		/* Atendemos pedidos, uno por linea */
		rc = fd_readline(csock, buf);
		if (rc < 0)
			quit("read... raro");

		if (rc == 0) {
			/* linea vacia, se cerró la conexión */
      slist_destruir(lista);
			close(csock);
			return;
		}

    command = strtok(buf, " ");
    k = strtok(NULL, " ");
    v = strtok(NULL, " ");

    if(!command || !k || strtok(NULL, " ")) { //si comomand es NULL, k es NULL o HAY MAS COSAS
      imprimir_msg(csock, "EINVAL\n");
    }
    else if(!strcmp(command, "PUT") && v) {
      lista = slist_borrar_par(lista, k);
      lista = slist_agregar_inicio(lista, k, v);
      imprimir_msg(csock, "OK\n");
    }
    else if(!strcmp(command, "DEL")) {
      lista = slist_borrar_par(lista, k);
      imprimir_msg(csock, "OK\n");
    }
    else if(!strcmp(command, "GET")) {
      v = slist_buscar(lista, k);
      if(v) {
        imprimir_msg(csock, "OK ");
        imprimir_msg(csock, v);
        imprimir_msg(csock, "\n");
      }
      else
        imprimir_msg(csock, "NOTFOUND\n");
    }
    else 
      imprimir_msg(csock, "EINVAL\n");
    /*
		if (!strcmp(buf, "NUEVO")) {
			char reply[20];
			sprintf(reply, "%d\n", lista);
			(lista)++;
			write(csock, reply, strlen(reply));
		} else if (!strcmp(buf, "CHAU")) {
			close(csock);
			return;
		}*/
	}
}

void wait_for_clients(int lsock)
{
	int csock;

	/* Esperamos una conexión, no nos interesa de donde viene */
	csock = accept(lsock, NULL, NULL);
	if (csock < 0)
		quit("accept");

  if(!fork()) { //CHILD
    /* Atendemos al cliente */
    handle_conn(csock);

  }
  else { //PARENT
    /* Volvemos a esperar conexiones */
    wait_for_clients(lsock);
  }
}

/* Crea un socket de escucha en puerto 3942 TCP */
int mk_lsock()
{
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

int main()
{
	int lsock;
	lsock = mk_lsock();
	wait_for_clients(lsock);

}
