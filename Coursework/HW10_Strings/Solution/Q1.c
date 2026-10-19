/**
 * @file    Q1.c
 * @brief   Q1. 중위수 구하기
 * @author  박철원 (Cheolwon Park)
 * @date    2026-10-19
 */

#include <stdio.h>

void sortArr(int arr[], int n)
{
	for (int i = 0; i < n - 1; i++) {
		int minIdx = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[minIdx])
				minIdx = j;
		}
		int tmp = arr[i];
		arr[i] = arr[minIdx];
		arr[minIdx] = tmp;
	}
}

double getMedian(int arr[], int n)
{
	if (n % 2 == 1)
		return arr[n / 2];
	else
		return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
}

void printArr(const char* name, int arr[], int n)
{
	printf("%s:", name);
	for (int i = 0; i < n; i++)
		printf(" %d", arr[i]);
	printf("\n");
}

int main()
{
	int vOne[] = { 15, 18, 10, 4, 27 };
	int vTwo[] = { 2, -4, 6, 9, 21, 44 };
	int nOne = sizeof(vOne) / sizeof(vOne[0]);
	int nTwo = sizeof(vTwo) / sizeof(vTwo[0]);

	printArr("vOne", vOne, nOne);
	sortArr(vOne, nOne);
	printArr("Sorted vOne", vOne, nOne);
	printf("Median of vOne: %.1f\n\n", getMedian(vOne, nOne));

	printArr("vTwo", vTwo, nTwo);
	sortArr(vTwo, nTwo);
	printArr("Sorted vTwo", vTwo, nTwo);
	printf("Median of vTwo: %.1f\n", getMedian(vTwo, nTwo));
}
