/**
 * @file    Example_GenericPointers.c
 * @brief   A generic swap written with void pointers, a dispatch table of function pointers, and a callback with a context pointer
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <stdio.h>
#include <stddef.h>

// Swaps two objects of size bytes, one byte at a time.
void swap_bytes(void *a, void *b, size_t size)
{
    unsigned char *pa = a;
    unsigned char *pb = b;

    for (size_t i = 0; i < size; i++) {
        unsigned char tmp = pa[i];

        pa[i] = pb[i];
        pb[i] = tmp;
    }
}

int add(int x, int y) { return x + y; }
int sub(int x, int y) { return x - y; }
int mul(int x, int y) { return x * y; }

typedef int (*BinaryOp)(int, int);

// Calls visit once for every element, passing ctx through unchanged.
void for_each(const int *a, size_t n, void (*visit)(int, void *), void *ctx)
{
    for (size_t i = 0; i < n; i++) {
        visit(a[i], ctx);
    }
}

void add_to_total(int value, void *ctx)
{
    int *total = ctx;
    *total += value;
}

void print_value(int value, void *ctx)
{
    (void)ctx;
    printf("%d ", value);
}

int main(void)
{
    int x = 1, y = 2;
    double d = 1.5, e = 2.5;

    swap_bytes(&x, &y, sizeof x);
    swap_bytes(&d, &e, sizeof d);
    printf("x = %d, y = %d, d = %.1f, e = %.1f\n", x, y, d, e);

    BinaryOp table[] = {add, sub, mul};
    const char *names[] = {"add", "sub", "mul"};

    for (size_t i = 0; i < sizeof table / sizeof table[0]; i++) {
        printf("%s(7, 3) = %d\n", names[i], table[i](7, 3));
    }

    int data[] = {3, 1, 4, 1, 5};
    int total = 0;

    for_each(data, 5, print_value, NULL);
    printf("\n");
    for_each(data, 5, add_to_total, &total);
    printf("total = %d\n", total);
    return 0;
}
