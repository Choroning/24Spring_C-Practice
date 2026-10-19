/**
 * @file    A10303-2_C08Q1.c
 * @brief   Q1. 선택 정렬
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-22
 */

#include <stdio.h>

int main()
{
	int data[5] = { 52, 31, 28, 17, 46 };
	int i, j, idx_min, tmp;

	printf("> 정렬 전:");
	for (i = 0; i < 5; i++)
	{
		printf("%4d", data[i]);
	}

	for (i = 0; i < 4; i++)
	{
		idx_min = i;
		for (j = i + 1; j < 5; j++)
		{
			if (data[idx_min] > data[j])
				idx_min = j;
		}
		if (idx_min != i)
		{
			tmp = data[i];
			data[i] = data[idx_min];
			data[idx_min] = tmp;
		}
	}
	printf("\n> 정렬 후:");
	for (i = 0; i < 5; i++)
	{
		printf("%4d", data[i]);
	}
}