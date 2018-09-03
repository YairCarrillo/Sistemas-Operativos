
#define TRUE	1
#define FALSE	0

typedef unsigned char boolean;
typedef struct elemento
{
	char Char;
	float Float;
}elemento;

typedef struct nodo
{
	
	elemento e;	
	struct nodo *abajo;
}nodo;

typedef struct pila
{		
	nodo *tope;
}pila;

void Initialize(pila *s);			
void Push(pila *s, elemento e);		
elemento Pop (pila *s);				
boolean Empty(pila *s);				
elemento Top(pila *s);				
int Size(pila *s);					
void Destroy(pila *s);				