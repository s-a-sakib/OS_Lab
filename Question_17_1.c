#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>

int x = 0;
pthread_mutex_t key;
void *addition(){
    for(int i = 0; i < 10; i++){
        int processor_no = sched_getcpu();
        pthread_mutex_lock(&key);
        printf("Addition Thread %d\n" , i);
        x++;
        printf("Addition Processor: %d  x: %d\n",processor_no , x);
        pthread_mutex_unlock(&key);
    }
    return NULL;
}

void *subtraction(){
    for(int i = 0; i < 100; i++){
        int processor_no = sched_getcpu();
        pthread_mutex_lock(&key);
        printf("Subtraction Thread %d\n" , i);
        x--;
        printf("Subtraction Processor: %d  x: %d\n",processor_no , x);
        pthread_mutex_unlock(&key);
    }
    return NULL;
}

void values(){
      printf("x:  %d \n", x);
}

void main(){
    pthread_t tid1,tid2;
    
    pthread_mutex_init(&key, NULL);  // Initialize mutex
    
    pthread_create(&tid1, NULL , &addition , NULL);
    pthread_create(&tid2, NULL , &subtraction , NULL);
    
    // for(int i = 0; i < 10; i++){
        int processor_no = sched_getcpu();
        printf("Main Processor: %d \n",processor_no); 
    //}
    
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    
    pthread_mutex_destroy(&key);  // Destroy mutex
}
