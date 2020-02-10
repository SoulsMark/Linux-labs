#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
    int status = fork();
    if(status)
    {
        struct sigaction act;
        act.sa_flags = SA_NOCLDWAIT;
        printf("Parent process executing\n");
        printf("Parent fork:%d\n", status);
        printf("parent_PID: %d\n parent_PPID: %d\n parent_GPID: %d\n", getpid(), getppid(), getgid());
        sigaction(SIGCHLD,&act,0);
        pause();
    }
    else
    {
        printf("Child process executing\n");
        printf("Child fork:%d\n", status);
        printf("child_PID: %d\n child_PPID: %d\n child_GPID: %d\n", getpid(), getppid(), getgid());
        exit(0);
    }
    printf("Status: %d\n", status);
    return 0;
}
