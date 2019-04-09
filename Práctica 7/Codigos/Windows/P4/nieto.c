#include <stdio.h>
#include "semaforo.h"
#include "matriz.h"
#include <windows.h>
#define TAM_MEM 400

HANDLE 
crea_memoria(char *id_memoria)
{
	HANDLE		han = CreateFileMapping(
					INVALID_HANDLE_VALUE,
					NULL,
					PAGE_READWRITE,
					0,
					TAM_MEM,
					id_memoria);
	if ((han) == NULL) {
		printf("%s\n", "Fallo creación de Memoria");
		exit(-1);
	}
	return han;
}

float          *
inicializa_memoria(HANDLE hArchMapeo)
{
	float          *in = (float *)MapViewOfFile(hArchMapeo,
						    FILE_MAP_ALL_ACCESS,
						    0,
						    0,
						    TAM_MEM);
	if (in == NULL) {
		printf("%s (%i)\n", "No se accedio a la Memoria compartida", GetLastError());
		CloseHandle(in);
		exit(-1);
	}
	return in;
}

int 
main(int argc, char const *argv[])
{
	char           *id_memoria = "Memoria";
	char           *id_memoria2 = "Memoria2";
	char           *id_memoria3 = "Memoria3";
	char           *id_semaforo = "semaforo";
	char           *id_semaforo2 = "semaforo2";
	char           *id_semaforo3 = "semaforo3";
	STARTUPINFO	si;
	PROCESS_INFORMATION pi;
	HANDLE		bloque1;
	HANDLE		bloque2;
	HANDLE		bloque3;
	HANDLE		hsem;
	HANDLE		hsem2;
	HANDLE		hsem3;
	float          *apdatos, *c, *apdatos2, *d, *apdatos3, *e;
	bloque1 = crea_memoria(id_memoria);
	apdatos = inicializa_memoria(bloque1);
	bloque2 = crea_memoria(id_memoria2);
	apdatos2 = inicializa_memoria(bloque2);
	bloque3 = crea_memoria(id_memoria3);
	apdatos3 = inicializa_memoria(bloque3);
	Sleep(200);
	hsem2 = abre_semaforo(id_semaforo2);
	ocupa_semaforo(hsem2);
	//creo tecer semaforo;
	printf("soy el nieto entrando al segundo semaforo\n");
	c = apdatos;
	d = apdatos2;
	e = apdatos3;
	libera_semaforo(hsem2);
	printf("soy el el nieto saliendo del segundo semaforo\n");
	printf("soy el el nieto entrando al tecer semaforo\n");
	hsem3 = crea_semaforo(id_semaforo3);
	ocupa_semaforo(hsem3);
	suma(c, d, e);
	e = apdatos3;
	muestra(e);
	Sleep(350);
	libera_semaforo(hsem3);
	printf("soy el el nieto liberando el tercer semaforo\n");
	Sleep(300);
	UnmapViewOfFile(apdatos);
	CloseHandle(bloque1);
	exit(0);
	return 0;
}
