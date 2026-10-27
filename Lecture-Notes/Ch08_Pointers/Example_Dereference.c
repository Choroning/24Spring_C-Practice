/**
 * @file    Example_Dereference.c
 * @brief   A pointer stores the address of a variable, and the dereference *p reads and writes that variable
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-13
 */

#include <stdio.h>

int main()
{
    int a = 3;
    int* p = &a;

    printf("[1] a: %d \n", a);
    printf("[2] &a: %p \n", &a);

    printf("[3] p: %p \n", p);
    printf("[4] &p: %p \n", &p);

    // use the data at the place pointer p refers to: dereference
    printf("[5] *p: %d \n", *p);

    // *p is interpreted as the memory area that pointer p refers to,
    // that is, 5 is assigned to the memory area p refers to!
    *p = 5;
    printf("[6] a: %d \n", a);
    printf("[7] *p: %d \n", *p);
}
