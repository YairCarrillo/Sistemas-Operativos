#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <windows.h>
#include <time.h>
#define TAM_MEM 27

int main(int argc, char *argv[])
{

	STARTUPINFO siH;
	PROCESS_INFORMATION piH;
	char *argvH[2];
	ZeroMemory(&siH, sizeof(siH));
	siH.cb = sizeof(siH);
	ZeroMemory(&piH, sizeof(piH));
	argvH[0] = "C:\\Users\\Alvaro\\Desktop\\Escuela\\Sistemas\\Practica6\\Emmanuel\\prueba3";
	argvH[1] = NULL;

	int A[10][10], B[10][10], b[10][10], c[10][10], d[10][10], mandada1[10][10], mandada2[10][10], producto[10][10];
	int aux, suma;
	char *PH = "PH"; //padre hijo
	char *HP = "HP"; //hijo padre
	char *HN = "HN"; //hijo nieto
	HANDLE hArchMapeoPH, hArchMapeoHP, hArchMapeoHN;
	int i, j, k, shmid;
	int *aPH, *aHP, *aHN;
	srand(time(NULL));
	int *shmPH, *shmHP, *shmHN;
	if (!CreateProcess(NULL, argvH[0], NULL, NULL, FALSE, 0, NULL, NULL, &siH, &piH))
	{
		printf("Fallo al invocar CreateProcess(%d)\n", GetLastError());
		return;
	}
	//	WaitForSingleObject(piH.hProcess,INFINITE);

	//MANDA MATRIZ A NIETO
	if ((hArchMapeoHN = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, TAM_MEM, HN)) == NULL)
	{
		printf("No se mapeo la memoria compartida: (%i)\n", GetLastError());
		exit(-1);
	}
	if ((shmHN = (int *)MapViewOfFile(hArchMapeoHN, FILE_MAP_ALL_ACCESS, 0, 0, TAM_MEM)) == NULL)
	{
		printf("No se creo la memoria compartida: (%i)\n", GetLastError());
		CloseHandle(hArchMapeoHN);
		exit(-1);
	}
	aHN = shmHN;

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			*aHN = rand() % 15 * 7;
			mandada1[i][j] = *aHN;
			*aHN++;
		}
	}
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			*aHN = rand() % 15 * 8;
			mandada2[i][j] = *aHN;
			*aHN++;
		}
	}
	*aHN = 101;
	while (*shmHN != -1)
		sleep(1);
	printf("2 MATRICES. HIJO -> NIETO. HIJO.\nMatriz 1.\n");
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%d\t", mandada1[i][j]);
		}
		printf("\n");
	}
	printf("Matriz 2.\n");
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%d\t", mandada2[i][j]);
		}
		printf("\n");
	}
	UnmapViewOfFile(shmHN);
	CloseHandle(hArchMapeoHN);


	//RECIBE MATRIZ DEL PADRE
	if ((hArchMapeoPH = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, PH)) == NULL)
	{
		printf("No se ario archsadfadsfdfdfdivo de mapeo de la memoria: (%i)\n", GetLastError());
		exit(-1);
	}
	if ((shmPH = (int *)MapViewOfFile(hArchMapeoPH, FILE_MAP_ALL_ACCESS, 0, 0, TAM_MEM)) == NULL)
	{
		printf("No se accedio a la memoria compartida: (%i)\n", GetLastError());
		CloseHandle(hArchMapeoPH);
		exit(-1);
	}
	aPH = shmPH;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			A[i][j] = *aPH;
			aPH++;
		}
	}
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			B[i][j] = *aPH;
			aPH++;
		}
	}
	*shmPH = -1;
	printf("2 MATRICES. PADRE -> HIJO. HIJO.\nMatriz 1\n");
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%d\t", A[i][j]);
		}
		printf("\n");
	}
	printf("\nMatriz 2\n");
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%d\t", B[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	UnmapViewOfFile(shmPH);
	CloseHandle(hArchMapeoPH);
	//HACE EL PRODUCTO
	for (i = 0; i<10; i++)
	{
		for (j = 0; j<10; j++)
		{
			aux = 0;
			suma = 0;
			while (aux<10)
			{
				suma += A[i][aux] * B[aux][j];
				aux++;
			}
			producto[i][j] = suma;
		}
	}


	//MANDA MATRIZ AL PADRE

	if ((hArchMapeoHP = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, TAM_MEM, HP)) == NULL)
	{
		printf("No se mapeo la memoria compartida: (%i)\n", GetLastError());
		exit(-1);
	}
	if ((shmHP = (int *)MapViewOfFile(hArchMapeoHP, FILE_MAP_ALL_ACCESS, 0, 0, TAM_MEM)) == NULL)
	{
		printf("No se creo la memoria compartida: (%i)\n", GetLastError());
		CloseHandle(hArchMapeoHP);
		exit(-1);
	}
	aHP = shmHP;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			*aHP = producto[i][j];
			*aHP++;
		}
	}
	printf("PRODUCTO. HIJO -> PADRE. HIJO.\n");
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%d\t", producto[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	*aHP = 101;
	while (*shmHP != -1)
		sleep(1);
	UnmapViewOfFile(shmHP);
	CloseHandle(hArchMapeoHP);
	CloseHandle(piH.hProcess);
	CloseHandle(piH.hThread);
	exit(0);//break;
}

prueba3.c  - Recibe 2 matrices de su proceso padre (hijo/prueba2), calcula su producto y los envia al proceso abuelo (padre/prueba1).
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <windows.h>
#include <time.h>
#define TAM_MEM 27

int main(int argc, char *argv[])
{
	int A[10][10], B[10][10], b[10][10], suma[10][10], d[10][10], mandada1[10][10], mandada2[10][10];
	char *NP = "NP";
	char *HN = "HN";
	HANDLE hArchMapeoNP, hArchMapeoHN;
	int i, j, k, shmid;
	int *aHN, *aNP;
	srand(time(NULL));
	int *shmNP, *shmHN;
	//RECIBE MATRIZ DEL HIJO
	if ((hArchMapeoHN = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, HN)) == NULL)
	{
		printf("No se ario archivode mapeo de la memoria: (%i)\n", GetLastError());
		exit(-1);
	}
	if ((shmHN = (int *)MapViewOfFile(hArchMapeoHN, FILE_MAP_ALL_ACCESS, 0, 0, TAM_MEM)) == NULL)
	{
		printf("No se accedio a la memoria compartida: (%i)\n", GetLastError());
		CloseHandle(hArchMapeoHN);
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
	printf("2 MATRICES. HIJO -> NIETO. NIETO.\nMatriz 1\n");
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%d\t", A[i][j]);
		}
		printf("\n");
	}
	printf("\nMatriz 2\n");
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%d\t", B[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	UnmapViewOfFile(shmHN);
	CloseHandle(hArchMapeoHN);
	//HACE LA SUMA
	for (i = 0; i<10; i++)
	{
		for (j = 0; j<10; j++)
		{
			suma[i][j] = A[i][j] + B[i][j];
		}
	}



	//MANDA MATRIZ AL PADRE

	if ((hArchMapeoNP = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, TAM_MEM, NP)) == NULL)
	{
		printf("No se mapeo la memoria compartida: (%i)\n", GetLastError());
		exit(-1);
	}
	if ((shmNP = (int *)MapViewOfFile(hArchMapeoNP, FILE_MAP_ALL_ACCESS, 0, 0, TAM_MEM)) == NULL)
	{
		printf("No se creo la memoria compartida: (%i)\n", GetLastError());
		CloseHandle(hArchMapeoNP);
		exit(-1);
	}
	aNP = shmNP;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			*aNP = suma[i][j];
			*aNP++;
		}
	}
	printf("SUMA. NIETO -> PADRE. NIETO.\n");
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%d\t", suma[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	*aNP = 101;
	while (*shmNP != -1)
		sleep(1);
	UnmapViewOfFile(shmNP);
	CloseHandle(hArchMapeoNP);

	exit(0);
}
