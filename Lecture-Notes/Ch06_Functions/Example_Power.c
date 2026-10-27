/**
 * @file    Example_Power.c
 * @brief   A function, getPower(), that computes x to the power of y by repeated multiplication
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-29
 */

#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>
int getPower(int x, int y);

int main()
{
    int x, y;

    printf(">> input two values: ");
    scanf(" %d %d", &x, &y);

    printf("%d to the power of %d: %d", x, y, getPower(x, y));
}

int getPower(int x, int y) {
    int i, xycal = 1;
    for (i = 0; i < y; i++) {
        xycal *= x;
    }
    return xycal;
}
