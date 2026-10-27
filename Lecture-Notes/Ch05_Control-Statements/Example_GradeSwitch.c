/**
 * @file    Example_GradeSwitch.c
 * @brief   Prints a message for a grade from 1 to 7 with a switch statement
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-01
 */

#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main()
{
    int grade;

    printf(">> Input grade(1~7): ");
    scanf(" %d", &grade);

    switch (grade) {
    case 1:
        printf("Very good!");
        break;
    case 2:
        printf("Good!");
        break;
    case 3:
        printf("Good!");
        break;
    case 4:
        printf("So So!");
        break;
    case 5:
        printf("So So!");
        break;
    case 6:
        printf("Cheer up!");
        break;
    case 7:
        printf("Cheer up!");
        break;
    default:
        printf("Input error!");
        // break; may be omitted in the last default
    }

    /* Improvement: cases 2-3, 4-5, and 6-7 do the same thing.
       Without break, execution continues into the next case, so cases 2, 4, and 6
       can have all their statements removed.

       Also, a case label cannot take a range or a relational expression;
       each case handles exactly one value.
    */
}
