/**
 * @file    Example_CounterMain.c
 * @brief   Uses the counter module through its header; build together with Example_Counter.c
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <stdio.h>
#include "Example_Counter.h"
#include "Example_Counter.h"    // Included twice on purpose: the header guard makes this harmless

int main(void)
{
    counter_reset();
    counter_increment();
    printf("after one increment: %d\n", counter_value());

    counter_step = 60;          // Assigns the variable defined in Example_Counter.c
    counter_increment();
    counter_increment();
    printf("after two steps of 60: %d\n", counter_value());

    return 0;
}
