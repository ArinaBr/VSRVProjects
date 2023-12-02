#include <stdio.h>

void main() {
        printf("Enter the text: \n");
        char text[50];
        gets(text);
        printf("The entered text: \n%s\n", text);
        return;
}
