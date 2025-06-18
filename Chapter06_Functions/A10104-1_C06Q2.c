/**
 * @file    A10104-1_C6Q2.c
 * @brief   Q2. 윤년 판별
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-17
 */

#include <stdio.h>

int isLeapYear(int year)
{
    return ((year % 4) == 0) ? ((year % 100) == 0 ? ((year % 400) == 0 ? 1 : 0) : 1) : 0;
}

int main()
{
    int input, count = 0;

    printf("-------------------------------------------------\n");
    printf("               2000~2150년 사이의 윤년\n");
    printf("-------------------------------------------------\n");

    for (input = 2000; input <= 2150; input++) {
        if (isLeapYear(input) == 1) {
            printf("%d ", input);
            count++;
            if (count % 10 == 0)
                printf("\n");
        }
    }

    return 0;
}
