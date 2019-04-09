#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "matriz.h"
#include "semaforo.h"
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
	if (han == NULL) {
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
	if (hArchMapeo == NULL) {
		printf("%s (%i)\n", "No se accedio a la Memoria compartida", GetLastError());
		CloseHandle(hArchMapeo);
		exit(-1);
	}
	return in;
}

void 
crea_proceso(STARTUPINFO si, PROCESS_INFORMATION pi, char *dir)
{
	if (!CreateProcess(NULL, dir, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		printf("%s\n", "Fallo al crear el proceso");

	}
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
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	HANDLE		hsemaforo;
	HANDLE		hsemaforo2;
	HANDLE		hsemaforo3;
	HANDLE		bloque1;
	HANDLE		bloque2;
	HANDLE		bloque3;
	float          *apdatos, *c, *apdatos2, *d, *apdatos3, *e;
	char           *dir = "p.exe";
	printf("%s\n", dir);
	bloque1 = crea_memoria(id_memoria);
	bloque2 = crea_memoria(id_memoria2);
	bloque3 = crea_memoria(id_memoria3);
	apdatos = inicializa_memoria(bloque1);
	apdatos2 = inicializa_memoria(bloque2);
	apdatos3 = inicializa_memoria(bloque3);
	hsemaforo = crea_semaforo(id_semaforo);
	crea_proceso(si, pi, dir);
	ocupa_semaforo(hsemaforo);
	printf("Soy el padre ejecutando el semaforo\n");
	c = apdatos;
	d = apdatos2;
	genera_int(1, c);
	Sleep(1000);
	genera_int(1, d);
	c = apdatos;
	d = apdatos2;
	printf("%s\n", "MATRIZ 1 A TRABAJAR");
	muestra(c);
	printf("%s\n", "MATRIZ 2 A TRABAJAR");
	muestra(d);
	libera_semaforo(hsemaforo);
	Sleep(250);
	hsemaforo2 = abre_semaforo(id_semaforo2);
	ocupa_semaforo(hsemaforo2);
	printf("Soy el padre entrando al 2 el semaforo\n");
	e = apdatos3;
	inversa(e);
	e = apdatos3;
	printf("Inversa multiplicación\n");
	muestra_inversa(e);
	e = apdatos3;
	escribe(e, "InversaMultiplicación.txt");
	libera_semaforo(hsemaforo2);
	printf("%s\n", "Soy el padre saliendo del segundo semaforo");
	Sleep(600);
	hsemaforo3 = abre_semaforo(id_semaforo3);
	ocupa_semaforo(hsemaforo3);
	printf("%s\n", "Soy el padre entrando al tercer semaforo");
	e = apdatos3;
	inversa(e);
	e = apdatos3;
	printf("Inversa Suma\n");
	muestra_inversa(e);
	escribe(apdatos3, "InversaSuma.txt");
	libera_semaforo(hsemaforo3);
	printf("%s\n", "Soy el padre saliendo del tercer semaforo");
	UnmapViewOfFile(apdatos);
	UnmapViewOfFile(apdatos2);
	UnmapViewOfFile(apdatos3);
	CloseHandle(bloque1);
	CloseHandle(bloque2);
	CloseHandle(bloque3);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}
