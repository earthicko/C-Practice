#include <stdio.h>

int main() {
    FILE* fp = fopen("./C-bal/23-1/a.txt", "r");
    int size = 0;

    while (fgetc(fp) != EOF) size++;

    printf("File size: %d bytes\n", size);
    fclose(fp);
    return 0;
}