/**
 * @file    Example_ToUpper.c
 * @brief   Converting the lowercase letters of a string to uppercase by subtracting 'a' - 'A'
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
    int i;

    printf(">> input str: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';     // remove the newline that fgets keeps

    /*int len = 0;

    while (str[len] != '\0')
        len++;

    for (i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 'a' - 'A';
    }*/

    for (i = 0; str[i]; i++) {      // the loop range can be set without computing the length as above (str[i] != '\0')
                                    // str[i] alone works instead of str[i] != '\0' because the ASCII value of \0 is 0
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 'a' - 'A';
    }

    printf("-> str: %s", str);
}
