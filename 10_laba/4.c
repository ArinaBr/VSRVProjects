#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* PrintHello(void* data) {
        pthread_t tid;
        tid = (pthread_t)data;
        sleep(1);
        printf("\n I am thread %u \n", tid);
        printf("\n Hello from new thread %u - got %u\n", pthread_self(), tid);
        pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
        int rc;
        pthread_t thread_id;
        pthread_t tid;
        tid = pthread_self();
        rc = pthread_create(&thread_id, NULL, PrintHello, &tid);

        if(rc) {
                printf("\n ERROR: return code from pthread_create is %d\n", rc);
                exit(1);
        }

        printf("\n Created new thread (%u)... \n", thread_id);
}
