/**
 * @file    A10303-1_C08Q2.c
 * @brief   Q2. 배열 연산
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-18
 */

#include <stdio.h>

void arrSum(int* pX, int* pY, int* pZ)
{
	*pZ = *pX + *pY;
}

int main()
{
	int arrX[4] = { -2, 4, 6, -32 };
	int arrY[4] = { 4, 3, -5, 6 };
	int arrZ[4] = { 0 };

	for (int i = 0; i < 4; i++)
		arrSum(&arrX[i], &arrY[i], &arrZ[i]);

	printf("\narrZ: ");
	for (int i = 0; i < 4; i++)
		printf("%3d  ", arrZ[i]);
}