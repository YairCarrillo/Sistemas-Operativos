#include <stdio.h>
#include <stdlib.h>
#include  "Operaciones.h"
int main(int argc, char const *argv[]){
	int Matriz[10][10];
	int MatrizAux[10][10];
	int aux[10][10];
	int i,j;
	FILE * fp;
	CrearMatriz(Matriz);
	
	CrearMatriz(MatrizAux);
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

