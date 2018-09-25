#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>

int main(){
	char Permission[10];
	int Permission_Octal;
	char direction[200];
	struct stat file; // para apuntar al archivo que deseamos cambiar los permisos
	printf("Necesitamos la direcion del directorio donde se encuentran los archivos\n 
		Por ejemplo: /home/yirz/Escritorio/File\n");
	scanf("%s",direction);
	if(stat(direction,&file)==0){
		printf("Los permisos estan definidos por:\n");
		printf("rwx_7-Lectura, Escritura y Ejecucion\n");
		printf("rw-_6- Lectura y Escritura\n");
		printf("r-x_5-Lectura y ejecucion\n");
		printf("r--_4-Lectura\n");
		printf("-wx_3-Escritura y ejecucion\n");
		printf("-w-_2-Escritura\n");
		printf("--x_1-Ejecucion\n");
		printf("---_0-Sin permisos\n");
		printf("Los permisos del directorio o archivo son:\n");
		printf("\n");
		//Propietario
		printf("Permisos de Propietario");
		printf( (file.st_mode & S_IRUSR) ? "r" : "-");
    	printf( (file.st_mode & S_IWUSR) ? "w" : "-");
    	printf( (file.st_mode & S_IXUSR) ? "x" : "-");
    	printf("\n\n");
    	//GRUPO
    	printf("Permisos de Grupo\n");
    	printf( (file.st_mode & S_IRGRP) ? "r" : "-");
   		printf( (file.st_mode & S_IWGRP) ? "w" : "-");
    	printf( (file.st_mode & S_IXGRP) ? "x" : "-");
    	printf("\n\n");
    	//OTROS
    	printf("Permisos de Otros\n");
    	printf( (file.st_mode & S_IROTH) ? "r" : "-");
    	printf( (file.st_mode & S_IWOTH) ? "w" : "-");
    	printf( (file.st_mode & S_IXOTH) ? "x" : "-");
    	printf("\n\n");
    	printf("Ingrese el los nuevos permisos para el directorio o archivo\n");
    	scanf("%s",Permission);
    	Permission_Octal=strtol(Permission,0,8);
    	if(chmod(direction,Permission_Octal)==0)
    		printf("Permisos Cambiados\n");
    	else
    		printf("Permisos no cambiados\n");

	}
	else{
		printf("Dritectorio o archivo no existente\n");
	}
	return 0;
}
