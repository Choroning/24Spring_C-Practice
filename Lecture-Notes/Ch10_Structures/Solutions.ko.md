# 10장 연습 문제 풀이 — 구조체

[레포지토리 안내](../../README.ko.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **최종 수정일:** 2026-10-27

**문항 출처:** 임영희 교수, 컴퓨터언어Ⅰ (DCCS101-04)

---

<br>

## 목차

- [연습 문제 1: Student 구조체](#연습-문제-1-student-구조체)
- [연습 문제 2: Rectangle 구조체](#연습-문제-2-rectangle-구조체)

---

<br>

## 연습 문제 1: Student 구조체

**문제:** 이름, 국어, 영어, 수학 점수, 평균, 등수를 멤버로 갖는 `student` 구조체에 대해, 학생 정보를 입력받고 평균을 계산하는 `input_student()`, 배열 전체를 표로 출력하는 `display_student_arr()`, 두 학생을 교환하는 `swap_student()`, 평균의 내림차순으로 정렬하며 등수를 매기는 `sort_student_arr()`를 정의하라. 문제 전문과 실행 예시는 [연습 문제 1](Exercises.ko.md#연습-문제-1-student-구조체)에 있다.

### 풀이

**접근 방법:** 구조체를 변경하는 함수는 구조체 포인터로, 읽기만 하는 함수는 `const` 구조체 배열로 받는다([10장 2.3절](Concepts_Lecture.ko.md#23-함수에-구조체-전달)).

- **`input_student()`:** 포인터 `p`가 가리키는 학생의 멤버에 `->`로 접근한다. `p->name`은 배열이므로 `scanf("%s", p->name)`에 `&`를 붙이지 않고, 정수 멤버는 `&p->kor`처럼 주소를 전달한다. 평균은 세 점수의 합을 `3.0`으로 나누어 `double` 나눗셈으로 계산한다. `3`으로 나누면 정수 나눗셈이 되어 소수점 아래가 버려진다.
- **`display_student_arr()`:** 머리글 세 줄을 출력한 뒤 각 학생을 `%-10s`(왼쪽 정렬 이름), `%3d`(점수), `%6.2f`(평균), `%2d`(등수) 형식으로 한 줄씩 출력한다. 출력만 하므로 매개변수가 `const struct student p[]`이다.
- **`swap_student()`:** 같은 구조체형의 임시 변수 `temp`에 `*p1`을 대입하고, `*p1 = *p2;`, `*p2 = temp;`로 두 구조체를 통째로 교환한다. 구조체 대입은 배열 멤버 `name`까지 모두 복사한다([10장 1.6절](Concepts_Lecture.ko.md#16-구조체-대입)).
- **`sort_student_arr()`:** 선택 정렬로 `i`번째 자리부터 끝까지에서 평균이 가장 큰 학생의 인덱스를 찾아(`p[index_min].avg < p[j].avg`이면 갱신) `i`번째 학생과 교환한다. 변수 이름은 `index_min`이지만 실제로는 최댓값의 인덱스를 저장한다. 정렬이 끝나면 앞에서부터 `rank`에 1, 2, 3, ...을 매긴다.
- **`main()`:** `input_student(&classA[i])`로 각 원소의 주소를 전달한다. 예시 코드의 `classA + i`와 같은 주소이다.

**코드:** [Lab_Q1.c](../../Coursework/Lab10_Structures/Lab_Q1.c)

```c
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
```

**실행 결과:** `#pragma warning(disable:4996)`과 `#pragma warning(disable:6031)`은 Visual Studio의 경고 C4996(`scanf` 같은 보안 위험 함수 사용)과 C6031(반환값 무시)을 끄는 MSVC 전용 지시문이다. `gcc -std=c99 -Wall -Dscanf_s=scanf Lab_Q1.c`로 컴파일하면 이 두 `#pragma`를 알 수 없다는 경고가 나오지만 실행에는 영향이 없다. 실행 예시의 값을 입력한 결과는 다음과 같다.

```text
A반 학생 수를 입력하세요: 5

이름을 입력하세요: 김ㅇㅇ
국어 점수: 53
영어 점수: 41
수학 점수: 37

이름을 입력하세요: 이ㅇㅇ
국어 점수: 97
영어 점수: 84
수학 점수: 87

이름을 입력하세요: 박ㅇㅇ
국어 점수: 64
영어 점수: 88
수학 점수: 71

이름을 입력하세요: 최ㅇㅇ
국어 점수: 37
영어 점수: 98
수학 점수: 100

이름을 입력하세요: 정ㅇㅇ
국어 점수: 67
영어 점수: 89
수학 점수: 76
--------------------------------------------------------
   이름        국어   영어   수학     평균     등수
--------------------------------------------------------
 이ㅇㅇ     97    84    87    89.33    1
 최ㅇㅇ     37    98   100    78.33    2
 정ㅇㅇ     67    89    76    77.33    3
 박ㅇㅇ     64    88    71    74.33    4
 김ㅇㅇ     53    41    37    43.67    5
```

이ㅇㅇ의 평균은 (97 + 84 + 87) / 3 = 268 / 3 ≈ 89.33이고, 김ㅇㅇ의 평균은 131 / 3 ≈ 43.67이다. 안내문(`A반 학생 수를 입력하세요:`, `이름을 입력하세요:`, `국어 점수:` 등)과 표의 구분선 길이, 열 간격은 실행 예시와 다르며, 마지막 학생을 입력한 뒤 표 앞에 빈 줄이 없다. 또한 `%-10s`는 화면 폭이 아니라 바이트 수로 폭을 맞추는데, UTF-8에서 한글 한 글자는 3바이트이므로 `이ㅇㅇ`(9바이트) 뒤에는 공백이 한 칸만 채워진다. 한글을 2바이트로 저장하는 Windows 콘솔(CP949)에서는 같은 코드라도 열의 위치가 달라진다.

> **주의:** `size`가 `MAX_STD`(20)보다 크면 `classA` 배열의 범위를 넘어 쓰게 되므로, 입력받은 `size`가 1 이상 `MAX_STD` 이하인지 검사하는 것이 안전하다. 또 `scanf("%s", p->name)`은 길이 제한이 없으므로 `%19s`처럼 너비를 지정해야 19바이트를 넘는 이름(UTF-8 한글 7글자 이상)으로 인한 오버플로를 막을 수 있다. 평균이 같은 학생들은 공동 등수가 아니라 정렬된 위치에 따라 서로 다른 등수를 받는다.

---

<br>

## 연습 문제 2: Rectangle 구조체

**문제:** 좌상단 점과 우하단 점으로 정의한 사각형 구조체 `Rect`에 대해, 두 점이 사각형을 이루는지 검사하는 `isRectangle()`과 면적을 반환하는 `computeArea()`를 작성하고, 사각형이 성립할 때까지 좌표를 다시 입력받아 면적을 출력하는 프로그램을 완성하라. 문제 전문과 실행 예시는 [연습 문제 2](Exercises.ko.md#연습-문제-2-rectangle-구조체)에 있다.

### 풀이

**접근 방법:** 두 점이 사각형을 이루려면 두 점의 x 좌표가 서로 다르고 y 좌표도 서로 달라야 한다. x 좌표나 y 좌표 중 하나라도 같으면 넓이가 0인 선분이나 점이 된다. 이 코드는 y축이 위로 갈수록 커지는 수학 좌표계를 기준으로, 좌상단 점은 x가 작고 y가 크며 우하단 점은 x가 크고 y가 작다고 본다.

- **`isRectangle()`:** 두 점의 관계를 네 경우로 나눈다. (1) 좌상단과 우하단이 올바르게 입력되었으면 1을 반환한다. (2) x 좌표만 반대이면 두 점의 x 좌표를 교환하고, (3) y 좌표만 반대이면 y 좌표를 교환하고, (4) 두 점이 모두 반대이면 두 점을 통째로 교환한 뒤 각각 안내문을 출력하고 1을 반환한다. 네 경우 중 어디에도 해당하지 않는 경우, 즉 x 좌표가 같거나 y 좌표가 같으면 0을 반환한다. 좌표를 교환하여 호출한 쪽의 `rect`를 바꿔야 하므로 매개변수를 `Rect* r` 포인터로 받는다.
- **`computeArea()`:** 너비 `rightDown.x - leftUp.x`와 높이 `leftUp.y - rightDown.y`를 곱한다. 곱이 음수이면 부호를 바꿔 반환한다. `isRectangle()`이 좌표를 정규화한 뒤에 호출되므로 실제로는 항상 양수이다.
- **`main()`:** 무한 반복 안에서 두 점을 입력받고, `isRectangle(&rect)`가 1이면 면적을 출력하고 `break`로 빠져나오며, 0이면 오류 메시지를 출력하고 다시 입력받는다.

**코드:** [Lab_Q2.c](../../Coursework/Lab10_Structures/Lab_Q2.c)

```c
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
```

**실행 결과:** 두 실행 예시의 값을 입력한 결과는 다음과 같다.

```text
사각형의 좌표를 입력하세요.
좌상단 좌표: 1 3
우하단 좌표: 7 10
y 좌표가 반대로 입력되어 서로 교환합니다.
사각형의 면적 = 42
```

```text
사각형의 좌표를 입력하세요.
좌상단 좌표: -2 5
우하단 좌표: 7 5
입력 오류! 입력한 좌표로는 사각형을 만들 수 없습니다.

좌상단 좌표: 1 10
우하단 좌표: 1 -4
입력 오류! 입력한 좌표로는 사각형을 만들 수 없습니다.

좌상단 좌표: -2 5
우하단 좌표: 4 -1
사각형의 면적 = 36
```

(-2, 5)와 (7, 5)는 y 좌표가 같고, (1, 10)과 (1, -4)는 x 좌표가 같아 사각형이 아니며, (-2, 5)와 (4, -1)은 너비 6, 높이 6이므로 면적이 36이다. 첫 번째 실행은 면적이 (7 - 1) × (10 - 3) = 42이고, 실행 예시에 없는 `y 좌표가 반대로 입력되어 서로 교환합니다.`라는 줄이 더 출력된다. 첫 번째 실행 예시는 y축이 아래로 갈수록 커지는 화면 좌표계처럼 좌상단의 y(3)가 우하단의 y(10)보다 작고, 두 번째 실행 예시는 좌상단의 y(5)가 우하단의 y(-1)보다 커서 두 예시의 좌표계가 서로 다르다. 이 코드는 수학 좌표계를 기준으로 하되 어느 쪽으로 입력해도 좌표를 정규화하므로 두 예시의 면적을 모두 올바르게 구한다.

> **참고:** **요구사항과의 차이.** 요구사항은 `int isRectangle(Rect r);`의 원형을 바꾸지 말라고 했지만, 이 코드는 좌표를 교환하여 원본을 정규화하려고 `int isRectangle(Rect* r);`로 바꾸었고, 검사 함수 안에서 안내문도 출력한다. 원형을 지키려면 `isRectangle()`은 값으로 받은 `r`에 대해 `r.leftUp.x != r.rightDown.x && r.leftUp.y != r.rightDown.y`만 반환하고, `computeArea()`에서 너비와 높이의 절댓값을 곱하면 된다. 이렇게 하면 어느 좌표계로 입력해도 면적이 같고, 첫 번째 실행에서 안내문 없이 실행 예시와 같은 결과가 나온다.

> **주의:** 숫자가 아닌 값을 입력하면 `scanf`가 실패하고 입력 버퍼에 그 문자가 남으므로, 반복할 때마다 같은 문자에서 다시 실패하여 무한 반복에 빠진다. `scanf`의 반환값이 2인지 확인하고, 실패하면 남은 입력을 줄 끝까지 버리는 처리가 필요하다. 또한 너비와 높이의 곱은 `int`로 계산하므로 좌표가 매우 크면 오버플로가 일어날 수 있다.
