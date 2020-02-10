#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/file.h>

/*
Создать два параллельных процесса, в каждом из которых осуществляется
работа с одним и тем же файлом. Каждый процесс открывает файл (имя
файла передается через список аргументов командной строки). Один
процесс пишет в файл, другой - читает из него. Что произойдет без
включения блокировок*/

#define BUF_SIZE 100

int main(int argc, char *argv[]){
    (void)argc; (void)argv;     // сокрытие предупреждений

    (void)argc; (void)argv;     // сокрытие предупреждений
    int fd_fifo; /*дескриптор FIFO*/
    int startFile;
    if(argc < 2){
        printf("Not enough Arguments");
        exit(0);
    }
    char *f_name = argv[1];

    char buffer[]="String variable for file\n";
    char buf[BUF_SIZE];

    fd_fifo = open (f_name, O_RDWR);

    pid_t pid;
    switch(pid=fork()) {
    case -1:
        perror("fork"); /* произошла ошибка */
        exit(1); /*выход из родительского процесса*/
    case 0:
        startFile = lseek(fd_fifo, 0L, SEEK_SET);
        for(int i = 0 ; i < 10 ; i++){
            lseek(fd_fifo, startFile, SEEK_SET);
            write(fd_fifo,buffer,10);
            startFile++;
        }
        break;
    default:
        for(int i = 0 ; i < 10 ; i++){
            read(fd_fifo, &buf, 1);
            printf ("%c",buf[0]);
            memset(buf, '\0', BUF_SIZE);
        }
        close (fd_fifo);
    }
    return 0;
}
