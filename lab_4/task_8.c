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
Добавить в один из процессов использование слабой блокировки. Что
произойдет?*/

#define BUF_SIZE 100

int main(int argc, char *argv[]){
    (void)argc; (void)argv;     // сокрытие предупреждений
    int fd_fifo; /*дескриптор FIFO*/

    if(argc < 2){
        printf("Arguments");
        exit(0);
    }
    char *f_name = argv[1];

    char buffer[]="Текстовая строка для fifo\n";
    char buf[BUF_SIZE];

    struct flock lock;

    fd_fifo = open (f_name, O_RDWR);

    pid_t pid;
    switch(pid=fork()) {
    case -1:
        perror("fork"); /* произошла ошибка */
        exit(1); /*выход из родительского процесса*/
    case 0:

        for(int i = 0 ; i < 10 ; i++){
            write(fd_fifo,buffer,strlen(buffer));
        }
        break;

    default:

        lock.l_type = F_RDLCK;
        lock.l_start = 0;
        lock.l_whence = SEEK_SET;
        lock.l_len = 0;
        fcntl(fd_fifo, F_SETLKW, &lock);

        for(int i = 0 ; i < 10 ; i++){
            read(fd_fifo, &buf, sizeof(buf));
            printf ("%s",buf);
            memset(buf, '\0', BUF_SIZE);
        }

        lock.l_type = F_ULOCK;
        fcntl(fd_fifo, F_SETLKW, &lock);
    }
    return 0;
}

//F_GETLK, F_SETLK и F_SETLKW используются для установки, снятия и тестирования существующих блокировок записи

//struct flock {
//    ...
//    short l_type;    /* Тип блокировки: F_RDLCK,
//                        F_WRLCK, F_UNLCK */
//    short l_whence;  /* Как интерпретировать l_start:
//                        SEEK_SET, SEEK_CUR, SEEK_END */
//    off_t l_start;   /* Начальное смещение для блокировки */
//    off_t l_len;     /* Количество байт для блокировки */
//    pid_t l_pid;     /* PID процесса блокирующего нашу блокировку
//                        (F_GETLK only) */
//    ...
//}
