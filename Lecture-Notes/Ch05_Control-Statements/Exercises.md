# Chapter 5 Exercises — Control Statements

[Repository Guide](../../README.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

> **Last Updated:** 2026-10-19
>
> Warming-Up C Programming, 천정아, Ch 5

**Problem Source:** Prof. Younghee Im, Computer Language Ⅰ (DCCS101-04)

Exercises 1-3 practice conditional (selection) statements, and Exercises 4 and 5 practice loop statements.

---

<br>

## Exercise 1: Quadrant of a Point in the Plane

**Textbook Problem:** Page 182, problem 3

**Problem:** Write a program that reads the coordinates `(x,y)` of a point in the two-dimensional plane and prints which quadrant the point lies in.

- **Input:** The coordinates of the point (x value, y value)
- **Output:** One of the origin, on the x-axis, on the y-axis, or a point in quadrant n

**Sample Runs:**

```text
점의 좌표 (x,y)? 0 0
(0,0)은 원점에 위치합니다.

Program ended with exit code: 0
```

```text
점의 좌표 (x,y)? -2 0
(-2,0)은 x축 위에 위치합니다.

Program ended with exit code: 0
```

```text
점의 좌표 (x,y)? 0 10
(0,10)은 y축 위에 위치합니다.

Program ended with exit code: 0
```

```text
점의 좌표 (x,y)? 3 7
(3,7)은 1사분면 위에 위치합니다.

Program ended with exit code: 0
```

```text
점의 좌표 (x,y)? 8 -2
(8,-2)은 4사분면 위에 위치합니다.

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-1-quadrant-of-a-point-in-the-plane)**

---

<br>

## Exercise 2: Converting Between Celsius and Fahrenheit

**Textbook Problem:** Page 183, problem 5

**Problem:** Write a program that reads a temperature and converts Celsius to Fahrenheit and Fahrenheit to Celsius. Use the following formulas for the conversion.

$$\text{Celsius} = \frac{5}{9} \times (\text{Fahrenheit} - 32)$$

$$\text{Fahrenheit} = \frac{9}{5} \times \text{Celsius} + 32$$

- **Input:** A temperature and its unit (C for Celsius, F for Fahrenheit)
- **Output:** The converted temperature

**Program Requirements:**

1. The temperature unit must be accepted regardless of letter case and spacing.
2. The program must use a `switch` statement.

**Sample Runs:**

```text
온도? 32C
32 C == 89.60 F

Program ended with exit code: 0
```

```text
온도? 100 f
100 F == 37.78 C

Program ended with exit code: 0
```

```text
온도? -28 g
입력 오류! 온도의 단위는 C(또는 c)와 F(또는 f)만 가능합니다.

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-2-converting-between-celsius-and-fahrenheit)**

---

<br>

## Exercise 3: Roots of a Quadratic Equation

**Problem:** Write a program that reads the coefficients a, b, c of the quadratic equation $ax^2 + bx + c = 0$ and computes its roots.

- **Input:** The coefficients a, b, c of the quadratic equation ($a \neq 0$, and a, b, c are all integers)
- **Output:** The roots of the quadratic equation

**Program Requirements:**

1. The roots of the quadratic equation are determined by the value of the discriminant $b^2 - 4ac$ as follows. Use the quadratic formula to compute the roots.
   - If $b^2 - 4ac < 0$, the equation has imaginary roots.
   - If $b^2 - 4ac = 0$, the equation has a double root $x = -\frac{b}{2a}$.
   - If $b^2 - 4ac > 0$, the equation has two distinct roots $x = \frac{-b \pm \sqrt{b^2 - 4ac}}{2a}$. Of the ± in the numerator, the root with + is written x1 and the root with - is written x2.
2. When computing the roots, take care that integer division does not occur, and print the exact results.
3. Compute the square root with the library function `sqrt()` (header `<math.h>`).

**Sample Runs:**

```text
이차 방정식의 상관계수 a, b, c 입력: 3 -1 -2
입력하신 이차 방정식은 두 근 x1 = 1, x2 = -0.666667 을 갖습니다.

Program ended with exit code: 0
```

```text
이차 방정식의 상관계수 a, b, c 입력: 9 -12 4
입력하신 이차 방정식은 중근 x = 0.666667 을 갖습니다.

Program ended with exit code: 0
```

```text
이차 방정식의 상관계수 a, b, c 입력: 1 1 1
입력하신 이차 방정식은 허근을 갖습니다.

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-3-roots-of-a-quadratic-equation)**

---

<br>

## Exercise 4: Sum and Average of Integers

**Problem:** Write a program that repeatedly reads integers from the user and computes and prints their sum and average. When the user enters `-1`, stop reading and print the results; `-1` must not be included in the computation.

- **Input:** Integer values (enter `-1` to stop)
- **Output:** The sum and the average of the inputs

**Program Requirements:**

1. Use a `while` statement.
2. Compute the average accurately to two decimal places.
3. The `-1` entered to stop must not affect the computation.

**Sample Run:**

```text
정수 입력(종료: -1): 10
정수 입력(종료: -1): 27
정수 입력(종료: -1): 61
정수 입력(종료: -1): 0
정수 입력(종료: -1): 98
정수 입력(종료: -1): -1
입력된 정수의 합: 196
입력된 정수의 평균: 39.20

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-4-sum-and-average-of-integers)**

---

<br>

## Exercise 5: Triangle Printing Menu

**Problem:** Implement the following menu with nested `for` statements and a `switch` statement, and write a program that prints the triangle chosen by the user with `*` characters. Complete the program by filling in the `[빈칸]` (blank) parts of the example code below.

**Example Code:**

```c
#include <stdio.h>
#include <windows.h>    // system 함수 사용을 위한 헤더

int main() {
    int size, i, j;
    char menu;          // 메뉴 데이터형은 변경할 수 없습니다.

    while (1) {
        printf("------------------------\n");
        printf("1. 왼쪽 정렬 삼각형 출력\n");
        printf("2. 오른쪽 정렬 삼각형 출력\n");
        printf("3. 왼쪽 정렬 역삼각형 출력\n");
        printf("4. 오른쪽 정렬 역삼각형 출력\n");
        printf("5. 종료\n");
        printf("------------------------\n");

        do {
            [빈칸]
            // 메뉴를 입력받는다.
            // 유효한 입력인지 검사하고, 유효한 입력이면 반복을 종료한다.
            // 유효한 입력이 아니면 오류 메시지를 출력하고 다시 입력받는다.
        } while (1);

        if ( [빈칸] ) {
            printf("프로그램을 종료합니다.\n");
            [빈칸]
        }

        printf("=> 삼각형 크기(line 수) 입력: ");
        scanf("%d", &size);

        switch (menu) {
        case '1': [빈칸]     // 왼쪽 정렬 삼각형 출력코드
        case '2': [빈칸]     // 오른쪽 정렬 삼각형 출력코드
        case '3': [빈칸]     // 왼쪽 정렬 역삼각형 출력코드
        case '4': [빈칸]     // 오른쪽 정렬 역삼각형 출력코드
        }
        system("pause");    // 화면 상태 유지
        system("cls");      // 화면 지우기
    }
}
```

**Sample Runs:**

```text
------------------------
1. 왼쪽 정렬 삼각형 출력
2. 오른쪽 정렬 삼각형 출력
3. 왼쪽 정렬 역삼각형 출력
4. 오른쪽 정렬 역삼각형 출력
5. 종료
------------------------
=> 메뉴 선택: 1
=> 삼각형 크기(line 수) 입력: 8

*
**
***
****
*****
******
*******
********

Program ended with exit code: 0
```

```text
------------------------
1. 왼쪽 정렬 삼각형 출력
2. 오른쪽 정렬 삼각형 출력
3. 왼쪽 정렬 역삼각형 출력
4. 오른쪽 정렬 역삼각형 출력
5. 종료
------------------------
=> 메뉴 선택: 4
=> 삼각형 크기(line 수) 입력: 7

*******
 ******
  *****
   ****
    ***
     **
      *

Program ended with exit code: 0
```

```text
------------------------
1. 왼쪽 정렬 삼각형 출력
2. 오른쪽 정렬 삼각형 출력
3. 왼쪽 정렬 역삼각형 출력
4. 오른쪽 정렬 역삼각형 출력
5. 종료
------------------------
=> 메뉴 선택: 9
입력 오류! 메뉴를 다시 선택하세요.
=> 메뉴 선택: 5
프로그램을 종료합니다.

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-5-triangle-printing-menu)**
