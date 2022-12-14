#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n, p, m;
int** A, **B, **C;

struct position {
	int row, col;
};

void* prod(void* arg) {
	struct position* idx = (struct position*) arg;
	int i = idx->row;
	int j = idx->col;
	free(idx);

	C[i][j] = 0;
	for (int k = 0; k < p; k++)
		C[i][j] += A[i][k] * B[k][j];

	return NULL;
}

int main() {
	scanf("%d%d%d", &n, &p, &m);

	A = malloc(sizeof(int*) * n);
	C = malloc(sizeof(int*) * n);
	for (int i = 0; i < n; i++) {
		A[i] = malloc(sizeof(int) * p);
		C[i] = malloc(sizeof(int) * m);
	}

	B = malloc(sizeof(int*) * p);
	for (int i = 0; i < p; i++) {
		B[i] = malloc(sizeof(int) * m);
	}

	for (int i = 0; i < n; i++) 
		for (int j = 0; j < p; j++)
			scanf("%d", &A[i][j]);

	for (int i = 0; i < p; i++) 
		for (int j = 0; j < m; j++)
			scanf("%d", &B[i][j]);

	pthread_t* threads = malloc(sizeof(pthread_t) * n * m);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			struct position* idx = malloc(sizeof(struct position));
			idx->row = i;
			idx->col = j;
			pthread_create(threads + i * m + j, NULL, prod, idx);
		}

	for (int i = 0; i < n * m; i++)
		pthread_join(threads[i], NULL);

	for(int i = 0;i < n; i++) {
		for(int j = 0; j < m; j++) {
			printf("%d ", C[i][j]);
		}
		puts("");
	}

	free(threads);
	for (int i = 0; i < n; i++) {
		free(A[i]);
		free(C[i]);
	}
	for (int i = 0; i < p; i++) {
		free(B[i]);
	}
	free(A);
	free(B);
	free(C);
	return 0;
}