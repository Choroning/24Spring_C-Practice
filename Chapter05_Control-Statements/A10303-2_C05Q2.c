/**
 * @file    A10303-2_C05Q2.c
 * @brief   Q2. 홀짝 판별
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-05
 */

#include <stdio.h>

int main()
{
	int num;

	printf(">> Input value: ");
	scanf(" %d", &num);

	if (num % 2) {
		printf("-> %d is an odd number.\n", num);
	} else {
		printf("-> %d is an even number.\n", num);
	}

	return 0;
}