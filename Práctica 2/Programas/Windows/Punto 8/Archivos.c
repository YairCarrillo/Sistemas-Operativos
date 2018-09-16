#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
	char name[]="Archivo .txt";
	char content[]="Hola Mundo";
	char dir[100];
	char aux[100];
	int NFile,IdFile,i;
	HANDLE file;// Apuntador al archivo
	printf("Give me the name of the Directory\n");
	scanf("%s",dir);
	if(!(CreateDirectory(dir,NULL))){
		printf("Directory don't create\n");
	}
	else{
		NFile=rand()%11;
		for (i = 0; i < NFile; ++i)
		{
			strcpy(aux,"./");
			strcpy(aux,dir);
			name[7]=i+'0';
			strcat(aux,"/");
			strcat(aux,name);
			printf("%s\n", aux);
			file=CreateFile(aux,GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);
			WriteFile(file,content,sizeof(content),NULL,NULL);
			strcpy(aux,"\0");
		}
	}
	return 0;
}

