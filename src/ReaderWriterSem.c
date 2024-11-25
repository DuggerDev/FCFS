#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

/* This is the code I pulled directly from the book for the problem */
// typedef struct _rwlock_t { 
//     sem_t lock; // binary semaphore (basic lock)
//     sem_t writelock; // allow ONE writer/MANY
//     readers int readers; // #readers in critical section
// } rwlock_t; void

// rwlock_init(rwlock_t *rw) {
//     rw->readers = 0;
//     sem_init(&rw->lock, 0, 1);
//     sem_init(&rw->writelock, 0, 1);
// }

// void rwlock_acquire_readlock(rwlock_t *rw) {
//     sem_wait(&rw->lock); rw->readers++;
//     if (rw->readers == 1) // first reader gets writelock
//     sem_wait(&rw->writelock);
//     sem_post(&rw->lock);
// }

// void rwlock_release_readlock(rwlock_t *rw) {
//     sem_wait(&rw->lock);
//     rw->readers--;
//     if (rw->readers == 0){ // last reader lets it go
//         sem_post(&rw->writelock);
//     }
//     sem_post(&rw->lock);
// }

// void rwlock_acquire_writelock(rwlock_t *rw) {
//     sem_wait(&rw->writelock);
// }

// void rwlock_release_writelock(rwlock_t *rw) {
//     sem_post(&rw->writelock);
// }

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

