/*
    Write a C program to analyze the effect of local and global variables on a 
    parent process and a child process.

    The program should create a child process using fork() and demonstrate how 
    changes to local and global variables in the parent process do not affect 
    the child process, and vice versa.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int global_var = 10; // Global variable

void child_process() {
    int local_var = 20; // Local variable in child process
    global_var += 5; // Modify global variable in child process
    local_var += 5; // Modify local variable in child process

    printf("Child Process:\n");
    printf("Global Variable: %d\n", global_var);
    printf("Local Variable: %d\n", local_var);
}

void parent_process() {
    int local_var = 30; // Local variable in parent process
    global_var += 10; // Modify global variable in parent process
    local_var += 10; // Modify local variable in parent process

    printf("Parent Process:\n");
    printf("Global Variable: %d\n", global_var);
    printf("Local Variable: %d\n", local_var);
}
int main() {
    pid_t pid = fork(); // Create a child process

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        child_process();
    } else {
        // Parent process
        parent_process();
        wait(NULL); // Wait for child process to finish
    }

    return 0;
}