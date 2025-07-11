#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5
#define NUM_INCREMENTS 100000

int counter = 0;  // Shared resource among threads

// Function executed by threads
void* increment_counter(void* arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        counter++;  // Unsynchronized access, causes race condition
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Create multiple threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, increment_counter, NULL) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Expected counter value: NUM_THREADS * NUM_INCREMENTS
    printf("Final counter value: %d (Expected: %d)\n", counter, NUM_THREADS * NUM_INCREMENTS);

    return 0;
}
