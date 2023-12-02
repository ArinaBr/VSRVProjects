#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void) {
        int filedesc;
        char str[50];
        filedesc = open("test.txt", O_CREAT | O_RDWR | O_TRUNC);
        printf("Enter the text: \n");
        gets(str);
        write(filedesc, str, 6);
        dup2(filedesc, 1);
        printf("The entered text is redirected to a file \n");
}
