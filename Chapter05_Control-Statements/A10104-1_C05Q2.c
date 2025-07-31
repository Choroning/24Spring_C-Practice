/**
 * @file    A10104-1_C05Q2.c
 * @brief   Q2. 섭씨 ↔ 화씨 단위 변환
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-02
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 * 		    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
    int temp = 0;
    char tempal = 0;
    double cel = 0, far = 0;

    printf("온도? ");
    scanf_s(" %d %c", &temp, &tempal);

    switch (tempal) {
    case 67:  // 'C'
    case 99:  // 'c'
        //cel = temp;
        far = (double)temp * 9 / 5 + 32;
        printf("%.0lf C == %.2lf F", (double)temp, far);
        break;
    case 70:  // 'F'
    case 102: // 'f'
        //far = temp;
        cel = ((double)temp - 32) * 5 / 9;
        printf("%.0lf F == %.2lf C", (double)temp, cel);
        break;
    default:
        printf("입력 오류! 온도 단위는 C(혹은 c)와 F(혹은 f)만 허용됩니다.");
        break;
    }

    return 0;
}
