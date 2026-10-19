# Chapter 8 Exercises — Pointers

[Repository Guide](../../README.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

> **Last Updated:** 2026-10-19

**Problem Source:** Prof. Younghee Im, Computer Language Ⅰ (DCCS101-04)

---

<br>

## Exercise 1: 2D Plane Coordinate Calculator

**Problem:** Define functions that handle coordinates on a 2D plane and complete the program by referring to the example code. The problem practices the ways of passing function arguments (pass by value and pass by reference).

**Program Requirements:**

1. The `display_point()` function receives x and y coordinate values and prints them in coordinate form (see the sample run).

2. The `compute_distance()` function receives the coordinates of two points, computes the distance between them, and returns it (no output statement).
   The distance between two points is given by the following formula.

   $$\sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2}$$

3. The `move_point()` function receives x and y coordinate values and a displacement, and changes each of the x and y coordinate values by the displacement.

**Example Code:** Complete the program by filling in the parts marked `[빈칸]` (blank).

```c
#include <stdio.h>
#include <math.h>

// 각 함수의 선언
[빈칸]

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

    // compute_distance()를 호출하여 두 점 사이의 거리를 계산한 후 출력(실행 예시 참고)
    [빈칸]

    printf("좌표 이동량 입력: ");
    scanf("%d", &move);

    // move_point()를 호출하여 move만큼 p2에 해당하는 좌표값 변경
    [빈칸]

    printf("p2를 x축과 y축으로 각각 %d 만큼 이동 = ", move);
    display_point(x2, y2);

    return 0;
}

// 각 함수의 정의
[빈칸]
```

**Sample Run:**

```text
p1 좌표 입력(x축, y축 좌표값 입력): 1 1
p2 좌표 입력(x축, y축 좌표값 입력): 3 7
p1 = (1, 1)
p2 = (3, 7)
두 점 사이의 거리 = 6.32456

좌표 이동량 입력: -1
p2를 x축과 y축으로 각각 -1 만큼 이동 = (2, 6)

Program ended with exit code: 0
```

```text
p1 좌표 입력(x축, y축 좌표값 입력): -2 4
p2 좌표 입력(x축, y축 좌표값 입력): 3 -5
p1 = (-2, 4)
p2 = (3, -5)
두 점 사이의 거리 = 10.2956

좌표 이동량 입력: 3
p2를 x축과 y축으로 각각 3 만큼 이동 = (6, -2)

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-1-2d-plane-coordinate-calculator)**

---

<br>

## Exercise 2: Lotto Program

**Problem:** The following is a lotto program that randomly selects 6 numbers from 1-45. Complete the program so that it satisfies the program requirements.

**Program Requirements:**

1. Write a function that receives an array and its size and prints the array.
   It must use the pointer increment operation (`++`).
   
   ```c
   void printArray(const int p[], int size);
   ```

2. Write a function that receives an array and its size and checks for duplicates.
   It must return 1 if any of the 6 lotto numbers are duplicated and 0 if there is no duplicate.
   It must use pointer indexing (applying the subscript `[]` to a pointer).
   
   ```c
   int existDuplication(const int p[], int size);
   ```

3. Write a function that receives an array and its size and performs selection sort.
   The operation that swaps two elements during sorting must be done by calling the `swap()` function.
   It must use pointer arithmetic.
   
   ```c
   void selectionSort(int p[], int size);
   ```

**Example Code:** Complete the program by filling in the parts marked `[빈칸]` (blank).

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int p[], int size);       // 포인터의 증가연산 이용
int existDuplication(int p[], int size);  // 포인터의 색인화 이용
void swap(int* p, int* q);                // 두 정수의 swap
void selectionSort(int p[], int size);    // 포인터의 산술연산 이용

int main() {
    int lotto[6], setNo;

    srand((unsigned int)time(NULL));      // rand() 함수의 seed 값 자동 설정
    printf("몇 세트의 복권 번호를 생성할까요? ");
    scanf("%d", &setNo);

    for (int k = 0; k < setNo; k++) {
        do { // 중복 번호가 없을 때까지 반복
            for (int i = 0; i < 6; i++)
                lotto[i] = rand() % 45 + 1;

            // printArray(lotto, 6);      // 중복된 번호가 있는지 확인하기 위한 출력문
        } while ( [빈칸] );                // existDuplication() 함수 호출

        [빈칸]      // selectionSort() 함수 호출
        printArray(lotto, 6);
    }
    printf("\n행운을 빕니다!\n");

    return 0;
}

// 각 함수의 정의
[빈칸]
```

**Sample Run:** The numbers differ randomly on every run.

```text
몇 세트의 복권 번호를 생성할까요? 5
 3   6  20  24  30  45
12  17  19  25  26  28
 5  15  26  29  43  45
19  20  22  32  40  44
 3   7  11  16  38  39

행운을 빕니다!

Program ended with exit code: 0
```

```text
몇 세트의 복권 번호를 생성할까요? 3
13  23  27  33  38  45
 1  13  16  24  28  29
 1   3  10  13  40  43

행운을 빕니다!

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-2-lotto-program)**
