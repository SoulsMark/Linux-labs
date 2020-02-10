#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

//Создать параллельный процесс, используя только fork. Организовать
//обмен информацией между процессами через каналы. Предусмотреть
//двунаправленной связь исключить возможность появления «смертельных объятий».

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
        fcntl(fd_PC[READ_DESC],F_SETFL,O_NONBLOCK);

        while (strcmp (buff,"STOP") != 0) {
            printf(" CHILD: Готов читать ");
            scanf ("%s",buff);
            write (fd_CP[WRITE_DESC],buff,strlen (buff));
            write (fd_CP[WRITE_DESC],&i,1);

            if(read (fd_PC[READ_DESC],buff,BUFF_SIZE) > 0){
                printf (" CHILD:  %s \n",buff);
                memset(buff, '\0', BUFF_SIZE);
            }
        }
        break;

    default:                                                       //PARENT
        printf (" PARENT:Процесс-родитель получил управление \n");
        close(fd_CP[WRITE_DESC]);
        close(fd_PC[READ_DESC]);
        fcntl(fd_CP[READ_DESC],F_SETFL,O_NONBLOCK);

        while (strcmp (buff,"STOP") != 0) {
            printf(" PARENT: Готов читать \n");
            scanf ("%s",buff);
            write (fd_PC[WRITE_DESC],buff,strlen (buff));
            write (fd_PC[WRITE_DESC],&i,1);

            if(read (fd_CP[READ_DESC],buff,BUFF_SIZE) > 0){
                printf (" PARENT: %s \n",buff);
                memset(buff, '\0', BUFF_SIZE);
            }
        }
}
return 0;
}
