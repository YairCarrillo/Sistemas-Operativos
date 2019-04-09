#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#define TAM 10
#include"math.h"
#define SWAP(a, b) {temp = (a);(a) = (b);(b) = temp;}
#include"time.h"
#define VALOR 1


void stchcat(char *cadena, char chr)
{
   size_t longitud = strlen(cadena);
   
   *(cadena + longitud) = chr;
   *(cadena + longitud + 1) = '\0';
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

void ImpMatriz(float** a){
     int i,j;
    for(i=0;i<TAM;i++){
    for(j=0;j<TAM;j++){
    printf("%.1f|\t",a[i][j]);
      }
    printf("\n");
    }
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
  char resultado[1000];
  char buffer[8]={};
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
 int hola= creat("/home/hp/SO/Inversa1.txt",0644);
write(hola,resultado,strlen(resultado)+1);
 
}

void 
matrizCofactores2 (float m1[TAM][TAM], int n, double determinante)
{
  char resultado[1000];
  char buffer[8]={};
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

memset(resultado,0,1000); 
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
int hola= creat("/home/hp/SO/Inversa2.txt",0644);
 write(hola,resultado,strlen(resultado)+1);
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

int main(int argc,char *argv[]){
int i,j,k=0,cout=0;
srand(time(NULL));
char buf[2000],cad[2000],aux[10],buff[1000];
memset(buf,0,2000);
memset(cad,0,2000);
memset(aux,0,10);
int desc_arch[2];


float a[10][10];
float b[10][10];

   for(i=0;i<10;i++){
   for(j=0;j<10;j++){
   a[i][j]=rand()%20;
b[i][j]=rand()%20;
   }
    }
printf("Matriz A:  \n");
ImpMatriz(toPointer(a));
printf("Matriz B:  \n");
ImpMatriz(toPointer(b));
    
if(pipe(desc_arch)!=0)
exit(1);
if(fork()==0) //Primer hijo
{
float **multi=generar();
multi=producto(a,b);
  memset(buf,0,2000);
    memset(aux,0,10);
    for(i=0;i<10;i++){
    for(j=0;j<10;j++){
    sprintf(aux,"%.1f",multi[i][j]);
    strcat(buf,aux);
    strcat(buf,"|");
    memset(aux,0,10);
    }
    }
memset(cad,0,2000);
strcpy(cad,buf);
if(pipe(desc_arch)!=0){
exit(1);}
if(fork()==0){ //Nieto

if(pipe(desc_arch)!=0){
exit(1);}
float **suma=generar();
suma=SumarMat(a,b);
memset(buf,0,2000);
    for(i=0;i<10;i++){
    for(j=0;j<10;j++){
    sprintf(aux,"%.1f",suma[i][j]);
    strcat(buf,aux);
    strcat(buf,"|");
    memset(aux,0,10);
    }
    }
write(desc_arch[1],buf,sizeof(buf));
}

memset(buf,0,2000);
read(desc_arch[0],buf,sizeof(buf));
strcat(cad,buf);
write(desc_arch[1],cad,strlen(cad)+1);
}

memset(cad,0,2000);
read(desc_arch[0],cad,sizeof(cad));
float mul[10][10];
   cout=0;
    for(i=0;i<10;i++){
for(j=0;j<10;j++){
    k=cout;
    while(cad[k]!='|'&&cad[k]!='#'){
    stchcat(aux,cad[k++]);
    cout++;                      
    }
    mul[i][j]=strtof(aux,NULL);
    cout++;
    memset(aux,0,10);
    }
    }
    memset(aux,0,10);
   printf("%d,%c\n",cout,cad[cout]);
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
    memset(aux,0,10);
    }
    }
printf("Matriz A:  \n");
ImpMatriz(toPointer(a));
printf("Matriz B:  \n");
ImpMatriz(toPointer(b));
printf("Matriz producto:  \n");
ImpMatriz(toPointer(mul));
printf("Matriz suma: \n");
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
