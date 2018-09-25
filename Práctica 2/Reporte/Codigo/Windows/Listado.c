#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sys/types.h>
#include <stdint.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <locale.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void comenzar();
int main(int argc, char *argv[]) {
	printf("Ingresa el directorio");
	comenzar();
	return 0;
}
void comenzar(){	
	char directorio[20];
	struct dirent *dp;
	struct stat statbuf;
	struct tm *tm;
	struct group *grp;
	struct passwd  *pwd;
	off_t tamanio;
	char datestring[30];
	
	scanf("%s",directorio);
	DIR *dirp=opendir(directorio);
	   tm = localtime(&statbuf.st_mtime);
    int i=-1;
	while((dp=readdir(dirp))!=NULL){
		if(stat(dp->d_name,&statbuf)==-1)
		{
            printf("%s\t", dp->d_name);
            printf("TAMANIO: ");
			printf(" %lld\t",statbuf.st_size);
			printf("Hora de acceso: ");
			tm = localtime(&statbuf.st_mtime);
			strftime(datestring, sizeof(datestring),"%x - %I:%M%p", tm);
			printf("%s",datestring);
			printf("\n");
		}
	
	}
		system("pause");		
}
