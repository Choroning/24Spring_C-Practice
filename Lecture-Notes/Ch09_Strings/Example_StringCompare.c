/**
 * @file    Example_StringCompare.c
 * @brief   A function, StrComp(), that returns 1 if two strings are equal and 0 otherwise
 * @author  박철원 (Cheolwon Park)
 * @date    2024-06-03
 */

#include <stdio.h>
#include <string.h>

int StrComp(char* pOne, char* pTwo);

int main()
{
    char sOne[10] = "ab c";
    char sTwo[10] = "ab d";

    printf("1. result: %d \n", StrComp(sOne, sTwo));
    printf("2. result: %d \n", StrComp("hi", "hi"));
    printf("3. result: %d \n", StrComp("hi", "hi#"));
}

int StrComp(char* pOne, char* pTwo)
{
    int i, lenOne = strlen(pOne), lenTwo = strlen(pTwo);

    if (lenOne != lenTwo)       // strings of different lengths are treated as different
        return 0;

    for (i = 0; i < lenOne; i++) {
        if (pOne[i] != pTwo[i])
            return 0;
    }
    return 1;
}
