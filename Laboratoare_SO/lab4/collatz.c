#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void collatz(int n) {
	printf("%d: %d ", n, n);
	while (n > 1) {
		n = (n % 2 == 0 ? n / 2 : n * 3 + 1); 
		printf("%d ", n);
	}
}

int main(int argc, char** argv) {
	pid_t child = fork();

	if (child == 0) {
		int num = atoi(argv[1]);
		collatz(num);
		printf("\nChild %d finished\n", getpid());
	}

	return 0;
}