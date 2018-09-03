/*
AUTOR: Dominguez Moran Joaqu�n, Garc�a Iba�ez Diego, Rosas S�nchez Paloma. Agosto 2017.
VERSI�N: 1.0.

DESCRIPCI�N: Programa que valida y evalua una expresi�n infija.

OBSERVACIONES: El programa utiliza 6 funciones para realizar las operaciones que poco a poco modifican la matriz original.

COMPILACI�N: 
			Windows: gcc main.c TADPilaEst.c
			Linux: gcc main.c TADPilaEst.c -lm

EJECUCI�N: 
			Windows: a.exe
			Linux: ./a.out
*/

//MACROS DEL PREPROCESADOR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "TADPilaEst.h"
#include "TADPilaDin.h"
#include <math.h>

//DEFINICIONES
#define TAM 100			//Se define el numero de datos que se pueden ingresar





/*
**void ValidarParentesis (char array[TAM])**
DESCRIPCI�N: Funci�n que evalua una expresi�n para asegurar que los parentesis estan escritos de manera correcta.
ENTRADA: Un arreglo de tipo caracter de TAM 100
SALIDA: Impresi�n en pantalla si la expresi�n es correcta, sino un mensaje de error y sale del programa.
OBSERVACIONES: Se emplea la libreria TADPilaEst.h,TADPilaDin.h,stdio.h,stdlib.h,string.h.
*/

void
ValidarParentesis (char array[TAM])
{
  int i = 0;			//Se declara una variable de tipo entero y se inicializa en 0 
  int tamano;			//Se declara una variable de tipo entero
  float valor;			//Se declara variable de tipo flotante
  tamano = strlen (array);	//Medir el tama�o del arreglo
  elemento e;			//Se declara un elemento e
  pila palpila;			//Se declara una pila "palpila"
  Initialize (&palpila);	//Inicializaci�n de la pila "palpila"
  for (i = 0; i < tamano; i++)	//Ciclo for que recorre cada caracter del arreglo
    {
      e.Char = array[i];
      if (array[i] == '(')	//Si el caracter es "(" introducirlo a la pila
	Push (&palpila, e);
      if (array[i] == ')')	//Si el caracter es ")" realizar un Pop a la pila
	{
	  if (Empty (&palpila))	//Si se intenta extraer un elemento y la pila es vacia Error
	    {
	      printf
		("Existen mas parentesis de los que cierran de los que abren. \n");
	      exit (1);
	    }

	  Pop (&palpila);

	}

    }

  if (!Empty (&palpila))	//Si al terminar de revisar la expresi�n  hay elementos en la pila 
    {
      printf
	("Existen mas parentesis de los que abren de los que cierran.\n");
      exit (1);
    }

  printf ("Expresion correcta.\n");	//Si la ejecuci�n termina de manera correcta 


  Destroy (&palpila);		//Se destruye la pila.

}

/*
**char *Posfijo (char array[TAM])**
DESCRIPCI�N: Funci�n que pasa una expresi�n aritm�tica en posfijo a partir de la expresi�n infija.
ENTRADA: Un arreglo de tipo caracter de tama�o 100
SALIDA: Un arreglo con la expresi�n infija transformada en posfija
OBSERVACIONES:Se emplea la libreria TADPilaEst.h,TADPilaDin.h,stdio.h,stdlib.h,string.h. El arreglo de tipo caracter contiene letras mayusculas y ya est�n validados los parentesis.
*/

char *
Posfijo (char array[TAM])
{
  int i;			//Se declara una variable de tipo entero que  se usar� como contador
  int j = 0;			//Se declara e inicializa una variable de tipo entero que  se usar� como contador
  int tamCadena;		//Se declara una variable de tipo entero que guardara el tama�o de la cadena
  char *resultado;		//Se declara variable de tipo apuntador
  elemento E, E1, E2;		//Se declara elemento E,E1,E2

  tamCadena = strlen (array);	////Medir el tama�o del arreglo

  pila posfijo;			//Se declara una pila "posfijo"
  Initialize (&posfijo);	//Inicializar pila "posfijo"

  resultado = (char *) malloc (1 * sizeof (char));	//Asiganamos memoria.



  for (i = 0; i < tamCadena; i++)	//Ciclo que recorre cada caracter de la cadena.
    {

      E.Char = array[i];	//Aisganamos a un elemento de tipo caracter la posici�n i del arreglo.




      if (E.Char >= (char) 65 && E.Char <= (char) 90)	//Si el elemento E.Char del arreglo es un operando se agrega directamente a resultado
	{

	  resultado = (char *) realloc (resultado, (j + 1) * sizeof (char));
	  resultado[j] = E.Char;
	  j++;


	}


      if (E.Char == '(')	//Si el elemento E.Char del arreglo es un parentesis que abre se agrega a la pila.
	{

	  Push (&posfijo, E);

	}



      if (E.Char == ')')	//Si el elemento i del arreglo es un parentesis que cierra se desempilan elementos hasta encontrar un parentesis que abre.
	{
	  if (Empty (&posfijo) == FALSE)	//Se valida que la pila no se encuentre vacia.
	    E1 = Top (&posfijo);	//Se le asigna al elemento E1 el elemento que se encuentra en el tope.
	  while (E1.Char != '(')	//Si el tope es diferente de un parentesis que abre.
	    {
	      E2 = Pop (&posfijo);	//Se desempila un elemento
	      resultado =
		(char *) realloc (resultado, (j + 1) * sizeof (char));
	      resultado[j] = E2.Char;	//Se colocan los elementos desempilados en el arreglo a retornar
	      j++;


	      if (Empty (&posfijo) == FALSE)	//Se valida que la pila no se encuentre vacia.
		E1 = Top (&posfijo);	//Se le asigna al elemento E1 el elemento que se encuentra en el tope.

	    }
	  Pop (&posfijo);	//Se desempila el parentesis que abre

	}


      if (E.Char == '+' || E.Char == '-')	//Si es un operador de suma o resta.
	{
	  if (Empty (&posfijo) == FALSE)	//Se valida que la pila no se encuentre vacia.
	    E1 = Top (&posfijo);	//Se le asigna al elemento E1 el elemento que se encuentra en el tope.

	  if ('(' == E1.Char || Empty (&posfijo) == TRUE)	//Si el tope es diferente de un parentesis que cierra o la pila esta vacia se empila el operador.
	    Push (&posfijo, E);	//Se empila el operador.

	  else
	    {

	      while (E1.Char != '(' && Empty (&posfijo) == FALSE)	//Si el tope es diferente de un parentesis que abre y la pila no se encuentra vacia.
		{
		  E2 = Pop (&posfijo);	//Se desempila un elemento
		  resultado =
		    (char *) realloc (resultado, (j + 1) * sizeof (char));
		  resultado[j] = E2.Char;	//Se colocan los elementos desempilados en el arreglo a retornar
		  j++;
		  if (Empty (&posfijo) == FALSE)	//Se valida que la pila no se encuentre vacia.
		    E1 = Top (&posfijo);	//Se le asigna al elemento E1 el elemento que se encuentra en el tope

		}

	      Push (&posfijo, E);	//Se empila el operador.
	    }

	}



      if (E.Char == '*' || E.Char == '/')	//Si es un operador de multiplicaci�n o divisi�n.
	{

	  if (Empty (&posfijo) == FALSE)	//Se valida que la pila no se encuentre vacia.
	    E1 = Top (&posfijo);	//Se le asigna al elemento E1 el elemento que se encuentra en el tope.

	  if (('*' != E1.Char && '/' != E1.Char && '^' != E1.Char) || Empty (&posfijo) == TRUE)	//Si el tope es diferente de un operador de menor o igual jerarqui la pila esta vacia se empila el operador.
	    Push (&posfijo, E);	//Se empila el operador.

	  else
	    {


	      while (('*' == E1.Char || '/' == E1.Char || '^' == E1.Char) && Empty (&posfijo) == FALSE)	//Si el tope es igual a un operador de igual o mayor jerarquia y la pila no se encuentra vacia.
		{
		  E2 = Pop (&posfijo);	//Se desempila un elemento
		  resultado =
		    (char *) realloc (resultado, (j + 1) * sizeof (char));
		  resultado[j] = E2.Char;	//Se colocan los elementos desempilados en el arreglo a retornar
		  j++;

		  if (Empty (&posfijo) == FALSE)	//Se valida que la pila no se encuentre vacia.
		    E1 = Top (&posfijo);	//Se le asigna al elemento E1 el elemento que se encuentra en el tope

		}

	      Push (&posfijo, E);	//Se empila el operador.
	    }

	}

      if (E.Char == '^')	//Si es un operador de potencia.
	{

	  if (Empty (&posfijo) == FALSE)	//Se valida que la pila no se encuentre vacia.
	    E1 = Top (&posfijo);	//Se le asigna al elemento E1 el elemento que se encuentra en el tope.
	  if ('^' != E1.Char || Empty (&posfijo) == TRUE)
	    Push (&posfijo, E);

	  else
	    {

	      while ('^' == E1.Char && Empty (&posfijo) == FALSE)	//Si el tope es igual a un operador de potencia.
		{
		  E2 = Pop (&posfijo);	//Se desempila un elemento
		  resultado =
		    (char *) realloc (resultado, (j + 1) * sizeof (char));
		  resultado[j] = E2.Char;	//Se colocan los elementos desempilados en el arreglo a retornar
		  j++;

		  if (Empty (&posfijo) == FALSE)	//Se valida que la pila no se encuentre vacia.
		    E1 = Top (&posfijo);	//Se le asigna al elemento E1 el elemento que se encuentra en el tope

		}

	      Push (&posfijo, E);	//Se empila el operador.
	    }

	}

    }


  if (Empty (&posfijo) == FALSE)	//Si al terminar el recorrido la pila no se encuentra vac�a.
    {

      while (Empty (&posfijo) == FALSE)	//Se valida que la pila no se encuentre vacia.
	{
	  E2 = Pop (&posfijo);	//Se desempila un elemento
	  resultado = (char *) realloc (resultado, (j + 1) * sizeof (char));
	  resultado[j] = E2.Char;	//Se colocan los elementos en el arreglo a retornar
	  j++;

	}

    }

  Destroy (&posfijo);		//Se destruye la pila.
  resultado[j] = '\0';		//Se pone fin de cadena al arreglo


  return resultado;		//Se retorna la cadena que contiene la expresi�n en posfijo


}

///////////////////////////////////////////////////////////////////////////////////////////


/*
**EvalPosfijo (char array[TAM])**
DESCRIPCI�N: Funci�n que evalua una expresi�n en posfijo.
ENTRADA: Un arreglo de tipo caracter de TAM 100
SALIDA: Un flotante que contiene el resultado de la evaluaci�n en posfijo.
OBSERVACIONES: Se emplea la libreria TADPilaEst.h,TADPilaDin.h,stdio.h,stdlib.h,string.h, math.h.Solicita el valor de las varibales.
*/

float
EvalPosfijo (char array[TAM])
{

  int i;			//Se declara una variable de tipo entero que  se usar� como contador                    
  int k = 0;			//Se declara e inicializa una variable de tipo entero que  se usar� como contador
  int tamCadena;		//Se declara una variable de tipo entero que  se usar� para almacenar la longitud de la cadena.
  int val_posicion = 0;		//Se declara una variable de tipo entero que  se usar� para almacenar la posici�n de un arreglo.
  float resultado = 0.0f;	//Se declara una variable e inicializa de tipo flotante que  se usar� para almacenar el resultado al aplicar un operador, 
  float res_final = 0.0f;	//Se declara una variable e inicializa de tipo flotante que  se usar� para almacenar el resultado de la evaluaci�n-
  float valor = 0.0f;		//Se declara una variable e inicializa de tipo flotante que  se usar� para almacenar el valor de la varibale.
  float valor_variable[27];	//Se declara una arreglo de logitud 27 de tipo flotante que  se usar� para alamcenar el valor de las varibales
  elemento E, E1, E2, E3, E4, Res;	//Se declaran 6 elementos

  pila valores;			//Se crea una pila.
  Initialize (&valores);	//Se inicializa una pila.

  tamCadena = strlen (array);	//Se obtiene la longitud de la cadena.

  while (k <= 27)		//Se limpia el arreglo donde se almacenaran los valores de las variables.
    {
      valor_variable[k] = '\0';
      k++;
    }

  for (i = 0; i < tamCadena; i++)	//Ciclo que recorre cada caracter de la cadena.
    {

      E.Char = array[i];	//Se aigana al elemento E la posici�n i del arreglo.
      E1.Float;
      E2.Float;

      if (E.Char >= (char) 65 && E.Char <= (char) 90)	//Si el elemento E.Char del arreglo es un operando
	{
	  val_posicion = (int) E.Char;	//Se asigna el valor en codigo ascci a val_posici�n.

	  if (valor_variable[val_posicion - 65] == '\0')	//Si la posici�n del arreglo que almacena el valor de las variables est� vacio.
	    {
	      printf ("Insertar el valor de la variable %c:", val_posicion);	//Se solicita al usuario final el valor de la variable.
	      scanf ("%f", &valor);	//Se almcena en la variable valor.
	      valor_variable[val_posicion - 65] = valor;	//La posici�n del arreglo que almacena el valor de las variables se le asigana el valor de la varibale.
	      valor = 0.0f;	//Se limpia la variable valor.
	    }



	  E4.Float = valor_variable[val_posicion - 65];	//Se le asigana a un elemento el valor de la posici�n del arreglo que almacena el valor de las varibales.
	  Push (&valores, E4);	//Se empila el elemento.

	}

      if (E.Char == '^')	//Si el operador es una potencia.
	{
	  E1 = Pop (&valores);	//Se desempila un elemento.
	  E2 = Pop (&valores);	//Se desempila un elemento.
	  resultado = pow (E2.Float, E1.Float);	//Se realiza la operaci�n potencia.
	  E3.Float = resultado;	//Se le asigna a E4 el valor del resultado de la operaci�n.
	  Push (&valores, E3);	//Se empila el resultado.
	}

      if (E.Char == '*')
	{
	  E1 = Pop (&valores);	//Se desempila un elemento.
	  E2 = Pop (&valores);	//Se desempila un elemento.
	  resultado = (E1.Float * E2.Float);	//Se realiza la operaci�n multiplicaci�n.
	  E3.Float = resultado;	//Se le asigna a E4 el valor del resultado de la operaci�n.
	  Push (&valores, E3);	//Se empila el resultado.
	}

      if (E.Char == '/')
	{
	  E1 = Pop (&valores);	//Se desempila un elemento.
	  E2 = Pop (&valores);	//Se desempila un elemento.
	  resultado = (E1.Float / E2.Float);	//Se realiza la operaci�n divisi�n.
	  E3.Float = resultado;	//Se le asigna a E4 el valor del resultado de la operaci�n.
	  Push (&valores, E3);	//Se empila el resultado.
	}

      if (E.Char == '+')
	{
	  E1 = Pop (&valores);	//Se desempila un elemento.
	  E2 = Pop (&valores);	//Se desempila un elemento.
	  resultado = (E1.Float + E2.Float);	//Se realiza la operaci�n suma.
	  E3.Float = resultado;	//Se le asigna a E4 el valor del resultado de la operaci�n.
	  Push (&valores, E3);	//Se empila el resultado.
	}
      if (E.Char == '-')
	{
	  E1 = Pop (&valores);	//Se desempila un elemento.
	  E2 = Pop (&valores);	//Se desempila un elemento.
	  resultado = (E1.Float - E2.Float);	//Se realiza la operaci�n resta.
	  E3.Float = resultado;	//Se le asigna a E4 el valor del resultado de la operaci�n.
	  Push (&valores, E3);	//Se empila el resultado.
	}




    }

  Res.Float;
  Res = Pop (&valores);		//Se le asigna al elemento Res el resultado final de la evaluaci�n.

  res_final = Res.Float;	//Se le asigana el resultado final a una variable.

  Destroy (&valores);		//Se destruye la pila.
  return res_final;		//Se retorna el resultado final de la evalauci�n.


}

//PRINCIPAL

int
main (void)
{
  char cadena[TAM];		//Se declara un arreglo de tipo caracter y de tama�o definido arriba (TAM 100)
  char *cadena_posfijo = '\0';	//Se declara Variable de tipo apuntador a caracter que recibe el arreglo que retorna la funci�n posfijo
  float resultado;		//Se declara una variable de tipo entero 

  printf ("<<<<<<<<<<<<<Bienvenido>>>>>>>>>>>>>:\n");	//Impresi�n en pantalla
  printf ("Inserte una expresion aritmetica:\n");	//Impresi�n en pantalla


  scanf ("%s", cadena);		//Captura la expresi�n y la guarda en el arreglo de tipo caracter declarado anteriormente

  ValidarParentesis (cadena);	//Se llama a la primer funci�n teniendo como entrada la cadena ingresada por el usuario

  cadena_posfijo = Posfijo (cadena);	//Variable de tipo caracter que llama a nuestra segunda funci�n (posfijo) 
  printf ("Expresion en posfijo:\t %s \n", cadena_posfijo);	//Impresi�n en pantalla del resultado del arreglo resultante de la funci�n que se llamo en la linea anterior

  resultado = EvalPosfijo (cadena_posfijo);	//Variable de tipo flotante que llama a nuestra tercera funci�n, tomando como entrada para esta, el arreglo retornado por la funci�n posfijo y sustituyendo los valores de las variables dadas por el usuario
  printf ("Evaluacion: \t %f \n", resultado);	//Impresi�n en pantalla del resultado de la operaci�n aritmetica.
}
