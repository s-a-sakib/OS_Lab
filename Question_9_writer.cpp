/*
    Write a C program to show how two unrelated processes can communicate 
    with each other by a named pipe.

    Use one process to write to the pipe and another process to read from it.
    The first process should write a message to the pipe, and the second process 
    should read that message and print it to the console.
*/

/*
    This is writer program.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PIPE_NAME "my_named_pipe"
int main() {
    // Creating a named pipe
    if (mkfifo(PIPE_NAME, 0666) == -1) {
        perror("mkfifo failed");
        exit(EXIT_FAILURE);
    }

    int fd = open(PIPE_NAME,O_WRONLY);
    
    if(fd < 0){
        perror("Open Failed");
        exit(EXIT_FAILURE);
    }

    char message[] = "Hi,This is a message from writer process.";
    write(fd,message,strlen(message) + 1);
    printf("Writer send : %s\n", message);
    close(fd);
    return 0;
}