/**
 * @file    Example_StringArray.c
 * @brief   A two-dimensional char array as an array of strings: printing each row and changing single characters
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-27
 */

#include <stdio.h>

int main()
{
    char str[3][6] = { {"ABC"}, {"defg"}, {"1Q$"} };
    int i;

    for (i = 0; i < 3; i++) {
        printf("%s \n", str[i]);
    }
    printf("------------ \n");
    str[0][0] = 'a';
    str[0][2] = 'c';
    printf("%c \n", str[0][0]);
    printf("%s \n", str[0]);
}
