#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* PrintHello(void* thread_id) {
        long tid = (long)thread_id;
        printf("Hello from thread %u - I was created in iteration %u\n", tid, tid-5);
        pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
        if(argc != 2) {
                printf("USAGE: <number of threads> \n");
                return 1;
        }

        int number_threads = atoi(argv[1]);
        pthread_t threads[number_threads];
        int rc;
        long t;

        for(t = 5; t < number_threads + 5; t++) {
                printf("I am thread 1. Created new thread (%u) in iteration %u...\n", t, t-5);
                rc = pthread_create(&threads[t], NULL, PrintHello, (void*)t);

                if(rc) {
                        printf("ERROR: return code from pthread_create is %d\n", rc);
                        return -1;
                }

                if(t % 5 == 0 || t % 4 == 0) {
                        sleep(1);
                }

        }

        pthread_exit(NULL);
}
