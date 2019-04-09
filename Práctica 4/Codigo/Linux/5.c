#include "Operaciones.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>	
#include <sys/wait.h>
#include <sys/timeb.h>


int main(int argc, char const *argv[])
{
	clock_t inicio,fin;
	double total;
	struct timeb start,end;
	int diff;
	ftime(&start);
	int Matriz[10][10];
	int MatrizAux[10][10];
	int aux[10][10];
	float resultado[10][10];
	int id_proc;
	int i,j;
	char c;
	FILE * fp;
	inicio=clock();
	CrearMatriz(Matriz);
	sleep(2);
	CrearMatriz(MatrizAux);
	if((id_proc=fork())==0){
		if((id_proc=fork())==0){
			fp=fopen("SumaMatrices.txt","w");
			if(fp){
				fprintf(fp, "Matriz A y Matriz B:\n");
				for(i=0;i<10;i++){
					for(j=0;j<10;j++){
						fprintf(fp, "%d ",Matriz[i][j]);
					}
					fprintf(fp, "\n");
				}
				fprintf(fp,"\n");
				
				for(i=0;i<10;i++){
					for(j=0;j<10;j++){
						fprintf(fp, "%d ",MatrizAux[i][j]);
					}
					fprintf(fp, "\n");
				}
				Suma(aux,Matriz,MatrizAux);
				fprintf(fp, "\nSuma de las Matrices:\n");
				for(i=0;i<10;i++){
					for(j=0;j<10;j++){
						fprintf(fp, "%d ",aux[i][j]);
					}
					fprintf(fp, "\n");
				}
				fclose(fp);
			}
			else{
				printf("Archivo no creado\n");
			}
			
			exit(0);
		}
		if((id_proc=fork())==0){
			fp=fopen("RestaMatrices.txt","w");
			if(fp){
				fprintf(fp, "Matriz A y Matriz B:\n");
				for(i=0;i<10;i++){
					for(j=0;j<10;j++){
						fprintf(fp, "%d ",Matriz[i][j]);
					}
					fprintf(fp, "\n");
				}
				fprintf(fp,"\n");
				for(i=0;i<10;i++){
					for(j=0;j<10;j++){
						fprintf(fp, "%d ",MatrizAux[i][j]);
					}
					fprintf(fp, "\n");
				}
				Resta(aux,Matriz,MatrizAux);
				fprintf(fp, "\nResta de las Matrices:\n");
				for(i=0;i<10;i++){
					for(j=0;j<10;j++){
						fprintf(fp, "%d ",aux[i][j]);
					}
					fprintf(fp, "\n");
				}
				fclose(fp);

			}
			else{
				printf("Archivo no creado\n");
			}
			exit(0);
		}
		if((id_proc=fork())==0){
			fp=fopen("MultiplicacionMatrices.txt","w");
			if(fp){
				fprintf(fp, "Matriz A y Matriz B:\n");
				for(i=0;i<10;i++){
					for(j=0;j<10;j++){
						fprintf(fp, "%d ",Matriz[i][j]);
					}
					fprintf(fp, "\n");
				}
				fprintf(fp,"\n");
				for(i=0;i<10;i++){
					for(j=0;j<10;j++){
						fprintf(fp, "%d ",MatrizAux[i][j]);
					}
					fprintf(fp, "\n");
				}
				Multiplicacion(aux,Matriz,MatrizAux);
				fprintf(fp, "\nMultiplicacion de las Matrices:\n");
				for(i=0;i<10;i++){
					for(j=0;j<10;j++){
						fprintf(fp, "%d ",aux[i][j]);
					}
					fprintf(fp, "\n");
				}
				fclose(fp);
			}
			else{
				printf("Archivo no creado\n");
			}
			
			exit(0);
		}
		if((id_proc=fork())==0){
			fp=fopen("TranspuestaMatriz.txt","w");
			if(fp){
				fprintf(fp, "Matriz A\n");
				for(i=0;i<10;i++){
					for(j=0;j<10;j++){
						fprintf(fp, "%d ",Matriz[i][j]);
					}
					fprintf(fp, "\n");
				}
				fprintf(fp,"\n");
				fprintf(fp, "Matriz B\n");
				for(i=0;i<10;i++){
					for(j=0;j<10;j++){
						fprintf(fp, "%d ",MatrizAux[i][j]);
					}
					fprintf(fp, "\n");
				}
				
				Transpuesta(aux,Matriz);
				fprintf(fp, "\nMatriz Transpuesta A\n");
				for(i=0;i<10;i++){
					for(j=0;j<10;j++){
						fprintf(fp, "%d ",aux[i][j]);
					}
					fprintf(fp, "\n");
				}
				Transpuesta(aux,MatrizAux);
				fprintf(fp, "\nMatriz Transpuesta B\n");
				for(i=0;i<10;i++){
					for(j=0;j<10;j++){
						fprintf(fp, "%d ",aux[i][j]);
					}
					fprintf(fp, "\n");
				}
				fclose(fp);

			}
			else{
				printf("Archivo no creado\n");
			}
			exit(0);
		}
		if((id_proc=fork())==0){
			fp=fopen("MatrizInversa.txt","w");
			if(fp){
				fprintf(fp, "Matriz A\n");
				for(i=0;i<10;i++){
					for(j=0;j<10;j++){
						fprintf(fp, "%d ",Matriz[i][j]);
					}
					fprintf(fp, "\n");
				}
				fprintf(fp,"\n");
				fprintf(fp, "Matriz B\n");
				for(i=0;i<10;i++){
					for(j=0;j<10;j++){
						fprintf(fp, "%d ",MatrizAux[i][j]);
					}
					fprintf(fp, "\n");
				}
				
				Inversas(Matriz,resultado);
				fprintf(fp, "\nMatriz Iinversa A\n");
				for(i=0;i<10;i++){
					for(j=0;j<10;j++){
						fprintf(fp, "%4.2f  ",resultado[i][j]);
					}
					fprintf(fp, "\n");
				}
				Inversas(MatrizAux,resultado);
				fprintf(fp, "\nMatriz Iinversa B\n");
				for(i=0;i<10;i++){
					for(j=0;j<10;j++){
						fprintf(fp, "%4.2f  ",resultado[i][j]);
					}
					fprintf(fp, "\n");
				}
				fclose(fp);

			}
			else{
				printf("Archivo no creado\n");
			}
			
			exit(0);
		}
		for (int i = 0; i < 5; ++i)
		{
			wait(0);
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
		exit(0);
	}
	wait(0);
	fin=clock();
	total=(double)(fin-inicio)/CLOCKS_PER_SEC;
	printf("Tiempo de ejecucion %f segudos\n",total);
	ftime(&end);
	diff=(int)(1000.0*(end.time-start.time)+(end.millitm-start.millitm));
	printf("Operation took %u milliseconds\n",diff );
	return 0;
}

