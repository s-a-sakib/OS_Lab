/*
    Write a C program to show how two unrelated processes can communicate 
    with each other by a named pipe.

    Use one process to write to the pipe and another process to read from it.
    The first process should write a message to the pipe, and the second process 
    should read that message and print it to the console.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PIPE_NAME "/tmp/my_named_pipe"
int main() {
    // Create a named pipe (FIFO)
    if (mkfifo(PIPE_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // Fork a process
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process: Writer
        int fd = open(PIPE_NAME, O_WRONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        
        const char *message = "Hello from the writer process!";
        write(fd, message, strlen(message) + 1); // +1 for null terminator
        close(fd);
    } else { // Parent process: Reader
        int fd = open(PIPE_NAME, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        
        char buffer[100];
        read(fd, buffer, sizeof(buffer));
        printf("Received message: %s\n", buffer);
        close(fd);

        // Optionally remove the named pipe
        unlink(PIPE_NAME);
    }

    return 0;
}