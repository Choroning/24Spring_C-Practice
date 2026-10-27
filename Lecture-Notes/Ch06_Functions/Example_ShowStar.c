/**
 * @file    Example_ShowStar.c
 * @brief   A function without a return value, showStar(), that prints n stars
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-29
 */

#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>
void showStar(int n);

int main() {
    int num;
    printf(">> input value: ");
    scanf(" %d", &num);

    showStar(num);
}

void showStar(int n) {
    int i;
    for (i = 1; i <= n; i++) {
        printf("*");
    }
    return;
}
