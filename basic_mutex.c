#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N_TIMES 150

int x = 0;

// mutex for touching x
pthread_mutex_t mutex;

void *optimist(void *arg) {
    int i;
    for (i =0; i < N_TIMES; i++) {
        pthread_mutex_lock(&mutex);
        //critical section
        x++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *pessimist(void *arg) {
    int i;
    for (i = 0; i < N_TIMES; i++) {
        pthread_mutex_lock(&mutex);
        // critical section
        x--;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char *argv[]) {

    // create addresses for threads
    pthread_t incT;    
    pthread_t decT;    

    pthread_create(&incT, NULL, optimist, NULL);
    pthread_create(&decT, NULL, pessimist, NULL);

    pthread_join(incT, NULL);
    pthread_join(decT, NULL);

    printf("done. x=%d\n", x);

    return 0;
}