/**
 * @file    A10303-1_C04Q1.c
 * @brief   Q1. 값의 n진수 출력
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-20
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *		    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
	int no;
	printf("enter no: ");
	scanf_s(" %d", &no);
	printf("%d, %#o, %#x", no, no, no);
}