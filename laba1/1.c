#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

int main() 
{
	int filedesc = open("qwe.txt", O_RDONLY);
	
	if (filedesc == -1)
	{
		printf("Error number is %d \n", errno);
		perror("Error message from perror(): ");
	}

	//%d - for int value (errno), %s - for char* value (sys_errlist)
	printf("sys_errlist[%d] = \"%s\"\n", errno, sys_errlist[errno]);

	return 0;
}