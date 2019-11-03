#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	pid_t fork_pid = fork();
	if (fork_pid == 0)
	{
		printf("This one is child:\n");
		printf("Child PID = %d\nFather's PID = %d\nChild GID = %d\n", getpid(), getppid(), getgid());
		setpgrp();
		pause();
	}
	else 
	{
		printf("This one is parent:\n");
		printf("Parent PID = %d\nFather's PID = %d\nParent GID = %d\n", getpid(), getppid(), getgid());
		pause();
	}

	return 0;
}