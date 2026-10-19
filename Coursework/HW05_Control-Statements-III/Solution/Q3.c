/**
 * @file    A10303-3_C05Q3.c
 * @brief   Q3. 반복문 연습 (3)
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-12
 */

#include <stdio.h>

int main()
{
	int count, sum = 0;
	
	for (count = 1; count <= 10; count++) {
		if (count % 2)
			sum += count;
		else
			sum -= count;
	}
	printf("1 - 2 + 3 - 4 + 5 - 6 + 7 - 8 + 9 - 10 = %d", sum);
}