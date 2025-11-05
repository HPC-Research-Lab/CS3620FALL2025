#include <iostream>
#include <pthread.h>
#include <stdlib.h>



int a[1000000];
size_t size = 0;

void *insert(void *) {

	for (int i=0; i<100000; i++) { 
		int x = rand();
		a[size] = x; 
		size = size + 1;
	}
	return NULL;
}

int main() {

	pthread_t threads[10];

	for (int i=0; i<10; i++)
		pthread_create(&threads[i], NULL, insert, NULL);

	for (int i=0; i<10; i++)
		pthread_join(threads[i], NULL);
	
	if (size != 1000000) {
		
		std::cout << size << std::endl;
		std::cerr << "error" << std::endl;
	}

	return 0;
}
