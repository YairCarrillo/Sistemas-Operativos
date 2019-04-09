#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>	
#include <sys/wait.h>
#include <sys/timeb.h>
#include <time.h>

int main(){
	pid_t pid;
	char * argv[6];
	int i;
	clock_t inicio,fin;
	double total;
	struct timeb start,end;
	int diff;
	ftime(&start);
	argv[0]="/home/yirz/Escritorio/Susttitucion/Suma";
	argv[1]="/home/yirz/Escritorio/Susttitucion/Resta";
	argv[2]="/home/yirz/Escritorio/Susttitucion/Multiplicacion";
	argv[3]="/home/yirz/Escritorio/Susttitucion/Transpuesta";
	argv[4]="/home/yirz/Escritorio/Susttitucion/Inversa";
	argv[5]="/home/yirz/Escritorio/Susttitucion/Archivos";
	argv[6]=NULL;
	inicio=clock();
	if((pid=fork())==0){
		if((pid=fork())==0){
			execv(argv[0],argv);
		
		}
		if((pid=fork())==0){
			execv(argv[1],argv);
		}
		if((pid=fork())==0){
			execv(argv[2],argv);
		}
		if((pid=fork())==0){
			execv(argv[3],argv);
		}
		if((pid=fork())==0){
			execv(argv[4],argv);
		}
		for(i=0;i<4;i++){
			wait(0);
		}
		execv(argv[5],argv);
	}
	wait(0);
	fin=clock();
	total=(double)(fin-inicio)/CLOCKS_PER_SEC;
	printf("Tiempo de ejecucion %f segudos\n",total);
}
