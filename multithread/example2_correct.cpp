#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <stdlib.h>

const int NUM_ACCOUNT = 100;
const int NUM_TRANS = 200;
const int INIT_AMOUNT = 100;
const int TOTAL_AMOUNT = NUM_ACCOUNT * INIT_AMOUNT;

int account[NUM_ACCOUNT];

pthread_rwlock_t lock;

void* read(void * id) {

	unsigned long idx = (unsigned long)id;
	
	for (int i=0; i<NUM_TRANS; i++) {

		int sum = 0;
		pthread_rwlock_rdlock(&lock);
		for (int j=0; j<NUM_ACCOUNT; j++) sum += account[j];
		pthread_rwlock_unlock(&lock);
		if (sum != TOTAL_AMOUNT) {
			std::cerr << "error" << std::endl;
			exit(-1);
		}
		usleep(1);
	}

	return NULL;
}

void* write(void * id) {
	unsigned long idx = (unsigned long)id;
	for (int i=0; i<NUM_TRANS; i++) {
	
		int to = rand() % NUM_ACCOUNT;
		pthread_rwlock_wrlock(&lock);
		int amount = rand() % account[idx];
		account[idx] -= amount;
		account[to] += amount;
		pthread_rwlock_unlock(&lock);
		
		usleep(2);
	}

	return NULL;
}

int main() {

	for (int i=0; i<NUM_ACCOUNT; i++) {
		account[i] = INIT_AMOUNT;
	}

	pthread_rwlock_init(&lock, NULL);

	pthread_t readers[NUM_ACCOUNT];
	pthread_t writers[NUM_ACCOUNT];

	for (int i=0; i<NUM_ACCOUNT; i++) {
		pthread_create(&(readers[i]), NULL, read, (void *)i);
	}


	for (int i=0; i<NUM_ACCOUNT; i++) {
		pthread_create(&(writers[i]), NULL, write, (void *)i);
	}

	for (int i=0; i<NUM_ACCOUNT; i++) {
		pthread_join(readers[i], NULL);
	}

	for (int i=0; i<NUM_ACCOUNT; i++) {
		pthread_join(writers[i], NULL);
	}

	for (int i=0; i<NUM_ACCOUNT; i++) {
		std::cout << account[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}
