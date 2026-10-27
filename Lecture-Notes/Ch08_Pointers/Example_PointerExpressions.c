/**
 * @file    Example_PointerExpressions.c
 * @brief   Evaluating p[2], *p + 1, *(p + 1), *(p + 3), and an assignment through *p on an array
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-13
 */

#include <stdio.h>

int main()
{
    int arr[6] = { 1,-3,5,-6,12,4 };
    int* p = arr;

    printf("1. %d \n", p[2]);       // result: 1. 5
    printf("2. %d \n", *p + 1);     // result: 2. 2
    printf("3. %d \n", *(p + 1));   // result: 3. -3
    printf("4. %d \n", *(p + 3));   // result: 4. -6

    *p = arr[2] - *p;
    printf("5. %d \n", arr[0]);     // result: 5. 4
}
