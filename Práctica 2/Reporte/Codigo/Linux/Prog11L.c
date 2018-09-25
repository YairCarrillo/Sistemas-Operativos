#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int Mostrar()
{
	char archi[50];
	int fd=0;
	char c;
		printf("\nEscriba cual es el archivo que desea abrir para ver su contenido, recuerde escribir la extension del mismo: ");
		scanf("%s", archi);
			
		fd = open(archi,O_RDONLY);
		printf("\n");
			
		if(fd!=-1) //Si el archivo existe...
		{
			//... se lee caracter por caracter y cada uno de estos es mostrado en pantalla.
			while(read(fd,&c,sizeof(c)!=0)){ 
				printf("%c",c);
				}
			//Se cierra el archivo y la opcion del menú.
			close(fd);
		}
			
		else
		printf("\nEl archivo no existe\n");
		
		return 0;
}

int Copiar()
{
	char c;
	char archi[50];
	int i=0;
	int fd=0;
	int fd2;
	char num='0';
	char destino[50]="/home/emm/11_Copias/*.txt";  //Se da una direccion destino previamente
	int con=1;
	
	while(con==1)
	{
		system("clear");
	printf("\nIngrese el archivo que desea copiar: ");
	scanf("%s", archi);
	
	 fd = open(archi,O_RDONLY);
 
			if(fd!=-1) //Si el archivo existe...
			{
									destino[20]=num;
				
				fd2 = open(destino,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR); //Se crea un nuevo archivo con el mismo nombre +"_c" ...
				while(read(fd,&c,sizeof(c)!=0))
				{
					write(fd2,&c,sizeof(c)); //se copia y ...
					}
						
						printf("\nArchivo fuente en: %s \nArchivo copiado en: %s\n", archi,destino);
						num++;
					close(fd);
					close(fd2);
			}  //... esto se repite para cada archivo que se desee copiar
			else 
			printf("\n El archivo escrito no existe en este directorio \n");
			
			printf("\nDesea introducir otro archivo? Si = 1 , No = 0 : ");	
			scanf("%d",&con);
	}
	return 0; 
}

int menu(int opc)
{	
	printf("\n\nQue desea hacer?\n");
	printf("1. Mostrar contenido de un archivo\n");
	printf("2. Copiar archivo al directorio previamente establecido\n");
	printf("3. Salir\n");
	return 0;
 } 

//Función principal
int main()
{
//Declaramos variables
int opc;


//O_RDONLY abre el archivo salida.txt en modo lectura

	do{
	menu(opc);
	scanf("%d", &opc);
	system("clear");
	
	switch(opc)
	{
		case 1:
			Mostrar();
			break;
			
		case 2:
			Copiar();
			break;
			
		default:
			printf("\nADIOS\n");
			break;
	
		}	
	} while(opc<3);

}
