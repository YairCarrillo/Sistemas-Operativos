/* Programa hijo.c */
#include "windows.h"
#include "stdio.h"
int 
main()
{
	char		mensaje   [20];
	DWORD		leidos;
	HANDLE		hStdIn = GetStdtHandle(STD_INPUT_HANDLE);
	SEGURITY_ATRIBUTES pipeSeg = {sizeof(SEGURITY_ATTRIBUTES), NULL, TRUE};
	/* Lectura desde la tuberia sin nombre */
	ReadFile(hStdIn, mensaje, sizeof(mensaje), &leidos, NULL);
	printf("Mensaje recibido del proceso padre:%s\n", mensaje);
	CloseHandle(hStdIn);
	printf("Termina el proceso hijo, continua el proceso padre\n");
	return 0;
}
