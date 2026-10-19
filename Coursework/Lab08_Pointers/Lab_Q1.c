/**
 * @file    A10104-1_C08Q1.c
 * @brief   Q1. 2차원 평면 좌표 계산기
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-14
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>
#include <math.h>

void display_point(int x, int y);
void compute_distance(int x1, int y1, int x2, int y2);
void move_point(int *x, int *y, int move);

int main()
{
    int x1, x2, y1, y2, move;
    double distance;

    printf("p1 좌표 입력(x1, y1 좌표값 입력): ");
    scanf_s(" %d %d", &x1, &y1);
    
    printf("p2 좌표 입력(x2, y2 좌표값 입력): ");
    scanf_s(" %d %d", &x2, &y2);

    printf("p1 = ");
    display_point(x1, y1);

    printf("p2 = ");
    display_point(x2, y2);

    compute_distance(x1, y1, x2, y2);

    printf("좌표 이동량 입력: ");
    scanf_s(" %d", &move);

    move_point(&x2, &y2, move);

    printf("p2를 x축과 y축으로 각각 %d만큼 이동 = ", move);
    display_point(x2, y2);

    return 0;
}

void display_point(int x, int y)
{
    printf("(%d, %d)\n", x, y);
}

void compute_distance(int x1, int y1, int x2, int y2)
{
    double distance;
    distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    printf("두 점 사이의 거리 = %.5f\n\n", distance);
}

void move_point(int *x, int *y, int move)
{
    *x += move;
    *y += move;
}
