/*
Write a multithreaded program that calculates various statistical values for a 
list of numbers. This program will be passed a series of numbers on the 
command line and will then create three separate worker threads. One thread 
will determine the average of the numbers, the second will determine the 
maximum value, and the third will determine the minimum value. For 
example, suppose your program is passed the integers 
90 81 78 95 79 72 85 
    The program will report 
    A.  The average value is 82 
    B.  The minimum value is 72 
    C.  The maximum value is 95 
The variables representing the average, minimum, and maximum values will 
be stored globally. The worker threads will set these values, and the parent 
thread will output the values once the workers have exited.
*/

/*
    gcc Question_20.c -o Question_20 -pthread
    ./Question_20 90 81 78 95 79 72 85
*/
#include <pthread.h>
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

int numCount;
float ave;
int minVal;
int maxVal;
int* numArray;

void *average(void *arg){
    int sum = 0;
    for(int i = 0; i < numCount; i++){
        sum += numArray[i];
    }
    ave = (float) (sum / numCount);

    printf("The average value is %.2f \n", ave);
    pthread_exit(NULL);
}

void *minimum(void *arg){
    printf("The minimum value is %d\n", numArray[0]);
    pthread_exit(NULL);
}

void *maximum(void *arg){
    printf("The maximum value is %d\n", numArray[numCount - 1]);
    pthread_exit(NULL);
}

int main(int args, char* argv[]){
    if(args < 2){
        printf("Number of element should be at least 2");
        return 1;
    }

    numCount = args - 1;
    numArray = (int *) malloc(sizeof(int) * numCount);

    for(int i = 0; i < numCount; i++)
        numArray[i] = atoi(argv[i + 1]);

    sort(numArray, numArray + numCount);
    
    // Creating Threads

    pthread_t thread1, thread2, thread3;
    pthread_create(&thread1, NULL, average, NULL);
    pthread_create(&thread2, NULL, minimum, NULL);
    pthread_create(&thread3, NULL, maximum, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    free(numArray);
    printf("\n");

    return 0;
}