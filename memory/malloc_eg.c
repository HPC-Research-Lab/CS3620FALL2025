#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

int main() {
	//int *p = (int*)malloc(sizeof(int));
	int *p = (int*)mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	//
	*p = 10;
	printf("%p, %d\n", p, *p);
	getchar();


	//free(p);
	munmap(p, 4096);
	
	printf("%p, %d\n", p, *p);
	return 0;
}


