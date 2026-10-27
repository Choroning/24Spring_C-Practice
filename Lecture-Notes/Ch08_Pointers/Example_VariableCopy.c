/**
 * @file    Example_VariableCopy.c
 * @brief   Initializing one variable with another copies only the value: the two variables have different addresses
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-13
 */

#include <stdio.h>

int main()
{
    int a = 3;
    int b = a;

    printf("[1] %d, %d \n", a, b); // expected: 3, 3
    printf("[1-1] %p, %p \n", &a, &b);

    // Can the value of a be changed through variable b?
    b = 5;

    printf("[2] %d, %d \n", a, b); // expected: 3, 5
}
