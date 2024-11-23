#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int main(){
    //accepts 10 arguments from the command line denoted as b1, b2, b3, b4, b5, b6, b7, b8, b9, b10

    //is either 0 or 1, o is reader, 1 is writer

    //after accepting 10 args, create 10 reader and writer threads and start them in the specified order

    //threads run concurrently

    //each thread both reader and writer performs one operation

    //read or write opperations are simulated by making the thread sleep for 1

    //message is printed when finished EX: "Reader 1 starts reading" - "Reader 1 ends reading"

    //use pthreads to create threads and sleep system
}

