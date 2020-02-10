#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>


void sighandler(int sig)
{
    printf("Отправка строки из %d\n", getpid());
}


int main()
{
    struct sigaction act, oact;
    act.sa_handler = sighandler;
    sigaction(SIGUSR1, &act, &oact);
    sigset_t mask, omask;
    sigfillset(&mask); //initializes set to full, including all signals
    sigprocmask(SIG_SETMASK, &mask, &omask); //set list of blocked signals
    sigdelset(&mask, SIGUSR1);  //delete signal signum from set
    int pid = getpid();
    int status = fork();
    if(status)
    {
        printf("Выполнение родительского процесса PID = %d\n", getpid());
        sigsuspend(&mask); //change mask and stop process before getting appropriate signal (process stoppage or )
        sleep(3);
        kill(status, SIGUSR1);
        // sigsuspend(&mask); 
        sleep(3);
        kill(status, SIGUSR1);
    }
    else{
        printf("Выполнение дочернего процесса PID = %d\n", getpid());
        sleep(3);
        kill(pid, SIGUSR1);
        // sigsuspend(&mask); 
        sleep(3);
        kill(pid, SIGUSR1);
        sigsuspend(&mask); 
    }
    return 0;
}

