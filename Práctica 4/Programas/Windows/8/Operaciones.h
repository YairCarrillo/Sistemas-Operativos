#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h> 


void CrearMatriz(int Matriz[10][10]);
void Suma(int aux[10][10],int Matriz1[10][10],int Matriz2[10][10]);
void Resta(int aux[10][10],int Matriz1[10][10],int Matriz2[10][10]);
void Multiplicacion(int aux[10][10],int Matriz1[10][10],int Matriz2[10][10]);
void Transpuesta(int aux[10][10],int Matriz[10][10]);
void Inversas(int Matriz[10][10],float resultado[10][10]);
void LeerArchivo(char Nombre[50]);

void CrearMatriz(int Matriz[10][10]){
	int i,j;
  	srand(time(NULL));
	for(i=0;i<10;i++){
    	for (j = 0; j < 10; j++){
    		Matriz[i][j]=rand()%10;
    	}
  	}
}

void Suma(int aux[10][10],int Matriz1[10][10],int Matriz2[10][10]){
	int i,j;
	for(i=0;i<10;i++){
    	for (j = 0; j < 10; j++){
    		aux[i][j]=Matriz1[i][j]+Matriz2[i][j];
    	}
  	}
}
void Resta(int aux[10][10],int Matriz1[10][10],int Matriz2[10][10]){
	int i,j;
	for(i=0;i<10;i++){
    	for (j = 0; j < 10; j++){
    		aux[i][j]=Matriz1[i][j]-Matriz2[i][j];
    	}
  	}
}
void Multiplicacion(int aux[10][10],int Matriz1[10][10],int Matriz2[10][10]){
	int i,j,k,temporal;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			temporal=0;
			for(k=0;k<10;k++){
				temporal+=Matriz1[i][k]*Matriz2[k][j];
				aux[i][j]=temporal;
			}
		}
	}	
}

void Transpuesta(int aux[10][10],int Matriz[10][10]){
	int i,j;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			aux[i][j]=Matriz[j][i];
		}
	}
}


void Inversas(int Matriz[10][10],float resultado[10][10]){
	int i,j,k,m,n,l;
	int x,y;
	float aux1[10][10];
	float pivote;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			resultado[i][j]=(float)Matriz[i][j];
		}
	}
	for(i=0; i<10; i++)
    {
        j=i;
        pivote=resultado[i][j];
        aux1[i][j]=1/pivote;
         
    	for(m=0; m<10; m++){
    		if(m != i)
            aux1[i][m]=resultado[i][m]/pivote;
    	}
        for(n=0; n<10; n++){
        	if(n != j)
            aux1[n][j]=-resultado[n][j]/pivote;
        }
        
        for(x=0 ;x<n; x++){
        	for(y=0; y<n; y++){
            	if(x!=i && y!=j)
                	aux1[x][y]=resultado[x][y]-(resultado[i][y]*resultado[x][j])/pivote;
        	}
        }
        for(k=0; k<10; k++){
            for(l=0; l<10; l++){
                resultado[k][l]=aux1[k][l];
            }
        }
    }
}

void LeerArchivo(char Nombre[]){
	FILE * fp;
	char c;
	fp=fopen(Nombre,"rt");
	if(fp){
		while((c=fgetc(fp))!=EOF){
			if(c=='\n'){
				printf("\n");
			}
			else{
				putchar(c);
			}
		}

	}
	else{
		printf("Archivo no se pudo abrir\n");
	}
	fclose(fp);
}
