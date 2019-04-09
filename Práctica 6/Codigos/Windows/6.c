#include <windows.h>		/* Cliente de la memoria compartida */
#include <stdio.h>		/* Tamaño de la memoria compartida en bytes */
#define TAM_MEM 27
int
main(void)
{
	HANDLE		hArchMapeo;
	char           *idMemCompartida = "Memoria compartida";
	char           *apDatos, *apTrabajo, c;
	if ((hArchMapeo = OpenFileMapping(
					  FILE_MAP_ALL_ACCESS	/* Accesos
								 * lectura/escritura de
								 * la memoria compartida */
					  ,FALSE	/* No herada el nombre */
					  ,idMemCompartida)	/* Identificador de la
								 * memoria compartida */
	     ) == NULL) {
		printf("No se abrio archivo de mapeo de la memoria compartida: (%i)\n", GetLastError());
		exit(-1);
	}
	if ((apDatos = (char *)MapViewOfFle(hArchMapeo,	/* Manejador del mapeo */
					    FILE_MAP_ALL_ACCESS,	/* Permido de
									 * lectura/escritura de
									 * la memoria compartida */
					    0, 0, TAM_MEM)) == NULL) {
		printf("No se accedio a  la memoria compartida: (%i)\n", GetLastError());
		CloseHandle(hArchMapeo);
		exit(-1);
	}
	for (apTrabajo = apDatos; *apTrabajo != '\0', apTrabajo++) {
		putchar(*apTrabajo);
	}
	putchar('\n');
	*apDatos = '*';
	UnmapViewOfFile(apDatos);
	CloseHandle(hArchMapeo);
	exit(0);
}
