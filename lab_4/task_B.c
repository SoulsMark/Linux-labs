#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <sys/file.h>


//Повторить выполнение п. 10, включив в процессы для синхронизации
//работы с терминалом использование режима слабой блокировки. Как
//изменится поведение процессов?

#define BUF_SIZE 100

int main(int argc, char *argv[]){
    (void)argc; (void)argv;     // сокрытие предупреждений
    int fd = 0; /*дескриптор FIFO*/

    char buf[BUF_SIZE];
    pid_t pid;
    struct flock lock;

    switch(pid=fork()) {
    case -1:
        perror("Fork:"); /* произошла ошибка */
        exit(1); /*выход из родительского процесса*/
    case 0:
        while (strcmp (buf,"STOP") != 0) {
            lock.l_start = 0;
            lock.l_whence = SEEK_SET;
            lock.l_type = F_WRLCK;
            lock.l_len = 0;
            fcntl(fd, F_SETLKW, &lock);
            scanf ("%s",buf);
            printf("CHILD %s \n",buf);
            memset(buf, '\0', BUF_SIZE);
            lock.l_type = F_UNLCK;
            fcntl(fd, F_SETLK, &lock);
            sleep (2);
        }
        break;

    default:
        while (strcmp (buf,"STOP") != 0) {
            lock.l_start = 0;
            lock.l_whence = SEEK_SET;
            lock.l_type = F_WRLCK;
            lock.l_len = 0;
            fcntl(fd, F_SETLKW, &lock);
            scanf ("%s",buf);
            printf("PARENT %s \n",buf);
            memset(buf, '\0', BUF_SIZE);
            lock.l_type = F_UNLCK;
            fcntl(fd, F_SETLK, &lock);
            sleep (2);
        }

        break;
    }
    return 0;
}
