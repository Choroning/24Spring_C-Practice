# Chapter 5 Solutions — Control Statements

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-19
>
> Warming-Up C Programming, 천정아, Ch 5

**Problem Source:** Prof. Younghee Im, Computer Language Ⅰ (DCCS101-04)

---

<br>

## Table of Contents

- [Exercise 1: Quadrant of a Point in the Plane](#exercise-1-quadrant-of-a-point-in-the-plane)
- [Exercise 2: Converting Between Celsius and Fahrenheit](#exercise-2-converting-between-celsius-and-fahrenheit)
- [Exercise 3: Roots of a Quadratic Equation](#exercise-3-roots-of-a-quadratic-equation)
- [Exercise 4: Sum and Average of Integers](#exercise-4-sum-and-average-of-integers)
- [Exercise 5: Triangle Printing Menu](#exercise-5-triangle-printing-menu)

---

<br>

## Exercise 1: Quadrant of a Point in the Plane

**Textbook Problem:** Page 182, problem 3

**Problem:** Read the coordinates (x, y) of a point and print whether it is the origin, on the x-axis, on the y-axis, or in quadrant 1-4. The full problem and sample runs are in [Exercise 1](Exercises.md#exercise-1-quadrant-of-a-point-in-the-plane).

### Solution

**Approach:** Use nested `if` statements that first split into three branches by the sign of x (positive, zero, negative) and then split each branch into three by the sign of y ([Chapter 5, Section 2.5](Concepts_Lecture.md#25-nested-if)). All 3 × 3 = 9 combinations are handled without gaps or overlaps.

- **x > 0:** y > 0 is quadrant 1, y = 0 is on the x-axis, and y < 0 is quadrant 4.
- **x = 0:** y > 0 is on the y-axis, y = 0 is the origin, and y < 0 is printed as `y축 아래` (below the y-axis).
- **x < 0:** y > 0 is quadrant 2, y = 0 is on the x-axis, and y < 0 is quadrant 3.

**Code:** [Lab_Q1.c](../../Coursework/Lab05_Control-Statements/Lab_Q1.c)

```c
/**
 * @file    A10104-1_C05Q1.c
 * @brief   Q1. 이차원 평면의 점 좌표 사분면 판별
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-02
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main(void)
{
    int posx, posy;

    // 사용자로부터 좌표를 입력받음
    printf("좌표 (x, y)? ");
    scanf_s(" %d %d", &posx, &posy);

    if (posx > 0) {
        if (posy > 0)
            printf("(%d, %d)는 제1사분면에 위치합니다.\n", posx, posy);
        else if (posy == 0)
            printf("(%d, %d)는 x축 위에 위치합니다.\n", posx, posy);
        else
            printf("(%d, %d)는 제4사분면에 위치합니다.\n", posx, posy);
    }
    else if (posx == 0) {
        if (posy > 0)
            printf("(%d, %d)는 y축 위에 위치합니다.\n", posx, posy);
        else if (posy == 0)
            printf("(%d, %d)는 원점에 위치합니다.\n", posx, posy);
        else
            printf("(%d, %d)는 y축 아래에 위치합니다.\n", posx, posy);
    }
    else {  // posx < 0
        if (posy > 0)
            printf("(%d, %d)는 제2사분면에 위치합니다.\n", posx, posy);
        else if (posy == 0)
            printf("(%d, %d)는 x축 위에 위치합니다.\n", posx, posy);
        else
            printf("(%d, %d)는 제3사분면에 위치합니다.\n", posx, posy);
    }

    return 0;
}
```

**Output:** These are the results of running eight cases in order: the five cases of the sample runs plus quadrant 2, quadrant 3, and the negative side of the y-axis. The classification matches the sample runs, but the wording differs. The input prompt is `좌표 (x, y)? `, the coordinates are printed with a space after the comma, as in `(0, 0)`, and the quadrant is printed as `제1사분면에` instead of `1사분면 위에`.

```text
좌표 (x, y)? 0 0
(0, 0)는 원점에 위치합니다.
좌표 (x, y)? -2 0
(-2, 0)는 x축 위에 위치합니다.
좌표 (x, y)? 0 10
(0, 10)는 y축 위에 위치합니다.
좌표 (x, y)? 3 7
(3, 7)는 제1사분면에 위치합니다.
좌표 (x, y)? -4 1
(-4, 1)는 제2사분면에 위치합니다.
좌표 (x, y)? -3 -8
(-3, -8)는 제3사분면에 위치합니다.
좌표 (x, y)? 8 -2
(8, -2)는 제4사분면에 위치합니다.
좌표 (x, y)? 0 -5
(0, -5)는 y축 아래에 위치합니다.
```

> **Note:** A point such as (0, -5), with x equal to 0 and y negative, also lies on the y-axis. The code prints this case as `y축 아래에 위치합니다` to indicate the negative side of the y-axis, while it prints points on the x-axis as `x축 위` regardless of the sign of x, so the two axes are described differently.

> **Note:** **`scanf_s` and the build environment.** The `scanf_s` used by the code of Exercises 1-4 is a function provided by Visual Studio (MSVC). Most standard libraries used with gcc and clang do not provide it, so the outputs in this document were produced without changing the code by compiling with `gcc -std=c99 -Wall -Dscanf_s=scanf`, which replaces `scanf_s` with `scanf`. The line `Program ended with exit code: 0` in the sample runs is not program output but the exit message added by the Xcode console.

---

<br>

## Exercise 2: Converting Between Celsius and Fahrenheit

**Textbook Problem:** Page 183, problem 5

**Problem:** Read an integer temperature and a unit letter (C or F, in either case), and convert Celsius to Fahrenheit and Fahrenheit to Celsius. The input must be accepted with or without a space before the unit, and a `switch` statement must be used. The full problem and sample runs are in [Exercise 2](Exercises.md#exercise-2-converting-between-celsius-and-fahrenheit).

### Solution

**Approach:** Use the unit letter as the expression of the `switch`, and place the uppercase and lowercase cases one after the other so that they execute the same statements ([Chapter 5, Section 2.7](Concepts_Lecture.md#27-switch)).

- **Input:** In the format string `" %d %c"`, the space before `%c` skips zero or more whitespace characters, so `32C` and `100 f` are read the same way.
- **Case labels:** 67, 99, 70, and 102 are the ASCII codes of `'C'`, `'c'`, `'F'`, and `'f'`. Writing the character constant `'C'` gives the same value and shows the intent more clearly.
- **Conversion formulas:** In `(double)temp * 9 / 5 + 32`, the cast is applied first, so every operation is computed in floating point. Computing in integers, as in `temp * 9 / 5`, would discard the fractional part. The Celsius conversion `((double)temp - 32) * 5 / 9` casts first for the same reason.
- **Output:** The input temperature is printed without decimals with `%.0lf`, and the converted value is printed to two decimal places with `%.2lf`. If the unit letter is none of the four, `default` prints an error message.

**Code:** [Lab_Q2.c](../../Coursework/Lab05_Control-Statements/Lab_Q2.c)

```c
/**
 * @file    A10104-1_C05Q2.c
 * @brief   Q2. 섭씨 ↔ 화씨 단위 변환
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-02
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
    int temp = 0;
    char tempal = 0;
    double cel = 0, far = 0;

    printf("온도? ");
    scanf_s(" %d %c", &temp, &tempal);

    switch (tempal) {
    case 67:  // 'C'
    case 99:  // 'c'
        //cel = temp;
        far = (double)temp * 9 / 5 + 32;
        printf("%.0lf C == %.2lf F", (double)temp, far);
        break;
    case 70:  // 'F'
    case 102: // 'f'
        //far = temp;
        cel = ((double)temp - 32) * 5 / 9;
        printf("%.0lf F == %.2lf C", (double)temp, cel);
        break;
    default:
        printf("입력 오류! 온도 단위는 C(혹은 c)와 F(혹은 f)만 허용됩니다.");
        break;
    }

    return 0;
}
```

**Output:** The converted values match the three sample runs. The error message, `입력 오류! 온도 단위는 C(혹은 c)와 F(혹은 f)만 허용됩니다.`, is worded differently from the sample run, and every output ends without a newline. 32°C is 32 × 9 / 5 + 32 = 89.6°F, and 100°F is (100 - 32) × 5 / 9 = 37.777...°C.

```text
온도? 32C
32 C == 89.60 F
온도? 100 f
100 F == 37.78 C
온도? -28 g
입력 오류! 온도 단위는 C(혹은 c)와 F(혹은 f)만 허용됩니다.
```

> **Caution:** MSVC's `scanf_s` is defined to take an extra argument giving the buffer size for each `%c`, `%s`, and `%[` conversion. The call `scanf_s(" %d %c", &temp, &tempal)` in this code lacks that argument, so it does not follow the `scanf_s` contract; to keep `scanf_s`, a size of 1 must be passed, as in `scanf_s(" %d %c", &temp, &tempal, 1)`. Also, the temperature is read with `%d`, so entering a decimal such as `32.5C` makes the `.` after 32 be read as the unit letter, and the error message is printed.

```text
온도? 32.5C
입력 오류! 온도 단위는 C(혹은 c)와 F(혹은 f)만 허용됩니다.
```

---

<br>

## Exercise 3: Roots of a Quadratic Equation

**Problem:** Read integer coefficients a, b, c, determine from the sign of the discriminant $b^2 - 4ac$ whether the equation has imaginary roots, a double root, or two distinct real roots, and compute the real roots. Avoid integer division and compute the square root with `sqrt()`. The full problem and sample runs are in [Exercise 3](Exercises.md#exercise-3-roots-of-a-quadratic-equation).

### Solution

**Approach:** Compute the discriminant first and separate the three cases, negative, zero, and positive, with an `else if` ladder ([Chapter 5, Section 2.4](Concepts_Lecture.md#24-else-if)).

- **Discriminant:** `(b * b) - (4 * a * c)` is computed in integers and stored in the `double` variable `cal`. Because it consists of integer multiplication and subtraction, the value is exact, so the comparison `cal == 0` also works exactly.
- **Roots:** In `(-b + sqrt(cal)) / (2 * a)`, `sqrt()` returns a `double`, so the numerator is floating-point and the division is floating-point division. For a double root, `sqrt(0)` is 0, so `ans1` equals $-\frac{b}{2a}$.
- **Handling a = 0:** The problem assumes $a \neq 0$, but the code first checks with `if (a)` whether a is 0 and, if so, prints an error message saying that the equation is not quadratic.
- **Output:** `%g` chooses the shorter of `%f` and `%e` within 6 significant digits and removes trailing zeros, so 1 is printed as `1` and 2/3 as `0.666667`.

**Code:** [Lab_Q3.c](../../Coursework/Lab05_Control-Statements/Lab_Q3.c)

```c
/**
 * @file    A10104-1_C05Q3.c
 * @brief   Q3. 이차 방정식의 근 계산
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-03
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>
#include <math.h>

int main()
{
    int a, b, c;
    double cal, ans1, ans2;

    printf("이차 방정식의 상관계수 a, b, c 입력: ");
    scanf_s(" %d %d %d", &a, &b, &c);

    cal = (b * b) - (4 * a * c);
    ans1 = (-b + sqrt(cal)) / (2 * a);
    ans2 = (-b - sqrt(cal)) / (2 * a);

    if (a) {  // a != 0일 때 이차 방정식으로 계산을 수행
        if (cal < 0)
            printf("입력하신 이차 방정식은 허근을 갖습니다.");
        else if (cal == 0)
            printf("입력하신 이차 방정식의 중근 x = %g입니다.", ans1);
        else
            printf("입력하신 이차 방정식의 해는 x1 = %g, x2 = %g입니다.", ans1, ans2);
    }
    else
        printf("입력 오류! a = 0일 때 이차 방정식이 성립하지 않습니다.");

    return 0;
}
```

**Output:** The values of the roots and the classification match the three sample runs. The wording differs from the sample runs, as in `입력하신 이차 방정식의 해는 x1 = 1, x2 = -0.666667입니다.` and `입력하신 이차 방정식의 중근 x = 0.666667입니다.`, and the output ends without a newline. The last run enters 0 for a.

```text
이차 방정식의 상관계수 a, b, c 입력: 3 -1 -2
입력하신 이차 방정식의 해는 x1 = 1, x2 = -0.666667입니다.
이차 방정식의 상관계수 a, b, c 입력: 9 -12 4
입력하신 이차 방정식의 중근 x = 0.666667입니다.
이차 방정식의 상관계수 a, b, c 입력: 1 1 1
입력하신 이차 방정식은 허근을 갖습니다.
이차 방정식의 상관계수 a, b, c 입력: 0 2 1
입력 오류! a = 0일 때 이차 방정식이 성립하지 않습니다.
```

> **Note:** The code computes both roots before checking the sign of the discriminant. If the discriminant is negative, `sqrt()` returns `nan`, and if a is 0, the code divides by zero, but these values are never printed and, being floating-point operations, do not stop the program. Computing the roots only after confirming that the discriminant is non-negative and a is not 0 would be logically cleaner.

---

<br>

## Exercise 4: Sum and Average of Integers

**Problem:** With a `while` statement, repeatedly read integers until `-1` is entered, then print the sum and the average (to two decimal places) of the inputs excluding `-1`. The full problem and sample run are in [Exercise 4](Exercises.md#exercise-4-sum-and-average-of-integers).

### Solution

**Approach:** Inside an infinite `while (1)` loop, exit with `break` when the input is the sentinel `-1`, and otherwise update the accumulator `sum1` and the counter `count` ([Chapter 5, Section 5.1](Concepts_Lecture.md#51-counter-and-accumulator)).

- **Sentinel handling:** The input is checked for `-1` before it is accumulated, so `-1` is not counted in the sum or the count. 0 is not the sentinel, so it is included in the sum and the count like any other value.
- **Average:** `(double)sum1 / count` performs floating-point division, and `%.2f` prints the result to two decimal places. 196 / 5 = 39.2.

**Code:** [Lab_Q4.c](../../Coursework/Lab05_Control-Statements/Lab_Q4.c)

```c
/**
 * @file    A10104-2_C05Q1.c
 * @brief   Q1. 정수의 합과 평균 계산
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-09
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
    int num = -1, sum1 = 0, count = 0;
    double ave = 0;
    
    while (1) {
        printf("정수 입력(종료: -1): ");
        scanf_s(" %d", &num);
        
        if (num == -1)
            break;
        else {
            sum1 = sum1 + num;
            count++;
        }
    }
    ave = (double)sum1 / count;
    printf("입력된 수의 합: %d\n", sum1);
    printf("입력된 수의 평균: %.2f\n", ave);

    return 0;
}
```

**Output:** The sum and the average match the sample run. The result labels read `입력된 수의 합` and `입력된 수의 평균` instead of `입력된 정수의 합`.

```text
정수 입력(종료: -1): 10
정수 입력(종료: -1): 27
정수 입력(종료: -1): 61
정수 입력(종료: -1): 0
정수 입력(종료: -1): 98
정수 입력(종료: -1): -1
입력된 수의 합: 196
입력된 수의 평균: 39.20
```

> **Caution:** If `-1` is entered first, `count` stays 0 and the program computes `(double)sum1 / count`, that is, 0.0 / 0, so the average is printed as `nan`. As in the sentinel example of Chapter 5, Section 3.2, printing the average only when at least one value was entered, with `if (count > 0)`, handles this case.

```text
정수 입력(종료: -1): -1
입력된 수의 합: 0
입력된 수의 평균: nan
```

---

<br>

## Exercise 5: Triangle Printing Menu

**Problem:** Complete the example code by filling in its blanks so that menu items 1-4 choose a left-aligned triangle, a right-aligned triangle, a left-aligned inverted triangle, or a right-aligned inverted triangle, read its size (number of lines), and print it with `*`, and item 5 ends the program. An invalid menu item is read again. The full problem and sample runs are in [Exercise 5](Exercises.md#exercise-5-triangle-printing-menu).

### Solution

**Approach:** The outer `while (1)` shows the menu repeatedly, and the inner `do-while` repeats the input until a valid menu item is received ([Chapter 5, Section 5.4](Concepts_Lecture.md#54-menu-driven-program)). Each case of the `switch` draws its triangle with nested `for` loops. The key is to decide the number of spaces and stars for the i-th line of the outer loop (i from 1 to size) ([Chapter 5, Section 3.4](Concepts_Lecture.md#34-nested-loops)).

- **Menu input:** `scanf(" %c", &menu)` reads one character; if it is outside `'1'`-`'5'`, an error message is printed and the input is read again, and if it is in range, `break` exits the `do-while`. Because the menu is a `char`, it is compared with the characters `'1'` and `'5'`, not with numbers.
- **Exit:** If the menu item is `'5'`, the program prints the exit message and leaves the outer `while` with `break`.
- **Case 1 (left-aligned triangle):** Line i prints i stars.
- **Case 2 (right-aligned triangle):** The loop from `j = size - i` down to 1 prints size - i spaces, followed by i stars.
- **Case 3 (left-aligned inverted triangle):** The loop runs from `j = size - i` down to 0, so it prints size - i + 1 stars. The first line has size stars and the last line has 1.
- **Case 4 (right-aligned inverted triangle):** The loop from `j = 1` to i prints i spaces, followed by size - i + 1 stars.

**Code:** [Lab_Q5.c](../../Coursework/Lab05_Control-Statements/Lab_Q5.c)

```c
/**
 * @file    A10104-2_C05Q2.c
 * @brief   Q2. 삼각형 출력 메뉴
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-10
 * 
 * @note    <windows.h> 헤더는 Windows 이외의 개발환경에서
 *          오류가 발생할 수 있음에 주의하시기 바랍니다.
 */

#pragma warning(disable:4996)
#include <stdio.h>
#include <windows.h>    // system 함수를 사용하기 위해 추가

int main()
{
    int size, i, j;
    char menu;

    while (1) {
        printf("-------------------------------\n");
        printf("1. 왼쪽 정렬 삼각형 출력\n");
        printf("2. 오른쪽 정렬 삼각형 출력\n");
        printf("3. 왼쪽 정렬 역삼각형 출력\n");
        printf("4. 오른쪽 정렬 역삼각형 출력\n");
        printf("5. 종료\n");
        printf("-------------------------------\n");

        do {
            printf("=> 메뉴 선택: ");
            scanf(" %c", &menu);
            if (menu < '1' || menu > '5')
                printf("입력 오류! 메뉴를 다시 선택하세요. \n");
            else
                break;
        } while (1);

        if (menu == '5') {
            printf("프로그램을 종료합니다. \n");
            break;
        }

        printf("=> 삼각형 크기(line 수) 입력: ");
        scanf(" %d", &size);

        switch (menu) {
        case '1':
            for (i = 1; i <= size; i++) {
                for (j = 1; j <= i; j++)
                    printf("*");
                printf("\n");
            }
            break;
        case '2':
            for (i = 1; i <= size; i++) {
                for (j = size - i; j >= 1; j--)
                    printf(" ");
                for (j = 1; j <= i; j++)
                    printf("*");
                printf("\n");
            }
            break;
        case '3':
            for (i = 1; i <= size; i++) {
                for (j = size - i; j >= 0; j--)
                    printf("*");
                printf("\n");
            }
            break;
        case '4':
            for (i = 1; i <= size; i++) {
                for (j = 1; j <= i; j++)
                    printf(" ");
                for (j = size - i; j >= 0; j--)
                    printf("*");
                printf("\n");
            }
            break;
        }

        system("pause");
        system("cls");
    }

    return 0;
}
```

**Output:** Menu item 1 and the error handling give the same results as the sample runs. The code's separator has 31 `-` characters, longer than the 24 in the sample runs, the triangle is printed right after the size is entered without a blank line, and some messages end with a trailing space. Each run printed a triangle and then ended with 5.

```text
-------------------------------
1. 왼쪽 정렬 삼각형 출력
2. 오른쪽 정렬 삼각형 출력
3. 왼쪽 정렬 역삼각형 출력
4. 오른쪽 정렬 역삼각형 출력
5. 종료
-------------------------------
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
-------------------------------
1. 왼쪽 정렬 삼각형 출력
2. 오른쪽 정렬 삼각형 출력
3. 왼쪽 정렬 역삼각형 출력
4. 오른쪽 정렬 역삼각형 출력
5. 종료
-------------------------------
=> 메뉴 선택: 5
프로그램을 종료합니다. 
```

Menu item 4 differs from the sample run. The first inner loop of case 4 prints i spaces instead of i - 1, so every line is shifted one column to the right compared with the sample run. The first line is ` *******` instead of `*******`. To match the sample run, the condition of the space loop should be `j < i` so that only i - 1 spaces are printed.

```text
-------------------------------
1. 왼쪽 정렬 삼각형 출력
2. 오른쪽 정렬 삼각형 출력
3. 왼쪽 정렬 역삼각형 출력
4. 오른쪽 정렬 역삼각형 출력
5. 종료
-------------------------------
=> 메뉴 선택: 4
=> 삼각형 크기(line 수) 입력: 7
 *******
  ******
   *****
    ****
     ***
      **
       *
-------------------------------
1. 왼쪽 정렬 삼각형 출력
2. 오른쪽 정렬 삼각형 출력
3. 왼쪽 정렬 역삼각형 출력
4. 오른쪽 정렬 역삼각형 출력
5. 종료
-------------------------------
=> 메뉴 선택: 5
프로그램을 종료합니다. 
```

```text
-------------------------------
1. 왼쪽 정렬 삼각형 출력
2. 오른쪽 정렬 삼각형 출력
3. 왼쪽 정렬 역삼각형 출력
4. 오른쪽 정렬 역삼각형 출력
5. 종료
-------------------------------
=> 메뉴 선택: 9
입력 오류! 메뉴를 다시 선택하세요. 
=> 메뉴 선택: 5
프로그램을 종료합니다. 
```

> **Note:** **Windows-specific parts.** `<windows.h>`, `system("pause")`, and `system("cls")` assume a Windows environment. `pause` prints `계속하려면 아무 키나 누르십시오 . . .` ("Press any key to continue . . .") and waits for a key, and `cls` clears the screen. The `system()` function itself is a standard function declared in `<stdlib.h>`. The outputs above were obtained on macOS without changing the code by putting a directory with an empty `windows.h` on the include path and compiling with `gcc -std=c99 -Wall -include stdlib.h`; macOS has no `pause` or `cls` command, so the error messages the shell prints to standard error are omitted. `#pragma warning(disable:4996)` is an MSVC-only directive that turns off the C4996 warning MSVC issues for `scanf`, and gcc and clang ignore it as an unknown pragma.
