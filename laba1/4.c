#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define STRING_MAX 256
int main(void) 
{
	char fileName[STRING_MAX], stringToFile[STRING_MAX], stringFromFile[STRING_MAX];
	int fileDesc, mode, fdclose, fileDescWrite;
	FILE *fileRead;
	long position;

	printf("Write name of the file: \n");
	fgets(fileName, STRING_MAX, stdin);
	fileName[strcspn(fileName, "\n")] = 0;
	printf("Name of the file: %s\n", fileName);

	printf("Write file mode (read-and-write 00644): \n");
	scanf("%o", &mode);
	fgetc(stdin);
	printf("Name of the file: %o\n", mode);
	

	fileDesc = creat(fileName, mode);
	if (fileDesc == -1)
	{
		printf("Error number is %d \n", errno);
		perror("creat() error: ");
	}
	else printf("Your file was created succesfully.\n");


	printf("Print info you want add to file: \n");
	fgets(stringToFile, STRING_MAX, stdin);
	stringToFile[strcspn(stringToFile, "\n")] = 0;

	position = lseek(fileDesc, 10L, SEEK_SET);
	if (position == -1L)
		perror("Lseek to current position error: ");
	fileDescWrite = write(fileDesc, stringToFile, strlen(stringToFile));
	if (fileDescWrite == -1)
	{
		printf("Error number is %d \n", errno);
		perror("write() error: ");
	}
	else printf("You've succesfully written into file.\n");

	fdclose = close(fileDesc);
	if (fdclose == -1)
	{
		printf("Error number is %d \n", errno);
		perror("close() error: ");
	}
	else printf("Your file was closed succesfully.\n");

	fileRead = fopen(fileName, "rt");
	if (fileRead == NULL)
	{
		printf("Error number is %d \n", errno);
		perror("fopen() error: ");
	}
	else printf("Your file was opened succesfully.\n");

	position = lseek(fileDesc, 6L, SEEK_CUR);
	if (position == -1L)
		printf("Error number is %d \n", errno);
	fgets(stringFromFile, STRING_MAX, fileRead);
	printf("Information from the file: %s\n", stringFromFile);
	if (fclose(fileRead))
	{
		printf("Error number is %d \n", errno);
		perror("fclose() error: ");
	}
	else printf("Your file was closed succesfully.\n");

	return 0;
}