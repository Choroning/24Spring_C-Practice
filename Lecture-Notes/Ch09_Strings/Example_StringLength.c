/**
 * @file    Example_StringLength.c
 * @brief   Computing the length of a string by counting characters up to the null character
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-27
 *
 * @note    Reads the line with the standard fgets; Visual Studio also offers gets_s(str, sizeof(str)).
 */

#include <stdio.h>
#include <string.h>

int main()
{
    char str[15] = "";
    int len = 0;

    printf(">> input str: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';     // remove the newline that fgets keeps

    while (str[len] != '\0')
        len++;

    printf("-> len: %d \n", len);       // strlen(str) also gives the length
}
