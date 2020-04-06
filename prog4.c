#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>


pthread_mutex_t mylock;
int transferAmt;
int balanceAcc1 = 1000, balanceAcc2 = 1000;

void *transferFunction12(){
    pthread_mutex_lock(&mylock);
    
    while(1 > 0){
        printf("\nEnter amount to tranfer: ");
        scanf("%d", &transferAmt);

        if(transferAmt >= balanceAcc1 || transferAmt < 0 || transferAmt >= 900 || transferAmt < 100){
            printf("Please enter valid amount!\n");
            
        }
        else{
            balanceAcc1 -= transferAmt;
            balanceAcc2 += transferAmt;
            break;
        }
    }

    printf("Transaction successfull!\n");
    pthread_mutex_unlock(&mylock);
}

void *transferFunction21(){
    pthread_mutex_lock(&mylock);
    
    while(1 > 0){
        printf("\nEnter amount to tranfer: ");
        scanf("%d", &transferAmt);

        if(transferAmt >= balanceAcc1 || transferAmt < 0 || transferAmt >= 900 || transferAmt < 100){
            printf("Please enter valid amount!\n");
            
        }
        else{
            balanceAcc2 -= transferAmt;
            balanceAcc1 += transferAmt;
            break;
        }
    }

    printf("Transaction successfull!\n");
    pthread_mutex_unlock(&mylock);
}



int main(){
    pthread_t mythread;
    pthread_mutex_init(&mylock, NULL);

    printf("Current balance\n");
    printf("Balance in account1: Rs %d/-\n", balanceAcc1);
    printf("Balance in account2: Rs %d/-\n", balanceAcc2);

    int choice;
    

    while(1 > 0){
        printf("\nChoose the account to transfer money from: ");
        scanf("%d", &choice);
        if(choice == 1){
            pthread_create(&mythread, NULL, transferFunction12, NULL);
            pthread_join(mythread, NULL);
            break;
        }
        else if(choice == 2){
            pthread_create(&mythread, NULL, transferFunction21, NULL);
            pthread_join(mythread, NULL);
            break;
        }
        else{
            printf("Please enter valid choice!\n");
        }
    }

    
    

    printf("\nCurrent balance\n");
    printf("Balance in account1: Rs %d/-\n", balanceAcc1);
    printf("Balance in account2: Rs %d/-\n", balanceAcc2);


    
}

