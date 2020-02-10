#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
void handler(int);
int main (int argc, char * argv[]) {
    int pid;
    if((pid = fork()) == -1) {
        perror("fork error");
        exit (1);
    }
    if(pid){
        printf("Fork returned %d\n", pid);
        printf("Parent process PID = %d\n", getpid());
        int code;
        if(kill(pid, SIGINT) == -1)
        {
            perror("kill error");
        }
        if(wait(&code) == -1){
            perror("wait error");
        }
        printf("Exit status: %d\n", code);
    }
    else{

        printf("Fork returned %d\n", pid);
        printf("Child process PID = %d\n", getpid());
        for(int i = 0;i < 100;i++){
#ifdef NUMBER7
            pause();
#else
            for(int j = 0; j < 10000 ; j++);
#endif
            printf("%d ", i);
        }
        printf("Process ended \n");
    }
    return 0;
}
void handler(int sigid){
    printf("Sygnal interfered by handler\n");
}
