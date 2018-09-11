#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h> //INCLUYE EL MKDIR
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
	char name[]="Archivo .txt";
	char content[]="Hola Mundo";
	char dir[100];
	char aux[100];
	int NFile,IdFile;
	printf("Give me the name of the Directory\n");
	scanf("%s",dir);
	if(mkdir(dir,0777)==-1){
		printf("Directory don't create\n");
	}
	else{
		NFile=rand()%11;
		
		for (int i = 0; i < NFile; ++i)
		{
			strcpy(aux,"./");
			strcpy(aux,dir);
			name[7]=i+'0';
			strcat(aux,"/");
			strcat(aux,name);
			printf("%s\n", aux);
			creat(aux,0777);
			IdFile=open(aux,O_RDWR);
			write(IdFile,content,sizeof(content));
			strcpy(aux,"\0");
			

		}
	}
	return 0;
}