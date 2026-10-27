/**
 * @file    Example_SignCheck.c
 * @brief   Classifies an input integer as positive, zero, or negative with an if-else if chain
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-01
 */

#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main()
{
    int num1;

    printf("Input num: ");
    scanf(" %d", &num1);

    if (num1 > 0)
        printf("Positive number!");
    else if (num1 == 0)
        printf("Zero!");
    else
        printf("Negative number!");
}
