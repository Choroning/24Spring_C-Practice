# 8장 연습 문제 풀이 — 포인터

[레포지토리 안내](../../README.ko.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **최종 수정일:** 2026-11-27
>
> Warming-Up C Programming, 천정아, Ch 8

**문항 출처:** 연습 문제 1, 2는 임영희 교수, 컴퓨터언어Ⅰ (DCCS101-04)

---

<br>

## 목차

- [연습 문제 1: 2차원 평면 좌표 계산기](#연습-문제-1-2차원-평면-좌표-계산기)
- [연습 문제 2: 로또 프로그램](#연습-문제-2-로또-프로그램)
- [연습 문제 3: 포인터의 선언과 초기화](#연습-문제-3-포인터의-선언과-초기화)
- [연습 문제 4: 포인터 연산의 결과](#연습-문제-4-포인터-연산의-결과)
- [연습 문제 5: `const` 포인터와 컴파일 오류](#연습-문제-5-const-포인터와-컴파일-오류)
- [연습 문제 6: 증감과 역참조의 실행 결과](#연습-문제-6-증감과-역참조의-실행-결과)
- [연습 문제 7: 합계와 평균을 구하는 함수](#연습-문제-7-합계와-평균을-구하는-함수)
- [연습 문제 8: 최솟값, 최댓값과 포인터로 배열 뒤집기](#연습-문제-8-최솟값-최댓값과-포인터로-배열-뒤집기)

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

```c wide-ok
/**
 * @file    A10104-1_C08Q1.c
 * @brief   Q1. 2D Plane Coordinate Calculator
 * @author  Cheolwon Park
 * @date    2024-05-14
 * 
 * @note    Note that scanf_s used in this source code may not run in IDEs
 *          other than Visual Studio.
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

```text wide-ok
p1 좌표 입력(x1, y1 좌표값 입력): 1 1
p2 좌표 입력(x2, y2 좌표값 입력): 3 7
p1 = (1, 1)
p2 = (3, 7)
두 점 사이의 거리 = 6.32456

좌표 이동량 입력: -1
p2를 x축과 y축으로 각각 -1만큼 이동 = (2, 6)
```

```text wide-ok
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

```c wide-ok
/**
 * @file    A10104-1_C08Q2.c
 * @brief   Q2. Lotto Program
 * @author  Cheolwon Park
 * @date    2024-05-14
 * 
 * @note    Note that scanf_s used in this source code may not run in IDEs
 *          other than Visual Studio.
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

```text wide-ok
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

---

<br>

## 연습 문제 3: 포인터의 선언과 초기화

**교재 문항:** 8장 연습 문제 3번

**문제:** 일곱 가지 포인터의 선언과 초기화 가운데 잘못된 것을 고르고 이유를 쓰라. 보기는 [연습 문제 3](Exercises.ko.md#연습-문제-3-포인터의-선언과-초기화)에 있다.

### 풀이

**정답:** ③, ⑥, ⑦

**해설:** 포인터에는 같은 타입 변수의 주소나 널 포인터만 넣는다([8장 1.7절](Concepts_Lecture.ko.md#17-포인터-사용-시-주의-사항)). ①과 ②는 널 포인터로 초기화하며, 정수 상수 0은 널 포인터로 바뀌므로 둘 다 올바르다. ④는 `int` 변수의 주소, ⑤는 배열 이름인 첫 원소의 주소이므로 올바르다. 잘못된 세 선언에 대해 Clang은 다음과 같이 진단한다.

```text
error: incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
error: initializing 'double *' with an expression of incompatible type 'double'; take the address with &
warning: incompatible pointer types initializing 'short *' with an expression of type 'int *' [-Wincompatible-pointer-types]
```

③은 0이 아닌 정수를 절대 주소로 넣으려 한 것이고, ⑥은 `&` 없이 `double` 값 자체를 넣으려 한 것이다. ⑦은 `int` 변수를 `short*`로 가리키므로, 역참조하면 4바이트 변수의 일부 2바이트만 `short`로 해석하게 된다.

---

<br>

## 연습 문제 4: 포인터 연산의 결과

**교재 문항:** 8장 연습 문제 5번

**문제:** 주소가 `0x100`인 `int` 배열 `{2, 4, 6, 8}`을 가리키는 포인터로 만든 여섯 수식의 값을 구하라. 수식은 [연습 문제 4](Exercises.ko.md#연습-문제-4-포인터-연산의-결과)에 있다.

### 풀이

**정답:** ① 2, ② `0x108`, ③ 6, ④ 8, ⑤ 3, ⑥ 4

**해설:** `ptr + n`은 n바이트가 아니라 원소 n개만큼, 즉 `n * sizeof(int)`바이트만큼 떨어진 주소이다([8장 2.1절](Concepts_Lecture.ko.md#21-포인터-연산)). 따라서 ② `ptr + 2`는 0x100 + 2 × 4 = 0x108이고, ③ `*(ptr + 2)`는 그 주소의 원소 `arr[2]` = 6이다. ④ `ptr[3]`은 `*(ptr + 3)`과 같으므로 `arr[3]` = 8이다. ⑤는 괄호 때문에 `*ptr`을 먼저 구한 2에 1을 더한 3이며 배열은 바뀌지 않는다. ⑥은 `arr[1]` = 4이다.

---

<br>

## 연습 문제 5: `const` 포인터와 컴파일 오류

**교재 문항:** 8장 연습 문제 6번

**문제:** `const int *ptr = x;`에 대한 여섯 문장 가운데 컴파일 오류가 나는 것을 모두 고르라. 보기는 [연습 문제 5](Exercises.ko.md#연습-문제-5-const-포인터와-컴파일-오류)에 있다.

### 풀이

**정답:** ①, ⑤, ⑥

**해설:** `const int *ptr`은 가리키는 `int`를 읽기만 할 수 있는 포인터이고, 포인터 자체는 바꿀 수 있다([8장 1.6절](Concepts_Lecture.ko.md#16-const-포인터)). 따라서 가리키는 값을 바꾸는 ① `*ptr = 0`, ⑤ `(*ptr)++`, ⑥ `ptr[1] = 3`은 모두 Clang에서 `read-only variable is not assignable` 오류이다. ②는 `ptr`을 널 포인터로, ③은 다른 배열 `y`를 가리키게, ④는 다음 원소를 가리키게 바꾸므로 포인터 자체의 변경이어서 허용된다. 포인터 자체를 고정하려면 `int *const ptr = x;`처럼 `const`를 `*` 뒤에 쓴다.

---

<br>

## 연습 문제 6: 증감과 역참조의 실행 결과

**교재 문항:** 8장 연습 문제 12번

**문제:** 배열을 가리키는 포인터로 `++(*p)`를 출력하고 `p++`로 이동하는 반복문과, 그 뒤 배열을 출력하는 반복문의 실행 결과를 쓰라. 코드는 [연습 문제 6](Exercises.ko.md#연습-문제-6-증감과-역참조의-실행-결과)에 있다.

### 풀이

**접근 방법:** `++(*p)`는 괄호 안의 `*p`, 즉 `p`가 가리키는 원소를 먼저 구한 뒤 그 원소를 1 증가시키고 증가한 값을 결과로 낸다. 그다음 줄의 `p++`는 포인터를 다음 원소로 옮긴다.

| 회차 | `p`가 가리키는 원소 | `++(*p)`의 결과 | 회차 뒤의 배열 |
|:-----|:-----|-----:|:-----|
| 0 | `arr[0]` | 2 | `{2, 2, 3, 4, 5}` |
| 1 | `arr[1]` | 3 | `{2, 3, 3, 4, 5}` |
| 2 | `arr[2]` | 4 | `{2, 3, 4, 4, 5}` |
| 3 | `arr[3]` | 5 | `{2, 3, 4, 5, 5}` |
| 4 | `arr[4]` | 6 | `{2, 3, 4, 5, 6}` |

**실행 결과:**

```text
2 3 4 5 6
2 3 4 5 6
```

각 원소가 한 번씩 증가했으므로 두 번째 줄의 배열도 첫 줄과 같다. 만약 `++*p++`처럼 한 식에 쓰면 후위 `++`가 먼저 결합하여 `++(*(p++))`가 되므로, 같은 결과를 내지만 읽기 어렵다.

---

<br>

## 연습 문제 7: 합계와 평균을 구하는 함수

**교재 문항:** 8장 연습 문제 13번의 변형

**문제:** 합계는 반환값으로, 평균은 출력 매개변수로 돌려주는 `get_sum_average`를 작성하고, `NULL`을 넘기면 평균을 저장하지 않게 하라. 실행 예시는 [연습 문제 7](Exercises.ko.md#연습-문제-7-합계와-평균을-구하는-함수)에 있다.

### 풀이

**접근 방법:** 결과가 두 개이므로 하나는 반환값으로, 다른 하나는 호출한 쪽의 변수 주소를 받아 `*average`에 기록한다([8장 3.3절](Concepts_Lecture.ko.md#33-여러-값-반환)). 출력 매개변수가 필요 없는 호출을 위해 역참조 전에 `NULL`인지 검사한다.

```c
#include <stdio.h>

int get_sum_average(const int arr[], int size, double *average)
{
    int sum, i;

    for (i = 0, sum = 0; i < size; i++)
        sum += arr[i];
    if (average != NULL)
        *average = (double)sum / size;
    return sum;
}

int main(void)
{
    int scores[5] = { 98, 99, 78, 85, 91 };
    double ave;

    printf("sum: %d\n", get_sum_average(scores, 5, &ave));
    printf("average: %.2f\n", ave);
    printf("sum only: %d\n", get_sum_average(scores, 3, NULL));
    return 0;
}
```

- `(double)sum / size`는 `sum`을 실수로 바꾼 뒤 나누므로 정수 나눗셈이 되지 않는다. 451 / 5 = 90.2이다.
- `printf`의 첫 호출이 끝나야 `ave`에 값이 들어가므로, 평균은 다음 문장에서 따로 출력한다. 한 `printf`의 인수에서 `get_sum_average(scores, 5, &ave)`와 `ave`를 함께 쓰면 인수의 평가 순서가 정해져 있지 않아 저장 전의 값을 읽을 수 있다.
- 세 번째 호출은 `NULL`을 넘기므로 평균을 저장하지 않고 앞 3개의 합 98 + 99 + 78 = 275만 반환한다.

**실행 결과:**

```text
sum: 451
average: 90.20
sum only: 275
```

---

<br>

## 연습 문제 8: 최솟값, 최댓값과 포인터로 배열 뒤집기

**문제:** 최솟값과 최댓값을 출력 매개변수로 돌려주는 `get_min_max`와, 양 끝을 가리키는 두 포인터로 배열을 뒤집는 `reverse`를 작성하라. 실행 예시는 [연습 문제 8](Exercises.ko.md#연습-문제-8-최솟값-최댓값과-포인터로-배열-뒤집기)에 있다.

### 풀이

**접근 방법:** `get_min_max`는 두 결과를 모두 출력 매개변수로 돌려준다. `reverse`는 첫 원소를 가리키는 `left`와 마지막 원소를 가리키는 `right`를 두고, `left`가 `right`보다 앞에 있는 동안 두 원소를 맞바꾼 뒤 서로 가까워지게 옮긴다.

```c
#include <stdio.h>

void get_min_max(const int *arr, int size, int *min, int *max)
{
    int i;

    *min = *max = arr[0];
    for (i = 1; i < size; i++) {
        if (arr[i] < *min)
            *min = arr[i];
        if (arr[i] > *max)
            *max = arr[i];
    }
}

void reverse(int *arr, int size)
{
    int *left = arr, *right = arr + size - 1, t;

    while (left < right) {
        t = *left;
        *left = *right;
        *right = t;
        left++;
        right--;
    }
}

int main(void)
{
    int data[6] = { 23, 45, 62, 12, 99, 83 };
    int lo, hi, i;

    get_min_max(data, 6, &lo, &hi);
    printf("min = %d, max = %d\n", lo, hi);
    reverse(data, 6);
    for (i = 0; i < 6; i++)
        printf("%d ", data[i]);
    printf("\n");
    return 0;
}
```

- `*min = *max = arr[0];`은 연쇄 대입으로 두 결과를 첫 원소로 시작한다. 7장 5.1절에서 주의한 것처럼 0이나 임의의 값으로 시작하면 모든 원소가 그보다 크거나 작을 때 틀린 결과가 나온다.
- `arr + size - 1`은 마지막 원소 `arr[5]`의 주소이다. 같은 배열 안의 두 포인터는 `<`로 비교할 수 있으므로 `left < right`가 거짓이 되면 가운데에 이른 것이다.
- 원소가 6개이면 (`arr[0]`, `arr[5]`), (`arr[1]`, `arr[4]`), (`arr[2]`, `arr[3]`)의 세 쌍을 맞바꾼 뒤 `left`가 `arr + 3`, `right`가 `arr + 2`가 되어 멈춘다. 원소가 홀수 개이면 가운데 원소에서 두 포인터가 만나 그 원소는 그대로 남는다.

**실행 결과:**

```text
min = 12, max = 99
83 99 12 62 45 23
```
