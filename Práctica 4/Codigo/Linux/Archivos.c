#include <stdio.h>
#include <time.h>
#include "Operaciones.h"
#include <sys/timeb.h>

int main(int argc, char const *argv[])
{
	printf("\nSuma de Matrices\n");
	LeerArchivo("SumaMatrices.txt");
	printf("Resta de Matrices\n");
	LeerArchivo("RestaMatrices.txt");
	printf("Multiplicacion de Matrices\n");
	LeerArchivo("MultiplicacionMatrices.txt");
	printf("Transpuesta de una Matrices\n");
	LeerArchivo("TranspuestaMatriz.txt");
	printf("Matricez Inversa\n");
	LeerArchivo("MatrizInversa.txt");
	
	exit(0);
}