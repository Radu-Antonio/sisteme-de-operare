#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	pid_t child = fork();

	if (child == 0) {
		char* argv[] = {"ls", NULL};
		execve("/usr/bin/ls", argv, NULL);
	} else {
		printf("My PID=%d, Cild PID=%d\n", getpid(), child);
	}

	return 0;
}