#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(){
	int i,k,j,y, id_proc;
	id_proc=fork();
  if(id_proc==0)
  {
  	printf("Soy el hijo %d, mi padre es %d (main)\n", getpid(), getppid());
	for(i=0;i<10;i++)  //Creamos 10 hijos horizontales
	{
	id_proc=fork();
	if(id_proc==0){
		printf("Soy el hijo %d, mi padre es %d\n", getpid(), getppid());
		
		if(i==0) //Rama 1, genera 10 hijos lineales y el último de estos genera 10 horizontales.
		{
			for(j=0;j<10;j++)
			{
				id_proc=fork();
				if(id_proc==0)
				{
					printf("  Soy el hijo %d, mi padre es %d\n", getpid(), getppid());
					if(j==9)  //Creación de 10 hijos horizontales del 10° proceso hijo lineal del primer hijo de main
					{
						for(k=0;k<10;k++)
						{
							id_proc=fork();
							if(id_proc==0)
							{
								printf("    Soy el hijo %d, mi padre es %d\n", getpid(), getppid());
								exit(0); //Hijos horizontales requieren exit(0) en cada final de proceso hijo
							}
							else
								wait(0);
							
						}
						wait(0); 
					}
					else
						wait(0);		
				}
				else
					break;  /*El exit(0) no se pone en if pues hablamos de crear hijos linealmente, mas bien utilizamos un break cuando ya no hablamos de procesos hijos para romper el ciclo.*/
			}
			wait(0);
		}  //Final de rama 1 
		
		if(i==1) //Rama 2, generan 9 hijos lineales y el último de estos genera 9 horizontales.
		{
			for(j=0;j<9;j++)
			{
				id_proc=fork();
				if(id_proc==0)
				{
					printf("  Soy el hijo %d, mi padre es %d\n", getpid(), getppid());
					if(j==8)  //Creación de 9 hijos horizontales del 9° proceso hijo lineal del primer hijo de main
					{
						for(k=0;k<9;k++)
						{
							id_proc=fork();
							if(id_proc==0)
							{
								printf("    Soy el hijo %d, mi padre es %d\n", getpid(), getppid());
								exit(0); //Hijos horizontales requieren exit(0) en cada final de proceso hijo
							}
							else
								wait(0);
							
						}
						wait(0); 
					}
					else
						wait(0);	
				}
				else
					break;  /*El exit(0) no se pone en if pues hablamos de crear hijos linealmente, mas bien utilizamos un break cuando ya no hablamos de procesos hijos para romper el ciclo.*/
			}
			wait(0);
		}  //Final de rama 2
		
		if(i==2) //Rama 3, genera 8 hijos lineales y el último de estos genera 8 horizontales.
		{
			for(j=0;j<8;j++)
			{
				id_proc=fork();
				if(id_proc==0)
				{
					printf("  Soy el hijo %d, mi padre es %d\n", getpid(), getppid());
					if(j==7)  //Creación de 8 hijos horizontales del 8° proceso hijo lineal del primer hijo de main
					{
						for(k=0;k<8;k++)
						{
							id_proc=fork();
							if(id_proc==0)
							{
								printf("    Soy el hijo %d, mi padre es %d\n", getpid(), getppid());
								exit(0); //Hijos horizontales requieren exit(0) en cada final de proceso hijo
							}
							else
								wait(0);		
						}
						wait(0); 
					}
					else
						wait(0);	
				}
				else
					break;  /*El exit(0) no se pone en if pues hablamos de crear hijos linealmente, mas bien utilizamos un break cuando ya no hablamos de procesos hijos para romper el ciclo.*/
			}
			wait(0);
		}  //Final de rama 3  
		
		if(i==3) //Rama 4, generan 7 hijos lineales y el último de estos genera 7 horizontales.
		{
			for(j=0;j<7;j++)
			{
				id_proc=fork();
				if(id_proc==0)
				{
					printf("  Soy el hijo %d, mi padre es %d\n", getpid(), getppid());	
					if(j==6)  //Creación de 7 hijos horizontales del 7° proceso hijo lineal del primer hijo de main
					{
						for(k=0;k<7;k++)
						{
							id_proc=fork();
							if(id_proc==0)
							{
								printf("    Soy el hijo %d, mi padre es %d\n", getpid(), getppid());
								exit(0); //Hijos horizontales requieren exit(0) en cada final de proceso hijo
							}
							else
								wait(0);
							
						}
						wait(0); 
					}
					else
						wait(0);
				}
				else
					break;  /*El exit(0) no se pone en if pues hablamos de crear hijos linealmente, mas bien utilizamos un break cuando ya no hablamos de procesos hijos para romper el ciclo.*/
			}
			wait(0);
		} //Final rama 4

		if(i==4) //Rama 5, generan 6 hijos lineales y el último de estos genera 6 horizontales.
		{
			for(j=0;j<6;j++)
			{
				id_proc=fork();
				if(id_proc==0)
				{
					printf("  Soy el hijo %d, mi padre es %d\n", getpid(), getppid());	
					if(j==5)  //Creación de 6 hijos horizontales del 6° proceso hijo lineal del primer hijo de main
					{
						for(k=0;k<6;k++)
						{
							id_proc=fork();
							if(id_proc==0)
							{
								printf("    Soy el hijo %d, mi padre es %d\n", getpid(), getppid());
								exit(0); //Hijos horizontales requieren exit(0) en cada final de proceso hijo
							}
							else
								wait(0);
							
						}
						wait(0); 
					}
					else
						wait(0);
				}
				else
					break;  /*El exit(0) no se pone en if pues hablamos de crear hijos linealmente, mas bien utilizamos un break cuando ya no hablamos de procesos hijos para romper el ciclo.*/
			}
			wait(0);
		}  //Final de rama 5
		if(i==5) //Rama 6, generan 5 hijos lineales y el último de estos genera 5 horizontales.
		{
			for(j=0;j<5;j++)
			{
				id_proc=fork();
				if(id_proc==0)
				{
					printf("  Soy el hijo %d, mi padre es %d\n", getpid(), getppid());	
					if(j==4)  //Creación de 5 hijos horizontales del 5° proceso hijo lineal del primer hijo de main
					{
						for(k=0;k<5;k++)
						{
							id_proc=fork();
							if(id_proc==0)
							{
								printf("    Soy el hijo %d, mi padre es %d\n", getpid(), getppid());
								exit(0); //Hijos horizontales requieren exit(0) en cada final de proceso hijo
							}
							else
								wait(0);
							
						}
						wait(0); 
					}
					else
						wait(0);
				}
				else
					break;  /*El exit(0) no se pone en if pues hablamos de crear hijos linealmente, mas bien utilizamos un break cuando ya no hablamos de procesos hijos para romper el ciclo.*/
			}
			wait(0);
		}//Final de la rama 6

		if(i==6) //Rama 7, generan 4 hijos lineales y el último de estos genera 4 horizontales.
		{
			for(j=0;j<4;j++)
			{
				id_proc=fork();
				if(id_proc==0)
				{
					printf("  Soy el hijo %d, mi padre es %d\n", getpid(), getppid());	
					if(j==3)  //Creación de 4 hijos horizontales del 4° proceso hijo lineal del primer hijo de main
					{
						for(k=0;k<4;k++)
						{
							id_proc=fork();
							if(id_proc==0)
							{
								printf("    Soy el hijo %d, mi padre es %d\n", getpid(), getppid());
								exit(0); //Hijos horizontales requieren exit(0) en cada final de proceso hijo
							}
							else
								wait(0);
							
						}
						wait(0); 
					}
					else
						wait(0);
				}
				else
					break;  /*El exit(0) no se pone en if pues hablamos de crear hijos linealmente, mas bien utilizamos un break cuando ya no hablamos de procesos hijos para romper el ciclo.*/
			}
			wait(0);
		}  //Final de rama 7
		if(i==7) //Rama 8, generan 3 hijos lineales y el último de estos genera 3 horizontales.
		{
			for(j=0;j<3;j++)
			{
				id_proc=fork();
				if(id_proc==0)
				{
					printf("  Soy el hijo %d, mi padre es %d\n", getpid(), getppid());	
					if(j==2)  //Creación de 6 hijos horizontales del 6° proceso hijo lineal del primer hijo de main
					{
						for(k=0;k<3;k++)
						{
							id_proc=fork();
							if(id_proc==0)
							{
								printf("    Soy el hijo %d, mi padre es %d\n", getpid(), getppid());
								exit(0); //Hijos horizontales requieren exit(0) en cada final de proceso hijo
							}
							else
								wait(0);
							
						}
						wait(0); 
					}
					else
						wait(0);
				}
				else
					break;  /*El exit(0) no se pone en if pues hablamos de crear hijos linealmente, mas bien utilizamos un break cuando ya no hablamos de procesos hijos para romper el ciclo.*/
			}
			wait(0);
		}  //Final de rama 8

		if(i==8) //Rama 9, generan 2 hijos lineales y el último de estos genera 2 horizontales.
		{
			for(j=0;j<2;j++)
			{
				id_proc=fork();
				if(id_proc==0)
				{
					printf("  Soy el hijo %d, mi padre es %d\n", getpid(), getppid());	
					if(j==1)  //Creación de 2 hijos horizontales del 2° proceso hijo lineal del primer hijo de main
					{
						for(k=0;k<2;k++)
						{
							id_proc=fork();
							if(id_proc==0)
							{
								printf("    Soy el hijo %d, mi padre es %d\n", getpid(), getppid());
								exit(0); //Hijos horizontales requieren exit(0) en cada final de proceso hijo
							}
							else
								wait(0);
							
						}
						wait(0); 
					}
					else
						wait(0);
				}
				else
					break;  /*El exit(0) no se pone en if pues hablamos de crear hijos linealmente, mas bien utilizamos un break cuando ya no hablamos de procesos hijos para romper el ciclo.*/
			}
			wait(0);
		}  //Final de rama 9
		
		if(i==9) //Rama 10, generan 2 hijos lineales
		{
			for(j=0;j<2;j++)
			{
				id_proc=fork();
				if(id_proc==0)
				{
					printf("  Soy el hijo %d, mi padre es %d\n", getpid(), getppid());	
				}
				else
					break;  /*El exit(0) no se pone en if pues hablamos de crear hijos linealmente, mas bien utilizamos un break cuando ya no hablamos de procesos hijos para romper el ciclo.*/
			}
			wait(0);
		}  //Final de rama 10 
		exit(0);
	}  //Final de la creacion de 10 hijos horizontales
	else	
		wait(0);
    }
    exit(0);
}
else
	wait(0);
}
