#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


//Создать два параллельных процесса, разделяющие ввод с клавиатуры и
//вывод на экран. Что получится при исполнении этих процессов?

#define BUF_SIZE 100

int main(int argc, char *argv[]){
    (void)argc; (void)argv;     // сокрытие предупреждений

    char buf[BUF_SIZE];
    pid_t pid;

    switch(pid=fork()) {
    case -1:
        perror("Fork:"); /* произошла ошибка */
        exit(1); /*выход из родительского процесса*/
    case 0:
        while (strcmp (buf,"STOP") != 0) {
            scanf ("%s",buf);
            printf("CHILD %s \n",buf);
            memset(buf, '\0', BUF_SIZE);
        }
        break;

    default:
        while (strcmp (buf,"STOP") != 0) {
            scanf ("%s",buf);
            printf("PARENT %s \n",buf);
            memset(buf, '\0', BUF_SIZE);
        }
        break;
    }
    return 0;
}
