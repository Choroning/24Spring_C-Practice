/**
 * @file    Example_Radian.c
 * @brief   A function, getRadian(), that converts degrees to radians with a macro constant PI
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-29
 */

#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>
#define PI 3.14159
double getRadian(int deg);

int main()
{
    int deg;

    printf(">> input degree(0~359): ");
    scanf(" %d", &deg);

    printf("The radian value of %d degrees is %.2lf", deg, getRadian(deg));
}
double getRadian(int deg) {
    double caldeg;
    caldeg = (deg / 180.0) * PI;

    return caldeg;
}
