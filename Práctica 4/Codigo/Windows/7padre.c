#include<windows.h>
#include<stdio.h>

int 
main(int argc, char *argv[])
{
	STARTUPINFO si;
	DWORD pid = GetCurrentProcessId();
		PROCESS_INFORMATION pi;
		int		i;
		argv[1]="H1.exe";
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		printf("Proceso Padre\n");
		if (!CreateProcess(NULL, argv[1], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
			printf("Fallo al invocar CreateProcess(%d)\n", GetLastError());
			return;
	} 
	
		WaitForSingleObject(pi.hProcess, INFINITE);
		printf("El ID de este proceso hijo es: %d padre %d\n", pid);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

} 


