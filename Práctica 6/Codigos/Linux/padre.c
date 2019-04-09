#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#define TAM_MEM 27

void fila_pivote(int i, float pivote, float a[10][10], float b[10][10])
{
	int m;
	for (m = 0; m<10; m++)
		if (m != i)
			b[i][m] = a[i][m] / pivote;
}

void col_pivote(int j, float pivote, float a[10][10], float b[10][10])
{
	int m;
	for (m = 0; m<10; m++)
		if (m != j)
			b[m][j] = -a[m][j] / pivote;
}

void otros(int i, int j, float pivote, float a[10][10], float b[10][10])
{
	int x, y;
	for (x = 0; x<10; x++)
		for (y = 0; y<10; y++)
			if (x != i && y != j)
b[x][y] = a[x][y] - (a[i][y] * a[x][j]) / pivote;
}

//--------------------------------- INVERSA DE MATRIZ --------------------------------------------
int invMat(int A[10][10], int B[10][10])
{
	int i, j, k, l, fd = 0;
	float pivote, b[10][10], c[10][10], d[10][10];
	FILE *m1, *m2;
	m1 = fopen("/home/alvaro/Desktop/SO/Practica6/inversa1.txt", "w");
	m2 = fopen("/home/alvaro/Desktop/SO/Practica6/inversa2.txt", "w");
	//printf("  Resultados guardados en archivo inversa.txt\n"); //Esto es lo unico que se imprime en pantalla

	//----- SACANDO INVERSA DE MATRIZ A (1) ---------
	for (i = 0; i<10; i++)
		for (j = 0; j<10; j++)
			c[i][j] = (float)A[i][j];

	for (i = 0; i<10; i++)
	{
		j = i;
		pivote = c[i][j];
		if (pivote != 0.0f)
		{
			b[i][j] = 1 / pivote;
			fila_pivote(i, pivote, c, b);
			col_pivote(j, pivote, c, b);
otros(i, j, pivote, c, b);
			for (k = 0; k<10; k++)
				for (l = 0; l<10; l++)
					c[k][l] = b[k][l];
		}
		else
		{
			if (m1 != 0)
			{
				fprintf(m1, " Matriz 1 no tiene inversa\n\n");
				fclose(m1);
			}
			//		return 0;  //Cortamos el calculo pues se sabe que matriz no tiene inversa
		}
	}

	//----- SACANDO INVERSA DE MATRIZ B (2) ---------
	for (i = 0; i<10; i++)
		for (j = 0; j<10; j++)
			d[i][j] = (float)B[i][j];

	for (i = 0; i<10; i++)
	{
		j = i;
		pivote = d[i][j];
		if (pivote != 0.0f)
		{
			b[i][j] = 1 / pivote;
			fila_pivote(i, pivote, d, b);
			col_pivote(j, pivote, d, b);
			otros(i, j, pivote, d, b);
			for (k = 0; k<10; k++)
				for (l = 0; l<10; l++)
					d[k][l] = b[k][l];
		}
		else
		{
			if (m2 != 0)
			{
			fprintf(m2, " Matriz 2 no tiene inversa\n\n");
				fclose(m2);
			}
			return 0;  //Cortamos el calculo pues se sabe que matriz no tiene inversa
		}
		//----- GUARDANDO MATRICES INVERSAS ------------
		if (m1 != 0)
		{
			fprintf(m1, "\n Matriz Inversa 1: \n");
			for (i = 0; i<10; i++)  //Guardando matriz transpuesta 1 en archivo
			{
				for (j = 0; j<10; j++)
				{
					fprintf(m1, "\t%.2f ", c[i][j]);
				}
				fprintf(m1, "\n");
			}
			fclose(m1);
			//		printf("\n");
		}
		if (m2 != 0)
		{
			fprintf(m2, "\nMatriz Inversa 2: \n");
			for (i = 0; i<10; i++) //Guardando matriz transpuesta 2 en archivo
			{
				for (j = 0; j<10; j++)
				{
					fprintf(m2, "\t%.2f ", d[i][j]);
				}
				fprintf(m2, "\n");
			}  //ya acabamos de escribir en txt, ahora lo cerraremos
			fclose(m2);
		}
		//	printf("\n\n");
	}
	return 0;
}
int main(void)
{
	key_t llavePadreHijo, llaveHijoPadre, llaveNietoPadre;
	llavePadreHijo = 1234;
	llaveHijoPadre = 4321;
	llaveNietoPadre = 8765;
	int i, j, k, shmid;
	int *aPH, *aHP, *aNP;
	int *shmPH, *shmHP, *shmNP;
	int A[10][10], B[10][10], b[10][10], c[10][10], d[10][10], mandada1[10][10], mandada2[10][10];
	pid_t pid;
	char *argv[2];
	argv[0] = "/home/alvaro/Desktop/SO/Practica6/hijo";
	argv[1] = NULL;
	srand(time(NULL));
	//A sera el producto
	//B sera la suma
	if ((pid = fork()) == 0)
	{
		//printf("Entro al hijo\n");
		execv(argv[0], argv);
	}
	else
	{
		//	wait(0);

		//MANDA DOS MATRICES AL HIJO\n
		if ((shmid = shmget(llavePadreHijo, TAM_MEM, IPC_CREAT | 0666))<0)
		{
			perror("Error al obtener la memoria compartida: shmget\n");
			exit(-1);
		}
		if ((shmPH = (int *)shmat(shmid, NULL, 0)) == (int *)-1)
		{
			perror("Error alenlazar la memoria compartida: shmat\n");
			exit(-1);
		}
		aPH = shmPH;
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				*aPH = rand() % 15;
				mandada1[i][j] = *aPH;
				//printf("%d\t",*aPH);
				*aPH++;
			}
			//	printf("\n");
		}
		//printf("\n\n");
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				*aPH = rand() % 15;
				mandada2[i][j] = *aPH;
				//printf("%d\t",*aPH);
				*aPH++;
			}
			//	printf("\n");
		}
		//printf("\n\n");
		*aPH = 101;
		while (*shmPH != -1)
			sleep(1);
		printf("MATRICES MANDADAS AL HIJO. PADRE - HIJO. EN EL PADRE.\n");
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				printf("%d\t", mandada1[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				printf("%d\t", mandada2[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		//RECIBRE PRIMERA MATRIZ - PRODUCTO

		if ((shmid = shmget(llaveHijoPadre, TAM_MEM, 0666))<0)
		{
			perror("Error al obtener memoria compartida: shmget");
			exit(-1);
		}
		if ((shmHP = (int *)shmat(shmid, NULL, 0)) == (int *)-1)
		{
			perror("Error al enlazar la memoria compartida: shmat");
			exit(-1);
		}
		aHP = shmHP;
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				A[i][j] = *aHP;
				aHP++;
			}
		}
		*shmHP = -1;
		printf("PRODUCTO DE MATRICES. EN EL PADRE.\n");
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				printf("%d\t", A[i][j]);
			}
			printf("\n");
		}
		printf("\n");

		//RECIBE SEGUNDA MATRIZ - SUMA
		if ((shmid = shmget(llaveNietoPadre, TAM_MEM, 0666))<0)
		{
			perror("Error al obtener memoria compartida: shmget");
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
				B[i][j] = *aNP;
				aNP++;
			}
		}
		*shmNP = -1;
		printf("SUMA DE MATRICES. EN EL PADRE. \n");
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				printf("%d\t", B[i][j]);
			}
			printf("\n");
		}
		printf("\n");

		invMat(A, B);
		exit(0);//break;
	}
	//exit(0);
	return 0; 
}
