/**
 * @file    A10303-2_C05Q4.c
 * @brief   Q4. switch-if 변환 (2)
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-05
 */

#include <stdio.h>

int main()
{
	int grade;

	printf(">> Input grade(1~7): ");
	scanf(" %d", &grade);

	if (grade == 1)
		printf("Very good!");
	else if (grade == 2 || grade == 3)
		printf("Good!");
	else if (grade == 4 || grade == 5)
		printf("So So!");
	else if (grade == 6 || grade == 7)
		printf("Cheer up!");
	else
		printf("Input error!");
}
