/*
    Write a C program to create a main process named ‘parent_process’ having 3 
    child processes without any grandchildren processes. Child Processes’ 
    names are child_1, child_2, child_3. Trace the position in the process tree
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <string.h>


int main() {
    pid_t pid1, pid2, pid3;

    //prctl(PR_SET_NAME, "parent_process", 0, 0, 0);
    printf("Parent Process: parent_process, PID: %d\n", getpid());

    pid1 = fork();
    if (pid1 == 0) {
        // Child 1
        prctl(PR_SET_NAME, "Child_1", 0, 0, 0);
        printf("Child Process: child_1, PID: %d, Parent PID: %d\n", getpid(), getppid());
        sleep(30); // Keeps process alive for tracing
        exit(0);
    }

    pid2 = fork();
    if (pid2 == 0) {
        // Child 2
        prctl(PR_SET_NAME, "Child_2", 0, 0, 0);
        printf("Child Process: child_2, PID: %d, Parent PID: %d\n", getpid(), getppid());
        sleep(30);
        exit(0);
    }

    pid3 = fork();
    if (pid3 == 0) {
        // Child 3
        prctl(PR_SET_NAME, "Child_3", 0, 0, 0);
        printf("Child Process: child_3, PID: %d, Parent PID: %d\n", getpid(), getppid());
        sleep(30);
        exit(0);
    }

    // Parent waits for all children
    sleep(30);  // Keeps parent alive for tracing
    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("Parent Process exiting: PID: %d\n", getpid());
    return 0;
}
/*
    Compile the code using:
    gcc Question_4.cpp -o Question_4

    Run the program using:
    ./Question_4

    You can use the `ps` command to trace the process tree:
    pstree -p Parent_Process_PID
*/