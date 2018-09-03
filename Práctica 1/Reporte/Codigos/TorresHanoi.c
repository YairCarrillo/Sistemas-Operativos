#include <stdio.h>

void Hanoi(int n, int *cont,char Origen, char Destino, char Auxiliar);
int main(){
	int n;
	int cont=0;
	char A,B,C;
	A='A';
	B='B';
	C='C';
	printf("Ingrese el numero de Discos\n");
	scanf("%d",&n);
	printf("MOVIMIENTOS\n");
	Hanoi(n,&cont,A,B,C);	
	printf("Numero de movimientos: %d \n",cont);
	return 0;
}
void Hanoi(int n,int *cont,char Origen,char Destino,char Auxiliar){
	(*cont)++;
	if(n==1){
		printf("%c ----> %c\n",Origen,Destino);
	}
	else{
		Hanoi(n-1,cont,Origen,Auxiliar,Destino);
		printf("%c ----> %c\n",Origen,Destino);
		Hanoi(n-1,cont,Auxiliar,Destino,Origen);

	}
}