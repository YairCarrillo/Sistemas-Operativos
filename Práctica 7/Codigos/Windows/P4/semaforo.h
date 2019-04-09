#include <windows.h>
#include <stdio.h>
 
HANDLE crea_semaforo(char* id)
{
        HANDLE smp;
        smp=CreateSemaphore(NULL,1,1,id);
        if(smp==NULL)
        {
                printf("Error al ejecutar el semaforo \n");
                exit(-1);
        }
        return smp;
}
HANDLE  abre_semaforo(char* id)
{
        HANDLE smp;
        smp=OpenSemaphore(SEMAPHORE_ALL_ACCESS,FALSE,id);
        if(smp==NULL)
        {
                printf("Error al abrir el semaforo \n");
                exit(-1);
        }
        return smp;
}
 
 
void libera_semaforo(HANDLE hsemaphore)
{
        if(!ReleaseSemaphore(hsemaphore,1,NULL))
        {
                printf("Error al invocar el semaforo\n");
                exit(-1);
        }
 
}
 
void ocupa_semaforo(HANDLE hsemaforo)
{
        WaitForSingleObject(hsemaforo,INFINITE);
}

