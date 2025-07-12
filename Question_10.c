/*
    Write a C program to show how two related processes can
    communicate with each other by a named pipe. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 100

int main() {
    int fd;
    char *fifo_path = "my_fifo";
    char buffer[BUFFER_SIZE];

    // Create the named pipe (FIFO)
    mkfifo(fifo_path, 0666);

    // Fork a child process
    if (fork() == 0) {
        // Child process: write to the FIFO
        fd = open(fifo_path, O_WRONLY);
        const char *message = "Hello from child process!";
        write(fd, message, strlen(message) + 1);
        close(fd);
        exit(0);
    } else {
        // Parent process: read from the FIFO
        fd = open(fifo_path, O_RDONLY);
        read(fd, buffer, BUFFER_SIZE);
        printf("Received from child: %s\n", buffer);
        close(fd);

        // Clean up: remove the FIFO
        unlink(fifo_path);
    }

    return 0;
}