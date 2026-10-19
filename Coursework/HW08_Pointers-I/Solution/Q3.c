/**
 * @file    Q3.c
 * @brief   Q3. 세 수 정렬
 * @author  박철원 (Cheolwon Park)
 * @date    2026-10-19
 */

#include <stdio.h>

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void sort3(int* pa, int* pb, int* pc)
{
	if (*pa > *pb)
		swap(pa, pb);
	if (*pb > *pc)
		swap(pb, pc);
	if (*pa > *pb)
		swap(pa, pb);
}

int main()
{
	int x, y, z;

	printf("정수 3개 입력: ");
	scanf(" %d %d %d", &x, &y, &z);

	printf("정렬 전: x = %d, y = %d, z = %d\n", x, y, z);
	sort3(&x, &y, &z);
	printf("정렬 후: x = %d, y = %d, z = %d\n", x, y, z);
}
