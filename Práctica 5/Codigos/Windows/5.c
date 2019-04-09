#include <windows.h>
#include <stdio.h>
DWORD WINAPI hilo(LPVOID lpParam);
DWORD	WINAPI hhilo(LPVOID lpParam);
DWORD	WINAPI hhhilo(LPVOID lpParam);
DWORD WINAPI hilo(LPVOID lpParam)
{
	DWORD		idHilo;
	int i ;
	HANDLE		manHilo;
	printf("ID: %d \n", GetCurrentThreadId());
	for (i= 0; i < 10; ++i) 
	{
		manHilo = CreateThread(NULL, 0, hhilo, NULL, 0, &idHilo);
		WaitForSingleObject(manHilo, INFINITE);
		CloseHandle(manHilo);
	}
	return 0;
}

DWORD	WINAPI hhilo(LPVOID lpParam)
{
	DWORD		idHilo;
	HANDLE		manHilo;
	int i;
	printf("ID: %d \n", GetCurrentThreadId());
	for ( i= 0; i < 5; ++i) {
		manHilo = CreateThread(NULL, 0, hhhilo, NULL, 0, &idHilo);
		WaitForSingleObject(manHilo, INFINITE);
		CloseHandle(manHilo);
	}
	return 0;
}

DWORD	WINAPI hhhilo(LPVOID lpParam)
{
	printf("Practica5\n");
	return 0;
}

int
main(void)
{
	DWORD		idHilo;
	HANDLE		manHilo;
	int i;
	for (i = 0; i < 15; ++i) {
		manHilo = CreateThread(NULL, 0, hilo, NULL, 0, &idHilo);
		WaitForSingleObject(manHilo, INFINITE);
		CloseHandle(manHilo);
	}
	return 0;
}


