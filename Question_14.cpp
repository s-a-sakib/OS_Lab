/*
    Write a C program to show how data inconsistency arises in two related 
    processes (e.g., parent & child processes) when they share a memory space
*/
/*
    gcc Question_14.cpp -o Question_14 -lpthread
    ./Question_14
*/

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

#define FILE_NAME "/_SC_SHARED_MEMORY_OBJECTS"
#define SHM_SIZE sizeof(int)
#define Itaration 100000

int main(){
    // Creating shared memory object
    int shm_id = shm_open(FILE_NAME, O_CREAT | O_RDWR, 0666);

    if(shm_id < 0) {
        printf("Error creating shared memory object\n");
        exit(EXIT_FAILURE);
    }

    // Setting the size of the shared memory object
    int trunk = ftruncate(shm_id, SHM_SIZE);
    if(trunk < 0) {
        printf("Error truncating shared memory object\n");
        exit(EXIT_FAILURE);
    }

    // Mapping the shared memory object
    int *shared_memory = (int *)mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_id, 0);
    if(shared_memory == MAP_FAILED) {
        printf("Error mapping shared memory object\n");
        exit(EXIT_FAILURE);
    }
    *shared_memory = 0; // Initialize shared memory

    // Forking a child process
    pid_t pid = fork();
    if(pid < 0) {
        printf("Error forking process\n");
        exit(EXIT_FAILURE);
    }
    if(pid == 0) { // Child process
        for(int i = 0; i < Itaration; i++) {
            (*shared_memory)++;
        }
        exit(EXIT_SUCCESS);
    } else { // Parent process
        for(int i = 0; i < Itaration; i++) {
            (*shared_memory)++;
        }
        wait(NULL); // Wait for child process to finish
        printf("Final value in shared memory: %d\n", *shared_memory);
        printf("Expected value: %d\n", Itaration * 2);
    }

    // Cleanup
    munmap(shared_memory, SHM_SIZE);
    shm_unlink(FILE_NAME);
    return 0;
}
