#include <stdio.h>

int main() {
    FILE* fp = fopen("./C-bal/23-1/a.txt", "r");
    char c;

    while ((c = fgetc(fp)) != EOF) {  // End of file is always -1 (== EOF)
        printf("%c", c);
    }
    fclose(fp);

    return 0;
}