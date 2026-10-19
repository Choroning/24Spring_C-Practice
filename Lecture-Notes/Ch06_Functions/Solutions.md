# Chapter 6 Solutions — Functions

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-19

**Problem Source:** Prof. Younghee Im, Computer Language Ⅰ (DCCS101-04)

---

<br>

## Table of Contents

- [Exercise 1: Rounding a Real Number](#exercise-1-rounding-a-real-number)
- [Exercise 2: Leap Year Test](#exercise-2-leap-year-test)
- [Exercise 3: Number of Days in a Month](#exercise-3-number-of-days-in-a-month)

---

<br>

## Exercise 1: Rounding a Real Number

**Problem:** Define a function that receives a real number and returns the integer obtained by rounding it at the first decimal place, and use it to read real numbers until `0.0` is entered and print each rounded result. Both positive and negative numbers must be rounded correctly. The full problem and sample run are in [Exercise 1](Exercises.md#exercise-1-rounding-a-real-number).

### Solution

**Approach:** Casting a `double` to `(int)` discards the fractional part and truncates toward zero. Therefore adding 0.5 to a positive number, or subtracting 0.5 from a negative number, before truncating yields the value rounded at the first decimal place.

- **`round_value()`:** If `value` is positive, it adds 0.5; otherwise it subtracts 0.5; then it converts the result with `(int)` and returns it. 2.75 becomes 3.25 and then 3, 9.1 becomes 9.6 and then 9, -6.3 becomes -6.8 and then -6, and -7.815 becomes -8.315 and then -8. If `value` is 0, it takes the subtracting branch and becomes -0.5, but truncation toward zero makes it 0.
- **Function name:** The solution code names the function `round_value()`. `round` is the name of a standard library function declared in `<math.h>` as `double round(double)` since C99, so defining `int round(double)` with the name given in the problem makes gcc warn that the type conflicts with the built-in function (`conflicting types for built-in function 'round'`) and makes clang warn about an incompatible redeclaration of a library function, even without including `<math.h>`.
- **`main()`:** Inside the infinite loop `do { ... } while (1);`, it reads a real number with `%lf` and ends the loop with `break` if the number is 0.0. For any other value, it prints the input to six decimal places with `%lf` in `printf` (which is the same as `%f` for output) and prints the return value of `round_value()` with `%d`. The return value can be used directly as an argument of `printf` without storing it in a variable because a call to a function with a return value is an expression ([Chapter 6, Section 2.5](Concepts_Lecture.md#25-function-call)).

**Code:** [Lab_Q1.c](../../Coursework/Lab06_Functions/Lab_Q1.c)

```c
/**
 * @file    A10104-1_C06Q1.c
 * @brief   Q1. 실수 반올림
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-16
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int round_value(double value)
{
    if (value > 0) {
        value += 0.5;
    }
    else {
        value -= 0.5;
    }
    return (int)value;
}

int main()
{
    double num;
    
    do {
        printf("실수를 입력하세요 (0.0 입력 시 종료) : ");
        scanf_s(" %lf", &num);

        if (num == 0.0)
            break;
        else
            printf("%lf의 반올림 결과 = %d\n\n", num, round_value(num));
    } while (1);

    return 0;
}
```

**Output:** `scanf_s` is a function provided by Visual Studio, so with gcc the code was compiled with `gcc -std=c99 -Wall -Dscanf_s=scanf`, which replaces it with `scanf` (no warnings). Entering the same values as in the sample run gives the same results. However, the prompt in the code has a space before the colon, as in `종료) : `, which differs by one space from `종료): ` in the sample run, and the last line of the sample run, `Program ended with exit code: 0`, is not program output but the exit message added by the Xcode console.

```text
실수를 입력하세요 (0.0 입력 시 종료) : 2.75
2.750000의 반올림 결과 = 3

실수를 입력하세요 (0.0 입력 시 종료) : 9.1
9.100000의 반올림 결과 = 9

실수를 입력하세요 (0.0 입력 시 종료) : -6.3
-6.300000의 반올림 결과 = -6

실수를 입력하세요 (0.0 입력 시 종료) : -7.815
-7.815000의 반올림 결과 = -8

실수를 입력하세요 (0.0 입력 시 종료) : 0.0
```

> **Note:** **`scanf_s`.** `scanf_s` is an optional feature defined in Annex K (bounds-checking interfaces) of C11; Visual Studio provides it, but glibc and the macOS C library used by gcc and clang do not. Compiling the code as is therefore fails under the implicit declaration rule of C99 and later. For numeric conversions such as `%d` and `%lf` it is used exactly like `scanf`, but reading characters with `%s` or `%c` requires passing the buffer size as an extra argument.

> **Caution:** This method rounds values whose fractional part is exactly 0.5, such as 2.5, away from zero (2.5 becomes 3 and -2.5 becomes -3). Also, if the input is a value whose rounded result is outside the range of `int` (for example, 3e10), the result of the `(int)` conversion is undefined.

---

<br>

## Exercise 2: Leap Year Test

**Problem:** Define a function `isLeapYear()` that receives a year and returns 1 for a leap year and 0 for a common year, and use it to print the leap years from 2000 to 2150, 10 per line, separated by spaces. The full problem and sample run are in [Exercise 2](Exercises.md#exercise-2-leap-year-test).

### Solution

**Approach:** Check the leap year conditions in the order given in the problem. A year not divisible by 4 is a common year; a year divisible by 4 but not by 100 is a leap year; a year divisible by 100 is a leap year only if it is also divisible by 400.

- **`isLeapYear()`:** It writes the three conditions as one expression by nesting the conditional operator `? :`. If the outer condition `(year % 4) == 0` is false, the result is 0; if it is true, `(year % 100) == 0` is checked, giving 1 if false, and if true the function returns 1 or 0 according to `(year % 400) == 0`. This expression yields the same value as `(year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)` in [Chapter 6, Section 2.5](Concepts_Lecture.md#25-function-call).
- **`main()`:** After printing the title, it increases `input` by 1 from 2000 to 2150, prints only the years for which `isLeapYear(input)` is 1 with `"%d "`, and increases `count` by 1. It starts a new line whenever `count` becomes a multiple of 10, so 10 years are printed per line.
- **Checking the result:** 2000 is divisible by 400, so it is a leap year, and 2100 is divisible by 100 but not by 400, so it is a common year. There are 38 multiples of 4 from 2000 to 2148, and removing 2100 leaves 37 leap years, so three lines of 10 and a last line of 7 are printed.

**Code:** [Lab_Q2.c](../../Coursework/Lab06_Functions/Lab_Q2.c)

```c
/**
 * @file    A10104-1_C06Q2.c
 * @brief   Q2. 윤년 판별
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-17
 */

#include <stdio.h>

int isLeapYear(int year)
{
    return ((year % 4) == 0) ? ((year % 100) == 0 ? ((year % 400) == 0 ? 1 : 0) : 1) : 0;
}

int main()
{
    int input, count = 0;

    printf("-------------------------------------------------\n");
    printf("               2000~2150년 사이의 윤년\n");
    printf("-------------------------------------------------\n");

    for (input = 2000; input <= 2150; input++) {
        if (isLeapYear(input) == 1) {
            printf("%d ", input);
            count++;
            if (count % 10 == 0)
                printf("\n");
        }
    }

    return 0;
}
```

**Output:** The same list of leap years as in the sample run is printed. Because a space is printed after each year, every line ends with one trailing space, and the last line ends without a newline because `count` is not a multiple of 10 after its 7 years.

```text
-------------------------------------------------
               2000~2150년 사이의 윤년
-------------------------------------------------
2000 2004 2008 2012 2016 2020 2024 2028 2032 2036 
2040 2044 2048 2052 2056 2060 2064 2068 2072 2076 
2080 2084 2088 2092 2096 2104 2108 2112 2116 2120 
2124 2128 2132 2136 2140 2144 2148 
```

> **Note:** **Comparing the return value.** `main()` compares the return value with `isLeapYear(input) == 1`, but since `isLeapYear()` returns only 0 or 1, `if (isLeapYear(input))` is equivalent. In C, a condition is treated as false if it is 0 and true otherwise.

---

<br>

## Exercise 3: Number of Days in a Month

**Problem:** Define a function `GetDaysOfMonth()` that receives a year and a month and returns the number of days in that month, and print the number of days for the year and month entered. Whether February is in a leap year is determined with `isLeapYear()` from Exercise 2. The full problem and sample runs are in [Exercise 3](Exercises.md#exercise-3-number-of-days-in-a-month).

### Solution

**Approach:** Only February has 29 or 28 days depending on whether the year is a leap year; of the remaining months, `switch` picks April, June, September, and November, which have 30 days, and treats all other months as having 31 days.

- **`GetDaysOfMonth()`:** In the solution code, this function takes the leap year flag (`detect`) and the month as parameters instead of the year. If `month` is 2, it returns 29 when `detect` is true and 28 when it is false; for other months, the `switch` groups `case 4`, `case 6`, `case 9`, and `case 11` to return 30 and returns 31 in `default`. When several `case` labels are written in a row, the same statements run whichever label is entered.
- **Nested `if-else`:** The `if (detect) ... else ...` inside `if (month == 2)` is written without braces. An `else` pairs with the nearest unmatched `if`, so the first `else` attaches to `if (detect)` and the second to `if (month == 2)`, and the code works as intended.
- **`main()`:** After reading the year and month, it passes the return value of `isLeapYear()` directly as an argument, as in `GetDaysOfMonth(isLeapYear(year), month)`. The function call used as an argument is evaluated first to 1 or 0, and that value is passed to `detect` ([Chapter 6, Section 2.5](Concepts_Lecture.md#25-function-call)).

**Code:** [Lab_Q3.c](../../Coursework/Lab06_Functions/Lab_Q3.c)

```c
/**
 * @file    A10104-1_C06Q3.c
 * @brief   Q3. 월별 날짜 수 계산
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-17
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int GetDaysOfMonth(int detect, int month)
{
    if (month == 2)
        if (detect)
            return 29;
        else
            return 28;
    else
        switch (month) {
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
            return 31;
        }
}

int isLeapYear(int year)
{
    return ((year % 4) == 0) ? ((year % 100) == 0 ? ((year % 400) == 0 ? 1 : 0) : 1) : 0;
}

int main()
{
    int year, month, days;

    printf("연도와 월을 입력하세요: ");
    scanf_s(" %d %d", &year, &month);

    days = GetDaysOfMonth(isLeapYear(year), month);

    printf("%d년 %d월은 %d일까지 있습니다.", year, month, days);

    return 0;
}
```

**Output:** Compiled with `-Dscanf_s=scanf` and given the four inputs of the sample runs in turn, the program produces the same results as the four sample runs. Because the output does not end with a newline, the next shell prompt continues on the same line in a terminal.

```text
연도와 월을 입력하세요: 2017 4
2017년 4월은 30일까지 있습니다.
```

```text
연도와 월을 입력하세요: 2020 8
2020년 8월은 31일까지 있습니다.
```

```text
연도와 월을 입력하세요: 2000 2
2000년 2월은 29일까지 있습니다.
```

```text
연도와 월을 입력하세요: 2100 2
2100년 2월은 28일까지 있습니다.
```

> **Note:** **Function interface.** The problem specifies that `GetDaysOfMonth()` receives a year and a month, but the solution code leaves the leap year test to the caller and receives the leap year flag and the month. The result is the same, but with the form that receives the year, the function calls `isLeapYear(year)` itself, as in the example in [Chapter 6, Section 2.5](Concepts_Lecture.md#25-function-call), so the caller does not need to know about the leap year test.

> **Caution:** The month is not validated, so a value outside 1-12 is handled by `default` and printed as 31 days. For example, entering `2024 13` prints "2024년 13월은 31일까지 있습니다.".
