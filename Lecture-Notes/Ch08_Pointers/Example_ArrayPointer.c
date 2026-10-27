/**
 * @file    Example_ArrayPointer.c
 * @brief   Accessing array elements through a pointer: arr[i], *(p + i), p[i], and moving the pointer with p++
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-20
 */

#include <stdio.h>
#define MAX 5

int main()
{
    int i, arr[MAX] = { 1,3,5,7,9 };
    int* p = arr;

    printf("arr: %p \n", arr);

    for (i = 0; i < MAX; i++)
    {
        printf("[%d, %d, %d], ", arr[i], *(p + i), p[i]);
        printf("[%p, %p] \n", &arr[i], (p + i));
    }
    printf("====================\n");

    for (i = 0; i < MAX; i++)
    {
        printf("[%d, %d], ", *(arr + i), *p);
        p++;
        printf("[%p, %p] \n", &arr[i], p);
    }
}
