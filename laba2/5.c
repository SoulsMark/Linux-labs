#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char *argv[])
{
	pid_t child_a, child_b, parent_pid;

	child_a = fork();

	if (child_a == 0) {
	printf("PID child a %d\n", getpid());
    exit(getpid());
	} else {
    	child_b = fork();

    if (child_b == 0) {
    	printf("PID child b %d\n", getpid());
        exit(getpid());
    	} else {
        printf("This one is parent:\n");
		printf("Parent PID = %d\nFather's PID = %d\nParent GID = %d\n", getpid(), getppid(), getgid());
		int status = 0;
		while ((parent_pid = wait(&status)) > 0);

		
   	 	}
	}
	return 0;
}