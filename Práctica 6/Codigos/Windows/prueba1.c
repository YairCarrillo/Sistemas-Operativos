#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>
#define TAM_MEM 27

//INVERSA
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
	m1 = fopen("C:\\Users\\Alvaro\\Desktop\\Escuela\\Sistemas\\Practica6\\Emmanuel\\inversa1.txt", "w");
	m2 = fopen("C:\\Users\\Alvaro\\Desktop\\Escuela\\Sistemas\\Practica6\\Emmanuel\\inversa2.txt", "w");
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
					fprintf(m1, "\t%.2f\t ", c[i][j]);
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
					fprintf(m2, "\t%.2f\t", d[i][j]);
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
	//Para crear el proceso
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	char *argv[2];
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	argv[0] = "C:\\Users\\Alvaro\\Desktop\\Escuela\\Sistemas\\Practica6\\Emmanuel\\prueba2";
	argv[1] = NULL;
	int A[10][10], B[10][10], b[10][10], c[10][10], d[10][10], mandada1[10][10], mandada2[10][10];
	char *HP = "HP";//Padre hijo
	char *PH = "PH";//hijo padre
	char *NP = "NP";//nieto padre
	HANDLE hArchMapeoPH, hArchMapeoHP, hArchMapeoNP;//1, hArchMapeo2;
	int i, j, k;
	int *aPH, *aHP, *aNP;
	int *shmPH, *shmHP, *shmNP;
	srand(time(NULL));
	if (!CreateProcess(NULL, argv[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		printf("Fallo al invocar CreateProcess(%d)\n", GetLastError());
		return;
	}
	//WaitForSingleObject(pi.hProcess,INFINITE);
	//MANDA 2 MATRICES A HIJO
	if ((hArchMapeoPH = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, TAM_MEM, PH)) == NULL)
	{
printf("No se mapeo la memoria compartida: (%i)\n", GetLastError());
		exit(-1);
	}
	if ((shmPH = (int *)MapViewOfFile(hArchMapeoPH, FILE_MAP_ALL_ACCESS, 0, 0, TAM_MEM)) == NULL)
	{
		printf("No se creo la memoria compartida: (%i)\n", GetLastError());
		CloseHandle(hArchMapeoPH);
		exit(-1);
	}
	aPH = shmPH;

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			*aPH = rand() % 15;
			mandada1[i][j] = *aPH;
			*aPH++;
		}
	}
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			*aPH = rand() % 15;
			mandada2[i][j] = *aPH;
			*aPH++;
		}
	}
	*aPH = 101;
	while (*shmPH != -1)
		sleep(1);
	printf("2 MATRICES. PADRE -> HIJO. PADRE.\nMatriz 1.\n");
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%d\t", mandada1[i][j]);
		}
		printf("\n");
	}
	printf("Matriz 2\n");
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%d\t", mandada2[i][j]);
		}
		printf("\n");
	}
	UnmapViewOfFile(shmPH);
	CloseHandle(hArchMapeoPH);

	//RECIBE MATRIZ DEL HIJO

	if ((hArchMapeoHP = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, HP)) == NULL)
	{
		printf("No se ario archsadfadsfdfdfdivo de mapeo de la memoria: (%i)\n", GetLastError());
		exit(-1);
	}
	if ((shmHP = (int *)MapViewOfFile(hArchMapeoHP, FILE_MAP_ALL_ACCESS, 0, 0, TAM_MEM)) == NULL)
	{
		printf("No se accedio a la memoria compartida: (%i)\n", GetLastError());
		CloseHandle(hArchMapeoHP);
		exit(-1);
	}
	aHP = shmHP;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			A[i][j] = *aHP++;
			//aHP++;
		}
	}
	*shmHP = -1;
	printf("PRODUCTO. HIJO -> PADRE. PADRE.\n");
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%d\t", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
UnmapViewOfFile(shmHP);
	CloseHandle(hArchMapeoHP);

	//RECIBE MATRIZ DEL NIETO

	if ((hArchMapeoNP = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, NP)) == NULL)
	{
		printf("No se ario PADRE archivo de mapeo de la memoria: (%i)\n", GetLastError());
		exit(-1);
	}
	if ((shmNP = (int *)MapViewOfFile(hArchMapeoNP, FILE_MAP_ALL_ACCESS, 0, 0, TAM_MEM)) == NULL)
	{
		printf("No se accedio a la memoria compartida: (%i)\n", GetLastError());
		CloseHandle(hArchMapeoNP);
		exit(-1);
	}
	aNP = shmNP;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			B[i][j] = *aNP++;
		}
	}
	*shmNP = -1;
	printf("SUMA. NIETO -> PADRE. PADRE.\n");
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%d\t", B[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	UnmapViewOfFile(shmNP);
	CloseHandle(hArchMapeoNP);
	invMat(A, B);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return 0;
}
