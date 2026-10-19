/**
 * @file    A10303-3_C05Q4.c
 * @brief   Q4. 반복문 연습 (4)
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-13
 */

#include <stdio.h>

int main()
{
	int i = 0, j = 0;

	for (i = 0; i <= 4; i++) {
		for (j = 0; j <= i; j++)
			printf("%d ", j);
		printf("\n");
	}
	for (i = 3; i >= 0; i--) {
		for (j = 0; j <= i; j++)
			printf("%d ", j);
		printf("\n");
	}
}