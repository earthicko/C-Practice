#include <stdio.h>

char flip_case(char input);

int main() {
    FILE* fp = fopen("./C-bal/23-1/search_target.txt", "r+");
    char c;

    if (fp == NULL) {
        printf("Error while reading file\n");
        return -1;
    }

    while ((c = fgetc(fp)) != EOF) {
        char flipped = flip_case(c);
        fseek(fp, -1, SEEK_CUR);
        fputc(flipped, fp);
        fseek(fp, 0, SEEK_CUR);
    }
    return 0;
}

char flip_case(char input) {
    if (65 <= input && input < 91)
        return input + 32;
    else if (97 <= input && input < 123)
        return input - 32;
    else
        return input;
}