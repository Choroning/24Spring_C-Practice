# Chapter 5 Solutions — Control Statements

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-27
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
- [Exercise 6: Statements About the if Statement](#exercise-6-statements-about-the-if-statement)
- [Exercise 7: The Keyword for a False Condition](#exercise-7-the-keyword-for-a-false-condition)
- [Exercise 8: Rewriting the Conditional Operator with if](#exercise-8-rewriting-the-conditional-operator-with-if)
- [Exercise 9: Statements About the switch Statement](#exercise-9-statements-about-the-switch-statement)
- [Exercise 10: Rewriting a switch Statement with if-else](#exercise-10-rewriting-a-switch-statement-with-if-else)
- [Exercise 11: Statements About the for Statement](#exercise-11-statements-about-the-for-statement)
- [Exercise 12: Rewriting a for Statement with while](#exercise-12-rewriting-a-for-statement-with-while)
- [Exercise 13: Statements About while and do-while](#exercise-13-statements-about-while-and-do-while)
- [Exercise 14: Branch Statements and Their Roles](#exercise-14-branch-statements-and-their-roles)
- [Exercise 15: Statements About Branch Statements](#exercise-15-statements-about-branch-statements)
- [Exercise 16: Finding Infinite Loops](#exercise-16-finding-infinite-loops)
- [Exercise 17: Output of a Nested if Statement](#exercise-17-output-of-a-nested-if-statement)
- [Exercise 18: Output of a for Loop with continue](#exercise-18-output-of-a-for-loop-with-continue)
- [Exercise 19: Grades by Absolute Evaluation](#exercise-19-grades-by-absolute-evaluation)
- [Exercise 20: Grades by Relative Evaluation](#exercise-20-grades-by-relative-evaluation)
- [Exercise 21: The Quadrant of a Point](#exercise-21-the-quadrant-of-a-point)
- [Exercise 22: Leap Year Test](#exercise-22-leap-year-test)
- [Exercise 23: Converting Celsius and Fahrenheit Temperatures](#exercise-23-converting-celsius-and-fahrenheit-temperatures)
- [Exercise 24: Electricity Bill with Progressive Rates](#exercise-24-electricity-bill-with-progressive-rates)
- [Exercise 25: Bitwise Operation Calculator](#exercise-25-bitwise-operation-calculator)
- [Exercise 26: Printing ASCII Characters](#exercise-26-printing-ascii-characters)
- [Exercise 27: Printing Multiples of an Integer](#exercise-27-printing-multiples-of-an-integer)
- [Exercise 28: Repeating the Electricity Bill Calculation](#exercise-28-repeating-the-electricity-bill-calculation)
- [Exercise 29: Prime Test](#exercise-29-prime-test)
- [Exercise 30: Printing the Primes up to N](#exercise-30-printing-the-primes-up-to-n)

---

<br>

## Exercise 1: Quadrant of a Point in the Plane

**Textbook Problem:** Chapter 5 programming assignment 3

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

**Output:** These are the results of running eight cases in order: the five cases of the sample runs plus quadrant 2, quadrant 3, and the negative side of the y-axis. The wording differs from the sample runs. The input prompt is `좌표 (x, y)? `, the coordinates are printed with a space after the comma, as in `(0, 0)`, and the quadrant is printed as `제1사분면에` instead of `1사분면 위에`.

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

> **Note:** **`scanf_s` and the build environment.** The `scanf_s` used by the code of Exercises 1-4 is a function provided by Visual Studio (MSVC). Most standard libraries used with gcc and clang do not provide it, so with these compilers the code compiles without changes as `gcc -std=c99 -Wall -Dscanf_s=scanf`, which replaces `scanf_s` with `scanf`. The line `Program ended with exit code: 0` in the sample runs is not program output but the exit message added by the Xcode console.

---

<br>

## Exercise 2: Converting Between Celsius and Fahrenheit

**Textbook Problem:** Chapter 5 programming assignment 5

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

**Output:** The error message, `입력 오류! 온도 단위는 C(혹은 c)와 F(혹은 f)만 허용됩니다.`, is worded differently from the sample run, and every output ends without a newline. 32°C is 32 × 9 / 5 + 32 = 89.6°F, and 100°F is (100 - 32) × 5 / 9 = 37.777...°C.

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

**Output:** The wording differs from the sample runs, as in `입력하신 이차 방정식의 해는 x1 = 1, x2 = -0.666667입니다.` and `입력하신 이차 방정식의 중근 x = 0.666667입니다.`, and the output ends without a newline. The last run enters 0 for a.

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

**Output:** The result labels read `입력된 수의 합` and `입력된 수의 평균` instead of `입력된 정수의 합`.

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

**Output:** The code's separator has 31 `-` characters, longer than the 24 in the sample runs, the triangle is printed right after the size is entered without a blank line, and some messages end with a trailing space. Each run prints a triangle and then ends with 5.

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

> **Note:** **Windows-specific parts.** `<windows.h>`, `system("pause")`, and `system("cls")` assume a Windows environment. `pause` prints `계속하려면 아무 키나 누르십시오 . . .` ("Press any key to continue . . .") and waits for a key, and `cls` clears the screen. The `system()` function itself is a standard function declared in `<stdlib.h>`. On macOS and Linux, the code runs without changes when a directory with an empty `windows.h` is put on the include path and the code is compiled with `gcc -std=c99 -Wall -include stdlib.h`; these systems have no `pause` or `cls` command, so the shell prints error messages to standard error. `#pragma warning(disable:4996)` is an MSVC-only directive that turns off the C4996 warning MSVC issues for `scanf`, and gcc and clang ignore it as an unknown pragma.

---

<br>

## Exercise 6: Statements About the if Statement

**Textbook Problem:** Chapter 5 exercise 1

**Problem:** Of seven statements about the `if` statement, choose all the incorrect ones. The options are in [Exercise 6](Exercises.md#exercise-6-statements-about-the-if-statement).

### Solution

**Answer:** ②, ⑤, ⑥

**Explanation:** The `if` statement executes the one statement that follows when the condition is true (a nonzero value), and `else` is added only when needed. The condition cannot be omitted, and several statements must be grouped in braces into a compound statement ([Chapter 5, Section 2.1](Concepts_Lecture.md#21-if), [Section 2.2](Concepts_Lecture.md#22-compound-statements--blocks)).

- **① (correct):** If the value of the condition is not 0, it is judged true and the statement after `if` is executed; if it is 0, that statement is skipped.
- **② (incorrect):** `else` is optional, so `if` can be used alone without `else`. `else` is added only when there is a separate statement to execute when the condition is false ([Section 2.3](Concepts_Lecture.md#23-if-else)).
- **③ (correct):** An `if` statement can be placed again where `if` or `else` expects its statement ([Section 2.5](Concepts_Lecture.md#25-nested-if)).
- **④ (correct):** The conditional operator is a shorthand for a simple `if-else`, so the same work can be written with `if-else` (Exercise 8). However, the conditional operator is an expression and `if-else` is a statement, so where an expression is required, such as an argument of `printf`, `if-else` first stores the result in a variable and then that variable is used ([Chapter 5, Section 1](Concepts_Lecture.md#1-control-statements-overview)).
- **⑤ (incorrect):** Leaving the condition empty, as in `if ()`, causes a compile error. Among the control statements, only `for` allows its condition to be omitted (Exercise 11).
- **⑥ (incorrect):** Without braces, only the first statement belongs to the `if` and the remaining statements run regardless of the condition. To execute several statements, they must be grouped in `{ }` into one compound statement.
- **⑦ (correct):** When only one `if` statement follows `else`, as in `else { if (...) ... }`, the braces can be removed and it can be written as `else if`. `else if` is not a separate keyword but the form in which an `if` statement occupies the statement position of `else` ([Section 2.4](Concepts_Lecture.md#24-else-if)).

---

<br>

## Exercise 7: The Keyword for a False Condition

**Textbook Problem:** Chapter 5 exercise 2

**Problem:** Write the keyword needed to describe the statement to execute when the condition of `if` is false. The full problem is in [Exercise 7](Exercises.md#exercise-7-the-keyword-for-a-false-condition).

### Solution

**Answer:** `else`

**Explanation:** The `if-else` statement executes the statement after `if` when the condition is true and the statement after `else` when it is false ([Chapter 5, Section 2.3](Concepts_Lecture.md#23-if-else)). Exactly one of the two statements runs, so a statement to execute only when the condition is false is written after `else`.

```c
if (num % 2 == 0)
    printf("짝수\n");    // executed when the condition is true
else
    printf("홀수\n");    // executed when the condition is false
```

---

<br>

## Exercise 8: Rewriting the Conditional Operator with if

**Textbook Problem:** Chapter 5 exercise 3

**Problem:** Rewrite the statement `max = x > y ? x : y;`, which uses the conditional operator, as an `if` statement. The full problem and code are in [Exercise 8](Exercises.md#exercise-8-rewriting-the-conditional-operator-with-if).

### Solution

**Answer:** Replace `max = x > y ? x : y;` with the following `if-else` statement.

```c
if (x > y)
    max = x;
else
    max = y;
```

**Explanation:** The conditional operator `condition ? value1 : value2` yields value1 as the value of the expression when the condition is true and value2 when it is false ([Chapter 4, Section 8.1](../Ch04_Operators/Concepts_Lecture.md#81-ternary-operator)).

- **Precedence:** The relational operator `>` has higher precedence than the conditional operator, and the conditional operator higher than the assignment operator, so `max = x > y ? x : y;` is evaluated as `max = ((x > y) ? x : y);` ([Chapter 4, Section 10.1](../Ch04_Operators/Concepts_Lecture.md#101-precedence-table)).
- **Correspondence:** The condition `x > y` becomes the condition of `if`, and the value for true, `x`, and the value for false, `y`, become the assignments `max = x;` and `max = y;` of `if` and `else` ([Chapter 4, Section 8.2](../Ch04_Operators/Concepts_Lecture.md#82-equivalent-ifelse)).
- **Equal values:** If x and y are equal, the condition is false, so both versions assign y to `max`. Since x and y have the same value then, the result is the same.

**Code:** The whole program with the rewritten part.

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int x, y, max;

    printf("두 수를 입력하세요: ");
    scanf("%d %d", &x, &y);
    if (x > y)
        max = x;
    else
        max = y;
    printf("큰 수: %d\n", max);

    return 0;
}
```

**Output:** All three inputs give the same results as the original code with the conditional operator. The last run is the case of two equal numbers.

```text
두 수를 입력하세요: 3 7
큰 수: 7
두 수를 입력하세요: 12 -4
큰 수: 12
두 수를 입력하세요: 5 5
큰 수: 5
```

The opposite problem, finding the maximum of three integers with the conditional operator only, is covered in [HW03 Problem 4](../../Coursework/HW03_Control-Statements-I/Assignment-Explanation.md#5-problem-4-comparing-magnitudes).

> **Note:** The textbook's code has no `return 0;` at the end of `main`. From C99, reaching the closing brace of `main` is treated as returning 0, so this code also compiles without warnings. This exception applies only to `main` ([Chapter 2, Section 1.4](../Ch02_C-Program-Basics/Concepts_Lecture.md#14-exit-code)).

---

<br>

## Exercise 9: Statements About the switch Statement

**Textbook Problem:** Chapter 5 exercise 4

**Problem:** Of eight statements about the `switch` statement, choose all the incorrect ones. The options are in [Exercise 9](Exercises.md#exercise-9-statements-about-the-switch-statement).

### Solution

**Answer:** ③, ④

**Explanation:** The `switch` statement jumps to the case label equal to the value of the integer expression and executes the statements after it in order until it meets `break` or the end of the `switch` ([Chapter 5, Section 2.7](Concepts_Lecture.md#27-switch)).

- **① (correct):** The parentheses of `switch` hold an expression of an integer type such as `char`, `int`, or `long`. A floating-point type such as `double` or a string cannot be used.
- **② (correct):** If no case matches the value of the expression, the statements of `default` are executed.
- **③ (incorrect):** `break` can be omitted. Omitting it causes fall-through, in which the statements of the next case run on, and it is used deliberately to make several cases execute the same statements, as with `'C'` and `'c'` of Exercise 2 or July and August of Exercise 10. Omitting the `break` of the last case or of `default` behaves the same, because the end of the `switch` is reached right away.
- **④ (incorrect):** Only an integer constant expression can follow case, so `case 1.5:` or `case "abc":` is a compile error. A character constant such as `'A'` is an integer constant, so it can be used.
- **⑤ (correct):** Without `break`, all statements from the matching case until `break` or the end of the `switch` are executed.
- **⑥ (correct):** `default` is optional. With no `default` and no matching case, no statement inside the `switch` is executed.
- **⑦ (correct):** Every `switch` statement can be rewritten with `if-else`. One case is the equality comparison `expression == value`, and cases sharing statements become a condition joining those comparisons with `||`. With several cases, `if` statements are chained after `else` to form an `else if` ladder, and since `else if` is also a form of `if-else` (option ⑦ of Exercise 6), the rewrite works for any number of cases (Exercise 10). Conversely, an `if-else` that compares ranges or real numbers cannot be turned directly into a `switch` ([Section 2.8](Concepts_Lecture.md#28-if-else-vs-switch-comparison)).
- **⑧ (correct):** The statements after a case label run in order up to the next label or `break`, so they need not be grouped in `{ }`.

> **Note:** **Declaring variables inside a case.** In the standards up to C17, a label must be followed by a statement, and a declaration is not a statement, so a declaration cannot come right after a case label, as in `case 1: int x = 5;`. To declare a variable inside a case, make a block with `{ }`, as in `case 1: { int x = 5; ... break; }`. From C23, a declaration right after a label is allowed.

---

<br>

## Exercise 10: Rewriting a switch Statement with if-else

**Textbook Problem:** Chapter 5 exercise 5

**Problem:** Rewrite the `switch` statement that sets the admission fee by month with `if-else`. The full problem and code are in [Exercise 10](Exercises.md#exercise-10-rewriting-a-switch-statement-with-if-else).

### Solution

**Answer:** Replace the whole `switch` statement with the following `if-else` statement.

```c
if (month == 7 || month == 8)       // peak season: July and August
    fee = 70000;
else if (month == 6 || month == 9)  // high season: June and September
    fee = 55000;
else                                // regular fee for the other months
    fee = 40000;
```

**Explanation:** The groups of cases of the `switch` move in order into the conditions of an `else if` ladder ([Chapter 5, Section 2.4](Concepts_Lecture.md#24-else-if), [Section 2.8](Concepts_Lecture.md#28-if-else-vs-switch-comparison)).

- **Consecutive cases:** `case 7:` and `case 8:` share the same statements, so they become `month == 7 || month == 8`, the two equality comparisons joined with `||`. `case 6:` and `case 9:` likewise become `month == 6 || month == 9`.
- **default:** It runs when none of the preceding cases match, so it becomes the last `else`.
- **break:** An `else if` ladder executes only the first block whose condition is true, so nothing corresponding to the `break` that leaves the `switch` is needed.
- **Range condition:** 7 and 8 are consecutive values, so `month >= 7 && month <= 8` would also work. 6 and 9 are apart, so they must be joined with `||`.

**Code:** The whole program with the rewritten part.

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int month;
    int fee;

    printf("몇 월? ");
    scanf("%d", &month);
    if (month == 7 || month == 8)       // peak season: July and August
        fee = 70000;
    else if (month == 6 || month == 9)  // high season: June and September
        fee = 55000;
    else                                // regular fee for the other months
        fee = 40000;
    printf("입장료 : %d\n", fee);

    return 0;
}
```

**Output:** Entering a peak-season month, a high-season month, and another month one at a time gives the same results as the original `switch` statement.

```text
몇 월? 7
입장료 : 70000
몇 월? 9
입장료 : 55000
몇 월? 12
입장료 : 40000
```

The same kind of rewriting from a `switch` statement to an `if` statement is also covered in [HW04 Problem 4](../../Coursework/HW04_Control-Statements-II/Assignment-Explanation.md#5-problem-4-switch-if-conversion-2).

---

<br>

## Exercise 11: Statements About the for Statement

**Textbook Problem:** Chapter 5 exercise 6

**Problem:** Of nine statements about the `for` statement, choose all the incorrect ones. The options are in [Exercise 11](Exercises.md#exercise-11-statements-about-the-for-statement).

### Solution

**Answer:** ②, ③, ⑧

**Explanation:** The `for` statement executes the initialization once and then, while the condition is true, alternates between the statement to repeat and the update expression ([Chapter 5, Section 3.1](Concepts_Lecture.md#31-for)).

- **① (correct):** The initialization is executed only once, before the loop begins.
- **② (incorrect):** All three expressions can be omitted. Some can be omitted, as in `for ( ; i < 5; )`, or all of them, as in `for ( ; ; )`, and the two semicolons must be written even then.
- **③ (incorrect):** The condition is checked before the statement to repeat, so if the condition is false right after the initialization, the loop exits `for` without executing the statement even once. `for (i = 0; i > 1; i++)` is an example (option ② of Exercise 16). The only loop that guarantees at least one execution is `do-while` ([Section 3.5](Concepts_Lecture.md#35-for-vs-while-vs-do-while-comparison)).
- **④ (correct):** If only the null statement `;` is placed where the statement to repeat goes, just the three expressions repeat. For example, `for (sum = 0, i = 1; i <= 10; sum += i, i++);` computes the sum from 1 to 10 in the update expression. An unintended `;` is also a common mistake that separates the statement to repeat from the `for`.
- **⑤ (correct):** An omitted condition is taken as always true, so the loop is infinite unless it is left with `break` or `return`.
- **⑥ (correct):** When there are several statements to repeat, they are grouped in `{ }` into a compound statement. Otherwise only the first statement is repeated.
- **⑦ (correct):** Several loop control variables can be used, as in `for (i = 0, j = 10; i < j; i++, j--)`.
- **⑧ (incorrect):** A `for` can be nested inside a `for`, and the inner loop runs from beginning to end for each iteration of the outer loop ([Section 3.4](Concepts_Lecture.md#34-nested-loops)).
- **⑨ (correct):** In the initialization or update, several expressions are combined with the comma operator, as in `i = 0, j = 10`. What the textbook calls statements are strictly expressions, and the comma operator evaluates them from the left in order to make one expression out of several.

---

<br>

## Exercise 12: Rewriting a for Statement with while

**Textbook Problem:** Chapter 5 exercise 7

**Problem:** Rewrite the `for` statement that computes the sum and product of 1 to 10 as a `while` statement. The full problem and code are in [Exercise 12](Exercises.md#exercise-12-rewriting-a-for-statement-with-while).

### Solution

**Answer:** Replace the `for` statement with the following code.

```c
i = 1;
while (i <= 10) {
    sum += i;
    times *= i;
    i++;
}
```

**Explanation:** `for (initialization; condition; update) statement` is the same as `initialization; while (condition) { statement update; }` ([Chapter 5, Section 3.5](Concepts_Lecture.md#35-for-vs-while-vs-do-while-comparison)).

- **Initialization:** `i = 1` moves in front of the `while` and is executed only once.
- **Condition:** `i <= 10` becomes the condition of the `while`.
- **Update:** `i++` is placed at the end of the statement to repeat so that it runs at the end of each iteration.

**Code:** The whole program with the rewritten part.

```c
#include <stdio.h>

int main(void)
{
    int i;
    int sum = 0;
    int times = 1;

    i = 1;
    while (i <= 10) {
        sum += i;
        times *= i;
        i++;
    }
    printf("합:%d, 곱:%d\n", sum, times);

    return 0;
}
```

**Output:** It gives the same result as the original `for` statement. 1 + 2 + ... + 10 = 55, and 10! = 3,628,800 is within the range of `int`.

```text
합:55, 곱:3628800
```

> **Caution:** If the statement to repeat contains `continue`, this transformation does not hold as it is. In `for`, `continue` goes to the update expression, but in `while` it goes straight to the condition check and skips the `i++` placed at the end, which can make an infinite loop ([Section 4.2](Concepts_Lecture.md#42-continue)).

---

<br>

## Exercise 13: Statements About while and do-while

**Textbook Problem:** Chapter 5 exercise 8

**Problem:** Of eight statements about the `while` and `do-while` statements, choose all the incorrect ones. The options are in [Exercise 13](Exercises.md#exercise-13-statements-about-while-and-do-while).

### Solution

**Answer:** ③, ④, ⑦

**Explanation:** `while` is a loop that checks the condition first, and `do-while` is a loop that executes the statement to repeat first and then checks the condition ([Chapter 5, Section 3.2](Concepts_Lecture.md#32-while), [Section 3.3](Concepts_Lecture.md#33-do-while)).

- **① (correct):** While the condition is true, the statement to repeat is executed; when it becomes false, the loop exits.
- **② (correct):** The condition of `while` is checked at the start of the loop, before each iteration.
- **③ (incorrect):** The condition of `do-while` is checked at the end of the loop, after the statement to repeat has been executed. Because the condition comes at the end of the statement, a semicolon is needed after `while (condition);`.
- **④ (incorrect):** If the condition of `while` is false from the start, the statement to repeat is not executed even once.
- **⑤ (correct):** `do-while` executes the statement to repeat before checking the condition, so it executes it at least once.
- **⑥ (correct):** The conditions of `while` and `do-while` cannot be omitted, and leaving them empty causes a compile error (options ③ and ⑦ of Exercise 16). This differs from `for`, whose three expressions can all be omitted.
- **⑦ (incorrect):** For a structured loop with a fixed number of iterations, `for`, which puts the initialization, condition, and update on one line, is suitable. `while` suits loops whose end depends on input values or events ([Section 3.5](Concepts_Lecture.md#35-for-vs-while-vs-do-while-comparison)).
- **⑧ (correct):** When there are several statements to execute, they are grouped in `{ }` into a compound statement.

---

<br>

## Exercise 14: Branch Statements and Their Roles

**Textbook Problem:** Chapter 5 exercise 9

**Problem:** Match the branch statements `break`, `continue`, `goto`, and `return` with their roles. The options are in [Exercise 14](Exercises.md#exercise-14-branch-statements-and-their-roles).

### Solution

**Answer:** (1) ②, (2) ①, (3) ④, (4) ③

**Explanation:** Branch statements move the flow of control to another place without a condition ([Chapter 5, Section 4](Concepts_Lecture.md#4-branch-statements)).

- **(1) `break` → ②:** Immediately exits the innermost `switch` statement or loop ([Section 4.1](Concepts_Lecture.md#41-break)).
- **(2) `continue` → ①:** Skips the rest of the statement to repeat and moves on to the next iteration. In `while` it goes to the condition check at the start of the loop, in `do-while` to the condition check at the end, and in `for` to the update expression ([Section 4.2](Concepts_Lecture.md#42-continue), option ④ of Exercise 15).
- **(3) `goto` → ④:** Moves unconditionally to the labeled statement within the same function ([Section 4.3](Concepts_Lecture.md#43-goto)).
- **(4) `return` → ③:** Ends the current function and goes back to where the function was called, and can return a value. A `return` in `main` ends the program ([Section 4.4](Concepts_Lecture.md#44-return)).

---

<br>

## Exercise 15: Statements About Branch Statements

**Textbook Problem:** Chapter 5 exercise 10

**Problem:** Of eight statements about branch statements, choose all the incorrect ones. The options are in [Exercise 15](Exercises.md#exercise-15-statements-about-branch-statements).

### Solution

**Answer:** ①, ②, ⑥, ⑧

**Explanation:** `break` leaves a `switch` or a loop, `return` leaves a function, and `continue` moves on to the next iteration without leaving the loop ([Chapter 5, Section 4](Concepts_Lecture.md#4-branch-statements)).

- **① (incorrect):** In a function whose return type is `void`, only `return;` without a value is written. A value after `return` is written in functions that return a value ([Section 4.4](Concepts_Lecture.md#44-return)).
- **② (incorrect):** `break` does not exit an `if` statement. A `break` inside an `if` exits the innermost loop or `switch` statement surrounding that `if`, and it is a compile error if there is none ([Section 4.1](Concepts_Lecture.md#41-break)).
- **③ (correct):** `goto` moves the flow of control to the position specified by a label.
- **④ (correct):** When `continue` is met inside a `for` statement, the rest of the statement to repeat is skipped, the update expression is executed, and the condition is checked to start the next iteration. The textbook describes this flow, which goes through the update and the condition check to the next iteration, as moving to the start of the loop. It differs from `while` in going through the update expression first rather than straight to the condition check ([Section 4.2](Concepts_Lecture.md#42-continue)).
- **⑤ (correct):** When `continue` is met inside a `do-while` statement, control moves to the condition at the end of the loop.
- **⑥ (incorrect):** A `break` in a `switch` statement inside a loop exits only the `switch` statement, and the loop continues. To leave the loop as well, check a flag variable or the like after the `switch` and use `break` again, or use `goto` or `return`.
- **⑦ (correct):** `break` exits only the innermost loop, but `goto` can move to a label outside the nested loops and exit them at once ([Section 4.3](Concepts_Lecture.md#43-goto)).
- **⑧ (incorrect):** `continue` does not exit the loop but moves on to the next iteration. Exiting a loop from the middle, not from its start or end, is done with `break`.

> **Note:** **Where `continue` goes.** The C standard defines `continue` as jumping to the end of the statement to repeat of the innermost loop, and what follows depends on the loop. `while` and `do-while` check the condition right away, and `for` executes the update expression and then checks the condition. In every case, the next iteration starts if the condition is true, so the textbook describes `while` and `for`, whose condition check comes first, as moving to the start of the loop, and `do-while`, whose condition check comes last, as moving to the end.

---

<br>

## Exercise 16: Finding Infinite Loops

**Textbook Problem:** Chapter 5 exercise 11

**Problem:** Of seven loops, choose all the infinite loops. The options are in [Exercise 16](Exercises.md#exercise-16-finding-infinite-loops).

### Solution

**Answer:** ①, ④, ⑥

**Explanation:** A loop judges a nonzero value of its condition as true and continues, so if the condition is always true and there is no `break`, the loop is infinite ([Chapter 5, Section 2.1](Concepts_Lecture.md#21-if), [Section 3.1](Concepts_Lecture.md#31-for)).

- **① (infinite loop):** An omitted condition of `for` is taken as always true, so it prints `a` without end.
- **② (not an infinite loop):** After the initialization `i = 0`, the first condition check `0 > 1` is false, so the statement to repeat is never executed.
- **③ (not an infinite loop):** The condition of `while` cannot be omitted, so it is a compile error.
- **④ (infinite loop):** 2 is a nonzero value and therefore true, so it is the same as `while (1)`.
- **⑤ (not an infinite loop):** 0 is false, so the statement to repeat is never executed.
- **⑥ (infinite loop):** The condition 1 is always true, so it prints `a` without end. The first `a` is printed before the condition is checked.
- **⑦ (not an infinite loop):** The condition of `do-while` cannot be omitted either, so it is a compile error.

---

<br>

## Exercise 17: Output of a Nested if Statement

**Textbook Problem:** Chapter 5 exercise 12

**Problem:** Write the output of a program with a nested `if` statement that starts from `n = 1`. The full problem and code are in [Exercise 17](Exercises.md#exercise-17-output-of-a-nested-if-statement).

### Solution

**Answer:** `n = 7`

**Explanation:** The inner `if-else` is inside the braces of the outer `if`, so the last `else` pairs with the outer `if (n > 0)` ([Chapter 5, Section 2.5](Concepts_Lecture.md#25-nested-if)).

1. `n` is 1, so `n > 0` is true; the statements in the braces are executed, and the `n++` of the outer `else` is not.
2. `n *= 2` makes `n` 2.
3. `n < 5`, that is `2 < 5`, is true, so `n += 5` makes `n` 7. The `n -= 5` of the inner `else` is not executed.
4. `printf` prints `n = 7`.

**Output:**

```text
n = 7
```

---

<br>

## Exercise 18: Output of a for Loop with continue

**Textbook Problem:** Chapter 5 exercise 13

**Problem:** Write the output of a program that increases `i` from 1 by 2 and skips multiples of 3 with `continue`. The full problem and code are in [Exercise 18](Exercises.md#exercise-18-output-of-a-for-loop-with-continue).

### Solution

**Answer:** `n = 13`

**Explanation:** `i` increases from 1 by 2 through 1, 3, 5, 7, and 9, and when it becomes 11, `i < 10` is false and the loop ends. At 3 and 9, the multiples of 3, `continue` skips `n += i` and moves to the update `i += 2` ([Chapter 5, Section 4.2](Concepts_Lecture.md#42-continue)).

| `i` | `i % 3 == 0` | Statement executed | `n` |
|:---:|:---:|:-----|:---:|
| 1 | False | `n += i` | 1 |
| 3 | True | `continue` | 1 |
| 5 | False | `n += i` | 6 |
| 7 | False | `n += i` | 13 |
| 9 | True | `continue` | 13 |

*Table 1. The statement executed in each iteration and the value of n*

So `n` is 1 + 5 + 7 = 13.

**Output:**

```text
n = 13
```

---

<br>

## Exercise 19: Grades by Absolute Evaluation

**Textbook Problem:** Chapter 5 programming assignment 1

**Problem:** Read an exam score (0-100) and print the grade: A for 90 or above, B for 80 or above, C for 70 or above, D for 60 or above, and F below 60. The full problem and sample run are in [Exercise 19](Exercises.md#exercise-19-grades-by-absolute-evaluation).

### Solution

**Approach:** The score ranges do not overlap, so an `else if` ladder that checks from the highest cutoff down is used ([Chapter 5, Section 2.4](Concepts_Lecture.md#24-else-if)).

- **Order of conditions:** The ladder executes only the first block whose condition is true, so when `score >= 80` is checked, `score >= 90` is already known to be false. That is why the 80s need not be written as `score >= 80 && score < 90`. Conversely, checking `score >= 60` first would make every score of 60 or above a D.
- **Input check:** If the score is outside 0-100, the program prints an error message without computing a grade and ends with exit code 1.
- **Output:** The grade is stored in the `char` variable `grade` and printed once with `%c`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int score;      // exam score (0-100)
    char grade;     // letter grade

    printf("점수? ");
    scanf("%d", &score);

    if (score < 0 || score > 100) {
        printf("입력 오류! 점수는 0~100 사이여야 합니다.\n");
        return 1;
    }

    // check the cutoffs from the highest one down
    if (score >= 90)
        grade = 'A';
    else if (score >= 80)
        grade = 'B';
    else if (score >= 70)
        grade = 'C';
    else if (score >= 60)
        grade = 'D';
    else
        grade = 'F';

    printf("학점: %c\n", grade);

    return 0;
}
```

**Output:** Entering 91 prints `학점: A`. The following runs enter the boundary values 90, 89, 60, and 59 and the out-of-range value 101.

```text
점수? 91
학점: A
점수? 90
학점: A
점수? 89
학점: B
점수? 60
학점: D
점수? 59
학점: F
점수? 101
입력 오류! 점수는 0~100 사이여야 합니다.
```

Handling the same cutoffs with a `switch` statement is shown in [Chapter 5, Section 2.7](Concepts_Lecture.md#27-switch) and [HW04 Problem 3](../../Coursework/HW04_Control-Statements-II/Assignment-Explanation.md#4-problem-3-switch-if-conversion-1).

---

<br>

## Exercise 20: Grades by Relative Evaluation

**Textbook Problem:** Chapter 5 programming assignment 2

**Problem:** Read a rank and the number of students and print the grade: A for the top 10%, B up to 30%, C up to 60%, D up to 90%, and F for the bottom 10%. The full problem and sample run are in [Exercise 20](Exercises.md#exercise-20-grades-by-relative-evaluation).

### Solution

**Approach:** The rank divided by the number of students tells within what top percentage the student falls. Rank 10 of 80 is 10 / 80 = 12.5%, which is above 10% and at most 30%, so it is a B. An `else if` ladder compares this ratio against the cutoffs from the smallest up ([Chapter 5, Section 2.4](Concepts_Lecture.md#24-else-if)).

- **Comparison without division:** Writing `rank / total * 100 <= 10` directly makes `rank / total` an integer division, which is always 0 when the rank is less than the number of students ([Chapter 4, Section 2.2](../Ch04_Operators/Concepts_Lecture.md#22-integer-division-vs-float-division)). Multiplying both sides by `total * 100` gives `rank * 100 <= total * 10`, which makes the same comparison with integer multiplication only, so neither the truncation of integer division nor the representation error of real numbers arises.
- **Ranges:** The top 10%, 30%, 60%, and 90% are checked in order, and the bottom 10% beyond 90% becomes F in the last `else`.
- **Input check:** The grade is computed only when the number of students is at least 1 and the rank is from 1 to the number of students.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int rank;       // rank of the student (1 is the top)
    int total;      // number of students
    char grade;     // letter grade

    printf("등수? ");
    scanf("%d", &rank);
    printf("전체 인원수? ");
    scanf("%d", &total);

    if (total < 1 || rank < 1 || rank > total) {
        printf("입력 오류! 등수는 1 이상 전체 인원수 이하여야 합니다.\n");
        return 1;
    }

    // rank / total <= p / 100 is tested as rank * 100 <= total * p
    // so that no division (and no rounding) is involved
    if (rank * 100 <= total * 10)
        grade = 'A';
    else if (rank * 100 <= total * 30)
        grade = 'B';
    else if (rank * 100 <= total * 60)
        grade = 'C';
    else if (rank * 100 <= total * 90)
        grade = 'D';
    else
        grade = 'F';

    printf("학점: %c\n", grade);

    return 0;
}
```

**Output:** Entering rank 10 of 80 prints `학점: B`. The following runs enter the ranks at range boundaries: 8 (10%), 9 (11.25%), 72 (90%), and 73 (91.25%).

```text
등수? 10
전체 인원수? 80
학점: B
등수? 8
전체 인원수? 80
학점: A
등수? 9
전체 인원수? 80
학점: B
등수? 72
전체 인원수? 80
학점: D
등수? 73
전체 인원수? 80
학점: F
```

> **Caution:** Because the grade is decided by the ratio of the rank to the number of students, even rank 1 cannot get an A when there are few students. Rank 1 of 5 is the top 20%, so it is a B, and with only one student, that rank 1 is the top 100% and gets an F. With fewer than ten students, no rank falls in the A range.

```text
등수? 1
전체 인원수? 5
학점: B
등수? 1
전체 인원수? 1
학점: F
```

---

<br>

## Exercise 21: The Quadrant of a Point

**Textbook Problem:** Chapter 5 programming assignment 3

**Problem:** Read the coordinates (x, y) of a point and print which quadrant it is in. The full problem and sample run are in [Exercise 21](Exercises.md#exercise-21-the-quadrant-of-a-point).

### Solution

This is the same problem as Exercise 1, so the [solution of Exercise 1](#exercise-1-quadrant-of-a-point-in-the-plane) is used as it is. The result of the classification is the same, but the message format differs. The textbook's sample run reads with the prompt `점의 좌표 (x, y)? ` and prints only the quadrant, as in `4사분면에 있습니다.`, whereas the code of Exercise 1 reads with `좌표 (x, y)? `, prints the coordinates together with `제4사분면에 위치합니다.`, and also distinguishes points on the axes and the origin.

**Output:** The result of compiling the code of Exercise 1 ([Lab_Q1.c](../../Coursework/Lab05_Control-Statements/Lab_Q1.c)) with `gcc -std=c99 -Wall -Dscanf_s=scanf` and entering the sample input `10 -10`.

```text
좌표 (x, y)? 10 -10
(10, -10)는 제4사분면에 위치합니다.
```

The difference between the two approaches that the textbook asks to compare lies in the number of checks. With `if-else`, as in the code of Exercise 1, checking stops at the first true condition, but with several independent `if` statements, such as `if (x > 0 && y > 0)` and `if (x < 0 && y > 0)`, all remaining conditions are still checked after the result is printed. The quadrant conditions do not overlap, so both approaches print the same output ([Chapter 5, Section 2.6](Concepts_Lecture.md#26-multiple-independent-if)).

---

<br>

## Exercise 22: Leap Year Test

**Textbook Problem:** Chapter 5 programming assignment 4

**Problem:** Read a year and test whether it is a leap year according to its divisibility by 4, 100, and 400. The full problem and sample run are in [Exercise 22](Exercises.md#exercise-22-leap-year-test).

### Solution

**Approach:** Summarizing the three rules, a year divisible by 400, or divisible by 4 but not by 100, is a leap year. Divisibility is judged by whether the result of the remainder operator `%` is 0, and the two cases are joined with logical operators into one condition of an `if-else` ([Chapter 4, Section 2.3](../Ch04_Operators/Concepts_Lecture.md#23-modulo-operator), [Chapter 4, Section 5.1](../Ch04_Operators/Concepts_Lecture.md#51-and-or-not)).

- **Condition:** `(year % 4 == 0 && year % 100 != 0) || year % 400 == 0`. `&&` has higher precedence than `||`, so it would be the same without the parentheses, but the parentheses show the two cases.
- **Check:** 2020 is divisible by 4 and not by 100, so it is a leap year. 1900 is divisible by 100 but not by 400, so it is not a leap year, and 2000 is divisible by 400, so it is a leap year.
- **Nested if:** A nested `if` that checks `year % 4`, `year % 100`, and `year % 400` in turn, following the order of the rules, gives the same result ([Chapter 5, Section 2.5](Concepts_Lecture.md#25-nested-if)).

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int year;

    printf("연도? ");
    scanf("%d", &year);

    // divisible by 4 but not by 100, or divisible by 400
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        printf("%d년은 윤년입니다.\n", year);
    else
        printf("%d년은 윤년이 아닙니다.\n", year);

    return 0;
}
```

**Output:** The runs enter 2020, the input of the sample run, followed by the common year 2023 and 1900 and 2000, which check the third rule.

```text
연도? 2020
2020년은 윤년입니다.
연도? 2023
2023년은 윤년이 아닙니다.
연도? 1900
1900년은 윤년이 아닙니다.
연도? 2000
2000년은 윤년입니다.
```

---

<br>

## Exercise 23: Converting Celsius and Fahrenheit Temperatures

**Textbook Problem:** Chapter 5 programming assignment 5

**Problem:** Read a temperature with a unit character, as in "27 C" or "27 F", and convert Celsius to Fahrenheit and Fahrenheit to Celsius. The full problem and sample run are in [Exercise 23](Exercises.md#exercise-23-converting-celsius-and-fahrenheit-temperatures).

### Solution

This is the same problem as Exercise 2, so the [solution of Exercise 2](#exercise-2-converting-between-celsius-and-fahrenheit) is used as it is. Exercise 2 handles the unit character with a `switch` statement regardless of case, so it covers all the conditions of this problem. The converted values are the same, but the output format differs. The textbook's sample run prints the input temperature to two decimal places, as in `27.00`, whereas the code of Exercise 2 reads the temperature as an integer, prints it as `27`, and does not end the line at the end of the output.

**Output:** The result of compiling the code of Exercise 2 ([Lab_Q2.c](../../Coursework/Lab05_Control-Statements/Lab_Q2.c)) with `gcc -std=c99 -Wall -Dscanf_s=scanf` and entering the sample input `27 C`. 27 × 9 / 5 + 32 = 80.6.

```text
온도? 27 C
27 C == 80.60 F
```

To accept a fractional temperature such as `27.5 C`, as the textbook does, the temperature must be declared `double` and read with `%lf`. The code of Exercise 2 reads the temperature with `%d`, so entering a fraction results in a unit error (the `Caution` box of Exercise 2).

---

<br>

## Exercise 24: Electricity Bill with Progressive Rates

**Textbook Problem:** Chapter 5 programming assignment 6

**Problem:** Read the monthly usage and compute the electricity bill from the progressive rate table, in which the basic charge and the energy rate change at 300 kWh. The full problem, the rate table, and the sample run are in [Exercise 24](Exercises.md#exercise-24-electricity-bill-with-progressive-rates).

### Solution

**Approach:** An `if-else` divides the two cases by whether the monthly usage is at most 300 kWh or above it ([Chapter 5, Section 2.3](Concepts_Lecture.md#23-if-else)), and the numbers of the rate table are defined as macro constants and used by name ([Chapter 3, Section 4.2](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#42-define-macro-constants)).

- **300 kWh or less:** The basic charge is 1,000 won, and the energy charge is `usage * 100`, applying 100 won to the whole usage.
- **Above 300 kWh:** The basic charge is 5,000 won, and the energy charge is `300 * 100 + (usage - 300) * 200`, applying 100 won to the first 300 kWh and 200 won to the excess `usage - 300`. For 350 kWh this is 30,000 + 10,000 = 40,000 won, and the total is 45,000 won.
- **Output width:** In a terminal, each Korean character takes two columns, so `전기 요금 합계:` and `  - 전력량요금:` take 15 columns and `  - 기본요금:` takes 13. Printing the amounts with `%6d`, `%8d`, and `%6d` makes the amounts of the three lines end in the same column, right-aligned as in the sample run ([Chapter 3, Section 5.2](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#52-width-and-alignment)).
- **Input check:** If the usage is negative, the program prints an error message and ends with exit code 1.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

#define TIER_LIMIT 300    // usage (kWh) up to which the lower tier applies
#define BASE_LOW   1000   // basic charge for usage up to 300 kWh (won)
#define BASE_HIGH  5000   // basic charge for usage above 300 kWh (won)
#define RATE_LOW   100    // energy rate for the first 300 kWh (won/kWh)
#define RATE_HIGH  200    // energy rate for the usage above 300 kWh (won/kWh)

int main(void)
{
    int usage;        // monthly usage (kWh)
    int base_fee;     // basic charge (won)
    int energy_fee;   // energy charge (won)

    printf("월 사용량 (kWh)? ");
    scanf("%d", &usage);

    if (usage < 0) {
        printf("입력 오류! 월 사용량은 0 이상이어야 합니다.\n");
        return 1;
    }

    if (usage <= TIER_LIMIT) {
        base_fee = BASE_LOW;
        energy_fee = usage * RATE_LOW;
    }
    else {
        base_fee = BASE_HIGH;
        energy_fee = TIER_LIMIT * RATE_LOW + (usage - TIER_LIMIT) * RATE_HIGH;
    }

    // widths chosen so that the amounts line up in a terminal,
    // where each Korean character takes two columns
    printf("전기 요금 합계: %6d원\n", base_fee + energy_fee);
    printf("  - 기본요금: %8d원\n", base_fee);
    printf("  - 전력량요금: %6d원\n", energy_fee);

    return 0;
}
```

**Output:** The runs enter 350, the input of the sample run, followed by the boundary values 300 and 301 and then 0. The totals for 300 kWh and 301 kWh differ by 4,200 won because, besides the 200 won for the 1 kWh of excess, the basic charge changes from 1,000 won to 5,000 won with the tier.

```text
월 사용량 (kWh)? 350
전기 요금 합계:  45000원
  - 기본요금:     5000원
  - 전력량요금:  40000원
월 사용량 (kWh)? 300
전기 요금 합계:  31000원
  - 기본요금:     1000원
  - 전력량요금:  30000원
월 사용량 (kWh)? 301
전기 요금 합계:  35200원
  - 기본요금:     5000원
  - 전력량요금:  30200원
월 사용량 (kWh)? 0
전기 요금 합계:   1000원
  - 기본요금:     1000원
  - 전력량요금:      0원
```

---

<br>

## Exercise 25: Bitwise Operation Calculator

**Textbook Problem:** Chapter 5 programming assignment 7

**Problem:** Read an expression made of two hexadecimal numbers and a bitwise operator (`&`, `|`, `^`), as in "0xAB & 0xCC", and print the result in hexadecimal. The full problem and sample run are in [Exercise 25](Exercises.md#exercise-25-bitwise-operation-calculator).

### Solution

**Approach:** Read the two hexadecimal numbers and the operator character between them with `%x` of `scanf`, and select the operation by using the operator character as the expression of a `switch` ([Chapter 5, Section 2.7](Concepts_Lecture.md#27-switch), [Chapter 4, Section 6.1](../Ch04_Operators/Concepts_Lecture.md#61-bitwise-and-or-xor-not)).

- **Input:** `%x` reads a hexadecimal number into an `unsigned int` variable, accepts a leading `0x` or `0X`, and ignores the case of the digits ([Chapter 2, Section 2.3](../Ch02_C-Program-Basics/Concepts_Lecture.md#format-specifiers-for-scanf)). In the format string `"%x %c %x"`, the space before `%c` skips any spaces before the operator, so both `0xAB & 0xCC` and `ab&cc` are read.
- **Input failure:** `scanf` returns the number of items it stored, so a value other than 3 is treated as a format error.
- **Operation:** The cases `'&'`, `'|'`, and `'^'` compute `a & b`, `a | b`, and `a ^ b`, and any other character is handled as an error in `default`.
- **Output:** `%X` prints uppercase hexadecimal without `0x`, so the result is `ABCDEF12 & F0F0F0F0 = A0C0E010` as in the sample run. To pad to eight digits, use `%08X`.
- **Check:** AB is `1010 1011` and CC is `1100 1100`, so AND is `1000 1000` (88), OR is `1110 1111` (EF), and XOR is `0110 0111` (67).

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    unsigned int a, b;      // operands read in hexadecimal
    unsigned int result;
    char op;                // operator character: &, |, or ^

    printf("비트 연산식? ");
    if (scanf("%x %c %x", &a, &op, &b) != 3) {
        printf("입력 오류! 0xAB & 0xCC 형식으로 입력하세요.\n");
        return 1;
    }

    switch (op) {
    case '&':
        result = a & b;
        break;
    case '|':
        result = a | b;
        break;
    case '^':
        result = a ^ b;
        break;
    default:
        printf("입력 오류! 연산자는 &, |, ^만 가능합니다.\n");
        return 1;
    }

    printf("%X %c %X = %X\n", a, op, b, result);

    return 0;
}
```

**Output:** After the input of the sample run, the following runs compute the three operations on 0xAB and 0xCC one by one, then enter the expression without spaces and with the unsupported operator `+`.

```text
비트 연산식? 0xabcdef12 & 0xF0F0F0F0
ABCDEF12 & F0F0F0F0 = A0C0E010
비트 연산식? 0xAB & 0xCC
AB & CC = 88
비트 연산식? 0xAB | 0xCC
AB | CC = EF
비트 연산식? 0xAB ^ 0xCC
AB ^ CC = 67
비트 연산식? ab&cc
AB & CC = 88
비트 연산식? 0xAB + 0xCC
입력 오류! 연산자는 &, |, ^만 가능합니다.
```

> **Caution:** If a value read with `%x` exceeds the range of `unsigned int` (`FFFFFFFF` for 32 bits), the behavior is undefined, so a hexadecimal number of nine or more digits must not be entered. Also, bitwise NOT (`~`) has one operand and the shifts (`<<`, `>>`) are two-character operators, so a calculator of this format cannot handle them.

---

<br>

## Exercise 26: Printing ASCII Characters

**Textbook Problem:** Chapter 5 programming assignment 8

**Problem:** Print the characters of ASCII codes 32-126, excluding the control characters, 24 per line. The full problem and sample run are in [Exercise 26](Exercises.md#exercise-26-printing-ascii-characters).

### Solution

**Approach:** Loop over the character codes 32 to 126 with a `for` statement, print each with `%c`, and end the line whenever the counter of printed characters becomes a multiple of 24 ([Chapter 5, Section 5.1](Concepts_Lecture.md#51-counter-and-accumulator), [Chapter 3, Section 1.3](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#13-character-type)).

- **Printing characters:** `char` is an integer that stores a character code, so printing the integer `code` with `%c` prints the character of that code. A space is printed after each character to separate them.
- **Line breaks:** When `count % 24 == 0`, a line is full, so `\n` is printed. There are 126 - 32 + 1 = 95 printable characters, so there are four lines of 24, 24, 24, and 23 characters, and since the last line does not reach 24, the line is ended after the loop.
- **First character:** Code 32 is the space character, so the first line starts with two spaces (the space character and the separating space) followed by `!`.

**Code:**

```c
#include <stdio.h>

#define FIRST_PRINTABLE 32    // space, the first printable ASCII code
#define LAST_PRINTABLE  126   // '~', the last printable ASCII code
#define PER_LINE        24    // characters per line

int main(void)
{
    int code;
    int count = 0;    // characters printed so far

    for (code = FIRST_PRINTABLE; code <= LAST_PRINTABLE; code++) {
        printf("%c ", code);
        count++;
        if (count % PER_LINE == 0)    // a line is full
            printf("\n");
    }
    if (count % PER_LINE != 0)        // finish the last, partial line
        printf("\n");

    return 0;
}
```

**Output:** Four lines are printed, and one separating space remains at the end of each line.

```text
  ! " # $ % & ' ( ) * + , - . / 0 1 2 3 4 5 6 7 
8 9 : ; < = > ? @ A B C D E F G H I J K L M N O 
P Q R S T U V W X Y Z [ \ ] ^ _ ` a b c d e f g 
h i j k l m n o p q r s t u v w x y z { | } ~ 
```

---

<br>

## Exercise 27: Printing Multiples of an Integer

**Textbook Problem:** Chapter 5 programming assignment 9

**Problem:** Read a positive integer and a number of multiples, and print that many multiples of the integer. The full problem and sample run are in [Exercise 27](Exercises.md#exercise-27-printing-multiples-of-an-integer).

### Solution

**Approach:** A `for` statement increases `i` from 1 to the number of multiples and prints the i-th multiple `num * i` ([Chapter 5, Section 3.1](Concepts_Lecture.md#31-for)).

- **Computing the multiples:** Instead of multiplying, an accumulator `multiple` starting at 0 and adding the integer each time with `multiple += num` gives the same multiples ([Section 5.1](Concepts_Lecture.md#51-counter-and-accumulator)).
- **Input check:** If the integer or the count is 0 or less, the program prints an error message and ends with exit code 1.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int num;      // the positive integer
    int count;    // how many multiples to print
    int i;

    printf("양의 정수? ");
    scanf("%d", &num);
    printf("배수의 개수? ");
    scanf("%d", &count);

    if (num <= 0 || count <= 0) {
        printf("입력 오류! 양의 정수를 입력하세요.\n");
        return 1;
    }

    for (i = 1; i <= count; i++)
        printf("%d ", num * i);    // the i-th multiple
    printf("\n");

    return 0;
}
```

**Output:** Entering 11 and 20 prints the 20 multiples from 11 to 220. A space is printed after each number, so one space remains at the end of the line. The second run enters 0 as the integer.

```text
양의 정수? 11
배수의 개수? 20
11 22 33 44 55 66 77 88 99 110 121 132 143 154 165 176 187 198 209 220 
양의 정수? 0
배수의 개수? 5
입력 오류! 양의 정수를 입력하세요.
```

> **Caution:** `num * i` is computed as `int`, so if the product of the integer and the count exceeds the maximum `int` value 2,147,483,647, signed integer overflow occurs and its result is undefined ([Chapter 3, Section 1.1](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#overflow-and-underflow)). To handle larger values, use the `long long` type and `%lld`.

---

<br>

## Exercise 28: Repeating the Electricity Bill Calculation

**Textbook Problem:** Chapter 5 programming assignment 10

**Problem:** Repeat the electricity bill calculation of Exercise 24 until 0 is entered as the monthly usage. The full problem and sample run are in [Exercise 28](Exercises.md#exercise-28-repeating-the-electricity-bill-calculation).

### Solution

**Approach:** Computing and printing the bill is the same as in the [solution of Exercise 24](#exercise-24-electricity-bill-with-progressive-rates), so only the added loop is explained here. The input and computation go inside an infinite `while (1)` loop, which is left with `break` when 0 is read as the monthly usage ([Chapter 5, Section 3.2](Concepts_Lecture.md#32-while), [Section 4.1](Concepts_Lecture.md#41-break)).

- **Sentinel:** 0 is the sentinel that means the end, so unlike Exercise 24, the loop ends without computing the basic charge of 1,000 won. Whether the input is 0 must be checked right after reading it and before computing the bill, so that no bill is printed for 0.
- **Input failure:** When `scanf` cannot read a number, it returns a value other than 1 and leaves the invalid input in the buffer. Without checking this, the next iteration would also fail to read the same input and keep printing the bill for the previous usage, so the loop ends in this case as well.
- **Negative numbers:** For a negative number, the program prints an error message, skips the calculation with `continue`, and reads again ([Section 4.2](Concepts_Lecture.md#42-continue)).

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

#define TIER_LIMIT 300    // usage (kWh) up to which the lower tier applies
#define BASE_LOW   1000   // basic charge for usage up to 300 kWh (won)
#define BASE_HIGH  5000   // basic charge for usage above 300 kWh (won)
#define RATE_LOW   100    // energy rate for the first 300 kWh (won/kWh)
#define RATE_HIGH  200    // energy rate for the usage above 300 kWh (won/kWh)

int main(void)
{
    int usage;        // monthly usage (kWh)
    int base_fee;     // basic charge (won)
    int energy_fee;   // energy charge (won)

    while (1) {
        printf("월 사용량 (kWh)? ");
        if (scanf("%d", &usage) != 1 || usage == 0)
            break;    // 0 (or input that is not a number) ends the loop

        if (usage < 0) {
            printf("입력 오류! 월 사용량은 0 이상이어야 합니다.\n");
            continue; // ask again without computing a fee
        }

        if (usage <= TIER_LIMIT) {
            base_fee = BASE_LOW;
            energy_fee = usage * RATE_LOW;
        }
        else {
            base_fee = BASE_HIGH;
            energy_fee = TIER_LIMIT * RATE_LOW + (usage - TIER_LIMIT) * RATE_HIGH;
        }

        printf("전기 요금 합계: %6d원\n", base_fee + energy_fee);
        printf("  - 기본요금: %8d원\n", base_fee);
        printf("  - 전력량요금: %6d원\n", energy_fee);
    }

    return 0;
}
```

**Output:** Entering 350, 250, and 0 in turn computes twice and then ends.

```text
월 사용량 (kWh)? 350
전기 요금 합계:  45000원
  - 기본요금:     5000원
  - 전력량요금:  40000원
월 사용량 (kWh)? 250
전기 요금 합계:  26000원
  - 기본요금:     1000원
  - 전력량요금:  25000원
월 사용량 (kWh)? 0
```

Entering a negative number prints an error message and reads again.

```text
월 사용량 (kWh)? -20
입력 오류! 월 사용량은 0 이상이어야 합니다.
월 사용량 (kWh)? 301
전기 요금 합계:  35200원
  - 기본요금:     5000원
  - 전력량요금:  30200원
월 사용량 (kWh)? 0
```

---

<br>

## Exercise 29: Prime Test

**Textbook Problem:** Chapter 5 programming assignment 11

**Problem:** Read an integer and test whether it is an integer greater than 1 divisible only by 1 and itself, that is, a prime. The full problem and sample run are in [Exercise 29](Exercises.md#exercise-29-prime-test).

### Solution

**Approach:** Starting from 2, check in turn whether some number (a divisor) divides n, and stop checking with `break` as soon as one is found ([Chapter 5, Section 4.1](Concepts_Lecture.md#41-break)).

- **Initial value:** A prime is an integer greater than 1, so `is_prime` starts with the value of `n > 1` (1 or 0). A number of 1 or less is decided not to be prime before the loop starts.
- **Range of the check:** If n = a × b (a ≤ b), then a × a ≤ n, so if a divisor exists, one must lie in the range where `i * i <= n`. The code writes this condition as `i <= n / i` to keep `i * i` from exceeding the range of `int` for large n. 12 is divisible at i = 2, so it is judged not prime right away.
- **Particle:** The particle `는` is attached after a number whose spoken form ends in a vowel, that is, whose last digit is 2 (이), 4 (사), 5 (오), or 9 (구), and `은` after the others, printing `12는` and `7은`. Numbers ending in 0, such as 10 and 100, are read as 십 and 백, which end in a consonant, so they take `은`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int n;
    int i;
    int is_prime;     // stays 1 while no divisor has been found
    int last_digit;   // decides the Korean particle after the number

    printf("양의 정수? ");
    scanf("%d", &n);

    is_prime = (n > 1);               // a prime is greater than 1
    for (i = 2; i <= n / i; i++) {    // same as i * i <= n, without overflow
        if (n % i == 0) {
            is_prime = 0;             // i divides n, so n is not prime
            break;                    // no need to try further divisors
        }
    }

    // a number whose reading ends in a vowel (last digit 2, 4, 5, 9)
    // takes the particle "는"; the others take "은"
    last_digit = n % 10;
    if (last_digit < 0)
        last_digit = -last_digit;
    if (last_digit == 2 || last_digit == 4 || last_digit == 5 || last_digit == 9)
        printf("%d는 ", n);
    else
        printf("%d은 ", n);

    if (is_prime)
        printf("소수입니다.\n");
    else
        printf("소수가 아닙니다.\n");

    return 0;
}
```

**Output:** Entering 12 prints `12는 소수가 아닙니다.`. The following runs enter 7, 2, 1, 97, and 2147483647, which is both the maximum `int` value and a prime.

```text
양의 정수? 12
12는 소수가 아닙니다.
양의 정수? 7
7은 소수입니다.
양의 정수? 2
2는 소수입니다.
양의 정수? 1
1은 소수가 아닙니다.
양의 정수? 97
97은 소수입니다.
양의 정수? 2147483647
2147483647은 소수입니다.
```

---

<br>

## Exercise 30: Printing the Primes up to N

**Textbook Problem:** Chapter 5 programming assignment 12

**Problem:** Read an integer N and print all primes from 1 to N, ten per line. The full problem and sample run are in [Exercise 30](Exercises.md#exercise-30-printing-the-primes-up-to-n).

### Solution

**Approach:** A nested loop puts the prime test of Exercise 29 in the inner loop, while the outer `for` statement checks the numbers from 2 to N in turn ([Chapter 5, Section 3.4](Concepts_Lecture.md#34-nested-loops)).

- **break and continue:** The inner loop ends with `break` when it finds a divisor, and the outer loop skips the printing with `continue` for a number that is not prime and moves on to the next number ([Section 4.1](Concepts_Lecture.md#41-break), [Section 4.2](Concepts_Lecture.md#42-continue)).
- **Output format:** Each prime is printed with `%3d`, right-aligned in three columns, and the line is ended whenever the counter of printed primes becomes a multiple of 10 ([Chapter 3, Section 5.2](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#52-width-and-alignment)).
- **Last line:** If the last line does not reach ten numbers, the line is ended after the loop, and if N is less than 2 so that there is no prime at all, the program says so.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

#define PER_LINE 10   // primes per line

int main(void)
{
    int n;
    int num;          // candidate number
    int i;
    int is_prime;
    int count = 0;    // primes printed so far

    printf("양의 정수? ");
    scanf("%d", &n);

    for (num = 2; num <= n; num++) {
        is_prime = 1;
        for (i = 2; i <= num / i; i++) {
            if (num % i == 0) {
                is_prime = 0;
                break;        // num has a divisor: stop the inner loop
            }
        }
        if (!is_prime)
            continue;         // skip printing for a composite number

        printf("%3d", num);
        count++;
        if (count % PER_LINE == 0)
            printf("\n");
    }

    if (count == 0)
        printf("%d 이하의 소수가 없습니다.\n", n);
    else if (count % PER_LINE != 0)
        printf("\n");         // finish the last, partial line

    return 0;
}
```

**Output:** Entering 100 prints the 25 primes on three lines.

```text
양의 정수? 100
  2  3  5  7 11 13 17 19 23 29
 31 37 41 43 47 53 59 61 67 71
 73 79 83 89 97
```

Entering 30, which has exactly ten primes, ends on one line without a blank line, and entering 1 prints the message that there is no prime.

```text
양의 정수? 30
  2  3  5  7 11 13 17 19 23 29
양의 정수? 1
1 이하의 소수가 없습니다.
```
