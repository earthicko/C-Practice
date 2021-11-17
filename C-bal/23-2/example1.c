#include <stdio.h>
#include <string.h>

int main() {
    FILE* fp = fopen("./C-bal/23-2/this_and_that.txt", "r+");

    char data[100];

    if (fp == NULL) {
        printf("Error while opening file\n");
        return -1;
    }

    while (fscanf(fp, "%s", data) != EOF) {
        if (strcmp(data, "this") == 0) {
            fseek(fp, -(long)strlen("this"), SEEK_CUR);
            fputs("that", fp);
            fflush(fp);
        }
    }
    fclose(fp);

    return 0;
}