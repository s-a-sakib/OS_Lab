/*
    Write a C program to show how two unrelated processes can communicate 
    with each other by a named pipe.

    Use one process to write to the pipe and another process to read from it.
    The first process should write a message to the pipe, and the second process 
    should read that message and print it to the console.
*/

/*
    This is reader program.
*/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define PIPE_NAME "my_named_pipe"

int main(){
    // Opening the pipe

    int fd = open(PIPE_NAME,O_RDONLY);
    if(fd < 0){
        perror("File openning failed.");
        exit(EXIT_FAILURE);
    }
    char buffer[100];

    printf("This is reader program.\n");
    read(fd, buffer, sizeof(buffer));
    printf("Message: %s\n",buffer);
    close(fd);

    return 0;
}