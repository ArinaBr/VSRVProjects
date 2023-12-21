#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* PrintHello(void* data) {
        int my_data = (int)(size_t)data;
        printf("\n Hello from new thread - got %d\n", my_data);
        pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
        int rc;
        pthread_t thread_id;
        int t = 11;
        rc = pthread_create(&thread_id, NULL, PrintHello, (void*)(size_t)t);

        if(rc) {
                printf("\n ERROR: return code from pthread_create is %d\n", rc);
                exit(1);
        }

        printf("\n Created new thread (%u)... \n", thread_id);
        pthread_exit(NULL);
}
