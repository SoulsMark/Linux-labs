#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>


//С помощью системных вызовов pipe и dup реализовать конвейер: who | wc -l.

#define WRITE_DESC 1
#define READ_DESC 0
//fd[0] является дескриптором для чтения, а fd[1] - дескриптором для записи в трубу


int main(int argc, char * argv[]){
    (void)argc; (void)argv;     // сокрытие предупреждений
    int fds[2];
    pipe(fds);
    if(fork() == 0){
        printf("CHILD who: Процесс-потомок получил управление\n");
        close(fds[READ_DESC]);
        dup2(fds[WRITE_DESC], 1);
        execl ("/usr/bin/who", "/usr/bin/who",NULL);
        perror("[C-WHO] execvp error");
    }

    if(fork() == 0){
        printf("CHILD wc: Процесс-потомок получил управление\n");
        close(fds[WRITE_DESC]);
        dup2(fds[READ_DESC], 0);
        printf("Result from who | wc -l\n");
        execl("/usr/bin/wc","/usr/bin/wc", "-l",NULL);
        perror("[C-WC] execvp error");
    }
    close(fds[0]);
    close(fds[1]);
    return 0;
}
//Ошибка при чтении из пустого канала в NONBLOCK

