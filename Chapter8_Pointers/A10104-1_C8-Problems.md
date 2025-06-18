# Chapter 8. 포인터 실습

**문항 출처:** *임영희 교수, 컴퓨터언어Ⅰ 교수자 (DCCS101-04)* <br>
**Source:** *Prof. Younghee&nbsp;Im, Instructor of COMPUTER LANGUAGE Ⅰ (DCCS101-04)*

---

## Q1. 2차원 평면 좌표 계산기

2차원 평면 상의 좌표를 다루는 함수를 정의하고, 예시 코드를 참고하여 프로그램을 완성하시오.

<br>**프로그램 요구사항**

1. `display_point()` 함수
   x축과 y축 좌표값을 전달받아 좌표 형태로 출력하는 함수(실행 예시 참고)

2. `compute_distance()` 함수
   두 점의 좌표를 전달받아 두 점 사이의 거리를 계산해서 반환해주는 함수(출력문 없음)<br>
   두 점 사이의 거리 공식은 다음과 같다.<br>
   ![두 점 사이의 거리 공식](/src/images/C8_A10104-1_1.png)

3. `move_point()` 함수
   x축과 y축 좌표값, 그리고 이동량을 전달받아 x축과 y축 좌표값을 각각 이동량만큼 변경하는 함수

<br>**예시 코드**

```c
#include <stdio.h>
#include <math.h>

// 각 함수의 선언
[빈칸]

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

    // compute_distance()를 호출하여 두 점 사이의 거리를 계산한 후 출력(실행 예시 참고)
    [빈칸]

    printf("좌표 이동량 입력: ");
    scanf_s(" %d", &move);

    // move_point()를 호출하여 move만큼 p2에 해당하는 좌표값 변경
    [빈칸]

    printf("p2를 x축과 y축으로 각각 %d만큼 이동 = ", move);
    display_point(x2, y2);

    return 0;
}

// 각 함수의 정의
[빈칸]
```


<br>**실행 예시**

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


---

## Q2. 로또 프로그램

다음은 1 - 45 사이의 숫자 중 6개를 무작위로 선택하는 로또 프로그램이다. 프로그램 요구사항을 충족하도록 프로그램을 완성하시오.

<br>**프로그램 요구사항**

1. 배열과 배열의 크기를 전달받아 출력하는 함수
   <br>(단, 포인터의 증가연산(++)을 이용할 것)
   
   ```c
   void printArray(const int p[], int size);
   ```

2. 배열과 배열의 크기를 전달받아 중복을 검사하는 함수
   <br>6개의 로또 번호 중 중복되는 것이 있으면 1을, 중복된 번호가 없으면 0을 반환해야 한다.
   <br>(단, 포인터의 색인화를 이용할 것)
   
   ```c
   int existDuplication(const int p[], int size);
   ```

3. 배열과 배열의 크기를 전달받아 선택 정렬을 수행하는 함수
   <br>정렬과정에서 두 원소를 swap하는 연산은 `swap()` 함수
   <br>(단, 포인터의 산술연산을 이용할 것)
   
   ```c
   void selectionSort(int p[], int size);
   ```


<br>**실행 예시**

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

        [빈칸]      // SelectionSort() 함수 호출
        printArray(lotto, 6);
    }
    printf("\n행운을 빕니다!\n");

    return 0;
}

// 각 함수의 정의
[빈칸]
```


---
