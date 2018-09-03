#include <stdio.h>
#include <stdlib.h>
# include "TADPilaDin.h"
#define TAM 100

boolean ValidarCadena(char * cadena, int tamCadena);
int TamCadena(char * cadena);
int main(){
	char CadenaParentesis[TAM];
	int i;
	int tam;
	boolean vereficar;
	printf("Ingrese la cadena de parentesis sin espacios\n");
	fflush(stdin);
	scanf("%s",&CadenaParentesis);
	tam=TamCadena(CadenaParentesis);
	vereficar= ValidarCadena(CadenaParentesis,tam);
	if(vereficar){
		printf("Cadena Valanceda\n");
	}
	else{
		printf("Cadena no Valanceda\n");
	}
}

boolean ValidarCadena(char cadena[TAM],int tamCadena){
	pila Pila;
	int i;
	elemento e,aux;
	Initialize(&Pila);
	for(i=0;i<tamCadena;i++){
		e.Char=cadena[i];	
		if(cadena[i]=='('){
			Push(&Pila,e);
		}
		else if(cadena[i]=='['){
			Push(&Pila,e);
		}
		else if(cadena[i]=='{'){
			Push(&Pila,e);
		}
		if(cadena[i]==')'){
			if(Empty(&Pila)){
				return FALSE;
			}
			aux=Top(&Pila);
			if(aux.Char=='('){
				Pop(&Pila);
			}
		}
		else if(cadena[i]==']'){
			if(Empty(&Pila)){
				return FALSE;
			}
			aux=Top(&Pila);
			if(aux.Char=='['){
				Pop(&Pila);
			}
		}
		else if(cadena[i]=='}'){
			if(Empty(&Pila)){
				return FALSE;
			}
			aux=Top(&Pila);
			if(aux.Char=='{'){
				Pop(&Pila);
			}
		}
	}
	if(Empty(&Pila)){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

int TamCadena(char cadena[TAM]){
	int cont=0;
	int i=0;
	while(cadena[i]!='\0'){
		i++;
		cont++;
	}
	
	return cont;
}

