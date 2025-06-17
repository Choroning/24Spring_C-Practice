/**
 * @file    A10104-1_C4Q2.c
 * @brief   Q2. 시간 - 초 환산
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-27
 *  
 * @note	소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 * 			IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#define SEC_PER_HOUR 3600
#define SEC_PER_MIN 60
#include <stdio.h>

int main()
{
	int hour, min, sec;
	int hour_cal, min_cal, sec_cal;
	int second_sum1, second_sum2;

	printf("시간을 차례로 입력하세요(시,분,초): ");
	scanf_s(" %d %d %d", &hour, &min, &sec);

	second_sum1 = hour * SEC_PER_HOUR + min * SEC_PER_MIN + sec;

	printf("%d시간 %d분 %d초는 총 %d초입니다. \n", hour, min, sec, second_sum1);
	printf("\n---------------------------------\n");

	printf("환산할 초를 입력하세요: ");
	scanf_s(" %d", &second_sum2);

	hour_cal = (second_sum2 / SEC_PER_HOUR);
	min_cal = (second_sum2 % SEC_PER_HOUR) / SEC_PER_MIN;
	sec_cal = (second_sum2 % SEC_PER_MIN);

	printf("%d초는 %d시간 %d분 %d초입니다. \n", second_sum2, hour_cal, min_cal, sec_cal);
}
