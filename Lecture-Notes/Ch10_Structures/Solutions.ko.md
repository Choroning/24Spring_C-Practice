# 10장 연습 문제 풀이 — 구조체

[레포지토리 안내](../../README.ko.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **최종 수정일:** 2026-11-27
>
> Warming-Up C Programming, 천정아, Ch 10

**문항 출처:** 연습 문제 1, 2는 임영희 교수, 컴퓨터언어Ⅰ (DCCS101-04)

---

<br>

## 목차

- [연습 문제 1: Student 구조체](#연습-문제-1-student-구조체)
- [연습 문제 2: Rectangle 구조체](#연습-문제-2-rectangle-구조체)
- [연습 문제 3: 구조체 정의의 오류 수정](#연습-문제-3-구조체-정의의-오류-수정)
- [연습 문제 4: 구조체 변수를 사용하는 코드의 오류](#연습-문제-4-구조체-변수를-사용하는-코드의-오류)
- [연습 문제 5: 비트 필드, 공용체, 열거체에 대한 설명](#연습-문제-5-비트-필드-공용체-열거체에-대한-설명)
- [연습 문제 6: 로그인 정보 구조체](#연습-문제-6-로그인-정보-구조체)
- [연습 문제 7: 공휴일 검사](#연습-문제-7-공휴일-검사)
- [연습 문제 8: 평균 이상인 학생 출력](#연습-문제-8-평균-이상인-학생-출력)

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

```c wide-ok
/**
 * @file    A10104-1_C10Q1.c
 * @brief   Q1. The Student Structure
 * @author  Cheolwon Park
 * @date    2024-06-13
 * 
 * @note    Note that scanf_s used in this source code may not run in IDEs
 *          other than Visual Studio.
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

```text wide-ok
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

```c wide-ok
/**
 * @file    A10104-1_C10Q2.c
 * @brief   Q2. The Rectangle Structure
 * @author  Cheolwon Park
 * @date    2024-06-14
 * 
 * @note    Note that scanf_s used in this source code may not run in IDEs
 *          other than Visual Studio.
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
    // Check that the upper-left and lower-right coordinates were entered correctly
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

```text wide-ok
사각형의 좌표를 입력하세요.
좌상단 좌표: 1 3
우하단 좌표: 7 10
y 좌표가 반대로 입력되어 서로 교환합니다.
사각형의 면적 = 42
```

```text wide-ok
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

---

<br>

## 연습 문제 3: 구조체 정의의 오류 수정

**교재 문항:** 10장 연습 문제 2번

**문제:** 문자 하나를 저장할 멤버 `gender`가 들어 있는 `employee` 구조체 정의에서 컴파일 오류가 나는 부분을 고쳐라. 코드는 [연습 문제 3](Exercises.ko.md#연습-문제-3-구조체-정의의-오류-수정)에 있다.

### 풀이

**정답:** 두 곳을 고친다. 멤버 `gender`에 데이터 타입이 없으므로 `char gender;`로 쓰고, 구조체 정의는 선언문이므로 닫는 중괄호 뒤에 세미콜론을 붙여 `};`로 끝낸다.

```c
struct employee {
    char name[20];
    char gender;            // a member needs a data type
    int salary;
    char department[20];
};                          // a structure definition ends with a semicolon
```

**해설:** 원래 코드를 Clang으로 컴파일하면 두 오류가 난다. 첫째 오류는 타입 없이 이름만 쓴 멤버를, 둘째 오류는 구조체 정의 뒤의 세미콜론 누락을 가리킨다([10장 1.2절](Concepts_Lecture.ko.md#12-구조체-정의)).

```text
error: type name requires a specifier or qualifier
error: expected ';' after struct
```

세미콜론이 빠지면 컴파일러는 다음 줄의 `int main(void)`까지를 이 구조체 정의의 일부로 읽으려 하므로, 오류가 정의의 끝이 아닌 다음 선언에서 보고되기도 한다.

---

<br>

## 연습 문제 4: 구조체 변수를 사용하는 코드의 오류

**교재 문항:** 10장 연습 문제 5번

**문제:** `contact` 구조체 변수 `c1`, `c2`를 사용하는 여섯 문장 가운데 컴파일 오류가 나는 것을 모두 고르라. 코드는 [연습 문제 4](Exercises.ko.md#연습-문제-4-구조체-변수를-사용하는-코드의-오류)에 있다.

### 풀이

**정답:** ②, ④, ⑤

**해설:** Clang은 세 문장에 차례로 다음 오류를 낸다.

```text
error: array type 'char[20]' is not assignable
error: expected expression
error: invalid operands to binary expression ('struct contact' and 'struct contact')
```

- ② `name`은 `char` 배열이므로 `=`로 문자열을 대입할 수 없다. `strcpy(c2.name, "Lee");`로 복사한다([10장 1.6절](Concepts_Lecture.ko.md#16-구조체-대입)).
- ④ 중괄호 초기화 리스트는 선언할 때만 쓸 수 있으므로, 이미 선언된 `c2`에 대입할 수 없다. 멤버를 하나씩 대입하거나, 같은 값을 가진 다른 구조체 변수를 대입한다.
- ⑤ 구조체에는 `==`를 쓸 수 없으므로 멤버별로 비교한다([10장 1.7절](Concepts_Lecture.ko.md#17-구조체-비교)).
- ①은 구조체 전체 대입이므로 배열 멤버까지 모두 복사되어 올바르고, ③은 `int` 멤버에 대한 대입이므로 올바르다. ⑥은 문자열 멤버를 `strcmp`로 비교하는 올바른 방법이다.

---

<br>

## 연습 문제 5: 비트 필드, 공용체, 열거체에 대한 설명

**교재 문항:** 10장 연습 문제 6번, 8번

**문제:** 비트 필드, 공용체, 열거체에 대한 여덟 가지 설명 가운데 잘못된 것을 모두 고르라. 보기는 [연습 문제 5](Exercises.ko.md#연습-문제-5-비트-필드-공용체-열거체에-대한-설명)에 있다.

### 풀이

**정답:** ③, ④, ⑦

**해설:** ③ 공용체의 멤버들은 같은 메모리를 나누어 쓰므로 공용체의 크기는 대개 가장 큰 멤버의 크기이고, 정렬 때문에 그보다 조금 커질 수 있을 뿐 멤버 크기의 합이 되지 않는다([10장 3.2절](Concepts_Lecture.ko.md#32-union)). ④ 비트 필드는 작은 범위의 멤버 여러 개를 한 정수 안에 모아 메모리를 줄이는 기능이다. 10장 2.6절의 날짜 비트 필드는 4바이트로, 같은 멤버를 `unsigned int` 세 개로 둔 12바이트보다 작았다. ⑦ 열거 상수는 정수형 상수이므로 실수를 값으로 줄 수 없다([10장 3.1절](Concepts_Lecture.ko.md#31-enum)). 나머지는 올바른 설명이다. 예를 들어 `enum color { RED, GREEN = 5, BLUE };`에서 값을 지정하지 않은 `RED`는 0이고, `BLUE`는 바로 앞의 `GREEN`보다 1 큰 6이다.

---

<br>

## 연습 문제 6: 로그인 정보 구조체

**교재 문항:** 10장 프로그래밍 과제 1번, 2번

**문제:** 아이디와 패스워드를 저장하는 `login_info` 구조체를 정의하고, 두 멤버를 소문자로 바꾸는 `normalize`와 패스워드를 `*`로 가려 출력하는 `print_login`을 작성하라. 실행 예시는 [연습 문제 6](Exercises.ko.md#연습-문제-6-로그인-정보-구조체)에 있다.

### 풀이

**접근 방법:** 최대 20글자에 널 문자 자리를 더해 두 멤버를 `char[21]`로 선언한다. 구조체를 바꾸는 `normalize`는 구조체 포인터로, 읽기만 하는 `print_login`은 `const` 구조체 포인터로 받는다. 소문자 변환은 문자열 하나를 처리하는 함수로 따로 만들어 두 멤버에 다시 쓴다.

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct login_info {
    char id[21];
    char password[21];
};

void to_lower_str(char *s)
{
    for (; *s != '\0'; s++)
        *s = (char)tolower((unsigned char)*s);
}

void normalize(struct login_info *info)
{
    to_lower_str(info->id);
    to_lower_str(info->password);
}

void print_login(const struct login_info *info)
{
    size_t i, n = strlen(info->password);

    printf("ID: %s\nPW: ", info->id);
    for (i = 0; i < n; i++)
        putchar('*');
    putchar('\n');
}

int main(void)
{
    struct login_info user;

    printf("ID? ");
    scanf("%20s", user.id);
    printf("Password? ");
    scanf("%20s", user.password);
    normalize(&user);
    print_login(&user);
    printf("stored: %s / %s\n", user.id, user.password);
    return 0;
}
```

- `scanf("%20s", user.id)`의 폭 20은 최대 20글자만 읽게 하여 21바이트 배열을 넘지 않게 한다. 배열 이름은 시작 주소이므로 `&`를 붙이지 않는다.
- `info->id`는 `(*info).id`와 같으며, `to_lower_str`가 그 배열의 문자를 직접 바꾸므로 `main`의 `user`가 바뀐다.
- `print_login`은 패스워드의 길이를 `strlen`으로 구해 그만큼 `*`를 출력하고, 패스워드 자체는 출력하지 않는다. `putchar`는 문자 하나를 출력하는 함수이다.

**실행 결과:**

```text
ID? Anonymous
Password? IDontKnow
ID: anonymous
PW: *********
stored: anonymous / idontknow
```

`IDontKnow`는 9글자이므로 `*`가 9개 출력된다.

---

<br>

## 연습 문제 7: 공휴일 검사

**교재 문항:** 10장 프로그래밍 과제 4번

**문제:** `date` 구조체와 두 날짜를 비교하는 `same_date`를 정의하고, 공휴일 배열에서 입력한 날짜를 찾아 결과를 출력하라. 실행 예시는 [연습 문제 7](Exercises.ko.md#연습-문제-7-공휴일-검사)에 있다.

### 풀이

**접근 방법:** 구조체는 `==`로 비교할 수 없으므로 `same_date`가 세 멤버를 모두 비교한다. 입력한 날짜를 공휴일 배열의 원소와 차례로 비교하는 순차 탐색으로 찾는다.

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct date {
    int year, month, day;
};

int same_date(struct date a, struct date b)
{
    return a.year == b.year && a.month == b.month && a.day == b.day;
}

int main(void)
{
    struct date holidays[] = {
        { 2024, 1, 1 }, { 2024, 3, 1 }, { 2024, 5, 5 }, { 2024, 6, 6 },
        { 2024, 8, 15 }, { 2024, 10, 3 }, { 2024, 10, 9 }, { 2024, 12, 25 }
    };
    int n = sizeof(holidays) / sizeof(holidays[0]);
    struct date d;
    int i, found;

    while (1) {
        printf("date? ");
        if (scanf("%d %d %d", &d.year, &d.month, &d.day) != 3)
            break;
        if (d.year == 0 && d.month == 0 && d.day == 0)
            break;
        found = 0;
        for (i = 0; i < n; i++) {
            if (same_date(d, holidays[i])) {
                found = 1;
                break;
            }
        }
        printf("%d/%d/%d is %sa holiday\n", d.year, d.month, d.day, found ? "" : "not ");
    }
    return 0;
}
```

- `same_date`는 관계식과 `&&`의 값 1 또는 0을 그대로 반환한다. 작은 구조체이므로 값으로 받아도 복사 비용이 작다.
- 배열의 크기를 생략하고 초기값으로 정한 뒤 `sizeof(holidays) / sizeof(holidays[0])`로 원소의 개수 8을 구하므로, 공휴일을 추가해도 `n`을 고칠 필요가 없다.
- `scanf`가 세 값을 읽지 못하면 반복을 끝내므로, 숫자가 아닌 입력으로 무한 반복에 빠지지 않는다(5장 3.8절).
- `found ? "" : "not "`은 조건 연산자로 출력할 문자열을 고르며, 찾지 못한 경우에만 `not `이 들어간다.

**실행 결과:**

```text
date? 2024 8 15
2024/8/15 is a holiday
date? 2024 5 2
2024/5/2 is not a holiday
date? 0 0 0
```

---

<br>

## 연습 문제 8: 평균 이상인 학생 출력

**문제:** 다섯 학생의 이름과 점수를 담은 구조체 배열에서 평균을 구하고, 평균 이상인 학생을 출력하라. 데이터와 실행 예시는 [연습 문제 8](Exercises.ko.md#연습-문제-8-평균-이상인-학생-출력)에 있다.

### 풀이

**접근 방법:** 평균을 알아야 비교할 수 있으므로 배열을 두 번 훑는다. 첫 번째 반복에서 합계를 구해 평균을 계산하고, 두 번째 반복에서 각 학생의 점수를 평균과 비교한다.

```c
#include <stdio.h>

struct student {
    char name[20];
    int score;
};

int main(void)
{
    struct student s[5] = {
        { "Kim", 82 }, { "Lee", 67 }, { "Park", 91 }, { "Choi", 74 }, { "Jung", 88 }
    };
    int i, n = 5, sum = 0;
    double avg;

    for (i = 0; i < n; i++)
        sum += s[i].score;
    avg = (double)sum / n;
    printf("average = %.1f\n", avg);
    for (i = 0; i < n; i++)
        if (s[i].score >= avg)
            printf("%s %d\n", s[i].name, s[i].score);
    return 0;
}
```

합계는 82 + 67 + 91 + 74 + 88 = 402이고 평균은 402 / 5 = 80.4이다. `s[i].score >= avg`에서 `int` 점수는 `double`로 변환되어 비교되므로, 평균이 80.4일 때 82, 91, 88이 조건을 만족한다. 평균을 `int`로 구하면 80이 되어 비교 기준이 달라지므로 `(double)`로 형 변환한다. `s[i].name`은 `[]`로 원소를 고른 뒤 `.`로 멤버를 고르는 순서이다.

**실행 결과:**

```text
average = 80.4
Kim 82
Park 91
Jung 88
```
