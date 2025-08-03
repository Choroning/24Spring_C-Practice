/**
 * @file    A10303-2_C08Q2.c
 * @brief   Q2. 2차원 배열 출력
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-22
 */

#include <stdio.h>

void printMat(int data[][4], int cols, int rows);

int main()
{
	int data[3][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	printMat(data, 3, 4);
}

void printMat(int arr[][4], int cols, int rows)
{
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			printf("%3d", arr[i][j]);
		}
		printf("\n");
	}
}