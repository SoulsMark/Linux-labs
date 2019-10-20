#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int copyFromFile()
{
	int readSize;
	char readBuffer[256];
	readSize = read(0, readBuffer, 256);
	write(1, readBuffer, readSize);
	return 0;
}


int main(int argc, char** argv) 
{	
	int toFileDescriptor, fromFileDescriptor;
	char sourceFile[256], targetFile[256];
		if (argc != 3)
		{
			printf("Enter name of file to copy\n");
   			fgets(sourceFile, 30, stdin);
   			sourceFile[strcspn(sourceFile, "\n")] = 0;
   			toFileDescriptor = open(sourceFile, O_RDONLY);
 			if (toFileDescriptor == -1)
			{
				printf("Error number is %d \n", errno);
				perror("open() error: ");
				exit(EXIT_FAILURE);
			}
			else printf("Your file was opened succesfully.\n");
   			printf("Enter name of target file\n");
   			fgets(targetFile, 30, stdin);
   			targetFile[strcspn(targetFile, "\n")] = 0;
 			fromFileDescriptor = open(targetFile, O_WRONLY);
 			if (fromFileDescriptor == -1)
			{
				printf("Error number is %d \n", errno);
				perror("open() error: ");
				exit(EXIT_FAILURE);
			}
			else printf("Your file was opened succesfully.\n");
 			dup2(toFileDescriptor, 0);
 			dup2(fromFileDescriptor, 1);
 			copyFromFile();
		}

		else
		{
			toFileDescriptor = open(argv[1], O_RDONLY);
			fromFileDescriptor = open(argv[2], O_WRONLY);
			dup2(toFileDescriptor, 0);
 			dup2(fromFileDescriptor, 1);
 			copyFromFile();
		}

	close(toFileDescriptor);
	close(fromFileDescriptor);
	return 0;
}