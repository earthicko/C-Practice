#include <stdio.h>

int main(int argc, char** argv) {
    FILE* fp;
    fp = fopen("a.txt", "w");

    if (fp==NULL){
        printf("Write Error\n");
        return -1;
    }

    fputs("Hello, World!\n", fp);
    fclose(fp);

    return 0;
}