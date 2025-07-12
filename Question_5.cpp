/*
Write a C program to create a main process named ‘parent_process’ having 
‘n’ child processes without any grandchildren processes. Child Processes’ 
names are child_1, child_2, child_3,......., child_n. Trace the position in the 
process tree. Number of child processes (n) and name of child processes will 
be given in the CLI of Linux based systems.  
 
Example: 
$ ./parent_process 3 child_1 child_2 child_3
    pstree -p Parent_Process_PID
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <number_of_children> <child_name_1> <child_name_2> ...\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]); // Number of child processes to create
    if (n <= 0 || n + 2 != argc) { // Check if n is valid and matches the number of child names provided
        fprintf(stderr, "Please provide a valid number of child processes and their names.\n");
        return 1;
    }

    printf("Parent Process: %d has created %d child processes.\n", getpid(), n);

    pid_t pids[n];

    for (int i = 0; i < n; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pids[i] == 0) {
            // Child process
            prctl(PR_SET_NAME, argv[i + 2], 0, 0, 0); // Set child process name
            printf("Child Process: %s with PID: %d\n", argv[i + 2], getpid());
            sleep(10); // Simulate some work or keep the process alive for tracing
            exit(0);
        }
    }

    // Parent process waits for all children to finish
    for (int i = 0; i < n; i++) {
        waitpid(pids[i], NULL, 0);
    }
    return 0;
}