/**
 * @file    Example_Counter.c
 * @brief   Implementation of the counter module: internal linkage hides the state and the helper function; has no main, so build together with Example_CounterMain.c
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include "Example_Counter.h"

int counter_step = 1;       // The one definition of the external variable

static int count = 0;       // Internal linkage: no other file can name this variable

static int clamp(int value) // Internal linkage: a helper private to this file
{
    return value > 100 ? 100 : value;
}

void counter_reset(void)
{
    count = 0;
}

void counter_increment(void)
{
    count = clamp(count + counter_step);
}

int counter_value(void)
{
    return count;
}
