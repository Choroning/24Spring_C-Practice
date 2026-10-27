/**
 * @file    Example_Transpose.c
 * @brief   Transposes a 3x3 matrix into a second two-dimensional array and prints both
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-20
 */

#include <stdio.h>

// Passing array contents between functions (not covered yet)
/*void print_array(int* pmat[], int vsize, int hsize)
{
    int i, j;

    for (i = 0; i < vsize; i++)
    {
        for (j = 0; j < hsize; j++)
        {
            printf("%3d", *pmat);
            *pmat++;
        }
        printf("\n");
    }
}*/

int main()
{
    int matA[][3] = { {5, 7, 4}, {6, 1, 8}, {3, 2, 7} };
    int matB[3][3] = { 0 };
    int i, j;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            matB[j][i] = matA[i][j];
        }
    }

    printf("[matA] \n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%3d", matA[i][j]);
        }
        printf("\n");
    }

    printf("[matB] \n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%3d", matB[i][j]);
        }
        printf("\n");
    }
}
