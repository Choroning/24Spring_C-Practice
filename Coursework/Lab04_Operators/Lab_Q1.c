/**
 * @file    A10104-1_C04Q1.c
 * @brief   Q1. 헬멧의 체적과 표면적 계산
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-26
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 * 	    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>
#define PI 3.14159265

int main()
{
	int height, base_radius;
	double volume, surface_area;

	printf("헬멧의 높이: ");
	scanf_s(" %d", &height);

	printf("base 반지름 입력: ");
	scanf_s(" %d", &base_radius);

	volume = (PI / 6.0 * height) * (3 * base_radius * base_radius + height * height);
	surface_area = 2.0 * PI * ((height / 3.0) + (volume / (PI * height * height))) * height;

	printf("헬멧의 체적: %lf \n", volume);
	printf("헬멧의 표면적: %lf \n", surface_area);
}
