#include <stdio.h>
#include <signal.h>

main() {
        void(*handler)();

        printf("I can be stopped with <ctr> + <c> \n");
        sleep(5);
        handler = signal(SIGINT, SIG_IGN);
        printf("I am now protected from <ctr> + <c> \n");
        sleep(5);
        signal(SIGINT, handler);
        printf("I can be stopped again with <ctr> + <c> \n");
        sleep(5);
        printf("Goodbye \n");
}
