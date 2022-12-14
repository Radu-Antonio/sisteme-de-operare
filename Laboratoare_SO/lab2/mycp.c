#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("nici nu sti sa folosesti comanda\n");
		return -1;
	}

	char* input_file = argv[1];
	char* output_file = argv[2];

	int fd_in = open(input_file, O_RDONLY, S_IRUSR);
	int fd_out = open(output_file, O_WRONLY, S_IWUSR);
	const int BUFF_SIZE = 1024;
	char* buffer = malloc(BUFF_SIZE * sizeof(char));

	int bytes_read = read(fd_in, buffer, BUFF_SIZE);
	while (bytes_read > 0) {
		write(fd_out, buffer, bytes_read);
		bytes_read = read(fd_in, buffer, BUFF_SIZE);
	}

	free(buffer);
	close(fd_in);
	close(fd_out);
	return 0;
}