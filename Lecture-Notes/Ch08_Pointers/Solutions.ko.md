# 8장 연습 문제 풀이 — 포인터

[레포지토리 안내](../../README.ko.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **최종 수정일:** 2026-10-27

**문항 출처:** 임영희 교수, 컴퓨터언어Ⅰ (DCCS101-04)

---

<br>

## 목차

- [연습 문제 1: 2차원 평면 좌표 계산기](#연습-문제-1-2차원-평면-좌표-계산기)
- [연습 문제 2: 로또 프로그램](#연습-문제-2-로또-프로그램)

---

<br>

## 연습 문제 1: 2차원 평면 좌표 계산기

**문제:** 좌표를 출력하는 `display_point()`, 두 점 사이의 거리를 계산하여 반환하는 `compute_distance()`, 두 좌표값을 이동량만큼 바꾸는 `move_point()`를 정의하여 프로그램을 완성하라. 문제 전문과 실행 예시는 [연습 문제 1](Exercises.ko.md#연습-문제-1-2차원-평면-좌표-계산기)에 있다.

### 풀이

**접근 방법:** 함수가 인자의 값을 읽기만 하는지, 호출한 쪽의 변수를 바꿔야 하는지에 따라 전달 방식을 고른다([8장 3.3절](Concepts_Lecture.ko.md#33-여러-값-반환)).

- **`display_point()`:** x, y 값을 읽기만 하는 입력 매개변수이므로 값으로 받아 `(x, y)` 형태로 출력하고 줄을 바꾼다.
- **`compute_distance()`:** 네 좌표를 값으로 받아 `sqrt()`로 $\sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2}$를 계산한다. 제곱은 `int` 곱셈으로 계산한 뒤 `sqrt()`에 넘길 때 `double`로 변환된다. 이 코드는 함수를 `void`로 선언하여 계산한 거리를 함수 안에서 `%.5f`로 출력한다.
- **`move_point()`:** `main()`의 `x2`, `y2`를 바꿔야 하므로 두 좌표를 주소로 받는다(`int *x, int *y`). 함수 안에서 `*x += move;`, `*y += move;`로 원본을 수정하고, 호출할 때는 `move_point(&x2, &y2, move);`처럼 주소를 전달한다([8장 3.2절](Concepts_Lecture.ko.md#32-포인터를-통한-변수-수정)).

**코드:** [Lab_Q1.c](../../Coursework/Lab08_Pointers/Lab_Q1.c)

```c
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
```

**실행 결과:** `scanf_s`는 Visual Studio(MSVC)가 제공하는 함수로, C11 표준에서 선택 사항인 부록 K(Annex K)에 속하여 gcc와 clang의 표준 라이브러리에는 선언되어 있지 않다. 이 코드의 `scanf_s`는 정수(`%d`)만 읽으므로 `scanf`와 같게 동작하며, gcc나 clang에서는 `gcc -std=c99 -Wall -Dscanf_s=scanf Lab_Q1.c -lm`처럼 매크로를 정의하여 컴파일한다. 이때 `main()`의 지역 변수 `distance`를 사용하지 않는다는 경고가 하나 나온다. 실행 예시의 값을 입력한 결과는 다음과 같으며, 입력한 값도 터미널 화면처럼 함께 보인다.

```text
p1 좌표 입력(x1, y1 좌표값 입력): 1 1
p2 좌표 입력(x2, y2 좌표값 입력): 3 7
p1 = (1, 1)
p2 = (3, 7)
두 점 사이의 거리 = 6.32456

좌표 이동량 입력: -1
p2를 x축과 y축으로 각각 -1만큼 이동 = (2, 6)
```

```text
p1 좌표 입력(x1, y1 좌표값 입력): -2 4
p2 좌표 입력(x2, y2 좌표값 입력): 3 -5
p1 = (-2, 4)
p2 = (3, -5)
두 점 사이의 거리 = 10.29563

좌표 이동량 입력: 3
p2를 x축과 y축으로 각각 3만큼 이동 = (6, -2)
```

첫 번째 거리는 $\sqrt{2^2 + 6^2} = \sqrt{40} \approx 6.324555$, 두 번째 거리는 $\sqrt{5^2 + 9^2} = \sqrt{106} \approx 10.295630$이다. 출력 형식에는 세 가지 차이가 있다. 첫째, 입력 안내문이 `(x축, y축 좌표값 입력)` 대신 `(x1, y1 좌표값 입력)`, `(x2, y2 좌표값 입력)`이다. 둘째, 이동량 다음에 공백 없이 `만큼`이 붙는다. 셋째, 거리를 소수점 아래 다섯 자리(`%.5f`)로 출력하므로 두 번째 거리가 `10.2956` 대신 `10.29563`으로 나온다. 실행 예시의 거리는 유효 숫자 6자리로 출력한 값(`%g`의 기본 형식)이다. 실행 예시의 마지막 줄 `Program ended with exit code: 0`은 프로그램의 출력이 아니라 Xcode 콘솔이 덧붙이는 종료 메시지이다.

> **참고:** 요구사항은 `compute_distance()`가 거리를 반환하고 출력문을 두지 않도록 정했지만, 이 코드는 반환값 없이 함수 안에서 출력한다. 요구사항대로 작성하려면 `double compute_distance(int x1, int y1, int x2, int y2)`로 선언하여 `return sqrt(...);`로 거리를 돌려주고, `main()`에서 `distance = compute_distance(x1, y1, x2, y2);`로 받은 뒤 `printf`로 출력한다. 그러면 예시 코드에 선언된 `distance` 변수도 쓰이게 되어 경고가 사라진다.

> **주의:** `(x2 - x1) * (x2 - x1)`은 `int`로 계산하므로 좌표 차의 절댓값이 46341 이상이면 곱이 `int`의 최댓값($2^{31} - 1$)을 넘어 오버플로가 일어난다. 큰 좌표를 다루려면 `(double)(x2 - x1)`처럼 먼저 `double`로 변환하여 곱한다. 또한 `sqrt()`는 `<math.h>`에 선언된 수학 라이브러리 함수이므로, Linux의 gcc에서는 `-lm` 옵션으로 수학 라이브러리를 링크해야 한다.

---

<br>

## 연습 문제 2: 로또 프로그램

**문제:** 1~45 사이의 서로 다른 번호 6개를 무작위로 뽑아 오름차순으로 출력하는 로또 프로그램을 완성하라. 배열 출력 함수 `printArray()`는 포인터의 증가 연산으로, 중복 검사 함수 `existDuplication()`은 포인터의 색인화로, 선택 정렬 함수 `selectionSort()`는 포인터의 산술 연산과 `swap()` 호출로 구현한다. 문제 전문과 실행 예시는 [연습 문제 2](Exercises.ko.md#연습-문제-2-로또-프로그램)에 있다.

### 풀이

**접근 방법:** 세 함수가 같은 배열을 서로 다른 포인터 표기로 다룬다([8장 2절](Concepts_Lecture.ko.md#2-배열과-포인터)).

- **`printArray()`:** 매개변수 `const int p[]`는 실제로는 포인터 변수 `const int *p`이므로 증가시킬 수 있다. `*p++`는 현재 원소를 읽은 뒤 `p`를 다음 원소로 옮긴다. 각 번호를 `%2d`와 공백 두 칸으로 출력하여 열을 맞춘다.
- **`existDuplication()`:** 인덱스 쌍 `(i, j)`, `i < j`를 모두 `p[i] == p[j]`로 비교하고, 같은 값을 찾는 즉시 1을 반환한다. 끝까지 같은 값이 없으면 0을 반환한다. 원소가 6개이므로 비교는 최대 $6 \times 5 / 2 = 15$번이다.
- **`swap()`:** 두 정수의 주소를 받아 임시 변수로 값을 교환한다([8장 3.2절](Concepts_Lecture.ko.md#32-포인터를-통한-변수-수정)).
- **`selectionSort()`:** `i`번째 자리부터 끝까지에서 가장 작은 원소의 인덱스 `index_min`을 `*(p + index_min) > *(p + j)` 비교로 찾는다. `index_min`이 `i`와 다르면 `swap(p + i, p + index_min)`으로 두 원소를 교환한다. 이 과정을 `i = 0`부터 `size - 2`까지 반복하면 배열이 오름차순으로 정렬된다.
- **`main()`:** `do-while` 문은 번호 6개를 뽑은 뒤 `existDuplication(lotto, 6)`이 1을 반환하는 동안, 즉 중복이 있는 동안 다시 뽑는다. 중복이 없는 세트를 얻으면 정렬하여 출력한다.

**코드:** [Lab_Q2.c](../../Coursework/Lab08_Pointers/Lab_Q2.c)

```c
/**
 * @file    A10104-1_C08Q2.c
 * @brief   Q2. 로또 프로그램
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-14
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
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
```

**실행 결과:** 연습 문제 1과 같이 `-Dscanf_s=scanf`를 주어 `gcc -std=c99 -Wall`로 컴파일한다. 번호는 `srand(time(NULL))`로 정한 시드에 따라 실행할 때마다 달라진다. 5세트를 생성한 실행 결과의 한 예는 다음과 같다.

```text
몇 세트의 로또 번호를 생성할까요? 5
 4  21  28  31  35  45  
 9  15  17  24  25  45  
 4  12  23  39  40  42  
 5   7  12  15  31  45  
 9  13  18  22  36  39  

행운을 빕니다!
```

각 세트는 중복 없이 오름차순으로 정렬되어 있다. 안내문은 실행 예시의 `복권 번호` 대신 `로또 번호`이며, 각 번호 뒤에 공백 두 칸을 출력하므로 줄 끝에 공백이 남는다.

> **참고:** 6개를 독립적으로 뽑을 때 중복이 하나도 없을 확률은 $\frac{45 \times 44 \times 43 \times 42 \times 41 \times 40}{45^6} \approx 0.706$이다. 따라서 평균적으로 약 29%의 시도가 중복 때문에 다시 뽑히며, 세트 하나를 얻는 데 평균 약 1.42번 뽑는다. 또한 `rand() % 45`는 `RAND_MAX + 1`이 45의 배수가 아니면 작은 번호가 조금 더 자주 나오는 편향이 있지만, 이 프로그램의 용도에서는 무시할 만한 수준이다.
