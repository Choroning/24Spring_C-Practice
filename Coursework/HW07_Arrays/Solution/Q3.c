/**
 * @file    A10303-1_C07Q3.c
 * @brief   Q3. 배열 원소 뒤집기
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-10
 */

#include <stdio.h>

int main()
{
	double arr[10] = { 1.2, 3.1, 4.3, 4.5, 6.7, 2.3, 8.7, 9.5, 2.3, 5.8 };
	double arrRev[10];

	for (int i = 0; i < 10; i++) {
		arrRev[i] = arr[9 - i];
	}

	printf("\n배열(원본): ");
	for (int i = 0; i < 10; i++) {
		printf("%.1f  ", arr[i]);
	}
	printf("\n배열(역순): ");
	for (int i = 0; i < 10; i++) {
		printf("%.1f  ", arrRev[i]);
	}
}