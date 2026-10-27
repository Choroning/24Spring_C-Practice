/**
 * @file    Example_SwapInline.c
 * @brief   Swapping the values of two variables in main with a temporary variable
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-13
 */

#include <stdio.h>

int main()
{
    int a = 3, b = 5, temp;
    printf("1. a, b: %d, %d \n", a, b);

    temp = a;
    a = b;
    b = temp;

    printf("2. a, b: %d, %d \n", a, b);
}
