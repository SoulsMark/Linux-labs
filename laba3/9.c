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
        wait(0);
        printf("Fork returned %d\n", pid);
        printf("Parent process PID = %d\n", getpid());
        int code;
        // signal(SIGALRM, handler);
        // alarm(3);
        
    }
    else{
        // signal(SIGALRM, handler);
        
        printf("Fork returned %d\n", pid);
        printf("Child process PID = %d\n", getpid());
        for(int i = 0;i < 5;i++){
            alarm(3);
            for(i = 0;i < 1000000;i++){
                printf("i = %d\n", i);
            }
            
        }
        printf("Child process ended \n");
    }
    return 0;

}
