#include <windows.h>		/* Servidor de la memoria compartida */
#include <stdio.h>		/* ejecutar el servidor antes de ejecutar el
				 * cliente */
#define TAM_MEM 27		/* Tamaño de la memoria compartida en bytes */
int
main(void)
{
	HANDLE		hArchMapeo;
	char           *idMemCompartida = "Memoria compartida";
	char           *apDatos, *apTrabajo, c;
	if ((hArchMapeo = CreateFileMapping(
					    INVALID_HANDLE_VALUE	/* Usa memoria
									 * compartida */
					    ,NULL	/* Seguridad por default */
					    ,PAGE_READWRITE	/* Acceso
								 * lectura/escritura a
								 * la memoria compartida */
					    ,0	/* Tamaño máximo parte alta
						 * de un DWORD */
					    ,TAM_MEM	/* Tamaño máximo parte
							 * baja de un DWORD */
					    ,idMemCompartida)	/* Identificador de la
								 * memoria compartida */
	     ) == NULL) {
		printf("No se mapeo  la memoria compartida: (%i)\n", GetLastError());
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
	apTrabajo = apDatos;
	for (c = 'a'; c <= 'z'; c++) {
		*apTrabajo++ = c;
	}
	*apTrabajo = '\0';
	while (*apDatos != '*') {
		sleep(1);
	}
	UnmapViewOfFile(apDatos);
	CloseHandle(hArchMapeo);
	exit(0);
}
