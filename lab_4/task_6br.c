#include <stdio.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

#define WRITE_DESC 1
#define READ_DESC 0
//fd[0] является дескриптором для чтения, а fd[1] - дескриптором для записи в трубу

#define BUFF_SIZE 64

int main()
{
    int fd[2];
    int i;
    char buff[BUFF_SIZE] = {0};

    fd[READ_DESC] = 2;
    fd[WRITE_DESC] = 3;

    printf(" CHILD: Процесс-потомок получил управление\n");
    while (strcmp (buff,"STOP") != 0) {
        scanf ("%s",buff);
        write (fd[WRITE_DESC],buff,strlen (buff));
        write (fd[WRITE_DESC],&i,1);
    }
    return 0;
}
