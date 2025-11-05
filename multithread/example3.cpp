#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t forks[5];

void think() {
	usleep(2);
}

void eat() {
	usleep(2);
}

void getforks(int i) {
	if (i != 0) {
		pthread_mutex_lock(&forks[i]);
		pthread_mutex_lock(&forks[(i+1)%5]);
	} else {
		pthread_mutex_lock(&forks[1]);
		pthread_mutex_lock(&forks[0]);
	}
}

void putforks(int i) {
	pthread_mutex_unlock(&forks[i]);
	pthread_mutex_unlock(&forks[(i+1)%5]);
}



void *philosopher(void * id) {

	int idx = (int)id;

	for (int i=0; i<100; i++) { 
		think();
		getforks(idx);
		eat();
		putforks(idx);
	}
	return NULL;
}

int main() {

	pthread_t threads[5];

	for (int i=0; i<5; i++)
		pthread_create(&threads[i], NULL, philosopher, (void*)i);

	for (int i=0; i<5; i++)
		pthread_join(threads[i], NULL);

	return 0;
}
