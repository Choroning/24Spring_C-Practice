/**
 * @file    A10303-1_C09Q1.c
 * @brief   Q1. 문자열 검색
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-31
 * 
 * @note    소스 코드에 사용된 gets_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
	char str[50] = "";
	int i, countU = 0, countL = 0;
	
	printf("Input str: ");
	gets_s(str, sizeof(str));

	for (i = 0; str[i]; i++) {
		if (str[i] >= 'a' && str[i] <= 'z')
			countL++;
		else if (str[i] >= 'A' && str[i] <= 'Z')
			countU++;
	}

	printf("Uppercase letters: %d\n", countU);
	printf("Lowercase letters: %d\n", countL);
}