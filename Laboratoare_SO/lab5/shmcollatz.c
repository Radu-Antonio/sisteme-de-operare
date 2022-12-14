#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv) {
	printf("Starting parent: %d\n", getpid());
	int page_size = getpagesize();
	int shm_size = argc * page_size;
	char file_name[] = "memory";
	int shm_fd = shm_open(file_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	ftruncate(shm_fd, shm_size);

	for (int i = 1; i < argc; i++) {
		pid_t child = fork();

		if (child == 0) {
			int n = atoi(argv[i]);
			char* shm_ptr = mmap(0, page_size, PROT_WRITE, MAP_SHARED, shm_fd, i * page_size);
			shm_ptr += sprintf(shm_ptr, "%d: %d ", n, n);
			
			while (n > 1) {
				n = (n % 2 == 0 ? n / 2 : n * 3 + 1); 
				shm_ptr += sprintf(shm_ptr, "%d ", n);
			}
			shm_ptr += sprintf(shm_ptr, "\n");
			munmap(shm_ptr, page_size);
			printf("Done. Parent %d Child %d\n", getppid(), getpid());
			exit(0);
		}
	}	

	for (int i = 1; i < argc; i++) {
		wait(NULL);
	}
	
	for (int i = 1; i < argc; i++) {
		char* shm_ptr = mmap(0, page_size, PROT_READ, MAP_SHARED, shm_fd, i * page_size);
		printf("%s", shm_ptr);
		munmap(shm_ptr, page_size);		
	}

	printf("Done. Parent %d Child %d\n", getppid(), getpid());
	shm_unlink(file_name);
	return 0;
}