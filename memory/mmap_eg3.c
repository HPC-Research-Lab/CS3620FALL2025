#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {

	int fd = open("input.txt", O_RDWR);
	printf("pid: %d\n", getpid());
	struct stat sb;
	fstat(fd, &sb);
	size_t file_size = sb.st_size;
	getchar();
	char *addr3 = (char *)mmap(0, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	getchar();
	addr3[0] = '9';
	msync(addr3, file_size, MS_SYNC);
	close(fd);
	return 0;

}
