#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char *argv[])
{
	fork();
	execvp(argv[1], argv + 1);
	system(argv[1]);
	return 0;
}