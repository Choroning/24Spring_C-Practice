/**
 * @file    Example_WordSplit.c
 * @brief   Printing each word of a line on its own line by testing characters with isspace()
 * @author  박철원 (Cheolwon Park)
 * @date    2024-06-03
 *
 * @note    Reads the line with the standard fgets; Visual Studio also offers gets_s(str, sizeof(str)).
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char str[15] = "";
    int i;

    printf(">> input str: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';     // remove the newline that fgets keeps

    printf("word: \n");
    for (i = 0; i < strlen(str); i++) {
        if (isspace(str[i]))        // isspace() returns 0 for a non-space character and a nonzero value for a space character
            printf("\n");
        else
            printf("%c", str[i]);
    }
}
