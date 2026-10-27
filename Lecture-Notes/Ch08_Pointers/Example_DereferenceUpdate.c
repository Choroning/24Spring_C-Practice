/**
 * @file    Example_DereferenceUpdate.c
 * @brief   *p = 2 + *p reads the variable through the pointer and writes the new value back, while p and &p stay the same
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-13
 */

#include <stdio.h>

int main()
{
    int a = 3;
    int* p = &a;

    printf("1. a: %d, &a: %p \n", a, &a);
    printf("2. p: %p, &p: %p \n", p, &p);
    printf("3. *p: %d \n", *p);

    *p = 2 + *p;
    printf("4. a: %d, &a: %p \n", a, &a);
    printf("5. p: %p, &p: %p \n", p, &p);
    printf("6. *p: %d \n", *p);
}
