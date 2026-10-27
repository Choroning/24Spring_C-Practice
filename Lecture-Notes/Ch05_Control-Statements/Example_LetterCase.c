/**
 * @file    Example_LetterCase.c
 * @brief   Tells whether an input character is an uppercase or a lowercase English letter
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-01
 */

#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main()
{
    char ch;

    printf(">> Input char: ");
    scanf(" %c", &ch);

    /*
    if (ch >= 65 && ch <= 90)
        printf("Large Letters of English!");
    else if (ch >= 97 && ch <= 122)
        printf("Small Letters of English!");
    else
        printf("Input Error!");
    */

    if (ch >= 'A' && ch <= 'Z')  // when the decimal ASCII values are not known
        printf("Large Letters of English!");
    else if (ch >= 'a' && ch <= 'z')
        printf("Small Letters of English!");
    else
        printf("Input error!");
}
