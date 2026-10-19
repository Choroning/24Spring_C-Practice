/**
 * @file    Q4.c
 * @brief   Q4. 배열에서 값 찾기
 * @author  박철원 (Cheolwon Park)
 * @date    2026-10-19
 */

#include <stdio.h>
#define SIZE 10

int main()
{
	int arr[SIZE] = { 7, 3, 9, 3, 12, 5, 3, 8, 1, 9 };
	int key, count = 0;

	printf("배열의 내용:");
	for (int i = 0; i < SIZE; i++) {
		printf(" %d", arr[i]);
	}

	printf("\n>> 찾을 값: ");
	scanf(" %d", &key);

	for (int i = 0; i < SIZE; i++) {
		if (arr[i] == key) {
			if (count == 0)
				printf("-> 인덱스:");
			printf(" %d", i);
			count++;
		}
	}

	if (count > 0)
		printf("\n-> 개수: %d\n", count);
	else
		printf("-> 찾는 값이 배열에 없습니다.\n");
}
