/**
 * @file    Example_ReverseString.c
 * @brief   Reversing a string in place with revStr(), which swaps the characters at both ends toward the middle
 * @author  박철원 (Cheolwon Park)
 * @date    2024-06-03
 *
 * @note    Reads the line with the standard fgets; Visual Studio also offers gets_s(str, SIZE).
 */

#include <stdio.h>
#include <string.h>
#define SIZE 10

void revStr(char* arr);
void swap(char* a, char* b);

int main()
{
    char str[SIZE] = "";

    printf(">> input str: ");
    fgets(str, SIZE, stdin);
    str[strcspn(str, "\n")] = '\0';     // remove the newline that fgets keeps

    revStr(str);
    printf("-> A reverse str: %s", str);
}

void revStr(char* arr)
{
    int i, len = strlen(arr);

    for (i = 0; i < (len / 2.0); i++) {
        swap(&arr[i], &arr[len - i - 1]);
    }
}

void swap(char* a, char* b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}
