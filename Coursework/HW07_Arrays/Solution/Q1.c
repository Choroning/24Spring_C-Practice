/**
 * @file    A10303-1_C07Q1.c
 * @brief   Q1. 평균과 표준편차 구하기
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-10
 */

#include <stdio.h>
#include <math.h>

int main()
{
	double arr_num[10], sum = 0, ave, Dev = 0, stdDev;

	for (int i = 0; i < 10; i++) {
		printf(">> Input data (%d): ", i + 1);
		scanf(" %lf", &arr_num[i]);
		sum += arr_num[i];
	}
	printf("배열의 내용: ");

	for (int i = 0; i < 10; i++) {
		printf("%.1f ", arr_num[i]);
	}
	ave = sum / 10;
	printf("\n-> 평균: %.2f", ave);

	for (int i = 0; i < 10; i++) {
		Dev += (arr_num[i] - ave)*(arr_num[i] - ave);
	}
	stdDev = sqrt(Dev / 10);
	printf("\n-> 표준편차: %.2f", stdDev);
}