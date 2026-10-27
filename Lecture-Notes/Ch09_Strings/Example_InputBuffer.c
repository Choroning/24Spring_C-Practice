/**
 * @file    Example_InputBuffer.c
 * @brief   scanf("%s") stops at a space and leaves the rest in the input buffer, while a line input function reads the whole line
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-27
 *
 * @note    Reads the line with the standard fgets; Visual Studio also offers gets_s(nTwo, sizeof(nTwo)).
 */

#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>
#include <string.h>
int main()
{
    char nOne[20] = "";
    char nTwo[20] = "";

    printf(">> 1. input name: ");
    scanf(" %s", nOne);     // enter a name such as hong gil dong

    // also note how the program behaves when the while loop below (which empties the buffer) is commented out
    while (getchar() != '\n');      // " gil dong" and Enter remain in the buffer after hong is read; this discards them

    printf(">> 2. input name: ");
    fgets(nTwo, sizeof(nTwo), stdin);   // enter a name such as hong gil dong
    nTwo[strcspn(nTwo, "\n")] = '\0';   // remove the newline that fgets keeps

    printf("-> nOne: %s \n", nOne);     // prints only hong (scanf stops at the space)
    printf("-> nTwo: %s \n", nTwo);     // prints all of hong gil dong
}
