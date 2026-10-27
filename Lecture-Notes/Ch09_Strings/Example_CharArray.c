/**
 * @file    Example_CharArray.c
 * @brief   Storing a string in a char array, by assigning characters one by one or by copying with strcpy()
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-27
 */

#define _CRT_SECURE_NO_WARNINGS  // allows strcpy in Visual Studio
#include <stdio.h>
#include <string.h>

/*int main()
{
    char str[7];
    printf("1. %s \n", str);

    // assign values with character literals
    str[0] = 'H';
    str[1] = 'e';
    str[2] = 'l';
    str[3] = 'l';
    str[4] = 'o';
    str[5] = '\0';
    printf("2. %s \n", str);
}*/

int main()
{
    char str[7];
    printf("1. %s \n", str);  // str is not initialized yet, so this prints whatever is in memory

    // update the string with strcpy()
    strcpy(str, "Hello");
    printf("2. %s \n", str);
}
