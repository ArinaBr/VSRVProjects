#include <stdio.h>
#include <stdlib.h>

int main() {
        int N;
        printf("Enter N: \n");
        scanf("%d", &N);
        int *ptr = (int*) calloc(N, sizeof(int));

        for(int i = 0; i < N; i++) {
                ptr[i] = (i << 5) / 2;
        }

        for(int i = 0; i < N; i++) {
                printf("Number: %3d, Address: %p \n", ptr[i], &ptr[i]);
        }

        free(ptr);
        return 0;
}
