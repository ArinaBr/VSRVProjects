#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

void error_out(const char *msg) {
        perror(msg);
        exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
        key_t mykey = 12345678;
        const size_t region_size = sysconf(_SC_PAGE_SIZE);
        int smid = shmget(mykey, region_size, IPC_CREAT | 0666);

        if (smid == -1) {
                error_out("shmget");
        }

        void *ptr;
        ptr = shmat(smid, NULL, 0);

        if (ptr == (void *) -1) {
                error_out("shmat");
        }

        pid_t pid = fork();

        if (pid == 0) {
                u_long *d = (u_long *) ptr;
                *d = 0xdeadbeef;
                exit(0);
        }

        else {
                int status;
                waitpid(pid, &status, 0);
                printf("child wrote %#lx\n", *(u_long *) ptr);
        }

        int r = shmdt(ptr);

        if (r == -1) {
                error_out("shmdt");
        }

        r = shmctl(smid, IPC_RMID, NULL);

        if (r == -1) {
                error_out("shmdt");
        }

        return 0;
}
