#include <stdio.h>

int find_string_from(FILE** where_to_find, char* which_to_find);

int main() {
    FILE* fp = fopen("./C-bal/23-1/search_target.txt", "r");
    char search_target[100] = "Excepteur";
    int search_counter = 0;

    while (1) {
        if (find_string_from(&fp, search_target)) {
            break;
        } else {
            // printf("String mismatch, counter is %d\n", search_counter);
            search_counter++;
            fseek(fp, search_counter, SEEK_SET);
        }
    }

    printf("%s is on location %d\n", search_target, search_counter);
    return 0;
}

int find_string_from(FILE** where_to_find, char* which_to_find) {
    int compare;
    while ((*which_to_find != NULL) && (compare != EOF)) {
        compare = fgetc(*where_to_find);
        // printf("from file: %c, from str: %c\n", compare, *which_to_find);
        if (compare != *which_to_find) return 0;
        // printf("%c", compare);
        which_to_find++;
    }
    // printf("\n");
    return 1;
}