# Chapter 5 Exercises — Control Statements

[Repository Guide](../../README.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

> **Last Updated:** 2026-10-27
>
> Warming-Up C Programming, 천정아, Ch 5

**Problem Source:** Prof. Younghee Im, Computer Language Ⅰ (DCCS101-04)

Exercises 1-3 practice conditional (selection) statements, and Exercises 4 and 5 practice loop statements. Exercises 6-18 are exercises 1-13 of Chapter 5 of the textbook, and Exercises 19-30 are programming assignments 1-12 of Chapter 5.

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

**Textbook Problem:** Chapter 5 programming assignment 5

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

---

<br>

## Exercise 6: Statements About the if Statement

**Textbook Problem:** Chapter 5 exercise 1

**Problem:** Choose all the incorrect statements about the `if` statement.

- ① If the condition of `if` is true, the statement following `if` is executed.
- ② `if` always requires `else`.
- ③ `if` statements can be nested.
- ④ `if-else` can be used instead of the conditional operator.
- ⑤ The condition of `if` can be omitted.
- ⑥ Even if there are several statements to execute when the condition of `if` is true, they do not need to be enclosed in `{ }`.
- ⑦ In `if-else`, when only an `if` statement follows `else`, it can be turned into `else if`.

**[Solution](Solutions.md#exercise-6-statements-about-the-if-statement)**

---

<br>

## Exercise 7: The Keyword for a False Condition

**Textbook Problem:** Chapter 5 exercise 2

**Problem:** Write the keyword needed to describe the statement to execute when the condition of `if` is false.

**[Solution](Solutions.md#exercise-7-the-keyword-for-a-false-condition)**

---

<br>

## Exercise 8: Rewriting the Conditional Operator with if

**Textbook Problem:** Chapter 5 exercise 3

**Problem:** In the following code, rewrite the statement `max = x > y ? x : y;`, which uses the conditional operator, with an `if` statement.

```c
#define _CRT_SECURE_NO_WARNINGS     // Visual Studio 2022에서 scanf 사용 시 필요
#include <stdio.h>
int main(void)
{
    int x, y, max;

    printf("두 수를 입력하세요: ");
    scanf("%d %d", &x, &y);
    max = x > y ? x : y;
    printf("큰 수: %d\n", max);
}
```

**[Solution](Solutions.md#exercise-8-rewriting-the-conditional-operator-with-if)**

---

<br>

## Exercise 9: Statements About the switch Statement

**Textbook Problem:** Chapter 5 exercise 4

**Problem:** Choose all the incorrect statements about the `switch` statement.

- ① An integer expression must be written inside the `( )` of `switch`.
- ② If no case matching the value of the integer expression is found, the statements given for `default` are executed.
- ③ The `break` for leaving a case cannot be omitted.
- ④ A floating-point value or a string can be given after case.
- ⑤ If a case has no `break`, all the statements that follow are executed until a `break` or the end of the `switch` is reached.
- ⑥ `default` can be omitted in `switch`.
- ⑦ `if-else` can be written instead of `switch`.
- ⑧ Even if a case has several statements to execute, they do not need to be enclosed in `{ }`.

**[Solution](Solutions.md#exercise-9-statements-about-the-switch-statement)**

---

<br>

## Exercise 10: Rewriting a switch Statement with if-else

**Textbook Problem:** Chapter 5 exercise 5

**Problem:** Rewrite the whole `switch` statement in the following code with `if-else`.

```c
#define _CRT_SECURE_NO_WARNINGS     // Visual Studio 2022에서 scanf 사용 시 필요
#include <stdio.h>
int main(void)
{
    int month;
    int fee;
    printf("몇 월? ");
    scanf("%d", &month);
    switch (month) {
    case 7:                         // 7~8월 극성수기 요금
    case 8:
        fee = 70000;
        break;
    case 6:                         // 6월, 9월 성수기 요금
    case 9:
        fee = 55000;
        break;
    default:                        // 나머지 정상 요금
        fee = 40000;
        break;
    }
    printf("입장료 : %d\n", fee);
}
```

**[Solution](Solutions.md#exercise-10-rewriting-a-switch-statement-with-if-else)**

---

<br>

## Exercise 11: Statements About the for Statement

**Textbook Problem:** Chapter 5 exercise 6

**Problem:** Choose all the incorrect statements about the `for` statement.

- ① The initialization expression of `for` is executed only once, when the `for` statement first starts.
- ② The initialization, condition, and update expressions of `for` cannot be omitted.
- ③ The statement repeated by `for` is always executed at least once.
- ④ The statement to repeat can be omitted in `for`.
- ⑤ Omitting the condition of `for` makes an infinite loop.
- ⑥ If `for` has several statements to repeat, they are enclosed in `{ }`.
- ⑦ Several loop control variables can be used in `for`.
- ⑧ `for` cannot be nested inside `for`.
- ⑨ The comma operator is used to combine several statements in the initialization or update expression.

**[Solution](Solutions.md#exercise-11-statements-about-the-for-statement)**

---

<br>

## Exercise 12: Rewriting a for Statement with while

**Textbook Problem:** Chapter 5 exercise 7

**Problem:** In the following code, rewrite the loop written with a `for` statement (the `for (i = 1; i <= 10; i++) { ... }` part) with a `while` statement.

```c
#include <stdio.h>
int main(void)
{
    int i;
    int sum = 0;
    int times = 1;
    for (i = 1; i <= 10; i++) {
        sum += i;
        times *= i;
    }
    printf("합:%d, 곱:%d\n", sum, times);
}
```

**[Solution](Solutions.md#exercise-12-rewriting-a-for-statement-with-while)**

---

<br>

## Exercise 13: Statements About while and do-while

**Textbook Problem:** Chapter 5 exercise 8

**Problem:** Choose all the incorrect statements about the `while` and `do-while` statements.

- ① If the condition of `while` is true, the statement is executed.
- ② The condition of `while` is checked at the start of the loop.
- ③ The condition of the `do-while` statement is checked at the start of the loop.
- ④ `while` always executes the statement to repeat at least once.
- ⑤ `do-while` always executes the statement to repeat at least once.
- ⑥ The conditions of `while` and `do-while` cannot be omitted.
- ⑦ `while` is more suitable than `for` for implementing a regular loop.
- ⑧ If there are several statements to execute when the condition of a `while` statement is true, they are enclosed in `{ }`.

**[Solution](Solutions.md#exercise-13-statements-about-while-and-do-while)**

---

<br>

## Exercise 14: Branch Statements and Their Roles

**Textbook Problem:** Chapter 5 exercise 9

**Problem:** Match each branch statement (1)-(4) with its role ①-④.

**Branch Statements:**

- (1) `break`
- (2) `continue`
- (3) `goto`
- (4) `return`

**Roles:**

- ① Moves to the start or the end of the loop.
- ② Exits a `switch` or a loop.
- ③ Returns to the place that called the function.
- ④ Moves to the position marked by a label.

**[Solution](Solutions.md#exercise-14-branch-statements-and-their-roles)**

---

<br>

## Exercise 15: Statements About Branch Statements

**Textbook Problem:** Chapter 5 exercise 10

**Problem:** Choose all the incorrect statements about branch statements.

- ① A `return` statement must always specify a value.
- ② `break` exits an `if` statement.
- ③ The `goto` statement moves the flow of control to a specific position.
- ④ When `continue` is reached inside a `for` statement, the flow of control moves to the start of the loop.
- ⑤ When `continue` is reached inside a `do-while` statement, the flow of control moves to the end of the loop.
- ⑥ When a loop contains a `switch` statement, `break` can exit both the `switch` statement and the loop at once.
- ⑦ `goto` can exit nested loops at once.
- ⑧ `continue` can exit a loop at a position other than the start or the end of the loop.

**[Solution](Solutions.md#exercise-15-statements-about-branch-statements)**

---

<br>

## Exercise 16: Finding Infinite Loops

**Textbook Problem:** Chapter 5 exercise 11

**Problem:** Choose all the infinite loops below.

- ① `for( ; ; ) { printf("a"); }`
- ② `for(i = 0 ; i > 1 ; i++) { printf("%d", i); }`
- ③ `while ( ) { printf("a"); }`
- ④ `while (2) { printf("a"); }`
- ⑤ `while (0) { printf("a"); }`
- ⑥ `do { printf("a"); } while (1);`
- ⑦ `do { printf("a"); } while ( );`

**[Solution](Solutions.md#exercise-16-finding-infinite-loops)**

---

<br>

## Exercise 17: Output of a Nested if Statement

**Textbook Problem:** Chapter 5 exercise 12

**Problem:** Write the output of the following program.

```c
#include <stdio.h>
int main(void)
{
    int n = 1;
    if (n > 0) {
        n *= 2;
        if (n < 5)
            n += 5;
        else
            n -= 5;
    }
    else
        n++;
    printf("n = %d\n", n);
}
```

**[Solution](Solutions.md#exercise-17-output-of-a-nested-if-statement)**

---

<br>

## Exercise 18: Output of a for Loop with continue

**Textbook Problem:** Chapter 5 exercise 13

**Problem:** Write the output of the following program.

```c
#include <stdio.h>
int main(void)
{
    int i;
    int n = 0;
    for (i = 1; i < 10; i += 2) {
        if (i % 3 == 0)
            continue;
        n += i;
    }
    printf("n = %d\n", n);
}
```

**[Solution](Solutions.md#exercise-18-output-of-a-for-loop-with-continue)**

---

<br>

## Exercise 19: Grades by Absolute Evaluation

**Textbook Problem:** Chapter 5 programming assignment 1

**Problem:** Grades are to be computed by absolute evaluation. Write a program that reads an exam score (0-100 points) and computes the grade: A for 90 points or more, B for 80 or more, C for 70 or more, D for 60 or more, and F for less than 60.

**Sample Run:**

```text
점수? 91
학점: A
```

**[Solution](Solutions.md#exercise-19-grades-by-absolute-evaluation)**

---

<br>

## Exercise 20: Grades by Relative Evaluation

**Textbook Problem:** Chapter 5 programming assignment 2

**Problem:** Grades are to be computed by relative evaluation. Write a program that reads a rank and the total number of students and computes the grade: A for the top 10%, B up to the top 30%, C up to the top 60%, D up to the top 90%, and F for the bottom 10%.

**Sample Run:**

```text
등수? 10
전체 인원수? 80
학점: B
```

**[Solution](Solutions.md#exercise-20-grades-by-relative-evaluation)**

---

<br>

## Exercise 21: The Quadrant of a Point

**Textbook Problem:** Chapter 5 programming assignment 3

**Problem:** Write a program that reads the coordinates (x, y) of a point in the two-dimensional plane and prints which quadrant the point belongs to. Quadrant 1 is the region with x > 0 and y > 0, quadrant 2 with x < 0 and y > 0, quadrant 3 with x < 0 and y < 0, and quadrant 4 with x > 0 and y < 0. Compare using `if-else` with using multiple independent `if` statements. This is the same task as [Exercise 1](#exercise-1-quadrant-of-a-point-in-the-plane).

**Sample Run:**

```text
점의 좌표 (x, y)? 10 -10
4사분면에 있습니다.
```

**[Solution](Solutions.md#exercise-21-the-quadrant-of-a-point)**

---

<br>

## Exercise 22: Leap Year Test

**Textbook Problem:** Chapter 5 programming assignment 4

**Problem:** Write a program that reads a year and tests whether it is a leap year. The conditions for a leap year are as follows.

- A year divisible by 4 is a leap year.
- Among the years divisible by 4, a year divisible by 100 is not a leap year.
- Among the years divisible by 100, a year divisible by 400 is a leap year.

**Sample Run:**

```text
연도? 2020
2020년은 윤년입니다.
```

**[Solution](Solutions.md#exercise-22-leap-year-test)**

---

<br>

## Exercise 23: Converting Celsius and Fahrenheit Temperatures

**Textbook Problem:** Chapter 5 programming assignment 5

**Problem:** Write a program that reads a temperature and converts a Celsius temperature to Fahrenheit and a Fahrenheit temperature to Celsius. A letter telling whether the temperature is Celsius or Fahrenheit is read together with it, as in "27 C" or "27 F"; if the letter is `'C'`, the program computes and prints the Fahrenheit temperature, and if it is `'F'`, the Celsius temperature. The conversion formulas are the same as in Exercise 2, and this is the same task as [Exercise 2](#exercise-2-converting-between-celsius-and-fahrenheit).

**Sample Run:**

```text
온도? 27 C
27.00 C == 80.60 F
```

**[Solution](Solutions.md#exercise-23-converting-celsius-and-fahrenheit-temperatures)**

---

<br>

## Exercise 24: Electricity Bill with Progressive Rates

**Textbook Problem:** Chapter 5 programming assignment 6

**Problem:** An electricity bill is the sum of a basic charge and an energy charge based on the monthly usage. Progressive rates apply according to the monthly usage, so the basic charge and the energy charge differ by tier. Referring to the progressive rate table in Table 1, write a program that computes the electricity bill from the monthly usage read as input.

| Basic charge tier | Basic charge (won/household) | Energy charge tier | Energy charge (won/kWh) |
|:-----|-----:|:-----|-----:|
| Usage up to 300 kWh | 1,000 | Up to 300 kWh | 100 |
| Usage above 300 kWh | 5,000 | Above 300 kWh | 200 |

*Table 1. Progressive electricity rate table*

For example, if the monthly usage is 350 kWh, the basic charge is 5,000 won and the energy charge is computed as 300 × 100 + (350 - 300) × 200 won.

**Sample Run:**

```text
월 사용량 (kWh)? 350
전기 요금 합계:  45000원
  - 기본요금:     5000원
  - 전력량요금:  40000원
```

**[Solution](Solutions.md#exercise-24-electricity-bill-with-progressive-rates)**

---

<br>

## Exercise 25: Bitwise Operation Calculator

**Textbook Problem:** Chapter 5 programming assignment 7

**Problem:** Write a calculator program that performs bitwise operations. It handles `&` as bitwise AND, `|` as bitwise OR, and `^` as bitwise XOR. It reads an expression such as "0xAB & 0xCC" and computes and prints the result. Since these are bitwise operations, the input is read in hexadecimal and the result is also printed in hexadecimal.

**Sample Run:**

```text
비트 연산식? 0xabcdef12 & 0xF0F0F0F0
ABCDEF12 & F0F0F0F0 = A0C0E010
```

**[Solution](Solutions.md#exercise-25-bitwise-operation-calculator)**

---

<br>

## Exercise 26: Printing ASCII Characters

**Textbook Problem:** Chapter 5 programming assignment 8

**Problem:** Write a program that prints characters using ASCII codes. ASCII codes 0-31 and 127 are control characters, so print only the characters assigned to codes 32-126, 24 characters per line.

**Sample Run:**

```text
  ! " # $ % & ' ( ) * + , - . / 0 1 2 3 4 5 6 7
8 9 : ; < = > ? @ A B C D E F G H I J K L M N O
P Q R S T U V W X Y Z [ \ ] ^ _ ` a b c d e f g
h i j k l m n o p q r s t u v w x y z { | } ~
```

**[Solution](Solutions.md#exercise-26-printing-ascii-characters)**

---

<br>

## Exercise 27: Printing Multiples of an Integer

**Textbook Problem:** Chapter 5 programming assignment 9

**Problem:** Write a program that prints multiples of an integer. It reads a positive integer and the number of multiples, and prints that many multiples of the integer.

**Sample Run:**

```text
양의 정수? 11
배수의 개수? 20
11 22 33 44 55 66 77 88 99 110 121 132 143 154 165 176 187 198 209 220
```

**[Solution](Solutions.md#exercise-27-printing-multiples-of-an-integer)**

---

<br>

## Exercise 28: Repeating the Electricity Bill Calculation

**Textbook Problem:** Chapter 5 programming assignment 10

**Problem:** Modify the electricity bill program of [Exercise 24](#exercise-24-electricity-bill-with-progressive-rates) so that it repeats until 0 is entered as the monthly usage.

**Sample Run:**

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

**[Solution](Solutions.md#exercise-28-repeating-the-electricity-bill-calculation)**

---

<br>

## Exercise 29: Prime Test

**Textbook Problem:** Chapter 5 programming assignment 11

**Problem:** A prime is a positive integer greater than 1 that is divisible only by 1 and itself. Write a program that reads an integer and tests whether it is a prime.

**Sample Run:**

```text
양의 정수? 12
12는 소수가 아닙니다.
```

**[Solution](Solutions.md#exercise-29-prime-test)**

---

<br>

## Exercise 30: Printing the Primes up to N

**Textbook Problem:** Chapter 5 programming assignment 12

**Problem:** Write a program that reads an integer N and finds and prints all the primes from 1 to N. The primes are printed 10 per line.

**Sample Run:**

```text
양의 정수? 100
  2  3  5  7 11 13 17 19 23 29
 31 37 41 43 47 53 59 61 67 71
 73 79 83 89 97
```

**[Solution](Solutions.md#exercise-30-printing-the-primes-up-to-n)**
