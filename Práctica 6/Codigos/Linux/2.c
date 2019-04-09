#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#define TAM_MEM 27
int main()
{
	int shmid;
	key_t llave;
	char*shm,*s;
	llave=5678;
	if ((shmid=shmget(llave,TAM_MEM,0666))<0)
	{
		perror("Eror al obtener memoria compartida:shmget");
		exit(-1);
	}
	if ((shm=shmat(shmid,NULL,0))==(char*)-1)
	{
		perror("Eror al enlazar la memoria compartida: shmat");
		exit(-1);
	}
	for (s=shm; *s!= '\0'; s++)
	{
		putchar(*s);
	}
	putchar('\n');
	*shmat='*';
	exit(0;)
}