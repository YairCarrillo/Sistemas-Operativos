#include <windows.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	int i;
	ZeroMemory(&si,sizeof(si));
	if(argc!=2){
		printf("Usar: %s Nombre_programa_hijo\n",argv[0]);
		return;
	}
	// Creación proceso hijo
	if(!CreateProcess(NULL,argv[1],NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
		printf("Fallo al invocar CreateProcess (%d)\n",GetLastError());
		return;
	}
	//Proceso Padre 
	printf("Soy el padre\n");
	WaitForSingleObject(pi.hProcess,INFINITE);
	//Terminación controlada del proceso e hijo asociado de ejecución
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}

