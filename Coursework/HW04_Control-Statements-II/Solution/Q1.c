/**
 * @file    A10303-2_C05Q1.c
 * @brief   Q1. 영문자 변환
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-05
 */

#include <stdio.h>

int main()
{
	char ch;

	printf(">> Input char: ");
	scanf(" %c", &ch);

	if (ch >= 'a' && ch <= 'z') {
		printf("-> Changed lower case %c to upper case %c!\n", ch, ch - 32);
	} else if (ch >= 'A' && ch <= 'Z') {
		printf("-> Changed upper case %c to lower case %c!\n", ch, ch + 32);
	} else {
		printf("-> Input error!\n");
	}

	return 0;
}