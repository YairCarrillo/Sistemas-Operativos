#include <stdio.h>
int main()
{
	int entrada, numero, i, j, k, numespacios, numespdentro, numastecpr, numastecse, numastec, numespenmedio;
	k = 0;
	char salida[10000];
	int l;
	scanf("%d", &entrada);
	numero = 2 * entrada;
	if (entrada % 2 == 1)
		numespacios = entrada / 2;
	else
		numespacios = entrada / 2;
	numastec = 1;
	numespenmedio = 0;
	i = 0;
	l = 0;
	while (i<entrada / 2)
	{
		k = 0;
		while (k<numespacios)
		{
			salida[l] = ' ';
			printf(" ");
			k++;
			l++;
		}
		salida[l] = '*';
		l++;
		printf("*");
		k = 0;
		while (k<numespenmedio)
		{
			salida[l] = ' ';
			l++;
			printf(" ");
			k++;
		}
		k = 0;
		if (numespenmedio != 0)
		{
			salida[l] = '*';
			l++;
			printf("*");
			numespenmedio = numespenmedio + 2;
		}
		else if (numespenmedio == 0)
			numespenmedio++;
		if (entrada % 2 == 1)
		{
			while (k<2 * numespacios)
			{
				salida[l] = ' ';
				l++;
				printf(" ");
				k++;
			}
		}
		else
		{
			while (k<(2 * numespacios - 2))
			{
				salida[l] = ' ';
				l++;
				printf(" ");
				k++;
			}
		}
		k = 0;
		while (k<numastec)
		{
			salida[l] = '*';
			l++;
			printf("*");
			k++;
		}
		k = 0;
		while (k<numespacios)
		{
			salida[l] = ' ';
			l++;
			printf(" ");
			k++;
		}
		numespacios--;
		numastec += 2;
		printf("\n");
		salida[l] = '\n';
		l++;
		i++;
	}
	k = 0;
	while (k<numero)
	{
		salida[l] = '*';
		l++;
		printf("*");
		k++;
	}
	printf("\n");
	salida[l] = '\n';
	l++;
	i = 0;
	numespacios++;
	numespenmedio -= 2;
	numastec -= 2;
	while (i<entrada / 2)
	{
		k = 0;
		while (k<numespacios)
		{
			salida[l] = ' ';
			l++;
			printf(" ");
			k++;
		}
		if (i + 1<entrada / 2)
		{
			printf("*");
			salida[l] = '*';
			l++;
		}
		k = 0;
		while (k<numespenmedio)
		{
			salida[l] = ' ';
			l++;
			printf(" ");
			k++;
		}
		k = 0;
		if (numespenmedio != 0)
		{
			salida[l] = '*';
			l++;
			printf("*");
			numespenmedio = numespenmedio - 2;
		}
		if (entrada % 2 == 1)
		{
			while (k<2 * numespacios)
			{
				salida[l] = ' ';
				l++;
				printf(" ");
				k++;
			}
		}
		else
		{
			while (k<(2 * numespacios - 2))
			{
				salida[l] = ' ';
				l++;
				printf(" ");
				k++;
			}
		}
		k = 0;
		while (k<numastec)
		{
			salida[l] = '*';
			l++;
			printf("*");
			k++;
		}
		k = 0;
		while (k<numespacios)
		{
			salida[l] = ' ';
			l++;
			printf(" ");
			k++;
		}
		numespacios++;
		numastec -= 2;
		printf("\n");
		salida[l] = '\n';
		l++;
		i++;
	}
	salida[l] = '0';
	printf("\n");
	char res;
	char nombre[50];
	printf("Desea guardar en archivo nuevo?[S/N]\n");
	scanf("%s", &res);
	if (res == 'S' || res == 's')
	{
		printf("Ingrese el nombre del archivo a guardar:\n");
		scanf("%s", nombre);
		FILE *archivo = fopen(nombre, "w+");
		if (archivo != NULL)
		{
			i = 0;
			while (salida[i] != '0')
			{
				fprintf(archivo, "%c", salida[i]);
				i++;
			}
			fclose(archivo);
		}
	}
	else if (res == 'N' || res == 'n')
	{
		printf(":(\n");
	}
}
