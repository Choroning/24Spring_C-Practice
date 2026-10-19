/**
 * @file    A10104-1_C10Q1.c
 * @brief   Q1. Student 구조체
 * @author  박철원 (Cheolwon Park)
 * @date    2024-06-13
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#pragma warning(disable:4996)
#pragma warning(disable:6031)
#include <stdio.h>
#include <string.h>
#define MAX_STD 20

struct student {
    char name[20];
    int kor, eng, math;
    double avg;
    int rank;
};

void input_student(struct student* p);
void display_student_arr(const struct student p[], int size);
void swap_student(struct student* p1, struct student* p2);
void sort_student_arr(struct student p[], int size);

int main() {
    struct student classA[MAX_STD];
    int size;

    printf("A반 학생 수를 입력하세요: ");
    scanf_s("%d", &size);

    for (int i = 0; i < size; i++) {
        input_student(&classA[i]);
    }

    sort_student_arr(classA, size);
    display_student_arr(classA, size);

    return 0;
}

void input_student(struct student* p) {
    printf("\n이름을 입력하세요: ");
    scanf("%s", p->name);

    printf("국어 점수: ");
    scanf("%d", &p->kor);

    printf("영어 점수: ");
    scanf("%d", &p->eng);

    printf("수학 점수: ");
    scanf("%d", &p->math);

    p->avg = (p->kor + p->eng + p->math) / 3.0;
}

void display_student_arr(const struct student p[], int size) {
    printf("--------------------------------------------------------\n");
    printf("   이름        국어   영어   수학     평균     등수\n");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < size; i++)
        printf(" %-10s   %3d   %3d   %3d   %6.2f   %2d\n",
               p[i].name, p[i].kor, p[i].eng, p[i].math, p[i].avg, p[i].rank);
}

void swap_student(struct student* p1, struct student* p2) {
    struct student temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void sort_student_arr(struct student p[], int size) {
    int i, j, index_min;

    for (i = 0; i < size - 1; i++) {
        index_min = i;
        for (j = i + 1; j < size; j++) {
            if (p[index_min].avg < p[j].avg)
                index_min = j;
        }
        if (i != index_min) {
            swap_student(&p[i], &p[index_min]);
        }
    }
    for (i = 0; i < size; i++)
        p[i].rank = i + 1;
}
