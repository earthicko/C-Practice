#include <stdio.h>
#include <math.h>
#include "calculator.h"

int str_to_int(char *input);

int main(int argc, char **argv)
{
    printf("Number of args: %d\n", argc);
    int i;
    for (i = 0; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }
    printf("\n");

    // argc=2 -> 1개 -> 숫자 1개 연산자 0개
    // argc=4 -> 3개 -> 숫자 2개 연산자 1개
    // argc=6 -> 5개 -> 숫자 3개 연산자 2개

    int operands[100];
    char operators[100];
    for (i = 1; i < argc; i++)
    {
        if (i % 2) {
            // 1->0, 3->1, 5->2...
            operands[(i - 1) / 2] = str_to_int(argv[i]);
            printf("DEBUG: operands[%d] = %d\n", (i - 1) / 2, operands[(i - 1) / 2]);
        } else {
            // 2->0, 4->1, 6->2...
            operators[i / 2 - 1] = argv[i][0];
            printf("DEBUG: operators[%d] = %c\n", i / 2 - 1, operators[i / 2 - 1]);
        }
    }

    // 2-> 1, 4->2, 6->3
    int operand_count = argc / 2;
    float result = calculate(operands, operators, operand_count);

    printf("result: %f\n", result);
    return 0;
}

int str_to_int(char *input)
{
    int output = 0;
    int char_count = 1;
    while (1)
    {
        if (input[char_count] == 0)
            break;
        char_count++;
    }
    int i;
    for (i = 0; i < char_count; i++)
    {
        int digit = (int)input[i] - 48;
        output += pow(10, char_count - i - 1) * digit;
    }
    return output;
}