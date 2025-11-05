#include <iostream>
#include <pthread.h>
using namespace std;

int a = 0;

pthread_mutex_t mutex;

void* thread_func(void *args) {
	for (int i=0; i<1000000; i++) {
		pthread_mutex_lock(&mutex);
		a += 1;
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}


int main() 
{
	pthread_t thread1, thread2;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread1, NULL, thread_func, NULL);
	pthread_create(&thread2, NULL, thread_func, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	cout << a << endl;
	return 0;
}
