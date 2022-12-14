#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void collatz(int n) {
	printf("%d: %d ", n, n);
	while (n > 1) {
		n = n % 2 == 0 ? n / 2 : n * 3 + 1; 
		printf("%d ", n);
	}
}

int main(int argc, char** argv) {
	printf("Staring parent %d\n", getpid());
	for (int i = 1; i < argc; i++) {
		pid_t child = fork();
		
		if (child == 0) {
			int num = atoi(argv[i]);
			collatz(num);
			printf("\nDone Parent %d Me %d\n", getppid(), getpid());
			return 0;
		}
	}

	for (int i = 1; i < argc; i++)
		wait(NULL);

	return 0;
}
