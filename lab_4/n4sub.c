#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char * argv[]){
    char buf[100];
    int n;
    printf("[SUB] Execve ok!\n");
    if((n = read(0, buf, sizeof(buf))) == -1){
        perror("[SUB] read error!");
    }

    if(write(1, buf, n) == -1){
        perror("[SUB] write error!");
    }
    printf("[SUB] Terminate...\n");
}
