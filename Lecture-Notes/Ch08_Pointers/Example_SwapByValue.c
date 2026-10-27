/**
 * @file    Example_SwapByValue.c
 * @brief   A swap() function with value parameters swaps only its own copies, so a and b in main stay unchanged
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-13
 */

#include <stdio.h>      // Extra problem 1: rewrite the swap with a function
void swap(int x, int y)
{
    int temp;
    temp = x;
    x = y;
    y = temp;
}

int main()
{
    int a = 3, b = 5;
    printf("1. a, b: %d, %d \n", a, b);

    swap(a, b);

    printf("2. a, b: %d, %d \n", a, b);
}
