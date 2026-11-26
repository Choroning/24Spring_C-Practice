# 8장 연습 문제 — 포인터

[레포지토리 안내](../../README.ko.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

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

**문제:** 2차원 평면 위의 좌표를 다루는 함수를 정의하고, 예시 코드를 참고하여 프로그램을 완성하라. 함수의 인자 전달 방식(값에 의한 전달과 주소에 의한 전달)을 연습하는 문제이다.

**프로그램 요구사항:**

1. `display_point()` 함수는 x축과 y축 좌표값을 전달받아 좌표 형태로 출력한다(실행 예시 참고).

2. `compute_distance()` 함수는 두 점의 좌표를 전달받아 두 점 사이의 거리를 계산해서 반환한다(출력문 없음).
   두 점 사이의 거리 공식은 다음과 같다.

   $$\sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2}$$

3. `move_point()` 함수는 x축과 y축 좌표값, 그리고 이동량을 전달받아 x축과 y축 좌표값을 각각 이동량만큼 변경한다.

**예시 코드:** `[blank]`로 표시한 부분을 채워 프로그램을 완성한다.

```c wide-ok
#include <stdio.h>
#include <math.h>

// Declarations of the functions
[blank]

int main()
{
    int x1, x2, y1, y2, move;
    double distance;

    printf("p1 좌표 입력(x축, y축 좌표값 입력): ");
    scanf("%d %d", &x1, &y1);
    
    printf("p2 좌표 입력(x축, y축 좌표값 입력): ");
    scanf("%d %d", &x2, &y2);

    printf("p1 = ");
    display_point(x1, y1);

    printf("p2 = ");
    display_point(x2, y2);

    // Call compute_distance() to compute the distance between the two points and print it (see the sample run)
    [blank]

    printf("좌표 이동량 입력: ");
    scanf("%d", &move);

    // Call move_point() to shift the coordinates of p2 by move
    [blank]

    printf("p2를 x축과 y축으로 각각 %d 만큼 이동 = ", move);
    display_point(x2, y2);

    return 0;
}

// Definitions of the functions
[blank]
```

**실행 예시:**

```text wide-ok
p1 좌표 입력(x축, y축 좌표값 입력): 1 1
p2 좌표 입력(x축, y축 좌표값 입력): 3 7
p1 = (1, 1)
p2 = (3, 7)
두 점 사이의 거리 = 6.32456

좌표 이동량 입력: -1
p2를 x축과 y축으로 각각 -1 만큼 이동 = (2, 6)

Program ended with exit code: 0
```

```text wide-ok
p1 좌표 입력(x축, y축 좌표값 입력): -2 4
p2 좌표 입력(x축, y축 좌표값 입력): 3 -5
p1 = (-2, 4)
p2 = (3, -5)
두 점 사이의 거리 = 10.2956

좌표 이동량 입력: 3
p2를 x축과 y축으로 각각 3 만큼 이동 = (6, -2)

Program ended with exit code: 0
```

**[풀이](Solutions.ko.md#연습-문제-1-2차원-평면-좌표-계산기)**

---

<br>

## 연습 문제 2: 로또 프로그램

**문제:** 다음은 1~45 사이의 숫자 중 6개를 무작위로 선택하는 로또 프로그램이다. 프로그램 요구사항을 충족하도록 프로그램을 완성하라.

**프로그램 요구사항:**

1. 배열과 배열의 크기를 전달받아 출력하는 함수를 작성한다.
   단, 포인터의 증가 연산(`++`)을 이용한다.
   
   ```c
   void printArray(const int p[], int size);
   ```

2. 배열과 배열의 크기를 전달받아 중복을 검사하는 함수를 작성한다.
   6개의 로또 번호 중 중복되는 것이 있으면 1을, 중복된 번호가 없으면 0을 반환해야 한다.
   단, 포인터의 색인화(포인터에 첨자 `[]`를 쓰는 방식)를 이용한다.
   
   ```c
   int existDuplication(const int p[], int size);
   ```

3. 배열과 배열의 크기를 전달받아 선택 정렬을 수행하는 함수를 작성한다.
   정렬 과정에서 두 원소를 교환하는 연산은 `swap()` 함수를 호출하여 수행해야 한다.
   단, 포인터의 산술 연산을 이용한다.
   
   ```c
   void selectionSort(int p[], int size);
   ```

**예시 코드:** `[blank]`로 표시한 부분을 채워 프로그램을 완성한다.

```c wide-ok
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int p[], int size);       // uses pointer increment
int existDuplication(int p[], int size);  // uses pointer indexing
void swap(int* p, int* q);                // swap two integers
void selectionSort(int p[], int size);    // uses pointer arithmetic

int main() {
    int lotto[6], setNo;

    srand((unsigned int)time(NULL));      // automatically set the seed of rand()
    printf("몇 세트의 복권 번호를 생성할까요? ");
    scanf("%d", &setNo);

    for (int k = 0; k < setNo; k++) {
        do { // repeat until there are no duplicate numbers
            for (int i = 0; i < 6; i++)
                lotto[i] = rand() % 45 + 1;

            // printArray(lotto, 6);      // print statement to check for duplicate numbers
        } while ( [blank] );                // call existDuplication()

        [blank]      // call selectionSort()
        printArray(lotto, 6);
    }
    printf("\n행운을 빕니다!\n");

    return 0;
}

// Definitions of the functions
[blank]
```

**실행 예시:** 번호는 실행할 때마다 무작위로 달라진다.

```text wide-ok
몇 세트의 복권 번호를 생성할까요? 5
 3   6  20  24  30  45
12  17  19  25  26  28
 5  15  26  29  43  45
19  20  22  32  40  44
 3   7  11  16  38  39

행운을 빕니다!

Program ended with exit code: 0
```

```text wide-ok
몇 세트의 복권 번호를 생성할까요? 3
13  23  27  33  38  45
 1  13  16  24  28  29
 1   3  10  13  40  43

행운을 빕니다!

Program ended with exit code: 0
```

**[풀이](Solutions.ko.md#연습-문제-2-로또-프로그램)**

---

<br>

## 연습 문제 3: 포인터의 선언과 초기화

**교재 문항:** 8장 연습 문제 3번

**문제:** `int a, arr[10]; double y;`가 선언되어 있을 때, 다음 포인터의 선언과 초기화 가운데 잘못된 것을 모두 고르고 이유를 쓰라.

- ① `char *pc = NULL;`
- ② `char *pch = 0;`
- ③ `int *pi = 0x12345678;`
- ④ `int *px = &a;`
- ⑤ `int *parr = arr;`
- ⑥ `double *pd = y;`
- ⑦ `short *ps = &a;`

**[풀이](Solutions.ko.md#연습-문제-3-포인터의-선언과-초기화)**

---

<br>

## 연습 문제 4: 포인터 연산의 결과

**교재 문항:** 8장 연습 문제 5번

**문제:** `int arr[4] = { 2, 4, 6, 8 }; int *ptr = arr;`이고 `int`가 4바이트이며, `ptr`에 저장된 주소가 `0x100`번지라고 가정한다. 다음 각 수식의 값을 쓰라.

- ① `*ptr`
- ② `ptr + 2`
- ③ `*(ptr + 2)`
- ④ `ptr[3]`
- ⑤ `(*ptr) + 1`
- ⑥ `*(ptr + 1)`

**[풀이](Solutions.ko.md#연습-문제-4-포인터-연산의-결과)**

---

<br>

## 연습 문제 5: `const` 포인터와 컴파일 오류

**교재 문항:** 8장 연습 문제 6번

**문제:** `int x[5] = { 2, 4, 6, 8, 10 }, y[5]; const int *ptr = x;`일 때, 다음 문장 가운데 컴파일 오류가 나는 것을 모두 고르라.

- ① `*ptr = 0;`
- ② `ptr = 0;`
- ③ `ptr = y;`
- ④ `++ptr;`
- ⑤ `(*ptr)++;`
- ⑥ `ptr[1] = 3;`

**[풀이](Solutions.ko.md#연습-문제-5-const-포인터와-컴파일-오류)**

---

<br>

## 연습 문제 6: 증감과 역참조의 실행 결과

**교재 문항:** 8장 연습 문제 12번

**문제:** 다음 프로그램이 출력하는 두 줄을 쓰라.

```c
#include <stdio.h>

int main(void)
{
    int arr[5] = { 1, 2, 3, 4, 5 };
    int *p = arr;
    int i;

    for (i = 0; i < 5; i++) {
        printf("%d ", ++(*p));
        p++;
    }
    printf("\n");
    for (i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
```

**[풀이](Solutions.ko.md#연습-문제-6-증감과-역참조의-실행-결과)**

---

<br>

## 연습 문제 7: 합계와 평균을 구하는 함수

**교재 문항:** 8장 연습 문제 13번의 변형

**문제:** `int` 배열의 합계를 반환하고, 평균은 출력 매개변수로 돌려주는 함수 `int get_sum_average(const int arr[], int size, double *average)`를 작성하라. `average`가 `NULL`이면 평균을 저장하지 않는다. 점수 `{98, 99, 78, 85, 91}`의 합계와 평균을 출력하고, 앞 3개의 합계만 `NULL`을 넘겨 구하라.

**실행 예시:**

```text
sum: 451
average: 90.20
sum only: 275
```

**[풀이](Solutions.ko.md#연습-문제-7-합계와-평균을-구하는-함수)**

---

<br>

## 연습 문제 8: 최솟값, 최댓값과 포인터로 배열 뒤집기

**문제:** 다음 두 함수를 작성하고 배열 `{23, 45, 62, 12, 99, 83}`으로 시험하라.

- `void get_min_max(const int *arr, int size, int *min, int *max)`: 최솟값과 최댓값을 두 출력 매개변수로 돌려준다.
- `void reverse(int *arr, int size)`: 인덱스를 쓰지 않고 양 끝을 가리키는 두 포인터를 가운데로 옮기며 원소를 맞바꾼다.

**실행 예시:**

```text
min = 12, max = 99
83 99 12 62 45 23
```

**[풀이](Solutions.ko.md#연습-문제-8-최솟값-최댓값과-포인터로-배열-뒤집기)**
