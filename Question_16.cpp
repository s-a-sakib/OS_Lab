/*
    Write a C program to handle racing situations in a multi-threaded process. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;

#define Iterations 1000000
int counter = 0;

void *increment_counter(void *arg) {
    for (int i = 0; i < Iterations; i++) {
        pthread_mutex_lock(&lock);
        counter++;  // Critical section
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(){
    pthread_t thread_1, thread_2;

    // Initialize mutex
    if(pthread_mutex_init(&lock, NULL) < 0) {
        perror("Mutex initialization failed");
        exit(EXIT_FAILURE);
    }

    // Create threads
    pthread_create(&thread_1, NULL, increment_counter, NULL);
    pthread_create(&thread_2, NULL, increment_counter, NULL);
    
    // Wait for threads to finish
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    // Print final counter value
    printf("Final counter value: %d\n", counter);

    // Cleanup
    pthread_mutex_destroy(&lock);
    return 0;
}
