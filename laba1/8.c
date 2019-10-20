#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


int copyFromFile(char sourceFile[256], char targetFile[256])
	{
	char tempChar, buf[256];
	ssize_t nread;
	int sourceDescription, targetDescription;
	sourceDescription = open(sourceFile, O_RDONLY);
 
 			if( sourceDescription == -1 )
   			{
      			printf("Can't open the file\n");
      			perror("source file error: ");
      			return -1;
   			}

   	targetDescription = open(targetFile, O_WRONLY);
 
   			if( targetDescription == -1 )
   			{
      			close(sourceDescription);
      			printf("Can't open the file\n");
      			perror("target file error: ");
      			return -1;
   			}

	while (nread = read(sourceDescription, buf, sizeof buf), nread > 0)
    {
        char *out_ptr = buf;
        ssize_t nwritten;

        do {
            nwritten = write(targetDescription, out_ptr, nread);

            if (nwritten >= 0)
            {
                nread -= nwritten;
                out_ptr += nwritten;
            }
        } while (nread > 0);
    }
	
	printf("File copied successfuly\n");
	close(sourceDescription);
	close(targetDescription);
	return 0;
	}


int main(int argc, char** argv) 
{
	char sourceFile[256], targetFile[256], buffer[512];
		if (argc != 3)
		{
			printf("What you want to print?\n");
			read(0, buffer, sizeof(buffer));
			write(1, buffer, strlen(buffer));
			printf("Successfuly printed using stdin and stdout.\n");
		}
		else 
			copyFromFile(argv[1], argv[2]);
	return 0;
}