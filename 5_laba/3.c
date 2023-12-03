#include <stdio.h>
#include <stdlib.h>

void amount(int array[], int size, int *sum1, int *sum2, int *sum3) {
        *sum1 = 0;
        *sum2 = 0;
        *sum3 = 0;

        for(int i = 0; i < size; i++) {
                int index1 = 3 * i;
                if(index1 >= size) {
                        break;
                }
                *sum1 += array[index1];
                int index2 = index1 + 1;
                if(index2 >= size) {
                        break;
                }
                *sum2 += array[index2];
                int index3 = index1 + 2;
                if(index3 >= size) {
                        break;
                }
                *sum3 += array[index3];
        }

}

int main() {
        int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        int size = 10;
        void (*function)(int*, int, int*, int*, int*);
        function = amount;
        int amount1 = 0;
        int amount2 = 0;
        int amount3 = 0;
        function(arr, size, &amount1, &amount2, &amount3);
        printf("Amount 1: %d, Amount 2: %d, Amount 3: %d \n", amount1, amount2, amount3);
        return 0;
}
