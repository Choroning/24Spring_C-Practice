/**
 * @file    A10104-1_C5Q3.c
 * @brief   Q3. 이차 방정식의 근 계산
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-03
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>
#include <math.h>

int main()
{
    int a, b, c;
    double cal, ans1, ans2;

    printf("이차 방정식의 상관계수 a, b, c 입력: ");
    scanf_s(" %d %d %d", &a, &b, &c);

    cal = (b * b) - (4 * a * c);
    ans1 = (-b + sqrt(cal)) / (2 * a);
    ans2 = (-b - sqrt(cal)) / (2 * a);

    if (a) {  // a != 0일 때 이차 방정식으로 계산을 수행
        if (cal < 0)
            printf("입력하신 이차 방정식은 허근을 갖습니다.");
        else if (cal == 0)
            printf("입력하신 이차 방정식의 중근 x = %g입니다.", ans1);
        else
            printf("입력하신 이차 방정식의 해는 x1 = %g, x2 = %g입니다.", ans1, ans2);
    }
    else
        printf("입력 오류! a = 0일 때 이차 방정식이 성립하지 않습니다.");

    return 0;
}
