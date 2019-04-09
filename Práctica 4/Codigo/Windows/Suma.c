#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include  "Operaciones.h"
int main(void){
	int Matriz[10][10];
	int MatrizAux[10][10];
	int aux[10][10];
	int i,j;
	FILE * fp;
	CrearMatriz(Matriz);
	sleep(20);
	CrearMatriz(MatrizAux);
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
		exit(0);
	}
	exit(0);
}
