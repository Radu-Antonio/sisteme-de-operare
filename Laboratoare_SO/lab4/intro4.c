#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	pid_t child = fork();

	if (child == 0) {
		printf("Sunt copilu: %d si parintele: %d\n", getpid(), getppid());
	} else {
		wait(NULL);
		printf("Sunt parintele: %d si copilul: %d\n", getpid(), child);
	}

	return 0;
}

int main() {
	char *argv[] = {"pwd", NULL};
	execve("/bin/pwd", argv, NULL);
	return 0;
}