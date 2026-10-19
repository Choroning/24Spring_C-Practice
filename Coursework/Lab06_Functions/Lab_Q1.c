/**
 * @file    A10104-1_C06Q1.c
 * @brief   Q1. 실수 반올림
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-16
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int round_value(double value)
{
    if (value > 0) {
        value += 0.5;
    }
    else {
        value -= 0.5;
    }
    return (int)value;
}

int main()
{
    double num;
    
    do {
        printf("실수를 입력하세요 (0.0 입력 시 종료) : ");
        scanf_s(" %lf", &num);

        if (num == 0.0)
            break;
        else
            printf("%lf의 반올림 결과 = %d\n\n", num, round_value(num));
    } while (1);

    return 0;
}
