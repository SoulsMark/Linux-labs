#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char *argv[])
{
	extern char **environ;
	pid_t fork_pid = fork();
	int i = 1;
	if (fork_pid == 0)
	{
		printf("This one is child:\n");
		printf("Child PID = %d\nFather's PID = %d\nChild GID = %d\n", getpid(), getppid(), getgid());
		printf("\e[42mArgument list of a child:\e[0m\n");
		while (argv[i] != NULL)
		{
			printf("%s\n", argv[i]);
			i++;
		}

		printf("\e[42mEnviroment list of a child:\e[0m\n");
		while (environ[i] != NULL)
		{
			printf("%s\n", environ[i]);
			i++;
		}
		exit(0);
	}
	else 
	{
		printf("This one is parent:\n");
		printf("Parent PID = %d\nFather's PID = %d\nParent GID = %d\n", getpid(), getppid(), getgid());
		wait(0);
		printf("\e[42mArgument list of a parent:\e[0m\n");
		
		while (argv[i] != NULL)
		{
			printf("%s\n", argv[i]);
			i++;
		}

		printf("\e[42mEnviroment list of a parent:\e[0m\n");
		while (environ[i] != NULL)
		{
			printf("%s\n", environ[i]);
			i++;
		}
	}
	return 0;
}