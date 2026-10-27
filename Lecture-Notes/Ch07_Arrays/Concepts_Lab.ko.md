# 7장 실습 — 1차원 배열과 다차원 배열

[레포지토리 안내](../../README.ko.md) | [English](Concepts_Lab.md) | [한국어](Concepts_Lab.ko.md)

> **최종 수정일:** 2026-10-27
>
> 문제풀이 중심의 C언어 연습, 김용일 외, Ch 8, 9

> **학습 목표:**
> 1. 배열 선언에 필요한 세 가지 요소를 말하고, 인덱스로 배열의 원소에 접근할 수 있다
> 2. 세 가지 방식으로 1차원 배열을 초기화하고 생략된 원소의 값을 구할 수 있다
> 3. 반복문과 `sizeof`로 배열의 원소를 차례로 입력, 출력, 연산할 수 있다
> 4. 2차원 배열을 선언, 초기화하고, 행 우선으로 저장되는 메모리 배치를 설명할 수 있다
> 5. 배열에서 값의 위치를 찾고 행렬을 전치하는 프로그램을 작성할 수 있다

---

## 목차

- [1. 1차원 배열](#1-1차원-배열)
  - [1.1 배열이란](#11-배열이란)
  - [1.2 배열 선언과 원소 접근](#12-배열-선언과-원소-접근)
  - [1.3 배열의 초기화](#13-배열의-초기화)
- [2. 1차원 배열 실습](#2-1차원-배열-실습)
  - [2.1 월별 날짜 수 출력](#21-월별-날짜-수-출력)
  - [2.2 입력한 원소의 합](#22-입력한-원소의-합)
  - [2.3 두 배열의 원소별 차](#23-두-배열의-원소별-차)
- [3. 다차원 배열](#3-다차원-배열)
  - [3.1 다차원 배열의 선언](#31-다차원-배열의-선언)
  - [3.2 2차원 배열의 원소 접근](#32-2차원-배열의-원소-접근)
  - [3.3 실제 메모리 구성](#33-실제-메모리-구성)
  - [3.4 2차원 배열의 초기화](#34-2차원-배열의-초기화)
  - [3.5 배열 크기의 생략](#35-배열-크기의-생략)
- [4. 배열 탐색과 행렬 실습](#4-배열-탐색과-행렬-실습)
  - [4.1 배열에서 값의 위치 찾기](#41-배열에서-값의-위치-찾기)
  - [4.2 행렬의 전치](#42-행렬의-전치)
- [요약](#요약)
- [점검 문제](#점검-문제)

---

<br>

## 1. 1차원 배열

### 1.1 배열이란

**배열(array)** 은 같은 데이터 타입의 변수 여러 개를 연속된 메모리 공간에 한꺼번에 확보한 것이다. `int a, b, c, d, e;`처럼 변수를 하나씩 선언하는 대신 `int arr[5];`로 선언하면, `int` 다섯 개가 메모리에 나란히 놓이고 모두 같은 이름 `arr`과 번호로 다룰 수 있다([7장 1.2절](Concepts_Lecture.ko.md#12-배열의-개념)).

### 1.2 배열 선언과 원소 접근

배열을 선언하려면 다음 세 가지가 필요하다([7장 1.3절](Concepts_Lecture.ko.md#13-배열-선언)).

| 요소 | 의미 | `int array[10];`에서 |
|:-----|:-----|:-----|
| 배열 길이(크기) | 배열을 이루는 변수(원소)의 개수. 상수로 정한다 | `10` |
| 원소의 데이터 타입 | 배열을 이루는 각 원소의 타입 | `int` |
| 배열 이름 | 배열에 접근할 때 쓰는 이름 | `array` |

*표 1. 배열 선언에 필요한 세 가지 요소*

배열의 각 원소는 **인덱스(index)** 로 위치를 나타내며, 인덱스는 0부터 시작한다. 따라서 크기가 10인 배열의 첫 원소는 `array[0]`, 마지막 원소는 `array[9]`이다([7장 3.1절](Concepts_Lecture.ko.md#31-원소-접근)).

```c
int array[10];      // declares an array of 10 ints
array[0] = 10;      // first element: index 0
array[1] = 20;      // second element
array[2] = 30;      // third element
/* ... */
array[9] = 100;     // tenth element: the last index is 9
```

다음 프로그램은 실수 네 개를 배열에 저장하고 평균을 구한다.

```c
#include <stdio.h>

int main(void)
{
    double total;
    double val[4];      // four double elements in a row

    val[0] = 1.01;
    val[1] = 2.02;
    val[2] = 3.03;
    val[3] = 4.04;

    total = val[0] + val[1] + val[2] + val[3];    // total is assigned here, so it needs no initial 0
    printf("평균 : %.1f \n", total / 4);

    return 0;
}
```

```text
평균 : 2.5 
```

합을 누적할 변수는 `sum = 0`으로 초기화한 뒤 `sum += ...`로 더해야 하지만, 이 프로그램의 `total`은 `total = val[0] + ... + val[3];`처럼 네 원소의 합을 한 번에 대입받으므로 0으로 초기화하지 않아도 된다. 1.01 + 2.02 + 3.03 + 4.04 = 10.1이고 평균은 2.525이므로, `%.1f`로 출력하면 2.5가 된다.

> **주의:** C 컴파일러는 인덱스가 배열의 범위 안에 있는지 검사하지 않는다. `array[10]`처럼 범위를 넘는 인덱스로 접근하면 정의되지 않은 동작이 되어 다른 변수의 값을 덮어쓰거나 프로그램이 비정상 종료될 수 있다([7장 3.3절](Concepts_Lecture.ko.md#33-인덱스-범위-초과)).

### 1.3 배열의 초기화

배열은 선언과 동시에 중괄호 안의 초기값 목록으로 초기화할 수 있다([7장 2.1절](Concepts_Lecture.ko.md#21-초기화-리스트), [2.2절](Concepts_Lecture.ko.md#22-크기-생략)).

```c
#include <stdio.h>

int main(void)
{
    int arr1[5] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 3, 5, 7, 9};      // size 5 from the number of initial values
    int arr3[5] = {1, 2};              // the missing elements become 0
    int i;

    for (i = 0; i < 5; i++)
        printf("%d %d %d\n", arr1[i], arr2[i], arr3[i]);

    return 0;
}
```

```text
1 1 1
2 3 2
3 5 0
4 7 0
5 9 0
```

| 선언 | 크기 | 원소 |
|:-----|:---:|:-----|
| `int arr1[5] = {1, 2, 3, 4, 5};` | 5 | 1, 2, 3, 4, 5 |
| `int arr2[] = {1, 3, 5, 7, 9};` | 5 | 크기를 생략하면 초기값의 개수로 크기가 정해진다 |
| `int arr3[5] = {1, 2};` | 5 | 1, 2, 0, 0, 0. 초기값이 부족하면 나머지는 0으로 초기화된다 |

*표 2. 1차원 배열의 세 가지 초기화 방식*

---

<br>

## 2. 1차원 배열 실습

배열의 원소를 하나하나 다룰 수도 있지만 배열이 크면 비효율적이므로, 인덱스를 반복문의 변수로 바꾸어 가며 처리한다([7장 3.2절](Concepts_Lecture.ko.md#32-배열과-반복문)). 다음 프로그램은 `gcc -std=c99 -Wall`로 경고 없이 컴파일되며, 출력은 실제로 실행한 결과이다.

### 2.1 월별 날짜 수 출력

**문제:** 배열을 `int day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};`로 초기화하고 배열의 내용을 `1월은 31일`처럼 출력하라.

**풀이:** 인덱스는 0부터, 월은 1부터 시작하므로 인덱스 `i`의 원소는 `i + 1`월의 날짜 수이다. `%2d`로 월을 두 칸에 맞추어 1월과 12월의 줄이 정렬되게 한다.

```c
#include <stdio.h>

int main(void)
{
    int day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};   // days of each month
    int i;

    for (i = 0; i < 12; i++)
        printf("%2d월은 %d일\n", i + 1, day[i]);   // index i holds month i + 1

    return 0;
}
```

```text
 1월은 31일
 2월은 28일
 3월은 31일
 4월은 30일
 5월은 31일
 6월은 30일
 7월은 31일
 8월은 31일
 9월은 30일
10월은 31일
11월은 30일
12월은 31일
```

### 2.2 입력한 원소의 합

**문제:** 원소가 5개인 1차원 배열 `int val[5]`의 값을 화면에서 입력받고, 다섯 원소의 합을 `+ 1 + 2 + 4 + 6 + -4 = 9`처럼 출력하라.

**풀이:** `scanf`에는 저장할 곳의 주소를 넘겨야 하므로 원소의 주소 `&val[i]`를 쓴다. 첫 반복으로 입력을 모두 받고, 둘째 반복에서 각 원소를 출력하면서 합을 누적한다.

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int val[5];
    int i, sum = 0;

    for (i = 0; i < 5; i++) {
        printf("%d번째 data input: ", i + 1);
        scanf("%d", &val[i]);      // &val[i] is the address of element i
    }

    for (i = 0; i < 5; i++) {
        printf(" + %d", val[i]);
        sum += val[i];
    }
    printf(" = %d\n", sum);

    return 0;
}
```

```text
1번째 data input: 1
2번째 data input: 2
3번째 data input: 4
4번째 data input: 6
5번째 data input: -4
 + 1 + 2 + 4 + 6 + -4 = 9
```

### 2.3 두 배열의 원소별 차

**문제:** 원소가 5개인 배열 `int arr1[5] = {1, 3, 5, 7, 9};`와 `int arr2[] = {4, 4, 6, 6, 8};`의 같은 인덱스에 있는 원소끼리의 차를 표 형태로 출력하라.

**풀이:** 같은 인덱스 `i`로 두 배열의 원소를 함께 읽어 `arr1[i] - arr2[i]`를 계산한다. 원소의 개수는 배열 전체의 크기를 원소 하나의 크기로 나눈 `sizeof(arr1) / sizeof(arr1[0])`, 즉 20 / 4 = 5로 구한다. 이렇게 하면 배열에 원소를 추가해도 반복 횟수를 고칠 필요가 없다([7장 1.4절](Concepts_Lecture.ko.md#14-sizeof와-배열)).

```c
#include <stdio.h>

int main(void)
{
    int arr1[5] = {1, 3, 5, 7, 9};
    int arr2[] = {4, 4, 6, 6, 8};
    int size = (int)(sizeof(arr1) / sizeof(arr1[0]));    // number of elements: 20 / 4 = 5
    int i;

    printf("arr1  arr2  (arr1-arr2)\n");
    for (i = 0; i < size; i++)
        printf("%3d %5d %9d\n", arr1[i], arr2[i], arr1[i] - arr2[i]);

    return 0;
}
```

```text
arr1  arr2  (arr1-arr2)
  1     4        -3
  3     4        -1
  5     6        -1
  7     6         1
  9     8         1
```

> **참고:** `sizeof`의 결과는 부호 없는 정수형 `size_t`이고, 64비트(x64) 빌드에서 `size_t`는 8바이트이다. 이 값을 `int` 변수에 대입하거나 `int`와 비교하면 Visual Studio가 데이터 손실 가능성(C4267)이나 부호 불일치 경고를 내는데, 32비트(x86) 빌드에서는 `size_t`가 4바이트라서 이 경고가 나지 않는다. 플랫폼 설정을 x86으로 바꾸는 대신, 위 코드처럼 `(int)`로 명시적으로 변환하거나 `size_t` 변수와 `%zu`를 쓰면 어느 빌드에서나 경고가 없다.

배열 원소 7개 중 최댓값과 최솟값을 찾는 문제는 [HW07 문제 2](../../Coursework/HW07_Arrays/Assignment-Explanation.ko.md#3-문제-2-배열에서-대소-비교)에서 다룬다.

---

<br>

## 3. 다차원 배열

### 3.1 다차원 배열의 선언

2차원 이상의 배열을 **다차원 배열(multidimensional array)** 이라고 한다. 대괄호의 개수가 차원 수이다([7장 4절](Concepts_Lecture.ko.md#4-다차원-배열)).

| 선언 | 차원 |
|:-----|:-----|
| `int arr[100];` | 1차원 배열 |
| `int arr[10][10];` | 10 × 10, 2차원 배열 |
| `int arr[5][5][5];` | 5 × 5 × 5, 3차원 배열 |

*표 3. 배열 선언과 차원*

2차원 배열 `int arr2[3][4];`는 3행(row) 4열(column)의 표로 생각할 수 있다. 첫 번째 크기가 행의 수, 두 번째 크기가 열의 수이다.

### 3.2 2차원 배열의 원소 접근

2차원 배열의 원소는 행 인덱스와 열 인덱스를 차례로 써서 `arr[행][열]`로 접근한다. 두 인덱스 모두 0부터 시작한다([7장 4.2절](Concepts_Lecture.ko.md#42-2차원-배열의-선언과-접근)).

```c
int arr[3][3];
arr[0][0] = 2;      // row 0, column 0
arr[1][0] = 4;      // row 1, column 0
arr[2][2] = 8;      // row 2, column 2: the last element
```

```text
          열 0   열 1   열 2
        ┌──────┬──────┬──────┐
 행 0   │  2   │      │      │   arr[0][0]
        ├──────┼──────┼──────┤
 행 1   │  4   │      │      │   arr[1][0]
        ├──────┼──────┼──────┤
 행 2   │      │      │  8   │   arr[2][2]
        └──────┴──────┴──────┘
```

*그림 1. 3 × 3 배열에서 세 원소의 위치*

### 3.3 실제 메모리 구성

다차원 배열도 1차원 배열처럼 연속된 메모리 공간을 쓴다. 2차원, 3차원은 그 연속된 공간을 행과 열로 나누어 해석하고 이해하는 방식일 뿐이다. C는 첫 행의 원소를 모두 놓은 뒤 다음 행을 놓는 **행 우선(row-major)** 순서로 저장한다.

```c
#include <stdio.h>

int main(void)
{
    int a[2][3] = { {1, 2, 3}, {4, 5, 6} };
    int i, j;

    for (i = 0; i < 2; i++)
        for (j = 0; j < 3; j++)
            printf("a[%d][%d] = %d at offset %d bytes\n", i, j, a[i][j],
                   (int)((char *)&a[i][j] - (char *)&a[0][0]));

    return 0;
}
```

```text
a[0][0] = 1 at offset 0 bytes
a[0][1] = 2 at offset 4 bytes
a[0][2] = 3 at offset 8 bytes
a[1][0] = 4 at offset 12 bytes
a[1][1] = 5 at offset 16 bytes
a[1][2] = 6 at offset 20 bytes
```

```text
 int a[2][3]의 메모리 배치 (int 4바이트)
  0       4       8       12      16      20      (바이트 오프셋)
┌───────┬───────┬───────┬───────┬───────┬───────┐
│a[0][0]│a[0][1]│a[0][2]│a[1][0]│a[1][1]│a[1][2]│
└───────┴───────┴───────┴───────┴───────┴───────┘
 └────── 행 0 ──────────┘└────── 행 1 ──────────┘
```

*그림 2. 2 × 3 배열이 메모리에 행 우선으로 놓인 모습*

`a[i][j]`의 위치는 배열 시작에서 (i × 3 + j) × 4바이트 떨어진 곳이다.

### 3.4 2차원 배열의 초기화

2차원 배열은 행마다 중괄호로 묶어 초기화하거나, 중괄호 하나에 값을 차례로 나열하여 초기화한다([7장 4.3절](Concepts_Lecture.ko.md#43-2차원-배열의-초기화)).

```c
int a[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
int b[3][3] = { {1}, {4, 5}, {7, 8, 9} };      // each row is filled from the left, the rest is 0
int c[3][3] = { 1, 2, 3, 4, 5, 6, 7 };         // filled row by row, the rest is 0
```

세 배열의 원소를 행마다 출력하면 다음과 같다.

```text
 1 2 3
 4 5 6
 7 8 9
--
 1 0 0
 4 5 0
 7 8 9
--
 1 2 3
 4 5 6
 7 0 0
```

- **행마다 중괄호로 묶은 경우:** 각 중괄호가 한 행을 왼쪽부터 채운다. `b`의 첫 행은 `{1}`이므로 1, 0, 0이 되고, 둘째 행은 `{4, 5}`이므로 4, 5, 0이 된다.
- **중괄호 하나에 나열한 경우:** 행 우선 순서로 첫 행부터 채운다. `c`는 7개의 값이 첫 행, 둘째 행, 셋째 행의 첫 원소를 채우고 나머지 두 원소는 0이 된다.

> **참고:** 행마다의 중괄호를 생략한 `c`의 초기화는 올바른 C 코드이지만, clang은 `-Wall`에서 `-Wmissing-braces` 경고("suggest braces around initialization of subobject")를 낸다. 행 구분이 분명해지도록 행마다 중괄호를 쓰는 것이 좋다.

### 3.5 배열 크기의 생략

1차원 배열은 초기값이 있으면 크기를 생략할 수 있다. 2차원 배열에서는 첫 번째 크기(행의 수)만 생략할 수 있고, 두 번째 크기(열의 수)는 반드시 써야 한다. 열의 수를 알아야 나열된 초기값을 몇 개씩 끊어 한 행으로 볼지 정할 수 있기 때문이다.

```c
int arr[] = {1, 2, 3, 4, 5};                  // OK: 5 elements
int arr[][] = {1, 2, 3, 4, 5, 6, 7, 8};       // error: the column size is missing
int arr[3][] = {1, 2, 3, 4, 5, 6, 7, 8};      // error: the column size is missing
int arr[][4] = {1, 2, 3, 4, 5, 6, 7, 8};      // OK: 2 rows of 4
int arr[][2] = {1, 2, 3, 4, 5, 6, 7, 8};      // OK: 4 rows of 2
int arr[4][2] = {1, 2, 3, 4, 5, 6, 7, 8};     // OK
int arr[2][4] = {1, 2, 3, 4, 5, 6, 7, 8};     // OK
```

위 선언은 각각 따로 쓰는 예이다. 열의 수가 없는 두 선언은 clang에서 "array has incomplete element type 'int[]'" 오류가 난다. 행의 수를 생략하면 초기값의 개수를 열의 수로 나누어 올림한 값이 행의 수가 되므로, `int arr[][4]`는 2행, `int arr[][2]`는 4행이다.

---

<br>

## 4. 배열 탐색과 행렬 실습

다음 문제의 풀이 코드는 이 단원 폴더의 예제 파일이다. 각 파일은 `gcc -std=c99 -Wall`로 경고 없이 컴파일되며, 출력은 실제로 실행한 결과이다.

### 4.1 배열에서 값의 위치 찾기

**문제:** 크기가 7인 배열 `int arr[] = { 23, 45, -34, 23, -124, 22, 2 };`에서, 화면에서 입력한 값이 저장된 위치(인덱스)를 출력하라.

**풀이:** 배열의 처음부터 끝까지 차례로 비교하는 **순차 탐색(sequential search)** 을 쓴다([7장 5.5절](Concepts_Lecture.ko.md#55-순차-탐색)). 반복 횟수를 `sizeof(arr) / sizeof(arr[0])`로 구하므로 배열의 원소 수가 바뀌어도 코드를 고칠 필요가 없다.

- **같은 값이 여러 개인 경우:** 코드의 첫 번째 주석처럼 값을 찾자마자 `break`하면, 23처럼 두 번 이상 들어 있는 값은 첫 위치만 출력된다. 그래서 `break` 없이 끝까지 비교하면서 찾은 개수를 `count`로 센다.
- **값이 없는 경우:** 반복이 끝난 뒤 `count`가 0이면 배열에 그 값이 없다는 메시지를 출력한다.
- **배열을 출력하는 함수:** 코드 끝의 주석은 배열과 크기를 받아 원소를 출력하는 `print_array` 함수의 형태이다. 배열을 함수에 넘기는 방법은 8장에서 다룬다.

**코드:** [Example_LinearSearch.c](Example_LinearSearch.c)

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main() // works even if the number of elements in the array changes
{
    int arr[] = { 23, 45, -34, 23, -124, 22, 2 };
    int i, val, count = 0;

    printf("arr = ");
    for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n>> input value: ");
    scanf(" %d", &val);

    /*for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (val == arr[i])
        {
            printf("인덱스 %d에 %d값이 위치함! \n", i, val);
            break; // written this way, it does not work correctly when the value appears two or more times in the array
        } // in that case, declare and use a variable such as count
    }
    if (i == sizeof(arr) / sizeof(arr[0]))
    {
        printf("배열에 %d값이 없습니다! \n", val);
    }*/

    for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (val == arr[i])
        {
            printf("인덱스 %d에 %d값이 위치함! \n", i, val);
            count++;
        }
    }
    if (count == 0)
    {
        printf("배열에 %d값이 없습니다! \n", val);
    }


    // With the function below, main can call it as print_array(arr, size);

    /*void print_array(int pArr[], int size){
        int i;
        for (i = 0; i < size; i++)
            printf("%d ", pArr[i]);
        printf("\n");
    }*/
}
```

```text
arr = 23 45 -34 23 -124 22 2 
>> input value: 23
인덱스 0에 23값이 위치함! 
인덱스 3에 23값이 위치함! 
```

```text
arr = 23 45 -34 23 -124 22 2 
>> input value: 7
배열에 7값이 없습니다! 
```

> **참고:** `i`는 `int`이고 `sizeof(arr) / sizeof(arr[0])`는 부호 없는 `size_t`이므로, 두 값을 비교하면 `i`가 `size_t`로 변환된다. 이 코드에서는 `i`가 음수가 되지 않으므로 결과가 같지만, 더 엄격한 경고 옵션(`-Wextra`)에서는 부호 비교 경고가 난다(2.3절의 참고).

같은 순차 탐색을 크기 10의 배열로 푼 과제는 [HW07 문제 4](../../Coursework/HW07_Arrays/Assignment-Explanation.ko.md#5-문제-4-배열에서-값-찾기)에 있다.

### 4.2 행렬의 전치

**문제:** 3 × 3 행렬 `int matA[][3] = { {5, 7, 4}, {6, 1, 8}, {3, 2, 7} };`의 내용을 전치(transpose)하여 `int matB[3][3] = { 0 };`에 저장하고, 두 행렬을 출력하라. 전치는 각 행을 열로 바꾸는 것이다.

**풀이:** 전치 행렬의 i행 j열 원소는 원래 행렬의 j행 i열 원소이다. 따라서 이중 `for`문으로 모든 (i, j)를 방문하며 `matB[j][i] = matA[i][j];`를 실행한다. 출력은 같은 이중 반복으로 행마다 `%3d`로 출력하고 줄을 바꾼다. 코드 앞의 주석은 2차원 배열을 함수로 넘겨 출력하려는 시도이며, 2차원 배열을 함수에 전달하는 방법은 [HW09 문제 2](../../Coursework/HW09_Pointers-II/Assignment-Explanation.ko.md#2-2차원-배열-출력)에서 다룬다.

**코드:** [Example_Transpose.c](Example_Transpose.c)

```c
#include <stdio.h>

// Passing array contents between functions (not covered yet)
/*void print_array(int* pmat[], int vsize, int hsize)
{
    int i, j;

    for (i = 0; i < vsize; i++)
    {
        for (j = 0; j < hsize; j++)
        {
            printf("%3d", *pmat);
            *pmat++;
        }
        printf("\n");
    }
}*/

int main()
{
    int matA[][3] = { {5, 7, 4}, {6, 1, 8}, {3, 2, 7} };
    int matB[3][3] = { 0 };
    int i, j;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            matB[j][i] = matA[i][j];
        }
    }

    printf("[matA] \n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%3d", matA[i][j]);
        }
        printf("\n");
    }

    printf("[matB] \n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%3d", matB[i][j]);
        }
        printf("\n");
    }
}
```

```text
[matA] 
  5  7  4
  6  1  8
  3  2  7
[matB] 
  5  6  3
  7  1  2
  4  8  7
```

`matA`의 첫 행 5, 7, 4가 `matB`의 첫 열이 되었다. 대각선 원소 5, 1, 7은 전치해도 같은 자리에 남는다.

---

<br>

## 요약

| 개념 | 핵심 요약 |
|:-----|:-----|
| 배열 | 같은 타입의 변수 여러 개를 연속된 메모리에 확보한 것이며, 크기, 원소의 타입, 이름으로 선언한다. |
| 인덱스 | 원소의 위치를 나타내며 0부터 시작하므로, 크기가 n인 배열의 마지막 인덱스는 n - 1이다. |
| 1차원 초기화 | 초기값으로 크기를 정할 수 있고, 초기값이 부족하면 나머지 원소는 0이 된다. |
| 반복문과 배열 | 인덱스를 반복 변수로 바꾸어 원소를 차례로 처리하며, 원소 수는 `sizeof(arr) / sizeof(arr[0])`로 구한다. |
| 다차원 배열 | 대괄호의 개수가 차원 수이고, 2차원 배열은 `arr[행][열]`로 접근한다. |
| 메모리 구성 | 다차원 배열도 연속된 메모리에 행 우선 순서로 저장된다. |
| 2차원 초기화 | 행마다 중괄호로 묶으면 행별로, 하나로 나열하면 행 우선으로 채우고 나머지는 0이 된다. |
| 크기 생략 | 2차원 배열은 행의 수만 생략할 수 있고 열의 수는 반드시 써야 한다. |
| 순차 탐색 | 처음부터 끝까지 비교하며, 같은 값이 여러 개이면 `break` 없이 끝까지 세어야 모두 찾는다. |
| 전치 | `matB[j][i] = matA[i][j]`로 행과 열을 바꾼다. |

---

<br>

## 점검 문제

1. **인덱스:** `int score[30];`의 첫 원소와 마지막 원소를 쓰고, `score[30]`에 값을 대입하면 어떤 문제가 생기는지 설명하라.

   <details>
   <summary>정답</summary>

   첫 원소는 `score[0]`, 마지막 원소는 `score[29]`이다. `score[30]`은 배열의 범위를 넘는 위치이며, C는 범위를 검사하지 않으므로 그 자리의 다른 데이터를 덮어쓰는 정의되지 않은 동작이 된다.

   </details>

2. **초기화:** `int d[6] = {5, 6};`일 때 `d[1]`과 `d[4]`의 값은 무엇인가?

   <details>
   <summary>정답</summary>

   `d[1]`은 두 번째 초기값 6이고, 초기값이 없는 `d[4]`는 0이다.

   </details>

3. **원소의 개수:** `double v[] = {1.5, 2.5, 3.5, 4.5};`에서 `sizeof(v)`와 `sizeof(v) / sizeof(v[0])`의 값을 쓰라.

   <details>
   <summary>정답</summary>

   `double`이 8바이트이고 원소가 4개이므로 `sizeof(v)`는 32이고, 원소의 개수는 32 / 8 = 4이다.

   </details>

4. **2차원 초기화:** `int m[2][3] = { {1}, {2, 3} };`과 `int n[2][3] = { 1, 2, 3 };`의 원소를 행마다 쓰라.

   <details>
   <summary>정답</summary>

   `m`은 행마다 중괄호로 묶었으므로 첫 행이 1, 0, 0이고 둘째 행이 2, 3, 0이다. `n`은 하나로 나열했으므로 첫 행이 1, 2, 3이고 둘째 행이 0, 0, 0이다.

   </details>

5. **메모리 배치:** `int a[3][4];`에서 `a[2][1]`은 배열 시작에서 몇 번째 원소이며, `int`가 4바이트일 때 몇 바이트 떨어져 있는가?

   <details>
   <summary>정답</summary>

   행 우선으로 저장되므로 2 × 4 + 1 = 9, 즉 0부터 세어 9번째 원소이며, 9 × 4 = 36바이트 떨어져 있다.

   </details>
