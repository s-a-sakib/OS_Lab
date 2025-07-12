/*
    Write a C program to show how two related processes can
    communicate with each other by an unnamed pipe.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100

int main() {
    int pipe_fd[2]; // File descriptors for the pipe
    char buffer[BUFFER_SIZE];

    // Create the pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork(); // Create a child process

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        sleep(5); // Sleep to ensure parent writes first
        close(pipe_fd[1]); // Close the write end of the pipe
        printf("Hello, this is the child process.\n");
        printf("Child is waiting for a message from the parent process.\n");
        // Read from the pipe
        read(pipe_fd[0], buffer, BUFFER_SIZE);
        printf("Child received: %s\n", buffer);

        close(pipe_fd[0]); // Close the read end of the pipe
    } else {
        // Parent process
        close(pipe_fd[0]); // Close the read end of the pipe
        printf("Hellow This is the parent process.\n");
        printf("Parent is sending a message to the child process.\n");
        // Write to the pipe
        const char *message = "Hello from parent!";
        write(pipe_fd[1], message, strlen(message) + 1);

        close(pipe_fd[1]); // Close the write end of the pipe
        wait(NULL); // Wait for child process to finish
    }

    return 0;
}

