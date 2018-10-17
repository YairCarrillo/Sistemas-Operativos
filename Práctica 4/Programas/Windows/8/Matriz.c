#include <windows.h>
#include <stdio.h>
#include "Operaciones.h"

int main(int argc, char const *argv[])
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	int i;
	ZeroMemory(&si,sizeof(si));
	if(argc!=6){
		printf("Usar: %s Nombre_programa_hijo\n",argv[0]);
		return 0;
	}
	// Creación proceso hijo
	for (i=1; i <=5; ++i)
	{
		if(!CreateProcess(NULL,argv[i],NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
			printf("Fallo al invocar CreateProcess (%d)\n",GetLastError());
			return 0;
		}
	}
	
	//Proceso Padre 
	printf("Soy el padre\n");
	for(i=0;i<5;i++){
		WaitForSingleObject(pi.hProcess,INFINITE);
	}
	
	printf("\nSuma de Matrices\n");
	LeerArchivo("SumaMatrices.txt");
	printf("Resta de Matrices\n");
	LeerArchivo("RestaMatrices.txt");
	printf("Multiplicacion de Matrices\n");
	LeerArchivo("MultiplicacionMatrices.txt");
	printf("Transpuesta de una Matrices\n");
	LeerArchivo("TranspuestaMatriz.txt");
	printf("Matricez Inversa\n");
	LeerArchivo("MatrizInversa.txt");
	//Terminación controlada del proceso e hijo asociado de ejecución
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}
