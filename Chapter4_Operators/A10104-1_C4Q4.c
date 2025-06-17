/**
 * @file    A10104-1_C4Q4.c
 * @brief   Q4. 16진수 RGB값을 4바이트 RGB값으로 변환
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-27
 *  
 * @note	소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 * 			IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
	int RGB = 0;
	int red, green, blue;

	printf("RGB 값을 입력(16진수 6자리): ");
	scanf_s(" %x", &RGB);

	red = (RGB & 0xFF);
    // AND 연산을 이용하여 0~7번째 비트(하위 8비트) 추출
    // 예: 00000000 00000000 11111111 => 0x0000FF => 255

    green = ((RGB >> 8) & 0xFF);
    // RGB를 오른쪽으로 8비트 시프트한 뒤
    // AND 연산으로 0~7번째 비트(녹색 정보) 추출

    blue = (RGB >> 16);
    // RGB를 오른쪽으로 16비트 시프트하여
    // 하위 8비트(파란색 정보)만 남김

	printf("\nRed    = %#04x (%d) \n", red, red);
	printf("Green  = %#04x (%d) \n", green, green);
	printf("Blue   = %#04x (%d) \n", blue, blue);
} 
