#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int number;

void* generator(void* arg) {
        while (1) {
                pthread_mutex_lock(&mutex);
                number = rand() % 100;
                printf("generated number: %d\n", number);
                pthread_mutex_unlock(&mutex);
                sleep(1);
        }

        return NULL;
}

void* squareNumber(void* arg) {
        while (1) {
                pthread_mutex_lock(&mutex);

                if (number % 2 == 0) {
                        int square = number * number;
                        printf("square of number: %d\n", square);
                }

                pthread_mutex_unlock(&mutex);
                sleep(1);
        }

        return NULL;
}

void* cubeNumber(void* arg) {
        while (1) {
                pthread_mutex_lock(&mutex);

                if (number % 2 == 1) {
                        int cube = number * number * number;
                        printf("cube of number: %d\n", cube);
                }

                pthread_mutex_unlock(&mutex);
                sleep(1);
        }

        return NULL;
}

int main() {
        pthread_t threadNumber, threadSquare, threadCube;

        pthread_create(&threadNumber, NULL, generator, NULL);
        pthread_create(&threadSquare, NULL, squareNumber, NULL);
        pthread_create(&threadCube, NULL, cubeNumber, NULL);

        pthread_join(threadNumber, NULL);
        pthread_join(threadSquare, NULL);
        pthread_join(threadCube, NULL);

        return 0;
}
