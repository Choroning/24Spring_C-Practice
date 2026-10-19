/**
 * @file    A10303-1_C04Q2.c
 * @brief   Q2. 연산의 기본
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-23
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *	    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
	int first, second, third, sum;
	printf("Enter 3 values: ");
	scanf_s(" %d %d %d", &first, &second, &third);
	sum = first + second + third;
	printf("%6d \n", first);
	printf("%6d \n", second);
	printf("%6d \n", third);
	printf("-------- \n");
	printf("%6d \n", sum);
	printf("%6.1lf \n", sum / 3.0);
}
