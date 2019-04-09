#include<windows.h>
#include<stdio.h>
int 
main(int argc, char *argv[])
{
	DWORD pid = GetCurrentProcessId();
		printf("El ID de este proceso hijo es: %d padre %d\n", pid);
		return 0;
} 
