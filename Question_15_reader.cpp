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

    // Open existing shared memory
    shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // Map memory
    counter = (int *)mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (counter == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Increment shared counter
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        (*counter)++;  // Not atomic
    }

    // Print final counter
    printf("Final counter value: %d\n", *counter);

    // Cleanup
    munmap(counter, SHM_SIZE);
    close(shm_fd);
    shm_unlink(SHM_NAME);  // Remove shared memory

    return 0;
}
