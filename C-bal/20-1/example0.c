#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    int size_of_array;
    int *arr;

    printf("Size of array: ");
    scanf("%d", &size_of_array);
    arr = (int*)malloc(sizeof(int) * size_of_array);

    free(arr);

    return 0;
}