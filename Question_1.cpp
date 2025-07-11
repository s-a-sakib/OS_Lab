/*
Write a C program to create a main process named ‘parent_process’ having 3 
child processes without any grandchildren processes.  
 
Trace parent and child processes in the process tree.   
 
Show that child processes are doing addition, subtraction and multiplication 
on two variables initialized in the parent_process 
*/ 

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int addition(int a , int b){
    return a + b;
}

int subtraction(int a, int b){
    return abs(a - b);
}

int multiplication(int a, int b){
    return a * b;
}

int main(){
    int a = 10, b = 5;
    pid_t pid_1, pid_2, pid_3;
    pid_1 = fork(); 

    if(pid_1 == 0){ // if pid_1 == 0, then it is the 1st child-process

        int ans = addition(a , b);
        printf("Child_1 ID: %d ; Parent ID: %d \n", getpid(), getppid());
        printf("Child 1 (Addition): %d + %d = %d\n", a, b, ans);
        sleep(20);
    }else if(pid_1 > 0){ // Parent process
        
        pid_2 = fork(); 

        if(pid_2 == 0){ // if pid_2 == 0, then it is the 2nd child-process

            int ans = subtraction(a , b);
            printf("Child_2 ID: %d ; Parent ID: %d \n", getpid(), getppid());
            printf("Child 2 (Subtraction): %d - %d = %d\n", a, b, ans);
            sleep(20);
        }else if(pid_2 > 0){ // Parent process
            pid_3 = fork();

            if(pid_3 == 0){ // if pid_3 == 0, then it is the 3rd child-process

                int ans = multiplication(a , b);
                printf("Child_3 ID: %d ; Parent ID: %d \n", getpid(), getppid());
                printf("Child 3 (Multiplication): %d * %d = %d\n", a, b, ans);
                sleep(20);
            }else if(pid_3 > 0){ // Parent process
                // Wait for all child processes to finish
                wait(NULL);
                wait(NULL);
                wait(NULL);
                printf("Parent process completed.\n");
                sleep(20);
            }
        }
    }
}


