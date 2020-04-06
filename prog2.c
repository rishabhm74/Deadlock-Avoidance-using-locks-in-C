#include <stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include <pthread.h>
#include <semaphore.h>


pthread_mutex_t mylock;
int count = 1;
int readernumber = 0;
sem_t wrt;


void *writer(void *writernum)
{   
    sem_wait(&wrt);
    count = count*2;
    printf("Writer %d modified count to %d\n",(*((int *)writernum)),count);
    sem_post(&wrt);

}
void *reader(void *readernum)
{   
    pthread_mutex_lock(&mylock);
    readernumber++;
    if(readernumber == 1) {
        sem_wait(&wrt); 
    }
    pthread_mutex_unlock(&mylock);
    printf("Reader %d: read count as %d\n",*((int *)readernum),count);
    pthread_mutex_lock(&mylock);
    readernumber--;
    if(readernumber == 0) {
        sem_post(&wrt); 
    }
    pthread_mutex_unlock(&mylock);
}

int main(){   
    pthread_t read[10],write[5];
    pthread_mutex_init(&mylock, NULL);
    sem_init(&wrt,0,1);

    int arr[10] = {1,2,3,4,5,6,7,8,9,10};

    for(int i = 0; i < 10; i++) {
        pthread_create(&read[i], NULL, (void *)reader, (void *)&arr[i]);
    }
    for(int i = 0; i < 5; i++) {
        pthread_create(&write[i], NULL, (void *)writer, (void *)&arr[i]);
    }

    for(int i = 0; i < 10; i++) {
        pthread_join(read[i], NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(write[i], NULL);
    }

    pthread_mutex_destroy(&mylock);
    sem_destroy(&wrt);
}

