#include "matriz.c"
#define TAM_MEM 400
double *startMemory (key_t llave){
   	int shmid;
   	double *shm;
  	if ((shmid = shmget (llave, TAM_MEM, IPC_CREAT|0666)) < 0)
  	{
      	perror ("Error al obtener memoria compartida: shmget");
      	exit (-1);
  	}
  	if ((shm = shmat (shmid, NULL, 0)) == (double *)-1)
  	{
		perror ("Error al enlazar la memoria compartida: shmat");
      	exit (-1);
    }
    return shm;
}
 
void writeMemory (double *shm, matriz A)
{
  for (int i = 0; i < N; i++)
    for (int k = 0; k < N; k++)
      *shm++ = A[i][k];
}
 
matriz castMemory (double *shm)
{
  matriz A = nueva ();
  for (int i = 0; i < N; i++)
    for (int k = 0; k < N; k++)
      A[i][k] = *shm++;
  return A;
}
int IniciarSemaforo ()
{
  	int semid;
  	int nsems = 1;
  	key_t llave = ftok ("/bin/ls", 1234);
  	if ((semid = semget (llave, nsems, IPC_CREAT | 0666)) == -1)
    {
      	perror ("semget: error al iniciar el semaforo");
      	exit (1);
    }
  	if (semctl (semid, 0, SETVAL, 0) == -1)
   	{
      	printf ("Error al crear el semaforo\n");
    }
  return semid;
}
 
void EncenderSemaforo (int semid)
{
  	struct sembuf sops;
	sops.sem_num = 0;
  	sops.sem_op = 1;
  	sops.sem_flg = 0;
  	if (semop (semid, &sops, 1) == -1)
    {
      	perror ("semop: error en operacion del semaforo\n");
    }
}
	 
void ApagarSemaforo (int semid)
{
  	struct sembuf sops;
  	sops.sem_num = 0;
  	sops.sem_op = -1;
  	sops.sem_flg = 0;
  	if (semop (semid, &sops, 1) == -1)
    {
      	perror ("semop: error en regreso de semop ()\n");
    }
}
