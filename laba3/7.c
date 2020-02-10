#define _POSIX_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
void signal_handler(int);
int main (int argc, char * argv[]) {
    int pid;
    if((pid = fork()) == -1) {
        perror("fork error");
        exit (1);
    }
    struct sigaction act, oact;
    act.sa_handler = signal_handler;
    if (sigaction(SIGINT, &act, &oact) == -1){
        perror("sigaction error");
    }

    if(pid){
        printf("Fork returned %d\n", pid);
        printf("Parent process PID = %d\n", getpid());
        int code;
        if(wait(&code) == -1){
            perror("wait error");
        }
        printf("Exit status: %d\n", code);
    }
    else{

        printf("Fork returned %d\n", pid);
        printf("Child process PID = %d\n", getpid());
        int i,j;
        for(i = 0;i < 100;i++){
            if(pause() == -1){
                perror("pause error");
            }
            printf("i = %d\n", i);
        }
        printf("Done!\n");
    }
    return 0;
}

void signal_handler(int sig_id){
    printf(" Signal interfered by handler \n");
}
