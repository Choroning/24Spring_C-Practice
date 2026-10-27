/**
 * @file    Example_LinearSearch.c
 * @brief   Sequential search that prints every index of an input value, sized with sizeof so it works for any array length
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-20
 */

#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main() // works even if the number of elements in the array changes
{
    int arr[] = { 23, 45, -34, 23, -124, 22, 2 };
    int i, val, count = 0;

    printf("arr = ");
    for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n>> input value: ");
    scanf(" %d", &val);

    /*for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (val == arr[i])
        {
            printf("인덱스 %d에 %d값이 위치함! \n", i, val);
            break; // written this way, it does not work correctly when the value appears two or more times in the array
        } // in that case, declare and use a variable such as count
    }
    if (i == sizeof(arr) / sizeof(arr[0]))
    {
        printf("배열에 %d값이 없습니다! \n", val);
    }*/

    for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (val == arr[i])
        {
            printf("인덱스 %d에 %d값이 위치함! \n", i, val);
            count++;
        }
    }
    if (count == 0)
    {
        printf("배열에 %d값이 없습니다! \n", val);
    }


    // With the function below, main can call it as print_array(arr, size);

    /*void print_array(int pArr[], int size){
        int i;
        for (i = 0; i < size; i++)
            printf("%d ", pArr[i]);
        printf("\n");
    }*/
}
