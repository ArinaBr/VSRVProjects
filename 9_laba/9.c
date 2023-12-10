#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct message {
        long int mtype;
        char mtext[128];
};

int send_msg(int qid, int mtype, const char text[]) {
        struct message msg = {
                .mtype = mtype
        };

        strncpy(msg.mtext, text, sizeof(msg.mtext));
        int r = msgsnd(qid, &msg, sizeof(msg), 0);

        if (r == -1) {
                perror("msgsnd");
        }

        return r;
}

int recv_msg(int qid, int mtype, struct message *msg) {
        int r = msgrcv(qid, msg, sizeof(struct message), mtype, 0);

        switch (r) {
                case sizeof(struct message):
                        break;
                case -1:
                        perror("msgrcv");
                        break;
                default:
                        printf("only received %d bytes \n", r);
        }

        return r;
}

void producer(int mqid) {
        send_msg(mqid, 1, "type 1 - first");
        send_msg(mqid, 2, "type 2 - second");
        send_msg(mqid, 1, "type 1 - third");
}

void consumer(int qid) {
        struct message msg;
        int r;
        int i;

        for (i = 0; i < 3; i++) {
                r = msgrcv(qid, &msg, sizeof(struct message), -2, 0);
                printf("%s\n", msg.mtext);
        }

}

int main(int argc, char *argv[]) {
        int mqid;
        mqid = msgget(IPC_PRIVATE, S_IREAD | S_IWRITE);

        if (mqid == -1) {
                perror("msgget");
                exit(1);
        }

        pid_t pid = fork();

        if (pid == 0) {
                consumer(mqid);
                exit(0);
        }

        else {
                int status;
                producer(mqid);
                wait(&status);
        }

        int r = msgctl(mqid, IPC_RMID, 0);

        if (r) {
                perror("msgctl");
        }

        return 0;
}
