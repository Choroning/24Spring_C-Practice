/**
 * @file    A10104-1_C10Q2.c
 * @brief   Q2. Rectangle 구조체
 * @author  박철원 (Cheolwon Park)
 * @date    2024-06-14
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

typedef struct point {
    int x, y;
} Point;

typedef struct rectangle {
    Point leftUp;
    Point rightDown;
} Rect;

int isRectangle(Rect* r);
int computeArea(const Rect* p);

int main()
{
    Rect rect;

    printf("사각형의 좌표를 입력하세요.\n");
    while (1) {
        printf("좌상단 좌표: ");
        scanf_s(" %d %d", &rect.leftUp.x, &rect.leftUp.y);
        printf("우하단 좌표: ");
        scanf_s(" %d %d", &rect.rightDown.x, &rect.rightDown.y);

        if (isRectangle(&rect)) {
            int area = computeArea(&rect);
            printf("사각형의 면적 = %d\n\n", area);
            break;
        }
        else {
            printf("입력 오류! 입력한 좌표로는 사각형을 만들 수 없습니다.\n\n");
        }
    }

    return 0;
}

int isRectangle(Rect* r) {
    // 좌상단과 우하단 좌표가 올바르게 입력되었는지 확인
    if ((r->leftUp.x < r->rightDown.x) && (r->leftUp.y > r->rightDown.y))
        return 1;
    else if ((r->leftUp.x > r->rightDown.x) && (r->leftUp.y > r->rightDown.y)) {
        printf("x 좌표가 반대로 입력되어 서로 교환합니다.\n");
        int temp = r->leftUp.x;
        r->leftUp.x = r->rightDown.x;
        r->rightDown.x = temp;
        return 1;
    }
    else if ((r->leftUp.x < r->rightDown.x) && (r->leftUp.y < r->rightDown.y)) {
        printf("y 좌표가 반대로 입력되어 서로 교환합니다.\n");
        int temp = r->leftUp.y;
        r->leftUp.y = r->rightDown.y;
        r->rightDown.y = temp;
        return 1;
    }
    else if ((r->leftUp.x > r->rightDown.x) && (r->leftUp.y < r->rightDown.y)) {
        printf("반대로 입력된 좌상단 좌표와 우하단 좌표를 서로 교환합니다.\n");
        Point temp = r->leftUp;
        r->leftUp = r->rightDown;
        r->rightDown = temp;
        return 1;
    }
    else
        return 0;
}

int computeArea(const Rect* p) {
    int width = p->rightDown.x - p->leftUp.x;
    int height = p->leftUp.y - p->rightDown.y;

    if ((width * height) < 0)
        return -width * height;
    else
        return width * height;
}
