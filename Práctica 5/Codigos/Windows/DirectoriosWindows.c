#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <windows.h>
#include <errno.h>
#include <string.h>
DWORD WINAPI abrefichero_file(LPVOID lpParam);
int error(char nombre[50]);
int copia_archivo(char f_org[200],char f_dest[200]);
int contador_hilos=0;
DWORD hilos[50];
HANDLE manhilo;
struct datos {
        char f_org[200];
        char f_dest[200];
};
int main(int argc, char const *argv[])
{
        char path_o[200];
        char  path_d [200];
        printf("CUAL ES TU DIRECCION ORIGEN \n");
        scanf("%s",path_o);
        printf("CUAL ES TU DIRECCION DESTINO \n");
        scanf("%s",path_d);
        struct datos p1 ;
        strcpy(p1.f_org,path_o);
        strcpy(p1.f_dest,path_d);
        manhilo=CreateThread(NULL,0,abrefichero_file,&p1,0,&hilos[contador_hilos]);
        WaitForSingleObject(manhilo,INFINITE);
        CloseHandle(manhilo);
        contador_hilos++;
        /* code */
        return 0;
}
DWORD WINAPI abrefichero_file(LPVOID arg)
{
    struct datos * p;
    struct datos aux_p;
    p = ( struct datos *) arg ;
    char aux_o[200];
    char aux_d[200];
    DIR* O;
    int i=0;
    DIR* D;
    struct dirent *dit;
    printf("la DIRECCION origen es %s  y la destino es %s \n",p->f_org,p->f_dest);
    if(!(O=opendir(p->f_org)) || !(D=opendir(p->f_dest)))
    {
        perror("Error de apertura de ficheros");
      exit(EXIT_FAILURE);
    }
    while ((dit = readdir(O)) != NULL )
    {
        strcpy(aux_p.f_org,p->f_org);
        strcpy(aux_p.f_dest,p->f_dest);
        strcat(aux_p.f_org,dit->d_name);
        strcat(aux_p.f_dest,dit->d_name);
        if(dit->d_type==0)
        {
            copia_archivo(aux_p.f_org,aux_p.f_dest);
        }
        else if(error(dit->d_name))
        {
            strcat(aux_p.f_org,"/");
            strcat(aux_p.f_dest,"/");
            CreateDirectory (aux_p.f_dest, NULL);
            //pthread_create (& hilos[contador_hilos] , NULL , abrefichero_file , ( void *) & aux_p);
            //pthread_join ( hilos[contador_hilos] , NULL ) ;
            manhilo=CreateThread(NULL,0,abrefichero_file,&aux_p,0,&hilos[contador_hilos]);
            WaitForSingleObject(manhilo,INFINITE);
            CloseHandle(manhilo);
            contador_hilos++;
            //abrefichero_file(aux_o,aux_d);
            //se crea hilo y se llama recursivamente
        }
    }
}
int copia_archivo(char f_org[200],char f_dest[200])
{
    FILE *fp_org, *fp_dest;
    int c=0;
    if(!(fp_org=fopen(f_org,"r")) || !(fp_dest=fopen(f_dest,"w")))
    {
            printf("%s\n",f_dest);
             perror("Error de apertura de ficheros");
            exit(EXIT_FAILURE);
    }
    while((c=fgetc(fp_org))!=EOF)
        fputc(c,fp_dest);
    if(ferror(fp_org) || ferror(fp_org))
         return 1;
    fclose(fp_org);
    fclose(fp_dest);
    return 0;
}
int error(char nombre[100])
{
    printf("%s\n",nombre);
    if(nombre[0]=='.')
        return 0;
    else 
        return 1;
}


