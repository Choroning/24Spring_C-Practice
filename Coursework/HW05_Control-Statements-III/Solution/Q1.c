/**
 * @file    A10303-3_C05Q1.c
 * @brief   Q1. 반복문 연습 (1)
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-12
 */

#include <stdio.h>

int main()
{
    int no = 0, max = 0, min = 100;

    while (1) {
        printf("Input value(no): ");
        scanf(" %d", &no);

        if (no > 100 || no < 0)
            printf("-- Error -- \n");
        else if (no == 0) {
            if (max < min)
                min = 0;
            break;
        }else {
            max = (no > max) ? no : max;
            min = (no < min) ? no : min;
        }
    }

    printf("MAX: %d, MIN: %d \n", max, min);
}