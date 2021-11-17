#include <stdio.h>

int main(int argc, char** argv) {
    FILE* fp;
    fp = fopen("./C-bal/23-1/a.txt", "w");

    if (fp == NULL) {  // Write Error -> Return Value 0
        printf("Write Error\n");
        return -1;
    }

    fputs("Hello, World!\n", fp);
    fclose(fp);

    return 0;
}