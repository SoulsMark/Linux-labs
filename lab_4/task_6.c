#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


//Создать именованный канал (любым способом). Убедиться, что канал
//создан. Рассмотреть особенности работы с именованным каналом (открыть
//файл с установленным и не установленным флагом O_NDELAY).
//Использовать его для обмена информацией с процессом, созданным другим
//пользователем (своим соседом).

#define BUF_SIZE 100

int main(int argc, char *argv[]){
    (void)argc; (void)argv;     // сокрытие предупреждений
    int fd_fifo; /*дескриптор FIFO*/

    char buffer[]="Текстовая строка для fifo от :PARENT\n";
    char buf[BUF_SIZE];

    unlink("fifo0001.1");
    mkfifo("fifo0001.1", S_IRWXU);
    fd_fifo = open ("fifo0001.1",O_NDELAY|O_WRONLY);

//    if(fork() == 0){
//        execl ("task_6","",NULL);
//    }

    fcntl(fd_fifo,F_SETFL,O_NONBLOCK);
    sleep (1);
    if(read(fd_fifo, &buf, sizeof(buf)) > 0){
        printf(" PARENT: Прочитано из FIFO %s\n",buf);
    }
    else{
        write(fd_fifo,buffer,strlen(buffer)) ;
    }
    
    if(read(fd_fifo, &buf, sizeof(buf)) > 0){
        printf(" PARENT: Прочитано из FIFO %s\n",buf);
    }
    else{
        write(fd_fifo,buffer,strlen(buffer));
    }

    return 0;
}
