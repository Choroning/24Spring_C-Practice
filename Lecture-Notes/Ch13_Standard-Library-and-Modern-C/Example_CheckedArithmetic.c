/**
 * @file    Example_CheckedArithmetic.c
 * @brief   Avoids undefined behavior in integer arithmetic by testing the operands before the operation
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

// Each function reports through its return value whether the result fits.
static bool safe_add(int a, int b, int *result)
{
    if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b)) {
        return false;
    }
    *result = a + b;
    return true;
}

static bool safe_multiply(int a, int b, int *result)
{
    long long product = (long long)a * b;  // long long holds any product of two int values
    if (product > INT_MAX || product < INT_MIN) {
        return false;
    }
    *result = (int)product;
    return true;
}

static bool safe_divide(int a, int b, int *result)
{
    if (b == 0 || (a == INT_MIN && b == -1)) {
        return false;
    }
    *result = a / b;
    return true;
}

// Shifting by the width of the type or more is undefined, so the count is checked.
static bool safe_shift_left(unsigned int value, int count, unsigned int *result)
{
    int width = (int)(sizeof value * CHAR_BIT);
    if (count < 0 || count >= width) {
        return false;
    }
    *result = value << count;
    return true;
}

int main(void)
{
    int r;
    unsigned int u;

    printf("add: %s\n", safe_add(INT_MAX, 1, &r) ? "ok" : "overflow");
    printf("add: %s, r = %d\n", safe_add(2, 3, &r) ? "ok" : "overflow", r);
    printf("multiply: %s\n", safe_multiply(100000, 100000, &r) ? "ok" : "overflow");
    printf("divide: %s\n", safe_divide(INT_MIN, -1, &r) ? "ok" : "not representable");
    printf("shift: %s\n", safe_shift_left(1u, 40, &u) ? "ok" : "count out of range");

    // Unsigned arithmetic is defined: it wraps around modulo 2^N
    unsigned int max = UINT_MAX;
    printf("UINT_MAX + 1 = %u\n", max + 1);

    return 0;
}
