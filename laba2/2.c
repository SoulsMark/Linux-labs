#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char *argv[])
{
	pid_t forkReturned = fork();
	if (forkReturned == 0)
	{
		printf("This one is child\n");
		printf("Value of a fork() : %d\n", forkReturned);
		printf("Process id of a child: %d\nProcess of TEST: %d\n", getpid(), getppid());
		printf("Father's id (in child_fork() : %d\n", getppid());
	}
	else 
	{
		printf("This one is parent\n");
		printf("Value of a fork() - must be equal to child PID: %d\n", forkReturned);
		printf("Process id of a father: %d\n", getpid());
		printf("Father's id (in father_fork() : %d\n", getppid());
		wait(0);
	}
	
	exit(0);
}