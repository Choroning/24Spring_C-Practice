/**
 * @file    Example_StorageDuration.c
 * @brief   Prints where objects of static, automatic, and allocated storage duration live, and shows that a static local keeps its value
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <stdio.h>
#include <stdlib.h>

int global_init = 7;            // static storage duration, initialized
int global_zero;                // static storage duration, initialized to 0

int next_ticket(void)
{
    static int counter = 100;   // initialized once, before main starts
    int step = 1;               // created anew on every call

    counter += step;
    return counter;
}

int main(void)
{
    const char *literal = "abc";
    int local = 1;
    int *heap = malloc(sizeof *heap);

    if (heap == NULL) {
        printf("allocation failed\n");
        return 1;
    }
    *heap = 2;

    printf("string literal : %p\n", (const void *)literal);
    printf("global_init    : %p\n", (void *)&global_init);
    printf("global_zero    : %p\n", (void *)&global_zero);
    printf("*heap          : %p\n", (void *)heap);
    printf("local          : %p\n", (void *)&local);

    printf("global_zero = %d\n", global_zero);
    for (int i = 0; i < 3; i++) {
        printf("ticket %d\n", next_ticket());
    }

    free(heap);
    return 0;
}
