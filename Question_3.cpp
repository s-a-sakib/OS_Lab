/*
    Write a C program to create a zombie process

    Q. What is a zombie process?
    A. A zombie process is a process that has completed execution but still has an entry in the process table. 
    This occurs when the parent process has not yet read the exit status of the child process, allowing the 
    child to remain in a "zombie" state until it is cleaned up by the parent or the system.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        // Parent process
        printf("Parent Process, PID: %d\n", getpid());
        printf("Child Process created with PID: %d\n", pid);
        
        // Sleep to keep parent alive so child becomes zombie after exit
        sleep(30);

        printf("Parent exiting...\n");

    } else if (pid == 0) {
        // Child process
        printf("Child Process (will exit to become zombie), PID: %d\n", getpid());
        exit(0);

    } else {
        // Fork failed
        perror("fork");
    }

    return 0;
}
