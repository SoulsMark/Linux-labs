#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

//Модифицировать программу п. 1 таким образом, чтобы родительский
//процесс читал из канала в цикле, пока не встретится конец файла
//(порожденный процесс может записывать в канал информацию, читаемую
//им из стандартного входного потока). Как избежать бесконечного ожидания
//родительским процессом чтения из пустого канала?

#define WRITE_DESC 1
#define READ_DESC 0
//fd[0] является дескриптором для чтения, а fd[1] - дескриптором для записи в трубу

#define BUFF_SIZE 64

int main(int argc, char *argv[]){
    (void)argc; (void)argv;     // сокрытие предупреждений
    pid_t pid;
    int fd_PC[2],fd_CP[2];
    char buff[BUFF_SIZE] = {0};
    int i = 0;

    if(pipe(fd_PC) < 0)

    { perror("pipe_1 : "); exit(0); }

    if(pipe(fd_CP) < 0)

    { perror("pipe_2 : "); exit(0); }


    switch(pid=fork()) {
    case -1:

        perror("fork"); /* произошла ошибка */
        exit(1); /*выход из родительского процесса*/

    case 0:                                                       //CHILD
        printf(" CHILD: Процесс-потомок получил управление\n");
        close(fd_CP[READ_DESC]);
        close(fd_PC[WRITE_DESC]);

        while (strcmp (buff,"STOP") != 0) {
            scanf ("%s",buff);
            write (fd_CP[WRITE_DESC],buff,strlen (buff));
            write (fd_CP[WRITE_DESC],&i,1);
        }
        i = EOF;
        write (fd_CP[WRITE_DESC],&i,1);
        sleep (5);
        printf ("CHILD: ended his writing\n");
        break;
    default:
        printf (" PARENT:Процесс-родитель получил управление \n");
        close(fd_CP[WRITE_DESC]);
        close(fd_PC[READ_DESC]);
        fcntl(fd_CP[READ_DESC],F_SETFL,O_NONBLOCK);
        while (read (fd_CP[READ_DESC],buff,BUFF_SIZE) != 0) {
            if(strcmp(buff,"") != 0){
                printf (" PARENT: %s \n",buff);
                memset(buff, '\0', BUFF_SIZE);
            }
        }


    }
    return 0;
}

