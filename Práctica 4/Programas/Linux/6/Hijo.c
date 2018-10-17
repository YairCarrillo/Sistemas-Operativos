#include <stdio.h>

int main(int argc, char const *argv[])
{
	char mensaje[100];
	strcpy(mensaje,"Hola mundo");
	strcat(mensaje,argv[1]);
	printf("%s\n",mensaje);
	return 0;
}