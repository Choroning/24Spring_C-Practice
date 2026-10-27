/**
 * @file    Example_GradeIfElse.c
 * @brief   Converts a score into a letter grade with an if-else if chain and rejects scores outside 0-100
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-01
 */

#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main()
{
    int score;

    printf(">> Input score(0~100): ");  // written for the case where any integer is entered
    scanf(" %d", &score);

    if (score >= 90 && score <= 100)
        printf("%d is a/an A!", score);
    else if (score >= 80 && score <= 89)
        printf("%d is a/an B!", score);
    else if (score >= 70 && score <= 79)
        printf("%d is a/an C!", score);
    else if (score >= 60 && score <= 69)
        printf("%d is a/an D!", score);
    else if (score < 60 && score >= 0)
        printf("%d is a/an F!", score);
    else
        printf("Input error!");

    /* If the score is assumed to be entered only in 0-100, it can be written as follows
    if (score >= 90)
        printf("%d is a/an A!", score);
    else if (score >= 80)
        printf("%d is a/an B!", score);
    else if (score >= 70)
        printf("%d is a/an C!", score);
    else if (score >= 60)
        printf("%d is a/an D!", score);
    else
        printf("%d is a/an F!", score);
    */

    /* If the score can be any integer, writing it as follows is better

    if (score >= 0 && score <= 100)
    {
        if (score >= 90 && score <= 100)
            printf("%d is a/an A!", score);
        else if (score >= 80 && score <= 89)
            printf("%d is a/an B!", score);
        else if (score >= 70 && score <= 79)
            printf("%d is a/an C!", score);
        else if (score >= 60 && score <= 69)
            printf("%d is a/an D!", score);
        else if (score < 60 && score >= 0)
            printf("%d is a/an F!", score);
        else
            printf("Input error!");
    }
    */
}
