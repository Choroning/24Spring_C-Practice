/**
 * @file    A10104-1_C04Q3.c
 * @brief   Q3. 4바이트 RGB값을 16진수 RGB값으로 변환
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-27
 *  
 * @note	소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 * 		IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
	int red, green, blue;
	int RGB = 0;

	printf("Red 값 입력(0~255): ");
	scanf_s(" %d", &red);
	printf("Green 값 입력(0~255): ");
	scanf_s(" %d", &green);
	printf("Blue 값 입력(0~255): ");
	scanf_s(" %d", &blue);

	RGB = red | green << 8 | blue << 16;

	/* 위와 동일한 과정
	RGB |= blue << 16;
	RGB |= green << 8;
	RGB |= red; */

	printf("RGB = %#08X", RGB);
}
