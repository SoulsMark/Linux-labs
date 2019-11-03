#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char *argv[])
{
	pid_t fork_pid = fork();
	int status;
	if (fork_pid == 0)
	{
		printf("This one is child:\n");
		printf("Child PID = %d\nFather's PPID = %d\nChild GID = %d\n", getpid(), getppid(), getgid());
		exit(1);
	}
	else 
	{
		printf("This one is parent:\n");
		printf("Parent PID = %d\nFather's PPID = %d\nParent GID = %d\n", getpid(), getppid(), getgid());
		printf("\nChild identifier from wait() = %d\n", wait(&status));

		if (WIFEXITED(status))
		{
			int exit_status = WEXITSTATUS(status);
			printf("Exit status of a child was %d\n", exit_status);
		}
	}

	return 0;
}