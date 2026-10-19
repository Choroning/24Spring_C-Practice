/**
 * @file    A10303-1_C07Q2.c
 * @brief   Q2. 배열에서 대소 비교
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-10
 */

#include <stdio.h>

int main()
{
	int arr_num[7], min, max;

	for (int i = 0; i < 7; i++) {
		printf(">> Input data (%d): ", i + 1);
		scanf(" %d", &arr_num[i]);
	}
	min = arr_num[0];
	max = arr_num[0];

	for (int i = 1; i < 7; i++) {
		min = (arr_num[i] < min) ? arr_num[i] : min;
		max = (arr_num[i] > max) ? arr_num[i] : max;
	}

	printf("\n배열에서 가장 큰 값: %d\n", max);
	printf("배열에서 가장 작은 값 : %d\n", min);
}