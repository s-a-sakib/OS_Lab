/*
    Write a C program to show how data inconsistency arises in two unrelated 
    processes when they share a memory space.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include "shared.h"

int main() {
    int shm_fd;
    int *counter;

    // Create shared memory (or open if exists)
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // Set size
    ftruncate(shm_fd, SHM_SIZE);

    // Map memory
    counter = (int *) mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (counter == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Initialize counter if needed
    *counter = 0;

    // Increment shared counter
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        (*counter)++;  // Not atomic — causes data inconsistency
    }

    // Cleanup
    munmap(counter, SHM_SIZE);
    close(shm_fd);

    return 0;
}
