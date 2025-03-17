#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

pid_t child_pid;

void handler_child(int signal) {

    printf("Child recibio señal.\n");
    kill(getppid(), SIGUSR1);
}

void handler_parent(int signal) {

    printf("Parent recibio señal.\n");
    kill(child_pid, SIGUSR1);
} 


int main() {
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    
    pid_t pid;
    pid = fork();

    if (pid == 0) {
        act.sa_handler = handler_child;
        sigaction(SIGUSR1, &act, NULL);
        while (1);

    } else {
        child_pid = pid;
        act.sa_handler = handler_parent;
        sigaction(SIGUSR1, &act, NULL);
        sleep(1);
        kill(pid, SIGUSR1);

        while (1);
    }

    return 0;
}
