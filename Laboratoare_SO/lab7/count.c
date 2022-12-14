#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#define MAXRESOURCES 5
#define MAXTHREADS 6

int available_resources = MAXRESOURCES;
pthread_mutex_t mtx; 

int increase_count(int resource_count) {
	pthread_mutex_lock(&mtx); 
	available_resources += resource_count ;
	printf("Released %d resources %d remaining\n", resource_count, available_resources);
	pthread_mutex_unlock(&mtx);

	return 0;
}

int decrease_count(int resource_count) {
	while(!pthread_mutex_lock(&mtx) && available_resources < resource_count) {
		pthread_mutex_unlock(&mtx); 
	}

	available_resources -= resource_count;
	printf("Got %d resources %d remaining\n", resource_count, available_resources);
	pthread_mutex_unlock(&mtx);

	return 0;
}

void *my_thread(void *arg) {
	int c = *((int *) arg);
	decrease_count(c);
	increase_count(c);

	return NULL;
}

int main() {
	pthread_mutex_init(&mtx, NULL);
	printf("MAX_RESOURCES = %d\n", available_resources);

	int resource_count;
	pthread_t *thread = malloc(MAXTHREADS * sizeof(pthread_t)); 
	
	srand(time(0));
	for(int i = 0; i < MAXTHREADS; i++)	{
		resource_count = rand() % (MAXRESOURCES + 1);
		pthread_create(&thread[i], NULL, my_thread, &resource_count);
	}

	for(int i = 0; i < MAXTHREADS; i++)	{
		pthread_join(thread[i], NULL);
	}

	pthread_mutex_destroy(&mtx); 	
	return 0;
}