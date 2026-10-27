/**
 * @file    Example_ReturnValue.c
 * @brief   Functions that take arguments and return a value: getPlus() and getQuad()
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-29
 */

#include <stdio.h>
int getPlus(int x);
int getQuad(int a, int x);

int main()
{
    // getPlus(): one parameter
    int val = 2, result;

    result = getPlus(val);
    printf("1. result: %d \n", result);
    printf("2. result: %d \n", getPlus(3));

    // getQuad(): two parameters
    int a = 1, x = 3;

    result = getQuad(a, x);
    printf("1. result: %d \n", result);
    printf("2. result: %d \n", getQuad(2, 4));
}

int getPlus(int x) {
    int y;
    y = x + 3;
    return y;
}

int getQuad(int a, int x) {
    int y;
    y = a * a + x - 3;
    return y;
}
