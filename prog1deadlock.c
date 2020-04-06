#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>

pthread_mutex_t  mylock;

int res1 = 0, res2 = 0, res3 = 0;


void *p1(), *p2(), *p3();

void *p1(){
    pthread_mutex_lock(&mylock);
    printf("Resource1 assigned to process P1.\n");
    res1 = 1;
    printf("As an acknownledgement, p1 changed value of res1 from 0 to %d!\n\n", res1);
    p2(); //call to p2 as p2 holds the r2 resource 
    pthread_mutex_unlock(&mylock);
}

void *p2(){
    pthread_mutex_lock(&mylock);
    printf("Resource2 assigned to process P2.\n");
    res2 = 2;
    printf("As an acknownledgement, p2 changed value of res2 from 0 to %d!\n\n", res2);
    res1 = 10; //deadlock detected as p2 tries to change the value of r1
    pthread_mutex_unlock(&mylock);
}


void *p3(){
    pthread_mutex_lock(&mylock);
    printf("Resource3 assigned to process P3.\n");
    res3 = 3;
    printf("As an acknownledgement, p3 changed value of res3 from 0 to %d!\n\n", res3);
    pthread_mutex_unlock(&mylock);
}

int main(){
    //printf("in main\n");
    pthread_mutex_init(&mylock, NULL);
    pthread_t mythread;    

    pthread_create(&mythread, NULL, p1, NULL);
    pthread_join(mythread, NULL);

    pthread_create(&mythread, NULL, p2, NULL);
    pthread_join(mythread, NULL);

    pthread_create(&mythread, NULL, p3, NULL);
    pthread_join(mythread, NULL);

}
