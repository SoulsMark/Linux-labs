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
    if(pid){
        printf("Fork returned %d\n", pid);
        printf("PID = %d\n", getpid());
        int code;
        if(wait(&code) == -1){
            perror("wait error");
        }
        else{
            printf("Exit status: %d\n", code);
        }
    }
    else{

        printf("Fork returned %d\n", pid);
        printf("Child process created. PID = %d\n", getpid());
#ifdef NUMBER7
    struct sigaction act, oact;
    act.sa_handler = signal_handler;
    if (sigaction(SIGALRM, &act, &oact) == -1){
        perror("sigaction error");
    }
#endif
        for(int i = 0;i < 100;i++){
#ifdef NUMBER7
            alarm(1);
            pause();
#else
            for(int j = 0; j < 10000 ; j++);
#endif
            printf("%d ",i);
        }
    }
    return 0;
}

void signal_handler(int sigid){
    printf("Signal catched by handler!\n");
}
