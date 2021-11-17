#include <stdio.h>

int main() {
    char file_loc[100];
    printf("Location of file: ");
    scanf("%s", file_loc);
    FILE* fp = fopen(file_loc, "w");
    if (fp == NULL) printf("Error while reading file %s\n", file_loc);
    fputc('a', fp);
    fclose(fp);
    return 0;
}