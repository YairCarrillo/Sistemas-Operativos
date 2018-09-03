#include <stdlib.h>
#include "TADPilaDin.h"

void Initialize(pila *s)
{
	s->tope=NULL; //(*s).tope=NULL;
	return;
}

void Push(pila *s, elemento e)
{
	nodo *aux;
	aux=malloc(sizeof(nodo));
	(*aux).e=e;  //aux->e=e;
	aux->abajo=s->tope;
	s->tope=aux;
	return;
}

elemento Pop (pila *s)
{
	elemento r;
	nodo *aux;
	r=s->tope->e;
	aux=s->tope;
	s->tope=s->tope->abajo;
	free(aux);
	return r;	
}

boolean Empty(pila *s)
{
	boolean r;
	if(s->tope==NULL)
	{
		r=TRUE;
	}	
	else
	{
		r=FALSE;
	}
	return r;	
}

elemento Top(pila *s)
{
	return s->tope->e;
}

int Size(pila *s)
{
	nodo *aux;
	int tam_pila=0;
	aux=s->tope;
	if(aux!=NULL)
	{
		tam_pila++;
		while(aux->abajo!=NULL)
		{
			tam_pila++;
			aux=aux->abajo;
		}
	}	
	return tam_pila;
}

void Destroy(pila *s)
{
	nodo *aux;
	if(s->tope!=NULL)
	{
		while(s->tope!=NULL)
		{				
			aux=s->tope->abajo;
			free(s->tope);
			s->tope=aux;
		}		
	}
	return;
}
