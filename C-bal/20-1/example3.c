#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    int width, height;

    printf("Width of array: ");
    scanf("%d", &width);

    printf("Height of array: ");
    scanf("%d", &height);

    int (*arr)[height] = (int(*)[height])malloc(sizeof(int) * width * height);

    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            int data;
            scanf("%d", &data);
            arr[i][j] = data;
        }
    }

    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    free(arr);
    return 0;
}