#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>

pid_t child_pid;

typedef void (*sighandler_t)(int);

void handler_child(int signal) {

    printf("Child recibio señal.\n");
    kill(getppid(), SIGUSR1);
}

void handler_parent(int signal) {

    printf("Parent recibio señal.\n");
    kill(child_pid, SIGUSR1);
}

int main(void) {

    pid_t pid = fork();

    if (!pid) {

        signal(SIGUSR1, handler_child);

        /*pause(); Si dejamos pause en vez de while, solo se reciben las señales 1 vez
         pues despues de pause, el proceso llega a su fin.
         Una buena implementacion seria colocar el pause dentro del while asi no se consume
         demasiada CPU. 
         */
        while(1);
    }
    else {

        child_pid = pid;
        signal(SIGUSR1, handler_parent);

        sleep(1);

        kill(pid, SIGUSR1);

        //pause();
        while(1);
    }

    return 0;
}
