#include <stdio.h>

int main(int argc, char** argv) {
    FILE* fp = fopen("./C-bal/23-1/a.txt", "r");

    fgetc(fp);
    fgetc(fp);
    fgetc(fp);
    fgetc(fp);

    fseek(fp, 0, SEEK_SET);
    printf("If we read from the very first char: %c\n", fgetc(fp));
    fclose(fp);
    return 0;
}