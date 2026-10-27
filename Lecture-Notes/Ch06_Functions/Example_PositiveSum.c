/**
 * @file    Example_PositiveSum.c
 * @brief   Sums only the non-negative values among 10 inputs, using a function getSign() as the condition
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-29
 */

#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>
int getSign(int val);

int main()
{
    int count = 1, val, sum = 0;

    do {
        printf(">> (%d) input val: ", count);
        scanf(" %d", &val);

        if (getSign(val)) {
            sum += val;
        }
        count++;
    } while (count <= 10);

    printf("-> sum of positive values: %d", sum);
}
int getSign(int val) {
    if (val >= 0) {
        return 1;
    }
    else {
        return 0;
    }
}
