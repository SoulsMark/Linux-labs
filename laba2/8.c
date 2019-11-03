#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <wait.h>
#include <errno.h>

#define BUFFER_SIZE 1500

int main(int argc, char *argv[])
{
	int fileDescriptor = open(argv[1], O_RDONLY);
	pid_t fork_pid = fork();
	if (fork_pid == 0)
	{
		
		int creatFileDescriptor = open("Children_file.txt", O_RDWR | O_CREAT, 00600);
		char readBuffer[BUFFER_SIZE];
		int length = read(fileDescriptor, readBuffer, BUFFER_SIZE);
		length = write(creatFileDescriptor, readBuffer, length);

		// printf("\e[41mThis is from child file\e[0m %s\n", readBuffer); for second part 
		int startFile = lseek(creatFileDescriptor, 0L, SEEK_SET);
		printf("\e[41mThis one is child:\e[0m\n");
		do 
		{
			lseek(creatFileDescriptor, startFile, SEEK_SET);
			char buf[2];
			length = read(creatFileDescriptor, buf, 1);
			printf("%c", buf[0]);
			startFile++;
		} while (length != 0);
		printf("\n");

		exit(0);
	}
	else 
	{
		// wait(0);
		int creatFileDescriptor = open("Parent_file.txt", O_RDWR | O_CREAT, 00600);
		char readBuffer[BUFFER_SIZE];
		int length = read(fileDescriptor, readBuffer, BUFFER_SIZE);
		length = write(creatFileDescriptor, readBuffer, length);
		
		// printf("\n \e[41mTThis is from parent file\e[0m %s\n", readBuffer); for second part 

		int startFile = lseek(creatFileDescriptor, 0L, SEEK_SET);
		printf("\n \e[41mThis one is parent:\e[0m\n");
		do 
		{
			lseek(creatFileDescriptor, startFile, SEEK_SET);
			char buf[2];
			length = read(creatFileDescriptor, buf, 1);
			printf("%c", buf[0]);
			startFile++;
		} while (length != 0);
		printf("\n");
	}

	return 0;
}