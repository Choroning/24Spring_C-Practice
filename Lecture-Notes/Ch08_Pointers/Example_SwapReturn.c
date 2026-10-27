/**
 * @file    Example_SwapReturn.c
 * @brief   The swap of Example_SwapInline.c with a function: exchange() returns one value, and the sum recovers the other
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-13
 */

#include <stdio.h>      // Extra problem 1: rewrite the swap with a function
int exchange(int x, int y)
{
    int temp;
    temp = x;
    x = y;
    y = temp;

    return x;
}

int main()
{
    int a = 3, b = 5, temp;
    printf("1. a, b: %d, %d \n", a, b);

    temp = a + b;
    a = exchange(a, b);
    b = temp - a;

    printf("2. a, b: %d, %d \n", a, b);
}
