#include<windows.h>
#include<stdio.h>

int 
main(int argc, char *argv[])
{
	
	STARTUPINFO si;
		PROCESS_INFORMATION pi;
		DWORD pid = GetCurrentProcessId();
		int		i;
		argv[1]="H2.exe";
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		//printf("\n");
		//printf("-Proceso Hijo1-\n");
		for (i = 0; i < 5; i++) {
			if (!CreateProcess(NULL, argv[1], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
				printf("Fallo al invocar CreateProcess(%d)\n", GetLastError());
				return;
		} 
	} 
		for(i=0;i<5;i++){
			WaitForSingleObject(pi.hProcess, INFINITE);
		}
		
		printf("El ID de este proceso es: %d padre %d\n", pid);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
} 
