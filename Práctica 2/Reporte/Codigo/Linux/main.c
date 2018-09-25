#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE1 10
#define SIZE2 100
#define TRUE 1
#define FALSE 0

int getPath(char paths[][SIZE2])
{	
	int i=0;
	int condition=TRUE;
	do{
		printf("Enter the pathname of the files where the files are located\n");
		printf("For example: /home/yirz/Escritorio/File\n"); 
		scanf("%s",&paths[i][SIZE2]);
		i++;
		printf("Do you want to enter another pathname? (Yes 1/ No 0)\n");
		scanf (" %d", &condition);
	}while( condition==TRUE);
	return i;
}

int main(int argc, char const *argv[])
{
	char paths[SIZE1][SIZE2];
	struct stat buffer;
	int status;
	int i,j;		
	i=getPath(paths);

	for (j = 0; j <= i; j++)
	{
		status = stat(&paths[j][0], &buffer);
		if(status==0)
		{
			printf("\nThe  the pathname of the file is : %s\n", &paths[j][0]);
			printf("File size: %lld bytes\n",(long long) buffer.st_size);
			printf("Last file access: %s", ctime(&buffer.st_atime));
			printf("Last file modification: %s", ctime(&buffer.st_mtime));
		}
		
	}
	return 0;
}