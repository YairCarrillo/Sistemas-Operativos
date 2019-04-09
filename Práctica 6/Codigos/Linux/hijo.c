#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#define TAM_MEM 27

int main(int argc, char *argv[])
{
	key_t llavePadreHijo, llaveHijoPadre, llaveHijoNieto;
	llavePadreHijo = 1234;
	llaveHijoPadre = 4321;
	llaveHijoNieto = 5678;
	int i, j, k;
	int *aPH, *aHP, *aHN, aux, suma;
	int *shmPH, *shmHP, *shmHN, shmid;
	int A[10][10],B[10][10],producto[10][10],mandada1[10][10],mandada2[10][10];
	pid_t pid;
	char *argvH[2];
	argvH[0] = "/home/alvaro/Desktop/SO/Practica6/nieto";
	argvH[1] = NULL;
	srand(time(NULL) ); 
	if((pid = fork()) == 0)
	{
		//printf("Entro al nieto\n");
		execv(argvH[0], argvH);
	}
	else
	{
		//wait(0);
		//MANDA DOS MATRICES AL NIETO
		if((shmid = shmget(llaveHijoNieto, TAM_MEM, IPC_CREAT|0666))<0)
		{
			perror("Error al obtener la memoria compartida: shmget\n");
			exit(-1);		
		}
		if((shmHN = (int *)shmat(shmid, NULL, 0)) == (int *)-1)
		{
			perror("Error alenlazar la memoria compartida: shmat\n");
			exit(-1);
		}
		aHN = shmHN;
			for(i = 0 ; i < 10 ; i++)
			{
				for(j = 0 ; j < 10 ; j++)
				{
					*aHN = (rand()%15*rand()%15)%15;
					mandada1[i][j] = *aHN;
					//printf("%d\t",*aPH);
					*aHN++;
				}
			//	printf("\n");
			}
			//printf("\n\n");
			for(i = 0 ; i < 10 ; i++)
			{
				for(j = 0 ; j < 10 ; j++)
				{
					*aHN = (rand()%15*rand()%15)%15;
					mandada2[i][j] = *aHN;
					//printf("%d\t",*aPH);
					*aHN++;
				}
			//	printf("\n");
			}
		
		*aHN = 101;
		while(*shmHN != -1)
			sleep(1);
		printf("MATRICES MANDADAS AL NIETO. HIJO - NIETO. EN EL HIJO.\n");
		for(i = 0 ; i < 10 ; i++)
		{
			for(j = 0 ; j < 10 ; j++)
			{
				printf("%d\t",mandada1[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		for(i = 0 ; i < 10 ; i++)
		{
			for(j = 0 ; j < 10 ; j++)
			{
				printf("%d\t",mandada2[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		//SE RECIBEN DOS MATRICES DEL PADRE
		if((shmid = shmget(llavePadreHijo,TAM_MEM,0666))<0)
		{
			perror("Error al obtener memoria compartida: shmget");
			exit(-1);
		}
		if((shmPH = (int *)shmat(shmid,NULL,0))==(int *)-1)
		{
			perror("Error al enlazar la memoria compartida: shmat");
			exit(-1);
		}
		aPH = shmPH;
		//while(*aPH != 101)
		//{
			for(i = 0 ; i < 10 ; i++)
			{
				for(j = 0 ; j < 10 ; j++)
				{
					A[i][j] = *aPH;
				//	printf("%d\t",*aPH);	//aPH++;
					aPH++;
				}
			}
			for(i = 0 ; i < 10 ; i++)
			{
				for(j = 0 ; j < 10 ; j++)
				{
	B[i][j] = *aPH;
				//	printf("%d\t",*aPH);//aPH++;
					aPH++;
				}
			}
		//}
		*shmPH = -1;
		printf("MATRICES RECIBIDAS DEL PADRE. PADRE - HIJO. EN EL HIJO.\n");	
		for(i = 0 ; i < 10 ; i++)
		{
			for(j = 0 ; j < 10 ; j++)
			{
				printf("%d\t",A[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		for(i = 0 ; i < 10 ; i++)
		{
			for(j = 0 ; j < 10 ; j++)
			{
				printf("%d\t",B[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		//SE HACE EL PRODUCTO

		for(i=0;i<10;i++)
		{
			for(j=0;j<10;j++)	
			{
				aux=0;
				suma=0;
				while(aux<10)
				{
					suma+=A[i][aux]*B[aux][j];
					aux++;
				}
				producto[i][j]=suma;
			}
		}
		printf("PRODUCTO DE MATRICES. EN EL HIJO.\n");
		for(i = 0 ; i < 10 ; i++)
		{
			for(j = 0 ; j < 10 ; j++)
			{
				printf("%d\t",producto[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		
		//SE DEVUELVE EL PRODUCTO AL PADRE
		if((shmid = shmget(llaveHijoPadre, TAM_MEM, IPC_CREAT|0666))<0)
		{
			perror("Error al obtener la memoria compartida: shmget");
			exit(-1);
		}
		if((shmHP = (int *)shmat(shmid,NULL,0)) == (int *)-1)
		{
			perror("Error al enlazar la memoria compartida: shmat");
			exit(-1);
		}
		aHP = shmHP;
		for(i = 0 ; i < 10 ; i++)
		{
			for(j = 0 ; j < 10 ; j++)
			{
				*aHP++ = producto[i][j];
			}
		}
		*aHP = 101;
		while(*shmHP != -1)
			sleep(1);

	exit(0);//break;
	}
	return 0;
	//exit(0);
}
