#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 12343

typedef struct {
    int socket;
    int counter;
} client_info_t;

int pid_counter = 0;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void* counter_handler(void* arg) {
    client_info_t* client_info = (client_info_t*) arg;
    int client_socket = client_info->socket;
    int counter;

    pthread_mutex_lock(&counter_mutex);
    counter = pid_counter++;
    pthread_mutex_unlock(&counter_mutex);

    char buffer[1024];
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            printf("Se ha desconectado el cliente: %d\n", client_socket);
            close(client_socket);
            break;
        }
        buffer[bytes_received] = '\0';

        if (strcmp(buffer, "NUEVO\n") == 0) {
            sprintf(buffer, "%d\n", counter);
            send(client_socket, buffer, strlen(buffer), 0);
        } else if (strcmp(buffer, "CHAU\n") == 0) {
            close(client_socket);
            break;
        } else {
            send(client_socket, "error\n", 6, 0);
        }
    }

    free(client_info);
    return NULL;
}

void* wait_for_clients(void* arg) {
    int server_socket = *(int*) arg;
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr*) &client_addr, &client_len);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }
        printf("Se conectó correctamente (process %d) con el cliente: %d\n", pid_counter, client_socket);

        client_info_t* client_info = malloc(sizeof(client_info_t));
        client_info->socket = client_socket;
        client_info->counter = pid_counter;

        pthread_t tid;
        pthread_create(&tid, NULL, counter_handler, client_info);
        pthread_detach(tid);
    }
    return NULL;
}

int main() {
    int server_socket;
    struct sockaddr_in server_addr;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 10) < 0) {
        perror("listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("El servidor de turnos se pone en escucha, puerto: %d\n", PORT);

    pthread_t tid;
    pthread_create(&tid, NULL, wait_for_clients, &server_socket);
    pthread_join(tid, NULL);

    close(server_socket);
    return 0;
}