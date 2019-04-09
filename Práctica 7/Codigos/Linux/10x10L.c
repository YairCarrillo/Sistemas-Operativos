#include <sys/types.h>         
#include <sys/ipc.h>           
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
#include "memory.h"
 
int main ()
{
  int semaforo [2];
  matriz A, B, C, D, E, F;
  double *AuxMemoria1, *AuxMemoria2;
  key_t llave1 = 1000;
  key_t llave2 = 2000;

  AuxMemoria1 = startMemory (llave1);
  AuxMemoria2 = startMemory (llave2);
  semaforo [0] = IniciarSemaforo ();
  semaforo [1] = IniciarSemaforo ();
 
  if (fork () == 0)
    {
      if (fork () == 0)
        {                      
          D = castMemory (AuxMemoria1);
          E = castMemory (AuxMemoria2);
          F = suma (D, E);
          writeMemory (AuxMemoria1, F);
          EncenderSemaforo (semaforo [1]);
        }
      else
        {                      
          A = castMemory (AuxMemoria1);
          B = castMemory (AuxMemoria2);
          C = multiplicacion (A, B);
       
          D = matrizAleatoria ();
          E = matrizAleatoria ();
          writeMemory (AuxMemoria1, D);
	      writeMemory (AuxMemoria2, E);
          ApagarSemaforo (semaforo [1]);
          writeMemory (AuxMemoria2, C);
          EncenderSemaforo (semaforo [0]);
        }
    }
  else
    {                          
    	A = matrizAleatoria ();
      	B = matrizAleatoria ();

      	writeMemory (AuxMemoria1, A);
     	writeMemory (AuxMemoria2, B);
	 
      	ApagarSemaforo (semaforo [0]);
      	printf ("\nInversa de la multiplicacion de dos matrices\n");
      	C = inversa (castMemory (AuxMemoria2));
      	writeFile (C, "inversaMultiplicacion.txt");
      	printMatriz (C);
 
     	printf ("\nInversa de la suma de dos matrices\n");
     	F = inversa (castMemory (AuxMemoria1));
    	writeFile (F, "inversaSuma.txt");
	    printMatriz (F);
    }
  	exit (0);
}
