#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_RESOURCES 3  // Max number of simultaneous accesses allowed
#define NUM_THREADS 5

sem_t counter_semaphore;

void* task(void* arg) {
    int thread_id = *((int*)arg);

    printf("Thread %d waiting to enter critical section...\n", thread_id);

    sem_wait(&counter_semaphore);  // Decrement semaphore, wait if 0

    printf("Thread %d entered critical section.\n", thread_id);
    sleep(2);  // Simulate work in critical section
    printf("Thread %d leaving critical section.\n", thread_id);

    sem_post(&counter_semaphore);  // Increment semaphore, signal others

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize semaphore with value MAX_RESOURCES
    sem_init(&counter_semaphore, 0, MAX_RESOURCES);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, task, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&counter_semaphore);

    return 0;
}
