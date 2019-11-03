#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fileDescriptor = open(argv[1], O_RDONLY);
	pid_t fork_pid = fork();
	if (fork_pid == 0)
	{
		int fileDescriptor = open(argv[1], O_RDONLY);
		int creatFileDescriptor = creat("Children_file.txt", 00600);
		char readBuffer[10200];
		int readFileDescriptor = read(fileDescriptor, readBuffer, 10200);
		write(creatFileDescriptor, readBuffer, readFileDescriptor);
		read(creatFileDescriptor, readBuffer, 10200);
		printf("Child file content \n%s\n", readBuffer);
	}
	else 
	{
		int fileDescriptor = open(argv[1], O_RDONLY);
		int creatFileDescriptor = creat("Parent_file.txt", 00600);
		char readBuffer[10200];
		int readFileDescriptor = read(fileDescriptor, readBuffer, 10200);
		write(creatFileDescriptor, readBuffer, readFileDescriptor);
		read(creatFileDescriptor, readBuffer, 10200);
		printf("Parent file content \n%s\n", readBuffer);
	}

	return 0;
}