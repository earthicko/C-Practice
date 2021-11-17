#include <stdio.h>

int main(int argc, char** argv) {
    FILE* fp = fopen("./C-bal/23-1/b.txt", "w");

    fputs("DHL is an excellent C programmer?\n", fp);
    fseek(fp, 0, SEEK_SET);
    fputs("Is DHL", fp);
    fclose(fp);

    return 0;
}