#include <windows.h>
#include <stdio.h>
#include <string.h>

int Copiar()
{
int con=1;
char num='0';
char destino[50]="F:\\SO\\Copias_11\\*.txt"; //Directorio destino previamente creado
char archi[50];
       while(con==1){
	system("cls"); 
	printf("\nEscriba el directorio del archivo que quiere copiar seguido de su nombre: ");
	scanf("%s", &archi);

	destino[16]=num; //El nombre del archivo copiado sera un numero
			
int cp= CopyFile(archi,destino,0);  //Copiamos lo encontrado en el archivo origen y lo mandamos al archivo destino
				if(!cp)
				{
					printf("\nError al copiar el archivo\n");
				}
				else
					{
						printf("\nArchivo fuente en: %s \nArchivo copiado en: %s\n", archi,destino);
						num++;
					}
					
					printf("\nDesea copiar otro archivo?  SI = 1 , NO = 0 : ");
					scanf("%d", &con);	
			}	
}

int menu(opc)
{	
	printf("\n\nQue desea hacer?\n");
	printf("1. Mostrar contenido de un archivo\n");
	printf("2. Copiar archivo al directorio previamente establecido\n");
	printf("3. Salir\n");
	return 0;
 } 

int main(){

//Declaramos variables
int opc;
int con=1;
HANDLE hFile;
char c;
int i;
char archi[60];
DWORD taman=1000;
DWORD bytesRead;
char buff[4096];

	do{
	menu(opc);
	scanf("%d", &opc);
	system("cls"); 
	
	switch(opc)
	{
		case 1:
				
			printf("\nEscriba cual es el archivo que desea abrir para ver su contenido, recuerde escribir la extension del mismo: ");
			scanf("%s", archi);
			hFile = CreateFile(archi, GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL); //Abrimos archivo
			printf("\n");
			
			if(hFile != INVALID_HANDLE_VALUE)
			{
			ReadFile(hFile,buff,4096, &bytesRead, NULL); //Leemos el archivo y almacenamos lo leido en buff.
			
			for(i=0;i<=strlen(buff);i++) //Mostramos en pantalla el mensaje leido de buff
					printf("%c",buff[i]);
				
				
			//Se cierra el archivo y la opcion del menú.
			close(hFile);
			
			for(i=0;i<strlen(buff);i++)
				buff[i]=' ';
			}
			else
				printf("\nProblema al intentar visualizar archivo\n");

			break;
			
		case 2:
			
			Copiar();
			break;
			
		default:
			printf("\nADIOS\n");
			break;
			
		}	
	} while(opc<3);
return 0;
}
