#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	printf("my pid is: %d\n", getpid());
	printf("location of code: %p\n", (void *) main);
	printf("location of heap: %p\n", (void *) malloc(1));
	int x = 3;
	printf("location of stack: %p\n", (void *) &x);

	sleep(1000);
}
