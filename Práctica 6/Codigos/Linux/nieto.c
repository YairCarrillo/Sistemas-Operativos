#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <time.h>
#define TAM_MEM 27

int main(int argc, char *argv[])
{
	key_t llaveHijoNieto, llaveNietoPadre;
	llaveHijoNieto = 5678;
	llaveNietoPadre = 8765;
	int i, j, k;
	int *aHN, *aNP;
	int *shmHN, *shmNP, shmid;
	int A[10][10], B[10][10], suma[10][10];
	pid_t pid;
	//printf("DESDE EL NIETO\n");
	srand(time(NULL));
	//RECIBE DOS MATRICES DEL HIJO
if ((shmid = shmget(llaveHijoNieto, TAM_MEM, 0666))<0)
	{
		perror("Error al obtener la memoria compartida: shmget");
		exit(-1);
	}
	if ((shmHN = (int *)shmat(shmid, NULL, 0)) == (int *)-1)
	{
		perror("Error al enlazar la memora compartida: shmat");
		exit(-1);
	}
	aHN = shmHN;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			A[i][j] = *aHN;
			aHN++;
		}
	}
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			B[i][j] = *aHN;
			aHN++;
		}
	}
	*shmHN = -1;
	printf("MATRICES RECIBIDAS DEL HIJO. HIJO - NIETO. EN EL NIETO.\n");
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%d\t", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%d\t", B[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	//SE HACE LA SUMA
	for (i = 0; i<10; i++)
	{
		for (j = 0; j<10; j++)
		{
			suma[i][j] = A[i][j] + B[i][j];
		}
	}
	printf("SUMA DE MATRICES. EN EL NIETO.\n");
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%d\t", suma[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	//SE DEVUELVE LA SUMA AL PADRE
	if ((shmid = shmget(llaveNietoPadre, TAM_MEM, IPC_CREAT | 0666))<0)
	{
		perror("Error al obtener la memoria compartida: shmget");
		exit(-1);
	}
	if ((shmNP = (int *)shmat(shmid, NULL, 0)) == (int *)-1)
	{
		perror("Error al enlazar la memoria compartida: shmat");
		exit(-1);
	}
	aNP = shmNP;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			*aNP++ = suma[i][j];
		}
	}
	*aNP = 101;
	while (*shmNP != -1)
		sleep(1);

	exit(0);
}
