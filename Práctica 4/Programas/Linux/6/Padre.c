#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){
	pid_t pid;
	char * argv[3];
	argv[0]="/usuario/hola"; // Cambiar por su ruta
	argv[1]="Desde el Hijo";
	argv[2]=NULL;
	if((pid=fork())==0){
		printf("Soy el hijo ejecutando: %s \n",argv[0]);
	}
	else{
		wait(0);
		printf("Soy el padre\n");
		exit(0);
	}
}