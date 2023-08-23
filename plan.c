#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define TOTAL_PRODUCTS 150
#define PRODUCT_1_BUFFER 10
#define PRODUCT_2_BUFFER 12

// struct used to keep track of producer items
// what will be passed through the pipe
typedef struct {
    int productType;    // 1 or 2
    int count;          // acts as a seriel number
} ProducerItem;


// buffers (storage areas)
ProducerItem buffer1[PRODUCT_1_BUFFER];
ProducerItem buffer2[PRODUCT_2_BUFFER];

// buffer counts (items in slots)
int buffer1count = 0;
int buffer2count = 0;


// require mutexes
// used in producer1 & producer2 process
// will be product_count_number/seriel number
int producer1_counter = 0;
int producer2_counter = 0;

// used by threads 
// consumer_count_product_1 - (2) consumer threads use to keep track of product1 consumption(removal of product from buffer)
// consumer_count_product_2 - (2) consumer threads use to keep track of product2 consumption(removal of product from buffer)
int consumer_count_product_1 = 0;
int consumer_count_product_2 = 0;


// mutexes
// buffers - when accessing slots, only one thread of the two can consume at a time, also when the ditributor thread is placing the products on respective buffers
// pipe - 1 pipe is shared across 3 process (main/consumer, producer1, producer2)
    // producers - only can write two the pipe BUT ONLY ONE AT A TIME!
pthread_mutex_t buffer1_mutex = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t buffer2_mutex = PTHREAD_MUTEX_INITIALIZER; 


// conidition variables
pthread_cond_t buffer1_not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer2_not_empty = PTHREAD_COND_INITIALIZER;


// process with producers - two procs call producer
void *producer1(void *arg) {
    int i;
    for (i = 0; i < TOTAL_PRODUCTS; i++) {
        Pthread_mutex_lock(&producer1_mutex);
        
        // critical section
            // wait() check if pipe is available
                
                    // create struct
                    // send through pipe
                
        Pthread_mutex_unlock(&producer1_mutex);
    }
}

void *producer2(void *arg) {
    int i;
    for (i = 0; i < TOTAL_PRODUCTS; i++) {
        Pthread_mutex_lock(&producer2_mutex);
        // critical section
            // while (wait() check if pipe is available)
                // lock pipe
                    // create struct
                    // send through pipe
                // unlock pipe
        Pthread_mutex_unlock(&producer2_mutex);
    }
}

void *distributor(void *arg) {
    int i;
    for (i = 0; i < 2*TOTAL_PRODUCTS; i++) {
        // while wait() for pipe to have product - COND
        // lock buffer 1/2 - MUTEX
            // place product
            // buffer1count ++; OR buffer2count++;
            // SIGNAL product_in_buffer available - COND
        // unlock buffer    
    }
}

// two threads will use this to consume product1
void *consumer1(void *arg) {
    int i;
    for (i = 0; i < TOTAL_PRODUCTS; i++) {
        // wait() product1_in_buffer, buffer not empty - COND
        // lock buffer1
            // eat product1
            // log
            // buffer1count--;
        // unlock buffer1
    }
}

// two threads will use this to consume product1
void *consumer2(void *arg) {
    int i;
    for (i = 0; i < TOTAL_PRODUCTS; i++) {
        // wait() product2_in_buffer, buffer not empty - COND
        // lock buffer2
            // eat product2
            // log
            // buffer2count --;
        // unlock buffer2
    }
}

int main(int argc, char *argv[]) {
    // thread 1 (main) - calls distributor

    // create 4 more threads

    int pid;

    if ((pid = fork()) < 0) {
        perror("1st fork failed.\n")
        exit(1);
    }else if(pid == 0) {
        // producer1 stuff;



        exit(0);
        
        int pid2;
        if ((pid2 = fork()) < 0) {
            perror("1st fork failed.\n")
            exit(1);
        }else if(pid2 == 0) {
            // producer2 stuff;



            exit(0);
        }
    }

    // call distributor - main thread
    // call consumer_p1_threads - 2 threads
    // call consumer_p2_threads - 2 threads

    // wait for (4) threads

}



    // // Initialize mutexes
    // pthread_mutex_init(&buffer1_mutex, NULL);
    // pthread_mutex_init(&buffer2_mutex, NULL);

    // // Initialize condition variables
    // pthread_cond_init(&buffer1_empty, NULL);
    // pthread_cond_init(&buffer1_fill, NULL);
    // pthread_cond_init(&buffer2_empty, NULL);
    // pthread_cond_init(&buffer2_fill, NULL);

    // // Destroy mutexes
    // pthread_mutex_destroy(&buffer1_mutex);
    // pthread_mutex_destroy(&buffer2_mutex);

    // // Destroy condition variables
    // pthread_cond_destroy(&buffer1_empty);
    // pthread_cond_destroy(&buffer1_fill);
    // pthread_cond_destroy(&buffer2_empty);
    // pthread_cond_destroy(&buffer2_fill);