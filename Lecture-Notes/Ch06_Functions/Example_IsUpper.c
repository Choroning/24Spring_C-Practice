/**
 * @file    Example_IsUpper.c
 * @brief   A function, isUpper(), that returns 1, -1, or 0 for an uppercase letter, a lowercase letter, or another character
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-29
 */

#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>
int isUpper(char ch);

int main()
{
    int ret;
    char alpha;
    printf(">> input char: ");
    scanf(" %c", &alpha);

    ret = isUpper(alpha);

    if (ret == 1) {
        printf("%c is a/an upper case!", alpha);
    }
    else if (ret == -1) {
        printf("%c is a/an lower case!", alpha);
    }
    else if (ret == 0) {
        printf("It's not an English alphabet!");
    }
}

int isUpper(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return 1;
    }
    else if (ch >= 'a' && ch <= 'z') {
        return -1;
    }
    else {
        return 0;
    }
}
