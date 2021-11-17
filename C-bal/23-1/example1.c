#include <stdio.h>

int main() {
    FILE* fp = fopen("./C-bal/23-1/a.txt", "r");
    char buf[20];
    if (fp == NULL) {  // Read Error -> Return Value 0
        printf("Read Error\n");
        return -1;
    }
    fgets(buf, 20, fp);
    printf("Input data: %s\n", buf);
    fclose(fp);
    return 0;
}