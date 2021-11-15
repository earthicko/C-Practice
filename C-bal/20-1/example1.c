#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int num_students;
    int i, input;
    int *scores;
    int sum = 0;

    printf("Number of students: ");
    scanf("%d", &num_students);

    scores = (int *)malloc(sizeof(int) * num_students);

    for (i = 0; i < num_students; i++)
    {
        printf("Score of student #%d: ", i);
        scanf("%d", scores + i);
        sum += *(scores + i);
    }
    printf("Avg of scores: %d\n", sum / num_students);
    free(scores);
    return 0;
}