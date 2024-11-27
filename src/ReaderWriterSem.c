#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

/* This is the code I pulled directly from the book for the problem */
typedef struct _rwlock_t { 
    sem_t lock; // binary semaphore (basic lock)
    sem_t writelock; // allow ONE writer/MANY readers
    int readers; // #readers in critical section
} rwlock_t;

typedef struct _threadArgs_t {
    int id;
    rwlock_t *rwlock;
} threadArgs_t;


rwlock_init(rwlock_t *rw) {
    rw->readers = 0;
    sem_init(&rw->lock, 0, 1);
    sem_init(&rw->writelock, 0, 1);
}


void rwlock_acquire_readlock(rwlock_t *rw) {
    sem_wait(&rw->lock); rw->readers++;
    if (rw->readers == 1){ // first reader gets writelock
        sem_wait(&rw->writelock);
    }
    sem_post(&rw->lock);
}

void rwlock_release_readlock(rwlock_t *rw) {
    sem_wait(&rw->lock);
    rw->readers--;
    if (rw->readers == 0){ // last reader lets it go
        sem_post(&rw->writelock);
    }
    sem_post(&rw->lock);
}

void rwlock_acquire_writelock(rwlock_t *rw) {
    sem_wait(&rw->writelock);
}

void rwlock_release_writelock(rwlock_t *rw) {
    sem_post(&rw->writelock);
}

// This is what all the threads are going to be running
void* opperateWriter(void* args){
    threadArgs_t *threadArgs = (threadArgs_t *)args;
    rwlock_acquire_writelock(threadArgs->rwlock);
    printf("Writer %d starts writing\n", threadArgs->id);
    sleep(1);
    printf("Writer %d ends writing\n", threadArgs->id);
    rwlock_release_writelock(threadArgs->rwlock);
}

void* opperateReader(void* args){
    //from the args assign it to type threadArgs
    threadArgs_t *threadArgs = (threadArgs_t *)args;
    rwlock_acquire_readlock(threadArgs->rwlock);
    printf("Reader %d starts reading\n", threadArgs->id);
    sleep(1);
    printf("Reader %d ends reading\n", threadArgs->id);
    rwlock_release_readlock(threadArgs->rwlock);
}

int main(char argc, char *argv[]){
    //initialize some variables for the current thread for output and then up to 10 threads
    int currentThread = 0;
    //we need 10 threads
    pthread_t threads[10];
    //then get our array of threadArgs
    threadArgs_t *threadArgs[10];
    //then initialize our lock object
    rwlock_t rwlock;
    rwlock_init(&rwlock);

    //ensure we have 10 arguments for our 0 and 1s
    if(argc != 11){
        return 1;
    } else {
        //loop through the arguments and create the threads

        for(int i = 0; i < 10; i++){
            //increment the current thread, we start at 0
            //now that weve incremented, assign the currentThread and rwlock to the threadArgs
            //initialize the threadArgs
            threadArgs[i] = malloc(sizeof(threadArgs_t)); //pain in the ass, apparently we have to do this
            threadArgs[i]->id = i + 1; //tried doing i++ but that didnt work
            threadArgs[i]->rwlock = &rwlock;

            //if the argument is 0, create a reader thread (there are 4 parameters to pthread, according to stackoverflow the second parameter can be null pretty safely)
            if(atoi(argv[i + 1]) == 0){
                pthread_create(&threads[i], NULL, opperateReader, threadArgs[i]); //https://stackoverflow.com/questions/71348098/seg-fault-when-using-pthread-create apparently we cant just call some function, we have to pass it args
            } else {
                //if the argument is 1, create a writer thread
                pthread_create(&threads[i], NULL, opperateWriter, threadArgs[i]);
            }
        }
    }

    //now that we have all the threads, apparently we need to join them, because it waits for the threads to finish and then does some cleanup
    for (int i = 0; i < 10; i++){
        pthread_join(threads[i], NULL);
        //free(threadArgs[i]); //maybe trying freeing it im not sure
    }

    //now that they are all joined up, get out of dodge
    return 0;
    
    //INSTRUCTION
    //accepts 10 arguments from the command line denoted as b1, b2, b3, b4, b5, b6, b7, b8, b9, b10

    //is either 0 or 1, o is reader, 1 is writer

    //after accepting 10 args, create 10 reader and writer threads and start them in the specified order

    //threads run concurrently

    //each thread both reader and writer performs one operation

    //read or write opperations are simulated by making the thread sleep for 1

    //message is printed when finished EX: "Reader 1 starts reading" - "Reader 1 ends reading"

    //use pthreads to create threads and sleep system
}

