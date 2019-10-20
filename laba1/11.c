#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char **argv[])
{
	struct stat file[argc];
	int biggestFileValue;
	for (int i = 0; i < argc; i++) 
	{
		stat(argv[i], &file[i]);
	}
	for (int i = 0; i < argc - 1 ; i++)
	{
		int firstFileValue = file[i].st_size;
		int secondFileValue = file[i + 1].st_size;
		if (firstFileValue > secondFileValue)
			biggestFileValue = firstFileValue;

		else 
			biggestFileValue = secondFileValue;
	}

	printf("Biggest file from command line (in bytes): %d\n", biggestFileValue);
	return 0;
}