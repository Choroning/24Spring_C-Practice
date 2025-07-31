/**
 * @file    A10303-3_C05Q2.c
 * @brief   Q2. 반복문 연습 (2)
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-12
 */

#include <stdio.h>

int main()
{
	int val, sum = 0, i = 0;
	double ave;

	do {
		printf(">> Input value: ");
		scanf_s(" %d", &val);

		sum += val;
		i++;
	} while (val != 0);
	
	printf("===================== \n");
	
	if (i == 1)
		printf("-> 0만 입력되었습니다!");
	else {
		ave = (double) sum / (i - 1);
		printf("-> SUM: %d, AVE: %.1lf", sum, ave);
	}	
}