#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define STRING_MAX 256
int main() 
{
	char fileName[STRING_MAX], stringToFile[STRING_MAX], stringFromFile[STRING_MAX];
	int fileDesc, mode, fdclose, fileDescWrite;
	FILE *fileRead;

	printf("Write name of the file: \n");
	fgets(fileName, STRING_MAX, stdin);
	fileName[strcspn(fileName, "\n")] = 0;
	printf("Name of the file: %s\n", fileName);

	printf("Write file mode (read-only 00444): \n");
	scanf("%o", &mode);
	fgetc(stdin);
	printf("Name of the file: %o\n", mode);
	
	printf("Print info you want add to file: \n");
	fgets(stringToFile, STRING_MAX, stdin);
	stringToFile[strcspn(stringToFile, "\n")] = 0;

	fileDesc = open(fileName, O_CREAT|O_RDONLY|O_TRUNC, S_IRUSR);
	if (fileDesc == -1)
	{
		printf("Error number is %d \n", errno);
		perror("creat() error: ");
	}
	else printf("Your file was created succesfully.\n");

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

	fgets(stringFromFile, STRING_MAX, fileRead);
	printf("Information from the file: %s\n", stringFromFile);
	if (fclose(fileRead))
	{
		printf("Error number is %d \n", errno);
		perror("fclose() error: ");
	}
	else printf("Your file was closed succesfully.\n");

	fileDesc = open(fileName, O_RDWR);
	if (fileDesc == -1)
	{
		printf("Error number is %d \n", errno);
		perror("open() error: ");
	}
	else printf("Your file was opened succesfully.\n");

	return 0;
}