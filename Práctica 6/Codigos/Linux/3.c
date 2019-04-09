#include <sys/types.h> /*Servidro de la memoria compartida*/
#include <sys/ipc.h>	/*ejecutar el servidor antes del cliente*/
#include <sys/shm.h>
#include <stdio.h>
#define TAM_MEM 27	/*Tamaño de la memoria compartida en bytes*/
int main()
{
	char c;
	int shmid;
	key_t llave;
	char*shm,*s;
	llave=5678;
	if ((shmid=shmget(llave,TAM_MEM,IPC_CREATE|0666))<0)
	{
		perror("Eror al obtener memoria compartida:shmget");
		exit(-1);
	}
	if ((shm=shmat(shmid,NULL,0))==(char*)-1)
	{
		perror("Eror al enlazar la memoria compartida: shmat");
		exit(-1);
	}
	s=shm;
	for ( c='a';c<= 'z';c++)
	{
		*s++=c;
	}
	*s='\0';
	while(*shmat!='*')
	{
		sleep(1);
	}
	exit(0;)
}