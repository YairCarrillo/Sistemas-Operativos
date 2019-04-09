#include<windows.h>
#include<stdio.h>
#include<string.h>
#define TAM 10
#include"math.h"
#define SWAP(a, b) {temp = (a);(a) = (b);(b) = temp;}
#include"time.h"

HANDLE crearArchivo(char* direccion){
HANDLE hFile;
hFile=CreateFile(direccion,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);
return hFile;
}
BOOL write(HANDLE hFile,char* texto){
BOOL bFile;
DWORD numberofbytes=(DWORD)strlen(texto);
DWORD numberwritten=0;
bFile= WriteFile(hFile,texto,numberofbytes,&numberwritten,NULL);
return bFile;
}  

void stchcat(char *cadena, char chr)
{
   size_t longitud = strlen(cadena);
   
   *(cadena + longitud) = chr;
   *(cadena + longitud + 1) = '\0';
}

void ImpMatriz(float** a){
     int i,j;
    for(i=0;i<TAM;i++){
    for(j=0;j<TAM;j++){
    printf("%.1f|\t",a[i][j]);
      }
    printf("\n");
    }
    }
    
float** generar(){
   int i;
   float** a=(float**)malloc(sizeof(float*)*TAM);
   for(i=0;i<TAM;i++){
   a[i]=(float*)malloc(sizeof(float)*TAM);
   }
   return a;
   }
   
float** toPointer(float a[TAM][TAM]){
        float** x=generar();
        int i,j;
       for(i=0;i<TAM;i++){
       for(j=0;j<TAM;j++){
       x[i][j]=a[i][j];
}
}
return x;
}

double 
Determinante (float m1[TAM][TAM],int n)
{
  double s = 1, det = 0;
  int i, j, k, m, x;
  HANDLE hFile;
  float m2[TAM][TAM];
  if (n == 1)
  {
    return m1[0][0];
  }
  else
  {
    for (k = 0; k < n; k++)
    {
      m = 0;
      x = 0;
      for (i = 0; i < n; i++)
      {
        for (j = 0; j < n; j++)
        {
          m2[i][j] = 0;
          if (i != 0 && j != k)
          {
            m2[m][x] = m1[i][j];
            if (x < (n - 2))
            {
              x++;
            }
			else
            {
              x = 0;
              m++;
            }
          }
        }
      }
      det = det + s * (m1[0][k] * Determinante(m2, n-1));
      s *= -1;
    }
  }
  return det;
}  

void matrizCofactores (float m1[TAM][TAM], int n, double determinante)
{
  char resultado[700];
  char buffer[8]={};
  int q, m, i, j, k, l;
  HANDLE hFile;
  float m2[TAM][TAM], matrizFactores[TAM][TAM], aux[TAM][TAM], inversa[TAM][TAM];
  for (l = 0; l < n; l++)
  {
    for (k = 0; k < n; k++)
    {
      m = 0; q = 0;
      for (i = 0; i < n; i++)
      {
        for (j = 0; j < n; j++)
        {
          if ( i != l && j != k)
          {
            m2[m][q] = m1[i][j];
            if (q < (n-2))
            {
              q++;
            }
			else 
            {
				q = 0; m++;
            }
          }
        }
      }
      matrizFactores[l][k] = (pow(-1, l + k)* Determinante (m2, n-1));
    }
  }
  for (i = 0; i < TAM; i++)
  {
    for (j = 0; j < TAM; j++)
    {
      aux[i][j] = matrizFactores[j][i];
    }
  }
  for (i = 0; i < TAM; i++)
  {
    for (j = 0; j < TAM; j++)
    {
      inversa[i][j] = aux[i][j] / determinante;
   
   }
  }
   strcpy(resultado,"\r\nMATRIZ INVERSA A\r\n ");
  for (i = 0; i < TAM; i++)
  {
    for (j = 0; j < TAM; j++)
    {
	  sprintf(buffer,"%.3lf\t",inversa[i][j]);
	  strcat(resultado,buffer);
	 memset(buffer,0,8);
    }
strcat(resultado,"\r\n");
  }
  printf("%s\n",resultado);
 DWORD noReaded=0;
 hFile=crearArchivo("F:\\Sistemas Operativos\\Practica6\\inversa1.txt");
 BOOL bFile=write(hFile,resultado);
 
}

void 
matrizCofactores2 (float m1[TAM][TAM], int n, double determinante)
{
  char resultado[700];
  char buffer[8]={};
  HANDLE hFile;
  int q, m, i, j, k, l;
  float m2[TAM][TAM], matrizFactores[TAM][TAM], aux[TAM][TAM], inversa[TAM][TAM];
  for (l = 0; l < n; l++)
  {
    for (k = 0; k < n; k++)
    {
      m = 0; q = 0;
      for (i = 0; i < n; i++)
      {
        for (j = 0; j < n; j++)
        {
          if ( i != l && j != k)
          {
            m2[m][q] = m1[i][j];
            if (q < (n-2))
            {
              q++;
            }
			else 
            {
				q = 0; m++;
            }
          }
        }
      }
      matrizFactores[l][k] = (pow(-1, l + k)* Determinante (m2, n-1));
    }
  }
  for (i = 0; i < TAM; i++)
  {
    for (j = 0; j < TAM; j++)
    {
      aux[i][j] = matrizFactores[j][i];
    }
  }
  for (i = 0; i < TAM; i++)
  {
    for (j = 0; j < TAM; j++)
    {
      inversa[i][j] = aux[i][j] / determinante;
    }
  }
  
  /*****************IMPRESION DE LA INVERSA************/
  strcpy(resultado,"\r\nMATRIZ INVERSA B \r\n");
  for (i = 0; i < TAM; i++)
  {
    for (j = 0; j < TAM; j++)
    {
	  sprintf(buffer,"%.3lf\t",inversa[i][j]);
	  strcat(resultado,buffer);
	  memset(buffer,0,8);
    }
	strcat(resultado,"\r\n");
  }
  printf("%s\n",resultado);
   hFile=crearArchivo("F:\\Sistemas Operativos\\Practica6\\inversa2.txt");
 BOOL bFile=write(hFile,resultado);
}
HANDLE hPipeLecturaIn,hPipeLecturaOut,hPipeEscrituraIn,hPipeEscrituraOut;

int main(int argc,char *argv[]){
int i,j,k=0,cout=0;
srand(time(NULL));
TCHAR buffer[10]={},buf[2000],cad[2000],aux[8];
memset(buf,0,2000);
memset(cad,0,2000);
memset(buffer,0,10);
memset(aux,0,8);
DWORD escritos,leidos;
PROCESS_INFORMATION piHijo;
STARTUPINFO siHijo;
SECURITY_ATTRIBUTES pipeSeg={sizeof(SECURITY_ATTRIBUTES),NULL,TRUE};
GetStartupInfo(&siHijo);


CreatePipe (&hPipeLecturaOut, &hPipeEscrituraOut, &pipeSeg, 0);
 CreatePipe (&hPipeLecturaIn, &hPipeEscrituraIn, &pipeSeg, 0);

float a[10][10];
float b[10][10];

	for(i=0;i<10;i++){
	for(j=0;j<10;j++){
	a[i][j]=rand()%20;
	b[i][j]=rand()%20;
	}
    } 
    
for(i=0;i<10;i++){
for(j=0;j<10;j++){
sprintf(buffer,"%.1f",a[i][j]);
strcat(buf,buffer);
strcat(buf,"|");
memset(buffer,0,8);
}
}
strcat(buf,"#");
for(i=0;i<10;i++){
for(j=0;j<10;j++){
sprintf(buffer,"%.1f",b[i][j]);
strcat(buf,buffer);
strcat(buf,"|");
memset(buffer,0,8);
}
}

WriteFile(hPipeEscrituraIn,buf,strlen(buf)+1,&escritos,NULL);

   siHijo.hStdError  = GetStdHandle (STD_ERROR_HANDLE);
   siHijo.hStdOutput = hPipeEscrituraOut;	/* Redirigimos la salida estándar */
   siHijo.hStdInput  = hPipeLecturaIn;	/* Redirigimos la entrada estándar */
   siHijo.dwFlags = STARTF_USESTDHANDLES;


CreateProcess(NULL,"hijo",NULL,NULL,TRUE,0,NULL,NULL,&siHijo,&piHijo);
WaitForSingleObject(piHijo.hProcess,INFINITE);
printf("Terminaron los procesos hijos...\n");
CloseHandle(piHijo.hThread);
CloseHandle(piHijo.hProcess);
CloseHandle(hPipeEscrituraIn);


ReadFile(hPipeLecturaOut,cad,sizeof(cad),&leidos,NULL);
CloseHandle(hPipeLecturaOut); 
CloseHandle(hPipeEscrituraOut); 
CloseHandle(hPipeLecturaIn);
cout=0;
memset(aux,0,10);
float mul[10][10];
    for(i=0;i<10;i++){
    for(j=0;j<10;j++){
    k=cout;
    while(cad[k]!='|'&&cad[k]!='#'){
    stchcat(aux,cad[k++]);
    cout++;                      
    }
    mul[i][j]=strtof(aux,NULL);
    cout++;
    memset(aux,0,8);
    }
    }
    memset(aux,0,10);
    memset(cad,0,1000);
float sum[10][10];    
    for(i=0;i<10;i++){
    for(j=0;j<10;j++){
    k=cout;
    while(cad[k]!='|'&&cad[k]!='#'){
    stchcat(aux,cad[k++]);
    cout++;                      
    }
   sum[i][j]=strtof(aux,NULL);
    cout++;
    memset(aux,0,8);
    }
    }
printf("Matriz A:  \n",cout);
ImpMatriz(toPointer(a));
printf("Matriz B:  \n",cout);
ImpMatriz(toPointer(b));
printf("Matriz producto:  \n",cout);
ImpMatriz(toPointer(mul));
printf("Matriz suma: \n",cout);
ImpMatriz(toPointer(sum));

if(Determinante(mul,10)!=0){
	matrizCofactores(mul,10,Determinante(mul,10));
}
else{
	printf("La matriz producto no tiene inversa");
}
if(Determinante(sum,10)!=0){
	matrizCofactores2(sum,10,Determinante(sum,10));
}
else{
	printf("La matriz suma no tiene inversa");
}

printf("Termina el proceso padre\n");
return 0;
}

Hijo:
#include"windows.h"
#include"stdio.h"
#include"stdlib.h"
#define TAM 10
void stchcat(char *cadena, char chr)
{
   size_t longitud = strlen(cadena);
   
   *(cadena + longitud) = chr;
   *(cadena + longitud + 1) = '\0';
}

void ImpMatriz(float** a){
     int i,j;
    for(i=0;i<TAM;i++){
    for(j=0;j<TAM;j++){
    printf("%.1f|\t",a[i][j]);
      }
    printf("\n");
    }
    }
    
float** generar(){
   int i;
   float** a=(float**)malloc(sizeof(float*)*TAM);
   for(i=0;i<TAM;i++){
   a[i]=(float*)malloc(sizeof(float)*TAM);
   }
   return a;
   }
    
float** producto(float a[10][10],float b[10][10]){
int c1=TAM,c2=TAM,f1=TAM,f2=TAM;
float** c=generar();
int suma=0,i=0,j=0,k=0,l=0;
if(c1==f2){
while(i<f1){
while(j<c1){
suma=suma+a[i][j]*b[j][k];
j++;
}
c[i][k]=suma;
suma=0;
if(j==c1){
j=0;
k++;
if(k==c2){
k=0;
i++;
}
}
}
}
return c;
}

float** toPointer(float a[TAM][TAM]){
        float** x=generar();
        int i,j;
       for(i=0;i<TAM;i++){
       for(j=0;j<TAM;j++){
       x[i][j]=a[i][j];
}
}
return x;
}
int main(){
//Inicializamos los parametros a utilizar en Tubería y en procesos hijos	
int i,j,k=0,cout=0;
TCHAR bfr[10]={},buf[1000],buff[2000],aux[8]={},buffer[2000];
memset(buff,0,1000);
memset(buf,0,1000);
memset(buffer,0,2000);
memset(aux,0,8);
memset(bfr,0,10);
DWORD escritos,leidos;
HANDLE hPipeEscrituraIn,hPipeEscrituraOut,hPipeLecturaIn,hPipeLecturaOut;
PROCESS_INFORMATION piHijo;
STARTUPINFO siHijo;
SECURITY_ATTRIBUTES pipeSeg={sizeof(SECURITY_ATTRIBUTES),NULL,TRUE};
GetStartupInfo(&siHijo);


	//Leemos la tubería enviada desde el padre.
	HANDLE hStdIn=GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
	
	ReadFile(hStdIn,buffer,sizeof(buffer),&leidos,NULL);
	printf("Mensaje recibido del proceso padre: Tamano:%d \n%s\n",strlen(buffer),buffer);
	CloseHandle(hStdIn);
	
	float a[10][10],b[10][10];
	/*Abrimos el buffer leído de la tubería y reconstruimos las matrices para realizar las multiplicaciones*/
    for(i=0;i<10;i++){
    for(j=0;j<10;j++){
    k=cout;
    while(buffer[k]!='|'&&buffer[k]!='#'){
    stchcat(aux,buffer[k++]);
    cout++;                      
    }
    a[i][j]=strtof(aux,NULL);
    cout++;
    memset(aux,0,8);
    }
    }
    if(buffer[cout]=='#'){
    cout++;
    }
    for(i=0;i<10;i++){
    for(j=0;j<10;j++){
    k=cout;
    while(buffer[k]!='|'&&buffer[k]!='#'){
    stchcat(aux,buffer[k++]);
    cout++;                      
    }
    b[i][j]=strtof(aux,NULL);
    cout++;
    if(buffer[cout]=='#'){
    cout++;
    }
    memset(aux,0,8);
    }
    }
    
    //Multiplicamos las matrices reconstruidas
    float **multi=generar();
    multi=producto(a,b);
    printf("Matriz 1\n");
    ImpMatriz(toPointer(a));
    printf("Matriz 2\n");
    ImpMatriz(toPointer(b));
    printf("Matriz producto:\n");
    ImpMatriz(multi);
    //Creamos las tuberías a utilizar
    CreatePipe(&hPipeLecturaIn,&hPipeEscrituraIn,&pipeSeg,0);
    CreatePipe(&hPipeLecturaOut,&hPipeEscrituraOut,&pipeSeg,0);
    
    //Escribimos en la tubería las dos matrices que se van a mandar al nieto
    WriteFile(hPipeEscrituraIn,buffer,strlen(buffer)+1,&escritos,NULL);
    siHijo.hStdError  = GetStdHandle (STD_ERROR_HANDLE);
    siHijo.hStdOutput = hPipeEscrituraOut; /* Redirección de la salida estándar */
    siHijo.hStdInput  = hPipeLecturaIn;	/* Redirección de la entrada estándar */
    siHijo.dwFlags = STARTF_USESTDHANDLES;
    //Creamos el proceso Nieto
	CreateProcess(NULL,"nieto",NULL,NULL,TRUE,0,NULL,NULL,&siHijo,&piHijo);
	WaitForSingleObject (piHijo.hProcess, INFINITE); /* Esperamos a que concluya */
    CloseHandle(piHijo.hThread);
    CloseHandle(piHijo.hProcess); /* Cerramos los manejadores de proceso */
    printf("Regresamos al padre\n");
    CloseHandle(hPipeEscrituraIn);
    
    //Leemos lo que escribio el nieto
    ReadFile(hPipeLecturaOut,buff,sizeof(buff),&leidos,NULL);
    CloseHandle(hPipeEscrituraOut);
    CloseHandle(hPipeLecturaIn);
    CloseHandle(hPipeLecturaOut);
    
    memset(buf,0,1000);
    memset(bfr,0,10);
    for(i=0;i<10;i++){
    for(j=0;j<10;j++){
    sprintf(bfr,"%.1f",multi[i][j]);
    strcat(buf,bfr);
    strcat(buf,"|");
    memset(bfr,0,8);
    }
    }
    
    WriteFile(hStdOut, buf, sizeof(buf), &escritos, NULL); /* Escribimos los resultados en la tubería padre */
    WriteFile(hStdOut, buff, sizeof(buff), &escritos, NULL);
    CloseHandle(hStdOut);


	printf("Termina el proceso hijo, continua el proceso padre\n");
	return 0;
}

Nieto:
#include"windows.h"
#include"stdio.h"
#include"stdlib.h"
#define TAM 10
void stchcat(char *cadena, char chr)
{
   size_t longitud = strlen(cadena);
   
   *(cadena + longitud) = chr;
   *(cadena + longitud + 1) = '\0';
}

void ImpMatriz(float** a){
     int i,j;
    for(i=0;i<TAM;i++){
    for(j=0;j<TAM;j++){
    printf("%.1f|\t",a[i][j]);
      }
    printf("\n");
    }
    }
    
float** generar(){
   int i;
   float** a=(float**)malloc(sizeof(float*)*TAM);
   for(i=0;i<TAM;i++){
   a[i]=(float*)malloc(sizeof(float)*TAM);
   }
   return a;
   }

float** SumarMat(float a[10][10],float b[10][10]){
      int i,j;
      int filas=TAM,columnas=TAM;
    float** c=generar();
      for(i=0;i<filas;i++){
      for(j=0;j<columnas;j++){
      c[i][j]=a[i][j]+b[i][j];
      }
      }
      return c;
}

float** toPointer(float a[TAM][TAM]){
        float** x=generar();
        int i,j;
       for(i=0;i<TAM;i++){
       for(j=0;j<TAM;j++){
       x[i][j]=a[i][j];
}
}
return x;
}
int main(){
//Inicializamos los parametros a utilizar en las tuberías.
int i,j,k=0,cout=0;
TCHAR bfr[10]={},buf[1000],buffer[1000],aux[8]={};
memset(buf,0,1000);
memset(aux,0,8);
memset(bfr,0,10);
memset(buffer,0,1000);
DWORD escritos,leidos;
HANDLE hLecturaPipe,hEscrituraPipe;
SECURITY_ATTRIBUTES pipeSeg={sizeof(SECURITY_ATTRIBUTES),NULL,TRUE};
hLecturaPipe=GetStdHandle(STD_INPUT_HANDLE);
hEscrituraPipe=GetStdHandle(STD_OUTPUT_HANDLE);

	//Leemos la Tubería para obtener el buffer donde vienen las dos matrices 
	ReadFile(hLecturaPipe,buffer,sizeof(buffer),&leidos,NULL);
	printf("Mensaje recibido del proceso hijo: \n%s\n",buffer);
	CloseHandle(hLecturaPipe);
	float a[10][10],b[10][10];
	/*Abrimos el buffer leído de la tubería y reconstruimos las matrices para realizar las sumas */
    for(i=0;i<10;i++){
    for(j=0;j<10;j++){
    k=cout;
    while(buffer[k]!='|'&&buffer[k]!='#'){
    stchcat(aux,buffer[k++]);
    cout++;                      
    }
    a[i][j]=strtof(aux,NULL);
    cout++;
    memset(aux,0,8);
    }
    }
    if(buffer[cout]=='#'){
    cout++;
    }
    for(i=0;i<10;i++){
    for(j=0;j<10;j++){
    k=cout;
    while(buffer[k]!='|'&&buffer[k]!='#'){
    stchcat(aux,buffer[k++]);
    cout++;                      
    }
    b[i][j]=strtof(aux,NULL);
    cout++;
    if(buffer[cout]=='#'){
    cout++;
    }
    memset(aux,0,8);
    }
    }
    
	float **sumar=generar();
    sumar=SumarMat(a,b); //Se calcula la suma de ambas matrices reconstruidas
    
    printf("Matriz 1\n");
    ImpMatriz(toPointer(a));
    printf("Matriz 2\n");
    ImpMatriz(toPointer(b));
    printf("Suma de matrices: \n");
    ImpMatriz(sumar);
    
    //Guardamos en un buffer nuevamente la matriz que resulta de la suma
    memset(buf,0,1000);
    memset(bfr,0,10);
for(i=0;i<10;i++){
    for(j=0;j<10;j++){
    sprintf(bfr,"%.1f",sumar[i][j]);
    strcat(buf,bfr);
    strcat(buf,"|");
    memset(bfr,0,8);
    }
    }
    //Escribimos en la Tuberia obtenida inicialmente
    WriteFile(hEscrituraPipe,buf,strlen(buf)+1,&escritos,NULL);
    CloseHandle(hEscrituraPipe);
	printf("Termina el proceso nieto, continua el proceso hijo\n");
	return 0;
}
 

