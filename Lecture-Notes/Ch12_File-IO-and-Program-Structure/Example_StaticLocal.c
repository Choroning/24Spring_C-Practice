/**
 * @file    Example_StaticLocal.c
 * @brief   Compares an automatic local variable with a static local variable across repeated calls
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <stdio.h>

static int next_id(void)
{
    int automatic = 0;          // Created and initialized on every call
    static int persistent = 0;  // Initialized once, before the program starts

    automatic++;
    persistent++;
    printf("automatic = %d, persistent = %d\n", automatic, persistent);

    return persistent;
}

int main(void)
{
    for (int i = 0; i < 3; i++) {
        next_id();
    }
    return 0;
}
