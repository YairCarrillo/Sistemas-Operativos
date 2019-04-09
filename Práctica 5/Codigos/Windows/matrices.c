#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <fcntl.h>
#include <string.h>
#include <windows.h>

int n=10,m=10;
	int a[10][10], b[10][10],suma[10][10],resta[10][10],multi[10][10],trans1[10][10],trans2[10][10];
	double inversa1[10][10],inversa2[10][10],identidad[10][10];

void crearArchivo(int type, int matriz[n][m]){
	FILE *fp=NULL;
	int i,j,tam=1;
	if(type==1){
		fp=fopen("Suma.txt","w");
		fprintf(fp,"%s", "\n Suma de la matriz A y B:\n");
	}
	if(type==2){
		fp=fopen("Res.txt","w");
		fprintf(fp,"%s", "\n Resta de la matriz A y B:\n");
	}
	if(type==3){
		fp=fopen("Multi.txt","w");
		fprintf(fp,"%s", "\n Multiplicacion de la matriz A y B:\n");
	}
	
		for(i=0; i<n; i++){
			for(j=0; j<m; j++){
				fprintf(fp, "%s%d ","\t", matriz[i][j]);
			}
			fputs("\n",fp);
		}
	
	fclose(fp);
}

void crearArchivo2(int type){
	FILE *fp=NULL;
	int i,j,tam=1;
	if(type==4)
		fp=fopen("Trans.txt","w");
	if (fp !=NULL){
		fprintf(fp,"%s", "\nTranspuesta De La Matriz A:\n");
		for(i=0; i<n; i++){
			for(j=0; j<m; j++){
				fprintf(fp, "%s%d ","\t", trans1[i][j]);
			}
			fputs("\n",fp);
		}
		fprintf(fp,"%s", "\nTranspuesta De La Matriz B:\n");
		for(i=0; i<n; i++){
			for(j=0; j<m; j++){
				fprintf(fp, "%s%d ","\t", trans2[i][j]);
			}
			fputs("\n",fp);
		}
	}
	fclose(fp);
}

void crearArchivoD(int type){
	FILE *fp=NULL;
	int i,j,tam=1;
	if(type==5)
		fp=fopen("Inversa.txt","w");
	if (fp !=NULL){
		fprintf(fp,"%s", "\nInversa De La Matriz A:\n");
		for(i=0; i<n; i++){
			for(j=0; j<m; j++){
				fprintf(fp, "%s%f ","\t", inversa1[i][j]);
			}
			fputs("\n",fp);
		}
		fprintf(fp,"%s", "\nInversa De La Matriz B:\n");
		for(i=0; i<n; i++){
			for(j=0; j<m; j++){
				fprintf(fp, "%s%f ","\t", inversa2[i][j]);
			}
			fputs("\n",fp);
		}
	}
	fclose(fp);
}

DWORD WINAPI leerArchivo(int code2){
	FILE *archivo;
	int code;
	char caracter;
	code=(int)code2;
	if(code==1)
		archivo = fopen("Suma.txt","r");
	if(code==2)
		archivo = fopen("Res.txt","r");
	if(code==3)
		archivo = fopen("Multi.txt","r");
	if(code==4)
		archivo = fopen("Trans.txt","r");
	if(code==5)
		archivo = fopen("Inversa.txt","r");
	if (archivo == NULL){
		printf("\nError de apertura del archivo. \n\n");
    }else{
	    while (feof(archivo) == 0){
			caracter = fgetc(archivo);
			printf("%c",caracter);
	    }
    }
    fclose(archivo);	
    return 0;
}

void asignarMatriz(int a[n][m],int n,int m,int l){
	int i,j;
	if(n!=0&&m!=0&&l==1){
		for (i = 0; i < n; ++i){
			for(j=0;j<m;j++){
				a[i][j]=rand() % 10;
			}
		}
	}
	if(n!=0&&m!=0&&l==0){
		for (i = 0; i < n; ++i){
			for(j=0;j<m;j++){
				a[i][j]=0;
			}
		}
	}
}

void printMatriz(int a[n][m],int n,int m){
	int i,j;
	if(n!=0&&m!=0){
		for (i = 0; i < n; ++i){
			for(j=0;j<m;j++){
				printf("\t%d",a[i][j]);
			}
			printf("\n");
		}
	}
}

void printMatrizD(double a[n][m],int n,int m){
	int i,j;
	if(n!=0&&m!=0){
		for (i = 0; i < n; ++i){
			for(j=0;j<m;j++){
				printf("\t%f",a[i][j]);
			}
			printf("\n");
		}
	}
}

DWORD WINAPI sumaMatriz(){
	int i,j;
	if(n!=m){
		printf("\nNo se puede realizar la operacion");
	}else{
		for(i=0;i<n;i++){
			for (j = 0; j < m; j++){
				suma[i][j]=a[i][j]+b[i][j];
			}
		}
	}
	crearArchivo(1,suma);
	return 0;
}

int procesoSuma(){
	DWORD idHilo;	/*Identificador del hilo*/
	HANDLE manHilo;	//Manejador del hilo
	manHilo=CreateThread(NULL, 0, sumaMatriz, NULL,0, &idHilo);
	WaitForSingleObject(manHilo, INFINITE);
	return 0;
}

DWORD WINAPI restaMatriz(){
	int i,j;
	if(n!=m){
		printf("\nNo se puede realizar la operacion");
	}else{
		for(i=0;i<n;i++){
			for (j = 0; j < m; j++){
				resta[i][j]=a[i][j]-b[i][j];
			}
		}
	}
	crearArchivo(2,resta);
	return 0;
}

int procesoResta(){
	DWORD idHilo;	/*Identificador del hilo*/
	HANDLE manHilo;	//Manejador del hilo
	manHilo=CreateThread(NULL, 0, restaMatriz, NULL,0, &idHilo);
	WaitForSingleObject(manHilo, INFINITE);
	return 0;
}

DWORD WINAPI multiMatriz(){
	int i,j,k,cont,aux=0;
	for(i=0;i<n;i++){
		for (j = 0; j < m; j++){
			cont=0;
			for(k=0;k<n;k++){
				aux=aux+a[i][cont]*b[k][j];
				cont++;
			}
			multi[i][j]=aux;
			aux=0;
		}
	}
	crearArchivo(3,multi);
	return 0;
}

int procesoMulti(){
	DWORD idHilo;	/*Identificador del hilo*/
	HANDLE manHilo;	//Manejador del hilo
	manHilo=CreateThread(NULL, 0, multiMatriz, NULL,0, &idHilo);
	WaitForSingleObject(manHilo, INFINITE);
	return 0;
}

DWORD WINAPI transMatrizA(){
	int i,j,k,cont,aux=0;
    for(i = 0; i <n; i++){
        for(j = 0; j <m ; j++){
            trans1[i][j] = a[j][i];
        }
    }
    crearArchivo2(4);
    return 0;
}

DWORD WINAPI transMatrizB(){
	int i,j,k,cont,aux=0;
    for(i = 0; i <n; i++){
        for(j = 0; j <m ; j++){
            trans2[i][j] = b[j][i];
        }
    }
    crearArchivo2(4);
    return 0;
}

int procesoTrans(){
	DWORD idHilo,idHilo2;	/*Identificador del hilo*/
	HANDLE manHilo,manHilo2;	//Manejador del hilo
	manHilo=CreateThread(NULL, 0, transMatrizA, NULL,0, &idHilo);
	WaitForSingleObject(manHilo, INFINITE);
	manHilo2=CreateThread(NULL, 0, transMatrizB, NULL,0, &idHilo2);
	WaitForSingleObject(manHilo, INFINITE);
	return 0;
}

DWORD WINAPI inversaMatrizA(){
	int i,j,k,cont;
    double aux[n][m],count=0;
    for(i=0; i<10; i++){
		for(j=0; j<10; j++){
			if (j==i){
				identidad[i][j]=1;
			}else{
				identidad[i][j]=0;
			}					
		}
	}
	for(i = 0; i <n; i++){
		for(j = 0; j <m ; j++)
               aux[i][j] = a[i][j];
	}
	for (i=0; i<n; i++){
		count=aux[i][i];
		if(count !=1){
			for(j=0; j<m; j++){
				aux[i][j]= aux[i][j]/count;
				identidad[i][j]= identidad[i][j]/count;
			}
		}
		count=0;
		for (k=0; k<n; k++){
			if(i!=k){
				count= aux[k][i];
				for(j=0; j<m; j++){
					aux[k][j]=aux[k][j]- (count*aux[i][j]);
					identidad[k][j]=identidad[k][j]-(count*identidad[i][j]);
				}
			}
		}
		
	}
	for (i = 0; i < n; i++){
		for (j = 0; j < m; j++){
			inversa1[i][j]=identidad[i][j];
			
		}
	}
	crearArchivoD(5);
	return 0;
}

DWORD WINAPI inversaMatrizB(){
	int i,j,k,cont;
    double aux[n][m],count=0;
    for(i=0; i<10; i++){
		for(j=0; j<10; j++){
			if (j==i){
				identidad[i][j]=1;
			}else{
				identidad[i][j]=0;
			}					
		}
	}
	for(i = 0; i <n; i++){
		for(j = 0; j <m ; j++)
               aux[i][j] = b[i][j];
	}
	for (i=0; i<n; i++){
		count=aux[i][i];
		if(count !=1){
			for(j=0; j<m; j++){
				aux[i][j]= aux[i][j]/count;
				identidad[i][j]= identidad[i][j]/count;
			}
		}
		count=0;
		for (k=0; k<n; k++){
			if(i!=k){
				count= aux[k][i];
				for(j=0; j<m; j++){
					aux[k][j]=aux[k][j]- (count*aux[i][j]);
					identidad[k][j]=identidad[k][j]-(count*identidad[i][j]);
				}
			}
		}
		
	}
	for (i = 0; i < n; i++){
		for (j = 0; j < m; j++){
			inversa2[i][j]=identidad[i][j];
			
		}
	}
	crearArchivoD(5);
	return 0;
}

int procesoInversa(){
	DWORD idHilo,idHilo2;	/*Identificador del hilo*/
	HANDLE manHilo,manHilo2;	//Manejador del hilo
	manHilo=CreateThread(NULL, 0, inversaMatrizA, NULL,0, &idHilo);
	WaitForSingleObject(manHilo, INFINITE);
	manHilo2=CreateThread(NULL, 0, inversaMatrizB, NULL,0, &idHilo2);
	WaitForSingleObject(manHilo, INFINITE);
	return 0;
}

void procesoApertura(){
	int i;
	DWORD idHilo;	/*Identificador del hilo*/
	HANDLE manHilo;	//Manejador del hilo	
	for (i = 1; i < 6; ++i){
		manHilo=CreateThread(NULL, 0,(void*)leerArchivo,(void *)i,0, &idHilo);
		WaitForSingleObject(manHilo, INFINITE);
		Sleep(1);	
		printf("\n");
	}
}

int main(){
	clock_t start = clock();  
	time_t t;
	srand((unsigned) time(&t));
	printf("\nBienvenido\n");
	asignarMatriz(a,n,m,1);
	printf("\nMatriz A:\n\n");
	printMatriz(a,n,m);
	asignarMatriz(b,n,m,1);
	printf("\nMatriz B:\n\n");
	printMatriz(b,n,m);
	asignarMatriz(suma,n,m,0);
	asignarMatriz(resta,n,m,0);
	procesoSuma();
	procesoResta();
	procesoMulti();
	procesoTrans();
	procesoInversa();
	procesoApertura();
	printf("\n\nTiempo transcurrido: %f segundos\n\n", ((double)clock() - start) / CLOCKS_PER_SEC); 
}
