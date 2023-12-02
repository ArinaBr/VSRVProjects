#include <stdio.h>
#include <unistd.h>

int main() {
        printf("I'm process of main program %d and I'm about to exec an ls -l \n", getpid());
        int pid;
        pid = fork();
        if(pid != 0) {
                printf("I'm the parent process with pid %d \n", getpid());
                printf("My child's pid is %d \n", pid);
        }
        else {
                printf("I'm the child process with pid %d \n", getpid());
                execl("/bin/ls", "ls", "-l", NULL);
        }
        wait();
        printf("The child process is dead \n");
        printf("This is line should be executed after child's death \n");
        return 0;
}
