/**
 * @file    A10104-2_C05Q1.c
 * @brief   Q1. 정수의 합과 평균 계산
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-09
 * 
 * @note	소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 * 			IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
    int num = -1, sum1 = 0, count = 0;
    double ave = 0;
    
    while (1) {
        printf("정수 입력(종료: -1): ");
        scanf_s(" %d", &num);
        
        if (num == -1)
            break;
        else {
            sum1 = sum1 + num;
            count++;
        }
    }
    ave = (double)sum1 / count;
    printf("입력된 수의 합: %d\n", sum1);
    printf("입력된 수의 평균: %.2f\n", ave);

    return 0;
}
