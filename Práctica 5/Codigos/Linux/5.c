#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *hhhilo(void *arg)
{
	printf("Practica No.5\n");
	return 0;
}


void *hhilo(void *arg)
{
	pthread_t threads[5];
    	int i;
	printf("%lu\n",pthread_self());	
	for (i = 0; i < 5; i++) 
	{
		pthread_create(&threads[i], 0, (void *) hhhilo, 0);
		pthread_join(threads[i], 0);
	}
	return 0;;	
}

void *hilo(void *arg)
{
	pthread_t threads[10];
	int i;
	printf("%lu\n",pthread_self());	
	for (i = 0; i < 10; i++) 
	{
		pthread_create(&threads[i], 0, (void *) hhilo, 0);
		pthread_join(threads[i], 0);
	}
	return 0;	
}

int main( void )
{
	pid_t p = fork();
	if (p == 0) 
	{
		pthread_t threads[15];
		int i;
		printf("%lu\n",pthread_self());	
		for (i = 0; i < 15; i++) 
		{		
			pthread_create(&threads[i], 0, (void *) hilo, 0);
			pthread_join(threads[i], 0);
		}
		exit(0);
	}

	else
	{
		printf("\n%d\n",getpid());
	}
	 exit(0);
	
}


