#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_FOOD 1000
#define MIN_FOOD 100
#define CATS 5
#define CAT_EAT 100

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int bowlFood = MAX_FOOD;

void* owner(void* arg) {
        while (1) {
                pthread_mutex_lock(&mutex);
                bowlFood += MIN_FOOD + rand() % (MAX_FOOD - MIN_FOOD + 1);

                if (bowlFood > MAX_FOOD) {
                        bowlFood = MAX_FOOD;
                }

                printf("Owner added %d grams of food \n", bowlFood);
                pthread_mutex_unlock(&mutex);
                sleep(1);
        }

        return NULL;
}

void* cat(void* arg) {
        int catId = *((int*)arg);

        while (1) {
                pthread_mutex_lock(&mutex);

                if (bowlFood >= CAT_EAT) {
                        bowlFood -= CAT_EAT;
                        printf("Cat %d ate, there were %d grams of food in the bowl \n", catId, bowlFood);
                }

                else {
                        printf("Cat %d is hungry, there is no food in the bowl \n", catId);
                }

                pthread_mutex_unlock(&mutex);
                sleep(1);
        }

        return NULL;
}

int main() {
        pthread_t ownerThread, catThread[CATS];
        int catIds[CATS];
        pthread_create(&ownerThread, NULL, owner, NULL);

        for (int i = 0; i < CATS; ++i) {
                catIds[i] = i + 1;
                pthread_create(&catThread[i], NULL, cat, (void*)&catIds[i]);
        }

        pthread_join(ownerThread, NULL);

        for (int i = 0; i < CATS; ++i) {
                pthread_join(catThread[i], NULL);
        }

        return 0;
}
