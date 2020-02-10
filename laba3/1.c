#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void signal_handler(int);

int main(int argc, char * argv[], char * argp[]){
    signal(SIGINT, signal_handler);
    while(1){
        pause();
    }
    printf("TEST message\n");
    return 0;
}

void signal_handler(int signal_id){
    printf("  Signal was intercepted by handler!\n");
    signal(SIGINT, SIG_DFL);
}