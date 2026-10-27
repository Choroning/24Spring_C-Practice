/**
 * @file    Example_PointerArithmetic.c
 * @brief   Adding 1 to a pointer advances it by the size of the pointed-to type (char, int, double)
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-13
 */

#include <stdio.h>

int main()
{
    char ch = 'a';
    int di = 3;
    double db = 3.2;

    char* pc = &ch;
    int* pi = &di;
    double* pd = &db;

    printf("1. %p, %p, %p \n", pc, pi, pd);
    printf("2. %p, %p, %p \n", pc + 1, pi + 1, pd + 1);
}
