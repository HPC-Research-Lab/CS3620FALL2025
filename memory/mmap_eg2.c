#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
	printf("my pid is: %d\n", getpid());
	getchar();
	void *addr1 = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	printf("addr1: %p\n", addr1);
	getchar();

	int pid = fork();
	if (pid == 0) {
		printf("I'm child, my pid is: %d\n", getpid());
		*((int*)addr1) = 10;
	} else if (pid > 0) {
		wait(NULL);
		printf("the value of addr1 in the parent is %d\n", *((int*)addr1));
	} else {
	    printf("fail to create child\n");
		exit(-1);
	}

	return 0;

}
