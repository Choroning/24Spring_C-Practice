/**
 * @file    A10303-1_C08Q1.c
 * @brief   Q1. 맞바꾸기
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-18
 */

#include <stdio.h>

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main()
{
	int a = 3, b = 5;
	printf("초기상태: a = %d, b = %d\n", a, b);
	swap(&a, &b);
	printf("맞바꾸기: a = %d, b = %d\n", a, b);
}