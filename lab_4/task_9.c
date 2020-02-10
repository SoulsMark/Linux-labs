#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <sys/file.h>

/*
Добавить использование слабой блокировки во второй. Что изменится?
*/

#define BUF_SIZE 100

int main(int argc, char *argv[]){
    (void)argc; (void)argv;     // сокрытие предупреждений
    int fd = 0; /*дескриптор FIFO*/

    if(argc < 2){
        printf("Arguments");
        exit(0);
    }
    char *f_name = argv[1];

    char buffer[]="String for file\n";
    char buf[BUF_SIZE];

    struct flock lock;
    pid_t pid;
    fd = open(f_name,O_RDWR,O_TRUNC);
    perror ("creat ");
    switch(pid=fork()) {
    case -1:
        perror("fork"); /* произошла ошибка */
        exit(1); /*выход из родительского процесса*/
    case 0:
        lock.l_start = 0;
        lock.l_whence = SEEK_SET;
        lock.l_type = F_WRLCK;
        lock.l_len = 0;
        fcntl(fd, F_SETLKW, &lock);
        printf ("NO wait %i \n",fd);
        perror ("fcntl ");
        lseek (fd,0,SEEK_SET);
         for(int i = 0 ; i < 15 ; i++){
            read(fd, &buf, 1);
            printf ("%c",buf[0]);
            memset(buf, '\0', BUF_SIZE);
        }
        
        perror ("read ");
        printf ("%s\n",buf);

        break;
    default:
        lock.l_start = 0;
        lock.l_whence = SEEK_SET;
        lock.l_type = F_WRLCK;
        lock.l_len = 0;
        fcntl(fd, F_SETLKW, &lock);
        write(fd,buffer,strlen(buffer));
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
    }
    close(fd);
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
