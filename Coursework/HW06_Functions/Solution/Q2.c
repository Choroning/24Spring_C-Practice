/**
 * @file    A10303-1_C06Q2.c
 * @brief   Q2. 조건에 따라 합 구하기
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-01
 */

#include <stdio.h>
int getSign(int tmp);

int main()
{
	int val, i, sum = 0;

	for (i = 1; i <= 10; i++) {
		printf(">> (%d) Input value: ", i);
		scanf(" %d", &val);
		
		if (getSign(val)) {
			sum += val;
		}
	}
	printf("-> Sum of positive values: %d", sum);
}

int getSign(int tmp) 
{
	if (tmp > 0) {
		return 1;
	}
	else {
		return 0;
	}
}