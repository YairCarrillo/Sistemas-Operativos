#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
	int i,j;
	int pid;
	int semid;
	key_t llave =2234;
	int semban=IPC_CREAT|0666;
	int nsems=1;
	int nsops;
	struct sembuf *sops=(struct sembuf*)malloc(2*sizeof(struct sembuf));
	printf("Inicializando semaforo...\n");
	if((semid=semget(llave,nsems,semban))==-1){
		perror("semget:error al inicalizar semaforo");
		exit(1);
	}
	else{
		printf("Semaforo ininializado\n");
	}
	if((pid=fork())<0){
		perror("fork. error al crear proceso");
		exit(1);
	}
	if(pid==0){
		i=0;
		while(i<3){
			nsops=2;
			sops[0].sem_num=0;
			sops[0].sem_op=0;
			sops[0].sem_flg=SEM_UNDO;

			sops[1].sem_num=0;
			sops[1].sem_op=1;
			sops[1].sem_flg=SEM_UNDO|IPC_NOWAIT;
			printf("semop:hijo llamado a semop(%d,&sops,%d) con:", semid,nsops);
			for(j=0;j<nsops;j++){
				printf("\n\t sops[%d].sem_num=%d",j,sops[j].sem_num);
				printf("sem_op=%d",sops[j].sem_op);
				printf("sem_flg=%#o\n",sops[j].sem_flg);
			}
			if((j=semop(semid,sops,nsops))==-1){
				perror("sempo: error en operacion del semaforo");
			}
			else{
				printf("\tsemop:regreso de semop() %d\n",j);
				printf("\n\nProceso hijo toma el control del semaforo: %d/3 veces\n",i+1);
				sleep(5);
				nsops=1;
				sops[0].sem_num=0;
				sops[0].sem_op=-1;
				sops[0].sem_flg=SEM_UNDO|IPC_NOWAIT;
				if((j=semop(semid,sops,nsops))==-1){
					perror("sempo: error en operacion del semaforo");	
				}
				else{
					printf("Proceso hijo toma el control del semaforo: %d/3 veces\n",i+1);
					sleep(5);
				}
				++i;
			}
		}
	}
	else{
		i=0;
		while(i<3){
			nsops=2;
			sops[0].sem_num=0;
			sops[0].sem_op=0;
			sops[0].sem_flg=SEM_UNDO;

			sops[1].sem_num=0;
			sops[1].sem_op=1;
			sops[1].sem_flg=SEM_UNDO|IPC_NOWAIT;
			printf("semop:hijo llamado a semop(%d,&sops,%d) con:", semid,nsops);
			for(j=0;j<nsops;j++){
				printf("\n\t sops[%d].sem_num=%d",j,sops[j].sem_num);
				printf("sem_op=%d",sops[j].sem_op);
				printf("sem_flg=%#o\n",sops[j].sem_flg);
			}
			if((j=semop(semid,sops,nsops))==-1){
				perror("sempo: error en operacion del semaforo");
			}
			else{
				printf("\tsemop:regreso de semop() %d\n",j);
				printf("\n\nProceso hijo toma el control del semaforo: %d/3 veces\n",i+1);
				sleep(5);
				nsops=1;
				sops[0].sem_num=0;
				sops[0].sem_op=-1;
				sops[0].sem_flg=SEM_UNDO|IPC_NOWAIT;
				if((j=semop(semid,sops,nsops))==-1){
					perror("sempo: error en operacion del semaforo");	
				}
				else{
					printf("Proceso hijo toma el control del semaforo: %d/3 veces\n",i+1);
					sleep(5);
				}
				++i;
			}
		}
	}
}