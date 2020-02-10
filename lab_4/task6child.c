#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[])
{
    (void)argc; (void)argv;     // сокрытие предупреждений
    int fd_fifo; /*дескриптор FIFO*/

    char buffer[]="Текстовая строка для fifo от CHILD\n";
    char buf[100];

    fd_fifo = open ("fifo0001.1", O_RDWR);


    if(read(fd_fifo, &buf, sizeof(buf)) > 0){
        printf(" CHILD: Прочитано из FIFO : %s\n",buf);
    }

        write(fd_fifo,buffer,strlen(buffer)) ;
    return 0;
}
