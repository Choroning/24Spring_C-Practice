/**
 * @file    A10104-1_C8Q2.c
 * @brief   Q2. 로또 프로그램
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-14
 * 
 * @note	소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 * 		IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(const int p[], int size);
int existDuplication(const int p[], int size);
void swap(int* p, int* q);
void selectionSort(int p[], int size);

int main()
{
    int lotto[6], setNo;

    srand((unsigned int)time(NULL));
    printf("몇 세트의 로또 번호를 생성할까요? ");
    scanf_s(" %d", &setNo);

    for (int k = 0; k < setNo; k++) {
        do {
            for (int i = 0; i < 6; i++) {
                lotto[i] = rand() % 45 + 1;
            }
        } while (existDuplication(lotto, 6));
        selectionSort(lotto, 6);
        printArray(lotto, 6);
    }
    printf("\n행운을 빕니다!\n");
    return 0;
}

void printArray(const int p[], int size)
{
    for (int i = 0; i < size; i++) {
        printf("%2d  ", *p++);
    }
    printf("\n");
}

int existDuplication(const int p[], int size)
{
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (p[i] == p[j])
                return 1;
        }
    }
    return 0;
}

void swap(int* p, int* q)
{
    int temp;
    temp = *p;
    *p = *q;
    *q = temp;
}

void selectionSort(int p[], int size)
{
    int index_min, i, j;

    for (i = 0; i < size - 1; i++) {
        index_min = i;
        for (j = i + 1; j < size; j++) {
            if (*(p + index_min) > *(p + j)) {
                index_min = j;
            }
        }
        if (index_min != i) {
            swap((p + i), (p + index_min));
        }
    }
}
