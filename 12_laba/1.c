#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_MESSAGE 100

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int message[MAX_MESSAGE];
int count = 0;

void* producer(void* arg) {
        while (1) {
                int newMessage = rand() % MAX_MESSAGE;
                pthread_mutex_lock( &mutex );
                message[count++] = newMessage;
                printf("produced message: %d\n", newMessage);
                pthread_mutex_unlock( &mutex );
                sleep(1);
        }
        return NULL;
}

void* consumer(void* arg) {
        while (1) {
                pthread_mutex_lock( &mutex );

                if (count > 0) {
                        int consumedMessage = message[--count];
                        printf("consumed task: %d\n", consumedMessage);
                }

                pthread_mutex_unlock( &mutex );
                sleep(1);
        }
        return NULL;
}

int main() {
        pthread_t producerThread, consumerThread;
        pthread_create(&producerThread, NULL, producer, NULL);
        pthread_create(&consumerThread, NULL, consumer, NULL);
        pthread_join(producerThread, NULL);
        pthread_join(consumerThread, NULL);
        return 0;
}
