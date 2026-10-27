/**
 * @file    Example_TwelveHourClock.c
 * @brief   Converts an hour from 0 to 23 into the 12-hour clock with A.M and P.M
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-01
 */

#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main()
{
    int time;

    printf(">> Input Time(0~23): ");
    scanf(" %d", &time);

    if (time >= 1 && time <= 11)
        printf("[%d A.M]", time);
    else if (time == 12)
        printf("[%d P.M]", time);
    else if (time >= 13 && time <= 23)
        printf("[%d P.M]", time - 12);
    else if (time == 0)
        printf("[%d A.M]", time + 12);
    else
        printf("Input Error!");
}
