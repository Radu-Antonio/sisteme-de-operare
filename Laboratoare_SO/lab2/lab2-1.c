#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	char* s = "Hello World!\n";
	write(1, s, strlen(s));

	return 0;
}