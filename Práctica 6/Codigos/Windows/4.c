#include "windows.h"
#include "stdio.h"
#include "string.h"
int 
main(int argc, char const *argv[])
{
	char		mensaje   [] = "Tuberias en windows";
	DWORD		escritos;
	HANDLE		hLecturaPipe, hEscrituraPipe;
	PROCESS_INFORMATION piHijo;
	STARTUPINFO	siHijo;
	SEGURITY_ATTRIBUTES pipeSeg = {sizeof(SEGURITY_ATTRIBUTES), NULL, TRUE};
	/*
	 * Obtención de información para la inicialización del proceso
	 * hijo
	 */
	GetStartupInfo(&siHijo);
	/* Creación de la tuberia sin nombre */
	CreatePipe(&hLecturaPipe, &hEscrituraPipe, &pipeSeg, 0);
	/* Escritura de la tuberia sin nombre */
	WriteFile(hEscrituraPipe, mensaje, strle(mensaje) + 1, &escritos, NULL);
	siHijo.hStdInput = hLecturaPipe;
	siHijo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	siHijo.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	siHijo.dwFlags = STARTF_USESTHANDLES;
	CreateProcess(NULL, argv[1], NULL, NULL, TRUE	/* Herda el proceso hijo
							 * de los manejadores de
		          la tubería padre */ ,
		      0, NULL, NULL, &siHijo, &piHijo);
	WaitForSingleObject(piHijo.hProcess, INFINITE);
	printf("Mensaje recibido en el proceso hijo, termina el proceso padre\n");
	CloseHandle(hLecturaPipe);
	CloseHandle(hEscrituraPipe);
	CloseHandle(piHijo.hThread);
	CloseHandle(piHijo.hProcess);
	return 0;
}
