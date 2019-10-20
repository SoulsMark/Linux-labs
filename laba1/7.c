#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>

int main(int argc, char** argv) 
{
	if (argc != 2)
		{
			printf("Number of parametres transferred into program must be 2.\n"
				"First - compiled program, second - file/directory you want to get stat() information.\n");
			return -1;
		}

	struct stat fileStat;
	 if(stat(argv[1],&fileStat) < 0)    
        {
        	perror("Can't reach printed file: ");
        	return -1;
        }

    printf("Information for %s\n",argv[1]);
    printf("---------------------------\n");
    printf("File Size: \t\t\t%li bytes\n",fileStat.st_size);
    printf("Number of Hard-Links: \t\t%lu\n",fileStat.st_nlink);
    printf("File inode: \t\t\t%li\n",fileStat.st_ino);
	printf("Device from inode: \t\t%li\n",fileStat.st_rdev);
    //File permissions from numerals to characters
    printf("File Permissions: \t\t");
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");

    printf("\nOwnership: \t\t\tUID=%ld   GID=%ld\n", (long) fileStat.st_uid, (long) fileStat.st_gid);
    printf("ID containing device: \t\t[%lx,%lx]\n", (long) major(fileStat.st_dev), (long) minor(fileStat.st_dev));
    printf("Blocks size: \t\t\t%lld bytes\n", (long long) fileStat.st_blksize);
    printf("Number of blocks allocated: \t%lld\n", (long long) fileStat.st_blocks);
    printf("Last status change: \t\t%s", ctime(&fileStat.st_ctime));
    printf("Last file access: \t\t%s", ctime(&fileStat.st_atime));
    printf("Last file modification: \t%s", ctime(&fileStat.st_mtime));


	return 0;
}