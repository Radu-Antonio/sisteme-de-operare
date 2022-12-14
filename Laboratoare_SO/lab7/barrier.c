#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>

int NTHRS;
int at_barrier;
pthread_mutex_t mutex;
sem_t sem;

void barrier_point() {
	pthread_mutex_lock(&mutex);
	at_barrier++;
	if (at_barrier == NTHRS) {
		for (int i = 1; i <= NTHRS; i++) {
			sem_post(&sem);
		}
		at_barrier = 0;
	}
	pthread_mutex_unlock(&mutex);
	sem_wait(&sem);
}

void *tfun(void *id_thread) {
	int *tid = (int *) id_thread;
	printf("%d reached the barrier\n", *tid );
	barrier_point();
	printf("%d passed the barrier\n" , *tid );

	free(tid);
	return NULL;
}

int main() {
	printf("NTHRS = ");
	scanf("%d", &NTHRS);

	pthread_mutex_init(&mutex, NULL);
	sem_init(&sem, 0, 0);

	pthread_t thread[NTHRS];
	int i, *arg[NTHRS];

	for(i = 0; i < NTHRS; i++) {
		arg[i] = malloc(sizeof(int));
		*arg[i] = i;
		pthread_create(&thread[i], NULL, tfun, arg[i]);	
	}

	for(i = 0; i < NTHRS; i++)
		pthread_join(thread[i], NULL);

	pthread_mutex_destroy(&mutex);
	sem_destroy(&sem);
	return 0;
}