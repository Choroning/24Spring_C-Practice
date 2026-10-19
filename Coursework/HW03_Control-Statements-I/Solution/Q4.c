/**
 * @file    A10303-1_C05Q1.c
 * @brief   Q1. 대소 비교
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-28
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *	    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
	int num1, num2, num3;
	int max1, max2;

	printf("Input 3 values: ");
	scanf_s(" %d %d %d", &num1, &num2, &num3);

	max1 = num1 > num2 ? num1 : num2;
	max2 = max1 > num3 ? max1 : num3;

	printf("Max: %d", max2);
}
