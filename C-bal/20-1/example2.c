#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i;
    int x, y;
    int **arr;

    printf("Gonna make arr[x][y]. x, y: ");
    scanf("%d %d", &x, &y);

    arr = (int **)malloc(sizeof(int *) * x);
    for (i = 0; i < x; i++)
    {
        *(arr + i) = (int *)malloc(sizeof(int) * y);
    }

    printf("Created arr[x][y]\n");

    for (i = 0; i < x; i++)
        free(*(arr + i));

    free(arr);

    return 0;
}