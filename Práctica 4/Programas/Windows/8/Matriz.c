#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "Operaciones.h"
#include <sys\timeb.h>

int main(int argc, char const *argv[])
{
	clock_t inicio,fin;
	double total;
	struct timeb start,end;
	int diff;
	ftime(&start);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	int i;
	ZeroMemory(&si,sizeof(si));
	if(argc!=6){
		printf("Usar: %s Nombre_programa_hijo\n",argv[0]);
		return 0;
	}
	// Creación proceso hijo
	inicio=clock();
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
	fin=clock();
	total=(double)(fin-inicio)/CLOCKS_PER_SEC;
	printf("Tiempo de ejecucion %f segudos\n",total);
	ftime(&end);
	diff=(int)(1000.0*(end.time-start.time)+(end.millitm-start.millitm));
	printf("Operation took %u milliseconds\n",diff );
	return 0;
}
