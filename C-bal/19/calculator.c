#include <stdio.h>
#include "calculator.h"

float calculate(int *operands, char *operators, int operand_count)
{
    printf("DEBUG: operand_count=%d\n", operand_count);
    float output = *operands;
    operands++;

    int i;
    for (i = 1; i < operand_count; i++)
    {
        int operand_f = *operands;
        printf("DEBUG: %f %c %d\n", output, *operators, *operands);

        switch (*operators)
        {
        case '+':
            output = output + *operands;
            break;
        case '-':
            output = output - *operands;
            break;
        case '/':
            output = output / *operands;
            break;
        case '*':
            output = output * *operands;
            break;
        default:
            break;
        }
        operands++;
        operators++;
    }
    return output;
}