#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	printf("my pid is: %d\n", getpid());
	getchar();
	char *addr = (char *)mmap(0, 100, PROT_READ, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	printf("addr: %p\n", addr);
	getchar();
	return 0;

}
