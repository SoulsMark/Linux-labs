#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

//Повторить п. 2, создавая параллельные процессы с помощью связки fork -
//exec. Как передать дескрипторы канала в порожденный процесс?».

#define WRITE_DESC 1
#define READ_DESC 0
//fd[0] является дескриптором для чтения, а fd[1] - дескриптором для записи в трубу

#define BUFF_SIZE 64

int main(int argc, char *argv[]){
    (void)argc; (void)argv;     // сокрытие предупреждений
    pid_t pid;
    int fd_PC[2],fd_CP[2];
    char buff[BUFF_SIZE] = {0};

    if(pipe(fd_PC) < 0)

    { perror("pipe_1 : "); exit(0); }

    if(pipe(fd_CP) < 0)

    { perror("pipe_2 : "); exit(0); }


    switch(pid=fork()) {
    case -1:

        perror("fork"); /* произошла ошибка */
        exit(1); /*выход из родительского процесса*/

    case 0:                                                             //CHILD
        printf(" CHILD: Процесс-потомок получил управление\n");
        close(fd_CP[READ_DESC]);
        close(fd_PC[WRITE_DESC]);

        dup2(fd_CP[READ_DESC],0);
        dup2(fd_CP[WRITE_DESC],1);

        execl ("task_4"," ",NULL);
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

