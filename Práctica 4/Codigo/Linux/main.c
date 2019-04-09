#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>	
#include <sys/wait.h>
#include <sys/timeb.h>
#include <time.h>

int main(){
	pid_t pid;
	char * argv[4];
	int i;
	argv[0]="/Users/joaquinipn/Desktop/7/ExpresionArtimetica";
	argv[1]="/Users/joaquinipn/Desktop/7/PermisosUsuario";
	argv[2]="/Users/joaquinipn/Desktop/7/Inversa";
	argv[3]=NULL;
	if((pid=fork())==0)
	{
		if((pid=fork())==0)
		{
			if((pid=fork())==0)
			{
				printf("Ejecutando: %s \n",argv[0]);
				execv(argv[0],argv);
				exit(0);
			}
			if((pid=fork())==0)
			{
				printf("Ejecutando: %s \n",argv[1]);
				execv(argv[1],argv);
				exit(0);
			}
			if((pid=fork())==0)
			{
				printf("Ejecutando: %s \n",argv[2]);
				execv(argv[2],argv);
				exit(0);
			}
			exit(0);

		}
		else
			wait(0);	
	}
	else
		wait(0);

	exit(0);
}