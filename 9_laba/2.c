#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
        int shmid;
        char *shmbuf;

        if(argc != 2) {
                puts("USAGE: atshm <identifier>");
                exit(EXIT_FAILURE);
        }

        shmid = atoi(argv[1]);

        if((shmbuf = shmat(shmid, 0, 0)) < (char *)0) {
                perror("shmat");
                exit(EXIT_FAILURE);
        }

        printf("segment attached at %p\n", shmbuf);
        system("ipcs -m");

        if((shmdt(shmbuf)) < 0) {
                perror("shmdt");
                exit(EXIT_FAILURE);
        }

        puts("segment detached \n");
        system("ipcs -m");
        exit(EXIT_SUCCESS);
}
