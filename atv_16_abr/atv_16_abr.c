#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int NMAX = 10;
int ticket[10];
sem_t semaphore;

void create_tickets()
{
	for (int i = 0; i < NMAX; i++)
	{
		ticket[i] = 1;
	}
}

void *get_ticket(void *var)
{
	sem_wait(&semaphore);
	for (int i = 0; i < NMAX; i++)
	{
		if (ticket[i])
		{
			int *ret;
			ret = (int *)malloc(sizeof(int));
			*ret = i;
			ticket[i] = 0;
			printf("getting ticket %d\n", i);
			sem_post(&semaphore);
			pthread_exit(ret);
		}
	}
}

void *return_ticket(void *var)
{
	sem_wait(&semaphore);
	ticket[*(int *)var] = 1;
	printf("returning ticket %d\n", *(int *)var);
	free(var);
	sem_post(&semaphore);
	pthread_exit(NULL);
}

void *use_ticket(void *var)
{
	void *status;
	pthread_t tid, tid2;

	pthread_create(&tid, NULL, get_ticket, NULL);
	pthread_join(tid, &status);

	printf("using ticket %d\n", *(int *)status);

	pthread_create(&tid2, NULL, return_ticket, status);
	pthread_join(tid2, NULL);

	pthread_exit(NULL);
}

int main()
{
	pthread_t tid[30];
	sem_init(&semaphore, 0, 1);
	create_tickets();

	for (int i = 0; i < 30; i++)
	{
		pthread_create(&tid[i], NULL, use_ticket, NULL);
	}

	for (int i = 0; i < 30; i++)
	{
		pthread_join(tid[i], NULL);
	}
	return 0;
}
