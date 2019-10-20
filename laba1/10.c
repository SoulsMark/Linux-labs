#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fileDescription;
     
    if(argc < 2)
    {
    	printf("Number of parametres transferred into program must be 2.\n"
				"First - compiled program, second - file you want reverse string in.\n");
			return -1;
    }

    else 
    {
    fileDescription = open(argv[1], O_RDONLY);
    if(fileDescription == -1)
    {
		printf("Error number is %d \n", errno);
		perror("open() error: ");
		return -1;
    }
     
     int endOfFile = lseek(fileDescription, 0, SEEK_END);
     while (endOfFile--)
		{	

			lseek(fileDescription, endOfFile, SEEK_SET);
			char readBuffer[1];
			read(fileDescription, readBuffer, 1);
			printf("%c", readBuffer[0]);
		}
	printf("\n");
    }
    return 0;
}