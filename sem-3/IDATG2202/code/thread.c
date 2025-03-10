
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int loops;
int items = 1;

void *producer(void *arg) {
	printf("Produser\n");
}


void *consumer(void *arg) {
	printf("Consumer\n");
}


int main(int argc, char **argv) {

	// Dont run program if there are not 4 arguments.
	if (argc != 4)
		return 1;

	const int producers = atoi(argv[1]);
	const int consumers = atoi(argv[2]);

	const int size = producers + consumers;

	pthread_t threads[size];

	int i;
	for (i = 0; i < producers; i++)
		pthread_create(&threads[i], NULL, producer, NULL);

	for (; i < size; i++)
		pthread_create(&threads[i], NULL, consumer, NULL);

	for (int j = 0; j < size; j++)
		pthread_join(threads[j], NULL);

	return 0;
}
