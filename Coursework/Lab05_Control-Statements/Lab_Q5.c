/**
 * @file    A10104-2_C05Q2.c
 * @brief   Q2. 삼각형 출력 메뉴
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-10
 * 
 * @note    <windows.h> 헤더는 Windows 이외의 개발환경에서
 *          오류가 발생할 수 있음에 주의하시기 바랍니다.
 */

#pragma warning(disable:4996)
#include <stdio.h>
#include <windows.h>    // system 함수를 사용하기 위해 추가

int main()
{
    int size, i, j;
    char menu;

    while (1) {
        printf("-------------------------------\n");
        printf("1. 왼쪽 정렬 삼각형 출력\n");
        printf("2. 오른쪽 정렬 삼각형 출력\n");
        printf("3. 왼쪽 정렬 역삼각형 출력\n");
        printf("4. 오른쪽 정렬 역삼각형 출력\n");
        printf("5. 종료\n");
        printf("-------------------------------\n");

        do {
            printf("=> 메뉴 선택: ");
            scanf(" %c", &menu);
            if (menu < '1' || menu > '5')
                printf("입력 오류! 메뉴를 다시 선택하세요. \n");
            else
                break;
        } while (1);

        if (menu == '5') {
            printf("프로그램을 종료합니다. \n");
            break;
        }

        printf("=> 삼각형 크기(line 수) 입력: ");
        scanf(" %d", &size);

        switch (menu) {
        case '1':
            for (i = 1; i <= size; i++) {
                for (j = 1; j <= i; j++)
                    printf("*");
                printf("\n");
            }
            break;
        case '2':
            for (i = 1; i <= size; i++) {
                for (j = size - i; j >= 1; j--)
                    printf(" ");
                for (j = 1; j <= i; j++)
                    printf("*");
                printf("\n");
            }
            break;
        case '3':
            for (i = 1; i <= size; i++) {
                for (j = size - i; j >= 0; j--)
                    printf("*");
                printf("\n");
            }
            break;
        case '4':
            for (i = 1; i <= size; i++) {
                for (j = 1; j <= i; j++)
                    printf(" ");
                for (j = size - i; j >= 0; j--)
                    printf("*");
                printf("\n");
            }
            break;
        }

        system("pause");
        system("cls");
    }

    return 0;
}
