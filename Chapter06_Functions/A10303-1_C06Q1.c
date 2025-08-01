/**
 * @file    A10303-1_C06Q1.c
 * @brief   Q1. 합 구하기
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-01
 */

#include <stdio.h>
int getSum(int val);

int main()
{
	int val;

	printf(">> Enter value: ");
	scanf(" %d", &val);

	printf("-> Sum(%d) ---> %d", val, getSum(val));
}

int getSum(int val) {
	int i, sum = 0;

	if (val > 0) {
		for (i = 1; i <= val; i++) {
			sum += i;
		}
		return sum;
	}
	else if (val == 0) {
		return 0;
	}
	else {
		for (i = -1; i >= val; i--) {
			sum += i;
		}
		return sum;
	}
}