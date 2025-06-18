/**
 * @file    A10104-1_C7Q1.c
 * @brief   Q1. UPC 바코드의 Check Digit 계산
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-11
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>
#define SIZE 12

int main()
{
	int dig[SIZE], sum = 0, i;

	printf("Please enter the first eleven UPC digits, separated by white space: \n");

	for (i = 0; i < SIZE - 1; i++) {
		scanf_s("%1d", &dig[i]);
	}
	for (i = 0; i < SIZE - 1; i++) {
		printf("입력된 숫자: %d", dig[i]);
	}
	
	for (i = 0; i < SIZE - 1; i += 2) {
		sum += dig[i];
	}
	sum *= 3;
	for (i = 1; i < SIZE - 1; i += 2) {
		sum += dig[i];
	}
	dig[SIZE - 1] = (10 - sum % 10) % 10;

	printf("\nThe check digit is: %d \n", dig[SIZE - 1]);
	return 0;
}
