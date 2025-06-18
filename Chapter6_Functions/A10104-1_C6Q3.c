/**
 * @file    A10104-1_C6Q3.c
 * @brief   Q3. 월별 날짜 수 계산
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-17
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int GetDaysOfMonth(int detect, int month)
{
    if (month == 2)
        if (detect)
            return 29;
        else
            return 28;
    else
        switch (month) {
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
            return 31;
        }
}

int isLeapYear(int year)
{
    return ((year % 4) == 0) ? ((year % 100) == 0 ? ((year % 400) == 0 ? 1 : 0) : 1) : 0;
}

int main()
{
    int year, month, days;

    printf("연도와 월을 입력하세요: ");
    scanf_s(" %d %d", &year, &month);

    days = GetDaysOfMonth(isLeapYear(year), month);

    printf("%d년 %d월은 %d일까지 있습니다.", year, month, days);

    return 0;
}
