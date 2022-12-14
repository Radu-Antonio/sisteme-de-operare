#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv) {
	// shm_open = creeaza/deschide un obiect de memorie partajata
	// Link with -lrt.

	char shm_name[] = "myshm";
	int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR ,S_IRUSR | S_IWUSR);

	// setam dimensiunea cu ftruncate(int fd, off_t length)
	const int SHM_SIZE = 1000;
	ftruncate(int shm_fd, SHM_SIZE);

	// incarcam memoria partajata in spatiul procesului folosind: 
	// mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
	void* shm_ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);


	// dimensiunea trebuie sa fie multiplu de pagesize
	const int page_size = getpagesize();

	// cand nu mai este nevoie de zona de memorie incarcata folosim munmap
	munmap(shm_ptr, SHM_SIZE);


	// shm_unlink = distruge un obiect de memorie partajata
	shm_unlink(shm_name);

	return 0;
}