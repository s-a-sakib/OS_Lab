/*
    Write a C program to create an orphan process.
*/ 

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    pid_t pid;
    pid = fork(); // Create a new process

    if(pid == 0){ // Child process
        printf("Child process (PID: %d) created. Parent PID: %d\n", getpid(), getppid());
        sleep(5);
        printf("Child process (PID: %d) is now an orphan process.\n", getpid());
        printf("Now the parent of this orphan process is: %d\n", getppid());
    }else if(pid > 1){ // Parent process
        printf("Parent process (PID: %d) created child with PID: %d\n", getpid(), pid);
        sleep(2); // Allow child to run first
    }
}