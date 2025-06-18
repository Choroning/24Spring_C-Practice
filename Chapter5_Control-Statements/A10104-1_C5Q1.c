/**
 * @file    A10104-1_C5Q1.c
 * @brief   Q1. 이차원 평면의 점 좌표 사분면 판별
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-02
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main(void)
{
    int posx, posy;

    // 사용자로부터 좌표를 입력받음
    printf("좌표 (x, y)? ");
    scanf_s(" %d %d", &posx, &posy);

    if (posx > 0) {
        if (posy > 0)
            printf("(%d, %d)는 제1사분면에 위치합니다.\n", posx, posy);
        else if (posy == 0)
            printf("(%d, %d)는 x축 위에 위치합니다.\n", posx, posy);
        else
            printf("(%d, %d)는 제4사분면에 위치합니다.\n", posx, posy);
    }
    else if (posx == 0) {
        if (posy > 0)
            printf("(%d, %d)는 y축 위에 위치합니다.\n", posx, posy);
        else if (posy == 0)
            printf("(%d, %d)는 원점에 위치합니다.\n", posx, posy);
        else
            printf("(%d, %d)는 y축 아래에 위치합니다.\n", posx, posy);
    }
    else {  // posx < 0
        if (posy > 0)
            printf("(%d, %d)는 제2사분면에 위치합니다.\n", posx, posy);
        else if (posy == 0)
            printf("(%d, %d)는 x축 위에 위치합니다.\n", posx, posy);
        else
            printf("(%d, %d)는 제3사분면에 위치합니다.\n", posx, posy);
    }

    return 0;
}
