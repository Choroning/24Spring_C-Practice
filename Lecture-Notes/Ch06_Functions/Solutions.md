# Chapter 6 Solutions — Functions

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-27
>
> Warming-Up C Programming, 천정아, Ch 6

**Problem Source:** Prof. Younghee Im, Computer Language Ⅰ (DCCS101-04)

---

<br>

## Table of Contents

- [Exercise 1: Rounding a Real Number](#exercise-1-rounding-a-real-number)
- [Exercise 2: Leap Year Test](#exercise-2-leap-year-test)
- [Exercise 3: Number of Days in a Month](#exercise-3-number-of-days-in-a-month)
- [Exercise 4: The Concept of a Function](#exercise-4-the-concept-of-a-function)
- [Exercise 5: Advantages of Using Functions](#exercise-5-advantages-of-using-functions)
- [Exercise 6: Statements About Functions](#exercise-6-statements-about-functions)
- [Exercise 7: Return Types and Parameters](#exercise-7-return-types-and-parameters)
- [Exercise 8: The Three Requirements of a Function](#exercise-8-the-three-requirements-of-a-function)
- [Exercise 9: Calling a Function with a Return Value and Parameters](#exercise-9-calling-a-function-with-a-return-value-and-parameters)
- [Exercise 10: Local and Global Variables](#exercise-10-local-and-global-variables)
- [Exercise 11: Prototype of a Function That Computes the Perimeter of a Rectangle](#exercise-11-prototype-of-a-function-that-computes-the-perimeter-of-a-rectangle)
- [Exercise 12: Prototype of a Function That Checks for an English Letter](#exercise-12-prototype-of-a-function-that-checks-for-an-english-letter)
- [Exercise 13: Prototype of a Function That Computes a Discounted Price](#exercise-13-prototype-of-a-function-that-computes-a-discounted-price)
- [Exercise 14: Prototype of a Function That Computes the Greatest Common Divisor](#exercise-14-prototype-of-a-function-that-computes-the-greatest-common-divisor)
- [Exercise 15: Turning the Arithmetic Code into a Function](#exercise-15-turning-the-arithmetic-code-into-a-function)
- [Exercise 16: The Code Needed in the Blank](#exercise-16-the-code-needed-in-the-blank)
- [Exercise 17: Output of a Program with Variables of the Same Name](#exercise-17-output-of-a-program-with-variables-of-the-same-name)
- [Exercise 18: Printing Multiples of an Integer](#exercise-18-printing-multiples-of-an-integer)
- [Exercise 19: Perimeter of a Rectangle](#exercise-19-perimeter-of-a-rectangle)
- [Exercise 20: Distance Between Two Points](#exercise-20-distance-between-two-points)
- [Exercise 21: Computing Discounted Prices](#exercise-21-computing-discounted-prices)
- [Exercise 22: Printing a Menu](#exercise-22-printing-a-menu)
- [Exercise 23: The Red, Green, and Blue Values of an RGB Color](#exercise-23-the-red-green-and-blue-values-of-an-rgb-color)
- [Exercise 24: Leap Years from 2000 to 2100](#exercise-24-leap-years-from-2000-to-2100)
- [Exercise 25: Checking for a Valid Date](#exercise-25-checking-for-a-valid-date)
- [Exercise 26: Printing an Integer in Binary](#exercise-26-printing-an-integer-in-binary)
- [Exercise 27: Divisors and the Number of Divisors](#exercise-27-divisors-and-the-number-of-divisors)
- [Exercise 28: Prime Numbers from 1 to N](#exercise-28-prime-numbers-from-1-to-n)
- [Exercise 29: An Accumulator](#exercise-29-an-accumulator)

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

---

<br>

## Exercise 4: The Concept of a Function

**Textbook Problem:** Chapter 6 exercise 1

**Problem:** Of five statements about the concept of a function, choose all the incorrect ones. The options are in [Exercise 4](Exercises.md#exercise-4-the-concept-of-a-function).

### Solution

**Answer:** ③, ④

**Explanation:** A function is a named block of code that performs a specific task, and the caller can use a function without knowing its internal implementation ([Chapter 6, Section 1.1](Concepts_Lecture.md#11-why-functions)).

- **① (correct):** A function groups the code that performs a specific job and gives it a name, and the name runs the grouped code.
- **② (correct):** A function can be seen as a black box that takes input through its parameters, performs a fixed job, and produces a result as its return value.
- **③ (incorrect):** All that is needed to call a function is how to use it: its name, parameters, and return type. This is just as `printf` can be called with only the declaration that `<stdio.h>` provides, without knowing its internal code ([Chapter 6, Section 1.2](Concepts_Lecture.md#12-function-types)).
- **④ (incorrect):** A function's code exists only once in the program. Calling a function does not copy its code; the flow of execution (control) passes to the function and returns to the caller when the function ends ([Chapter 6, Section 4](Concepts_Lecture.md#4-function-call-overhead)). Compilers may also perform inline expansion, which places the body of a small function at the call site during optimization, but that is the compiler's choice for reducing call overhead.
- **⑤ (correct):** As in the factorial example of [Chapter 6, Section 1.1](Concepts_Lecture.md#11-why-functions), a repeated part of code already written can be taken out and defined as a function.

---

<br>

## Exercise 5: Advantages of Using Functions

**Textbook Problem:** Chapter 6 exercise 2

**Problem:** Of five statements about using functions, choose all the advantages. The options are in [Exercise 5](Exercises.md#exercise-5-advantages-of-using-functions).

### Solution

**Answer:** ②, ③, ⑤

**Explanation:** Functions give four benefits: code reuse, modularity, readability, and maintainability ([Chapter 6, Section 1.1](Concepts_Lecture.md#11-why-functions)).

- **① (not an advantage):** The opposite is true. With functions, the same code is defined once and called where needed instead of being copied to several places, so code duplication decreases and the code appears only once in the executable file.
- **② (an advantage):** A function written once can be called from many places in a program and reused in other programs.
- **③ (an advantage):** When a feature changes or a bug is fixed, modifying only that function updates every place that calls it.
- **④ (not an advantage):** With functions, the details are hidden inside the functions and `main()` reads like a table of contents of function calls, so the code becomes shorter and easier to read.
- **⑤ (an advantage):** A large problem is written as small functions by feature, which increases the modularity of the program.

---

<br>

## Exercise 6: Statements About Functions

**Textbook Problem:** Chapter 6 exercise 3

**Problem:** Of eleven statements about defining, declaring, and calling functions, choose all the incorrect ones. The options are in [Exercise 6](Exercises.md#exercise-6-statements-about-functions).

### Solution

**Answer:** ②, ③, ⑤, ⑧

**Explanation:** The return type, return value, and arguments in the options are the same terms as in the lecture notes. Using a function requires three elements, definition, declaration, and call, and of these only the declaration can be omitted ([Chapter 6, Section 1.3](Concepts_Lecture.md#13-function-requirements)).

- **① (correct):** The definition of a function that is called must appear in the program exactly once. With only a declaration and no definition, an error occurs at the link stage.
- **② (incorrect):** The textbook explains that an omitted return type is taken as `int`. So a function without a return value must state `void` rather than omit the return type ([Chapter 6, Section 2.2](Concepts_Lecture.md#22-return-type)).
- **③ (incorrect):** What describes the work a function actually performs is the function definition. The declaration (prototype) only tells the return type, function name, and parameter list, and ends with a semicolon without a body ([Chapter 6, Section 2.6](Concepts_Lecture.md#26-function-declaration-prototype)).
- **④ (correct):** The caller passes arguments to the parameters and gets back the return value when the function ends ([Chapter 6, Section 2.5](Concepts_Lecture.md#25-function-call)).
- **⑤ (incorrect):** The number of arguments must equal the number of parameters, and where the prototype is visible, too few arguments cause a compile error rather than being filled with 0. For example, calling `int add(int a, int b);` as `add(1)` makes clang report "too few arguments to function call, expected 2, have 1".
- **⑥ (correct):** The compiler reads the source code from top to bottom, so the function's declaration or definition must come before the call ([Chapter 6, Section 2.6](Concepts_Lecture.md#26-function-declaration-prototype)).
- **⑦ (correct):** An argument is an expression too, so its value is computed first and the function is called with that value passed to the parameter ([Chapter 6, Section 2.5](Concepts_Lecture.md#25-function-call)).
- **⑧ (incorrect):** C cannot define two or more functions with the same name (no overloading). Defining the same name twice causes a compile error such as "redefinition of 'add'" ([Chapter 6, Section 2.3](Concepts_Lecture.md#23-function-name)).
- **⑨ (correct):** A prototype may omit the parameter names and give only the types, as in `int add(int, int);`. Writing the names is still recommended because they document the function ([Chapter 6, Section 2.6](Concepts_Lecture.md#26-function-declaration-prototype)).
- **⑩ (correct):** If the function's definition comes before the call, the function can be called without a declaration ([Chapter 6, Section 1.3](Concepts_Lecture.md#13-function-requirements)).
- **⑪ (correct):** Declarations of the same function may be written several times as long as they agree. For example, `int add(int a, int b);` and `int add(int, int);` can both appear in one file without an error.

> **Note:** **The implicit `int` rule.** The rule that an omitted return type is taken as `int` belongs to C89 and earlier, and it was removed from the standard in C99. So when compiling to C99 or later, a compiler warns about or rejects a function definition without a return type, such as `f(void) { ... }`. With `-std=c99`, clang reports the error "type specifier missing, defaults to 'int'; ISO C99 and later do not support implicit int", and gcc also treats it as an error by default from version 14. Always state the return type.

---

<br>

## Exercise 7: Return Types and Parameters

**Textbook Problem:** Chapter 6 exercise 4

**Problem:** Of eight statements about the return type and parameters of a function, choose all the incorrect ones. The options are in [Exercise 7](Exercises.md#exercise-7-return-types-and-parameters).

### Solution

**Answer:** ③, ⑦

**Explanation:** The return type is the type of the value a function sends back, and a parameter is a local variable created when the function is called and initialized with the value of the argument ([Chapter 6, Section 2.2](Concepts_Lecture.md#22-return-type), [Section 2.4](Concepts_Lecture.md#24-parameters-and-arguments)).

- **① (correct):** The return type is the data type of the value a function returns as its result. The return type `int` of `int factorial(int n)` means the result is an integer.
- **② (correct):** A function with no value to return is written with the return type `void`, as in `void printLine(void)`.
- **③ (incorrect):** According to the textbook, an omitted return type is taken as `int`, not `void`. That is why a function without a return value must state `void` (option ② of Exercise 6).
- **④ (correct):** A function can return only one value with `return`, so when there are two or more results, it takes the addresses of the caller's variables as parameters and stores the results in those variables. This method is covered in Chapter 8 ([Chapter 6, Section 2.2](Concepts_Lecture.md#22-return-type)). Several values can also be grouped into one structure and returned, but even then the return value itself is one.
- **⑤ (correct):** Parameters are declared in the function definition and store the values of the arguments passed in the call ([Chapter 6, Section 2.4](Concepts_Lecture.md#24-parameters-and-arguments)).
- **⑥ (correct):** A function without parameters is written with `void`, as in `void printMenu(void)`, or with empty parentheses, as in `void printMenu()`. The two forms are the same in a function definition, but in a prototype before C23, empty parentheses declare the function without parameter information, so `void` is recommended ([Chapter 6, Section 2.4](Concepts_Lecture.md#24-parameters-and-arguments)).
- **⑦ (incorrect):** C does not limit the number of parameters to a value such as 8 ([Chapter 6, Section 2.4](Concepts_Lecture.md#24-parameters-and-arguments)). The standard requires a compiler to accept at least 127 parameters in one function.
- **⑧ (correct):** A parameter is a local variable that is created when the function is called, initialized with a copy of the argument, and destroyed when the function returns ([Chapter 6, Section 2.4](Concepts_Lecture.md#24-parameters-and-arguments)).

> **Note:** The implicit `int` rule behind ③ was removed from the standard in C99, so when compiling to C99 or later, a compiler warns about or rejects a function definition without a return type. The details are in [the note of Exercise 6](#exercise-6-statements-about-functions).

---

<br>

## Exercise 8: The Three Requirements of a Function

**Textbook Problem:** Chapter 6 exercise 5

**Problem:** Write all three requirements of a function. The full problem is in [Exercise 8](Exercises.md#exercise-8-the-three-requirements-of-a-function).

### Solution

**Answer:** The function definition, the function call, and the function declaration

**Explanation:** The lecture notes present these three as the three elements of using a function ([Chapter 6, Section 1.3](Concepts_Lecture.md#13-function-requirements)).

- **Function definition:** Implements what the function does, with a header made of the return type, function name, and parameter list, and a body `{}`. It must appear in the program exactly once ([Chapter 6, Section 2.1](Concepts_Lecture.md#21-function-definition)).
- **Function call:** Runs the function by putting the arguments in parentheses after its name. It is always needed to use a function ([Chapter 6, Section 2.5](Concepts_Lecture.md#25-function-call)).
- **Function declaration:** Tells the compiler the return type, function name, and parameter types in advance through a prototype. It can be omitted if the definition comes before the call ([Chapter 6, Section 2.6](Concepts_Lecture.md#26-function-declaration-prototype)).

---

<br>

## Exercise 9: Calling a Function with a Return Value and Parameters

**Textbook Problem:** Chapter 6 exercise 6

**Problem:** Of eight statements about calling a function that has a return value and parameters, choose all the incorrect ones. The options are in [Exercise 9](Exercises.md#exercise-9-calling-a-function-with-a-return-value-and-parameters).

### Solution

**Answer:** ②, ③, ⑧

**Explanation:** When a function is called, the values of the arguments are computed and copied in order to the parameters, and when the function ends, the return value becomes the value of the call expression ([Chapter 6, Section 2.5](Concepts_Lecture.md#25-function-call)).

- **① (correct):** C passes arguments by value, so the value of each argument is copied and stored in the parameter ([Chapter 6, Section 2.4](Concepts_Lecture.md#24-parameters-and-arguments)).
- **② (incorrect):** The direction of conversion is reversed. Where the prototype is visible and an argument's type differs from the parameter's, the argument's value is converted to the parameter's type and passed. For example, passing 101 to a `char` parameter passes the character `'e'`. The parameter's type is fixed by the function definition and does not change with the call.
- **③ (incorrect):** Even when the return value is not used, the function is called and its body runs to the end; the return value is simply discarded. `printf` and `scanf` also have return values, but they are usually called without using them.
- **④ (correct):** When an argument is an expression, as in `square(a + 1)`, the expression is evaluated first and its value is passed.
- **⑤ (correct):** When an argument is a function call, as in `printf("%d\n", factorial(5));`, the inner function is called first and its return value is used as the argument of the outer function. `GetDaysOfMonth(isLeapYear(year), month)` in [Exercise 3](#exercise-3-number-of-days-in-a-month) works the same way.
- **⑥ (correct):** When the type of the `return` expression differs from the return type, the value is converted to the return type. `return 3.7;` in an `int` function returns 3 ([Chapter 6, Section 2.2](Concepts_Lecture.md#22-return-type)).
- **⑦ (correct):** The numbers of arguments and parameters must be equal, and a mismatch causes a compile error (option ⑤ of Exercise 6).
- **⑧ (incorrect):** Arguments correspond to parameters by position, the first argument to the first parameter and the second to the second, so the order must be the same. Swapping two arguments of the same type still compiles but passes different values and changes the result.

---

<br>

## Exercise 10: Local and Global Variables

**Textbook Problem:** Chapter 6 exercise 7

**Problem:** Of ten statements about local and global variables, choose all the incorrect ones. The options are in [Exercise 10](Exercises.md#exercise-10-local-and-global-variables).

### Solution

**Answer:** ②, ⑤, ⑧

**Explanation:** A local variable can be used only inside the block where it is declared and is destroyed when the block is left, while a global variable can be used from its declaration to the end of the source file and exists while the program runs ([Chapter 6, Section 3.1](Concepts_Lecture.md#31-local-variables), [Section 3.2](Concepts_Lecture.md#32-global-variables)).

- **① (correct):** A local variable is a variable declared inside a function body or a statement's block `{}`, such as that of `if` or `for`.
- **② (incorrect):** The scope of a local variable is limited to the block where it is declared, so local variables with the same name in different functions do not conflict. `funcA()` and `funcB()` in [Chapter 6, Section 3.1](Concepts_Lecture.md#31-local-variables) each declare `x`, and the two `x` are independent variables.
- **③ (correct):** A local variable is visible only inside the function where it is declared, so other functions cannot access it by that name. To pass a value to another function, use arguments or return values.
- **④ (correct):** A parameter is a local variable created when the function is called.
- **⑤ (incorrect):** A variable declared inside a block is destroyed when the block is left, so it cannot be used outside the block. Printing `temp`, declared inside the `for` block of [Chapter 6, Section 3.1](Concepts_Lecture.md#31-local-variables), outside the block causes a compile error.
- **⑥ (correct):** A function's local variables are created anew each time the function is called and destroyed when it returns, so creation and destruction repeat as many times as the function is called.
- **⑦ (correct):** A global variable is a variable declared outside all functions ([Chapter 6, Section 3.2](Concepts_Lecture.md#32-global-variables)).
- **⑧ (incorrect):** The scope of a global variable runs from its declaration to the end of the source file, so functions that come before the declaration cannot use it. To use it throughout the source file, declare it at the top of the file.
- **⑨ (correct):** If there is a local variable with the same name, the local variable takes precedence within its scope and hides the global variable (shadowing). C has no operator like C++'s `::`, so the global variable cannot be accessed by that name within that scope ([Chapter 6, Section 3.3](Concepts_Lecture.md#33-scope-rules)).
- **⑩ (correct):** The lifetime of a global variable is the whole execution of the program. It is created when the program starts, initialized to 0 if no initial value is given, and destroyed when the program ends ([Chapter 6, Section 3.2](Concepts_Lecture.md#32-global-variables)).

---

<br>

## Exercise 11: Prototype of a Function That Computes the Perimeter of a Rectangle

**Textbook Problem:** Chapter 6 exercise 8

**Problem:** Write the prototype of a function that takes the integer width and height as parameters and computes the integer perimeter of a rectangle. The full problem is in [Exercise 11](Exercises.md#exercise-11-prototype-of-a-function-that-computes-the-perimeter-of-a-rectangle).

### Solution

**Answer:** `int get_perimeter(int width, int height);`

**Explanation:** A prototype gives the return type, function name, and parameter list and ends with a semicolon ([Chapter 6, Section 2.6](Concepts_Lecture.md#26-function-declaration-prototype)).

- **Return type:** The perimeter is an integer, so it is `int`.
- **Function name:** Named with a verb and a noun that describe what the function does. The name can be chosen freely, so `getPerimeter` would also do ([Chapter 6, Section 2.3](Concepts_Lecture.md#23-function-name)).
- **Parameters:** The width and height are integers, so each parameter gets its own type, as in `int width`, `int height`. In a prototype the names may be omitted, as in `int get_perimeter(int, int);`.

The function with this prototype is defined and used in [Exercise 19](#exercise-19-perimeter-of-a-rectangle).

---

<br>

## Exercise 12: Prototype of a Function That Checks for an English Letter

**Textbook Problem:** Chapter 6 exercise 9

**Problem:** Write the prototype of a function that takes a character as a parameter and checks whether it is an English letter. The full problem is in [Exercise 12](Exercises.md#exercise-12-prototype-of-a-function-that-checks-for-an-english-letter).

### Solution

**Answer:** `int is_alphabet(char ch);`

**Explanation:** The result of the check is true or false, so it is returned as the integer 1 or 0 ([Chapter 6, Section 2.6](Concepts_Lecture.md#26-function-declaration-prototype)).

- **Return type:** The function returns 1 for an English letter and 0 otherwise, so it is `int`. A C condition is true when it is not 0, so the return value can be used directly as a condition, as in `if (is_alphabet(ch))`.
- **Function name:** Giving a function that returns true or false a name starting with `is_` makes the meaning of its return value clear.
- **Parameter:** It takes one character, so it is `char ch`.

The function can be defined, for example, as follows. The standard library's `<ctype.h>` also has `int isalpha(int c);`, which does the same job.

```c
int is_alphabet(char ch)
{
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}
```

---

<br>

## Exercise 13: Prototype of a Function That Computes a Discounted Price

**Textbook Problem:** Chapter 6 exercise 10

**Problem:** Write the prototype of a function that takes the price of a product and the discount rate as parameters and computes the discounted price. The full problem is in [Exercise 13](Exercises.md#exercise-13-prototype-of-a-function-that-computes-a-discounted-price).

### Solution

**Answer:** `int computeDiscount(int price, int rate);`

**Explanation:** The function takes a price and a discount rate and returns one discounted price ([Chapter 6, Section 2.6](Concepts_Lecture.md#26-function-declaration-prototype)).

- **Return type:** The discounted price is returned as an integer number of won, so it is `int`.
- **Parameters:** It takes the product price `price` and the discount rate `rate`. The rate is taken as an integer percentage, such as 20 for 20%.
- **Another form:** If the price or rate can have fractions, `double` can be used, as in `double computeDiscount(double price, double rate);`.

The function with this prototype is defined and used in [Exercise 21](#exercise-21-computing-discounted-prices).

---

<br>

## Exercise 14: Prototype of a Function That Computes the Greatest Common Divisor

**Textbook Problem:** Chapter 6 exercise 11

**Problem:** Write the prototype of a function that takes two integers as parameters and computes their greatest common divisor. The full problem is in [Exercise 14](Exercises.md#exercise-14-prototype-of-a-function-that-computes-the-greatest-common-divisor).

### Solution

**Answer:** `int get_gcd(int x, int y);`

**Explanation:** The greatest common divisor of two integers is also an integer ([Chapter 6, Section 2.6](Concepts_Lecture.md#26-function-declaration-prototype)).

- **Return type:** The greatest common divisor is an integer, so it is `int`.
- **Parameters:** It takes two integers, so each parameter gets its own type, as in `int x, int y`. Sharing the type as in a variable declaration, `int get_gcd(int x, y);`, causes a compile error ([Chapter 6, Section 2.4](Concepts_Lecture.md#24-parameters-and-arguments)).

The function can be defined, for example, with the Euclidean algorithm as follows. `get_gcd(12, 18)` returns 6.

```c
int get_gcd(int x, int y)
{
    while (y != 0) {   // gcd(x, y) = gcd(y, x % y)
        int r = x % y;
        x = y;
        y = r;
    }
    return x;
}
```

---

<br>

## Exercise 15: Turning the Arithmetic Code into a Function

**Textbook Problem:** Chapter 6 exercise 12

**Problem:** In the code that reads an expression and prints the result of the arithmetic operation, define the whole `switch` statement as a function and change the code to call that function. Choose the function's return type, name, and parameters yourself. The full problem and code are in [Exercise 15](Exercises.md#exercise-15-turning-the-arithmetic-code-into-a-function).

### Solution

**Answer:** Move the `switch` statement into the body of `void print_result(int x, char op, int y)` and call it as `print_result(x, op, y);` in its place in `main()`. Since the form of the function is up to the writer, the name and the order of the parameters may differ.

**Explanation:** The form of the function follows from the values the `switch` statement uses and the result it produces.

- **Parameters:** The values the `switch` statement uses are the local variables `x`, `op`, and `y` of `main()`. Local variables cannot be used in another function, so the three values must be received as parameters ([Chapter 6, Section 3.1](Concepts_Lecture.md#31-local-variables)). Choosing `int x, char op, int y` in the order of the expression makes the call `print_result(x, op, y)` follow the order of the input.
- **Return type:** The `switch` statement only prints the result and has no value to return to the caller, so it is `void`.
- **Names:** Even if the parameters have the same names as the local variables of `main()`, they do not conflict, because they are local variables of different functions.
- **`return`:** The textbook's `main()` has no `return` statement, but from C99, reaching the closing `}` of `main()` is treated as returning 0. The solution code states `return 0;` explicitly.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

// Prints the result of the expression x op y
void print_result(int x, char op, int y)
{
    switch (op) {
    case '+': printf("%d + %d = %d\n", x, y, x + y); break;
    case '-': printf("%d - %d = %d\n", x, y, x - y); break;
    case '*': printf("%d * %d = %d\n", x, y, x * y); break;
    case '/': printf("%d / %d = %d\n", x, y, x / y); break;
    default:  printf("잘못된 수식입니다.\n");         break;
    }
}

int main(void)
{
    int x, y;  // operands
    char op;   // operator symbol stored as a character

    printf("수식 ? ");
    scanf("%d %c %d", &x, &op, &y);  // reads input such as 10 + 30

    print_result(x, op, y);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings. The problem has no sample run, so the results are shown for `10 + 30`, in the input form of the comment, for an integer division, and for the unsupported operator `%`, in that order.

```text
수식 ? 10 + 30
10 + 30 = 40
```

```text
수식 ? 100 / 7
100 / 7 = 14
```

```text
수식 ? 10 % 3
잘못된 수식입니다.
```

> **Caution:** Dividing by 0, as in `10 / 0`, makes the result of the integer division undefined, and on x86-family CPUs the program terminates abnormally. To prevent this, check whether `y` is 0 first in `case '/':`.

---

<br>

## Exercise 16: The Code Needed in the Blank

**Textbook Problem:** Chapter 6 exercise 13

**Problem:** In a program where `main()` calls `get_seconds()`, which is defined after `main()`, write the code needed in the blank between `#include <stdio.h>` and `main()`. The full problem and code are in [Exercise 16](Exercises.md#exercise-16-the-code-needed-in-the-blank).

### Solution

**Answer:** `int get_seconds(int hours, int minutes, int seconds);`

**Explanation:** `main()` calls `get_seconds()`, but the function's definition comes after `main()`. The compiler reads the source code from top to bottom, so the function's prototype must be declared before `main()` so that the return type and parameters are known at the call ([Chapter 6, Section 2.6](Concepts_Lecture.md#26-function-declaration-prototype)).

- **Contents of the prototype:** The header of the definition, `int get_seconds(int hours, int minutes, int seconds)`, followed by a semicolon. It may also be written without parameter names as `int get_seconds(int, int, int);`.
- **Another way:** Instead of a prototype, the whole definition of `get_seconds()` may be moved before `main()`, because no declaration is needed when the definition comes before the call.
- **Without the prototype:** From C99, the implicit declaration that allowed calling a function without a declaration was removed from the standard. Saving the code with the blank left empty as `seconds.c` and compiling it with clang gives the following error.

```text
seconds.c:9:62: error: call to undeclared function 'get_seconds'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
```

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int get_seconds(int hours, int minutes, int seconds);  // prototype

int main(void)
{
    int hour, min, sec;

    printf("시간 분 초? ");
    scanf("%d %d %d", &hour, &min, &sec);
    printf("%d시간 %d분 %d초 = %d초\n", hour, min, sec, get_seconds(hour, min, sec));

    return 0;
}

int get_seconds(int hours, int minutes, int seconds)
{
    int result = 0;

    result += (hours * 60 * 60);
    result += (minutes * 60);
    result += seconds;
    return result;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings. The problem has no sample run, so the result for 1 hour 30 minutes 15 seconds is shown. 1 × 3600 + 30 × 60 + 15 = 5415 seconds.

```text
시간 분 초? 1 30 15
1시간 30분 15초 = 5415초
```

---

<br>

## Exercise 17: Output of a Program with Variables of the Same Name

**Textbook Problem:** Chapter 6 exercise 14

**Problem:** Write the output of a program in which a global variable, a local variable of `main()`, and a local variable of the `for` block all use the name `data`. The full problem and code are in [Exercise 17](Exercises.md#exercise-17-output-of-a-program-with-variables-of-the-same-name).

### Solution

**Answer:** `data = 10`

**Explanation:** The program has three variables named `data`, and when the same name exists in several scopes, the variable of the innermost scope takes precedence ([Chapter 6, Section 3.3](Concepts_Lecture.md#33-scope-rules)).

| Variable | Where declared | Initial value | Where the name refers to it |
|:----|:----|:----|:----|
| Global `data` | Outside all functions | 100 | Outside `main()` |
| `data` of `main()` | Body of `main()` | 10 | Inside `main()` except the `for` body |
| `data` of the `for` body | Body block of `for` | 1 | Inside the body block of `for` |

*Table 1. The three `data` variables of Exercise 17*

- **Loop condition:** The condition `i < data` of the `for` is outside the body block, so the `data` declared in the body is not visible there, and it compares with the `data` of `main()` (10).
- **Body:** In each iteration a new `data` is created in the body with 1 and becomes 4 by `data += 3`. 4 > 10 is false, so `break` is not executed, and this `data` is destroyed when the body ends ([Chapter 6, Section 3.1](Concepts_Lecture.md#31-local-variables)).
- **Number of iterations:** The loop runs ten times with `i` from 0 to 9, and then `i < data` becomes false and the loop ends. The body changed only its own `data`, so the `data` of `main()` stays 10.
- **Output:** The `data` in `printf` is the local variable of `main()`, so `data = 10` is printed. The global `data` (100) is hidden inside `main()` and never used.

**Output:** Compiling the problem's code with `gcc -std=c99 -Wall` and running it gives the same result without warnings.

```text
data = 10
```

---

<br>

## Exercise 18: Printing Multiples of an Integer

**Textbook Problem:** Chapter 6 programming assignment 1

**Problem:** Write a function that takes an integer and a number of multiples as parameters and prints the multiples, and use it to print 20 multiples of each integer read. The program ends when an integer of 0 or less is entered. The full problem and sample run are in [Exercise 18](Exercises.md#exercise-18-printing-multiples-of-an-integer).

### Solution

**Approach:** The function only prints the result and has no value to return to the caller, so it is written with the return type `void` and parameters only ([Chapter 6, Section 2.2](Concepts_Lecture.md#22-return-type)).

- **`print_multiples()`:** Increases `i` from 1 to `count` and prints `num * i`. It prints a space before a value only when the value is not the first, so spaces appear only between values, and it ends the line at the end.
- **`main()`:** Reads an integer inside `while (1)` and ends the loop with `break` when the return value of `scanf` is not 1 (input that is not a number) or the integer is 0 or less. Otherwise it calls `print_multiples(num, 20)`. Because the number of multiples is passed as an argument, the function can be used for other counts without change.
- **Prototype:** The prototype is declared before `main()` and the definition placed after `main()` ([Chapter 6, Section 2.6](Concepts_Lecture.md#26-function-declaration-prototype)).

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

void print_multiples(int num, int count);

int main(void)
{
    int num;

    while (1) {
        printf("정수? ");
        if (scanf("%d", &num) != 1 || num <= 0)  // stop on 0, a negative number, or invalid input
            break;
        print_multiples(num, 20);
    }

    return 0;
}

// Prints the first count multiples of num on one line, separated by spaces
void print_multiples(int num, int count)
{
    int i;

    for (i = 1; i <= count; i++) {
        if (i > 1)
            printf(" ");
        printf("%d", num * i);
    }
    printf("\n");
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings and gives the same result as the sample run.

```text
정수? 3
3 6 9 12 15 18 21 24 27 30 33 36 39 42 45 48 51 54 57 60
정수? 11
11 22 33 44 55 66 77 88 99 110 121 132 143 154 165 176 187 198 209 220
정수? 0
```

> **Caution:** The multiples are computed as `int`, so entering an integer of 107374183 or more, for which `num * 20` exceeds the maximum `int` value 2147483647, causes overflow, and overflow of a signed integer is undefined behavior. To handle larger numbers, compute in `long long`, as in `(long long)num * i`, and print with `%lld`.

---

<br>

## Exercise 19: Perimeter of a Rectangle

**Textbook Problem:** Chapter 6 programming assignment 2

**Problem:** Write a function that takes the width and height as parameters and returns the perimeter of a rectangle, and use it to compute the perimeter for the width and height read. The full problem and sample run are in [Exercise 19](Exercises.md#exercise-19-perimeter-of-a-rectangle).

### Solution

**Approach:** The perimeter of a rectangle is 2 × (width + height). The function uses the prototype `int get_perimeter(int width, int height);` of [Exercise 11](#exercise-11-prototype-of-a-function-that-computes-the-perimeter-of-a-rectangle).

- **`get_perimeter()`:** Returns `2 * (width + height)`. Without the parentheses, `*` would be computed before `+`, so the parentheses make the addition come first.
- **`main()`:** Reads the width and height in turn and uses the return value of `get_perimeter(width, height)` directly as an argument of `printf` without storing it in a variable ([Chapter 6, Section 2.5](Concepts_Lecture.md#25-function-call)).

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int get_perimeter(int width, int height);

int main(void)
{
    int width, height;

    printf("가로? ");
    scanf("%d", &width);
    printf("세로? ");
    scanf("%d", &height);

    printf("직사각형의 둘레: %d\n", get_perimeter(width, height));

    return 0;
}

// Returns the perimeter of a width x height rectangle
int get_perimeter(int width, int height)
{
    return 2 * (width + height);
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings and gives the same result as the sample run.

```text
가로? 100
세로? 200
직사각형의 둘레: 600
```

---

<br>

## Exercise 20: Distance Between Two Points

**Textbook Problem:** Chapter 6 programming assignment 3

**Problem:** Write a function that takes the x and y coordinates of two points as parameters and returns the straight-line distance between them, and use it to compute the distance between the start and end points read. The full problem and sample run are in [Exercise 20](Exercises.md#exercise-20-distance-between-two-points).

### Solution

**Approach:** The distance between two points $(x_1, y_1)$ and $(x_2, y_2)$ is $\sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2}$. The square root is computed with the library function `sqrt()` declared in `<math.h>` ([Chapter 6, Section 1.2](Concepts_Lecture.md#12-function-types)).

- **`get_distance()`:** Takes the four coordinates as parameters. It stores the two coordinate differences in the `double` variables `dx` and `dy` and returns `sqrt(dx * dx + dy * dy)`. Because the differences are converted to `double` before squaring, no `int` multiplication overflow occurs even for large differences.
- **`main()`:** Reads the coordinates of the start and end points two at a time with `"%d %d"` and prints the result with `%f`, to six digits after the decimal point.
- **Linking:** With gcc on Linux, the `-lm` option must be added to link the math library, as in `gcc -std=c99 -Wall distance.c -lm`. It is not needed on macOS or in Visual Studio.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>
#include <math.h>   // sqrt

double get_distance(int x1, int y1, int x2, int y2);

int main(void)
{
    int x1, y1, x2, y2;

    printf("직선의 시작점 좌표? ");
    scanf("%d %d", &x1, &y1);
    printf("직선의 끝점 좌표? ");
    scanf("%d %d", &x2, &y2);

    printf("(%d, %d)~(%d, %d) 직선의 길이: %f\n",
           x1, y1, x2, y2, get_distance(x1, y1, x2, y2));

    return 0;
}

// Returns the straight-line distance between (x1, y1) and (x2, y2)
double get_distance(int x1, int y1, int x2, int y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;

    return sqrt(dx * dx + dy * dy);
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings and gives the same result as the sample run. The distance between (0, 0) and (3, 4) is $\sqrt{9 + 16} = 5$.

```text
직선의 시작점 좌표? 0 0
직선의 끝점 좌표? 3 4
(0, 0)~(3, 4) 직선의 길이: 5.000000
```

---

<br>

## Exercise 21: Computing Discounted Prices

**Textbook Problem:** Chapter 6 programming assignment 4

**Problem:** Write a function that takes a price and a discount rate as parameters and returns the discounted price, and use it to read the discount rate first and then print the discounted price for each price read. The program ends when 0 is entered as the price. The full problem and sample run are in [Exercise 21](Exercises.md#exercise-21-computing-discounted-prices).

### Solution

**Approach:** The discounted price is price × (100 - rate) / 100. The function uses the prototype `int computeDiscount(int price, int rate);` of [Exercise 13](#exercise-13-prototype-of-a-function-that-computes-a-discounted-price).

- **`computeDiscount()`:** Returns `price * (100 - rate) / 100`. `*` and `/` have the same precedence and associate from the left, so the multiplication is done first and then the division ([Chapter 4, Section 10.2](../Ch04_Operators/Concepts_Lecture.md#102-associativity)). Writing `price * ((100 - rate) / 100)` would make the integer division `80 / 100` equal 0, so the discounted price would always be 0.
- **`main()`:** Reads the discount rate once, then reads prices inside `while (1)` and ends the loop on 0 or input that is not a number. The `%` of the prompt is written as `%%` in the format string.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int computeDiscount(int price, int rate);

int main(void)
{
    int rate, price;

    printf("할인율(%%)? ");
    scanf("%d", &rate);

    while (1) {
        printf("제품의 가격? ");
        if (scanf("%d", &price) != 1 || price == 0)  // stop on 0 or invalid input
            break;
        printf("할인가: %d원\n", computeDiscount(price, rate));
    }

    return 0;
}

// Returns the price after a discount of rate percent (fractions of a won are dropped)
int computeDiscount(int price, int rate)
{
    return price * (100 - rate) / 100;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings and gives the same result as the sample run.

```text
할인율(%)? 20
제품의 가격? 10000
할인가: 8000원
제품의 가격? 5000
할인가: 4000원
제품의 가격? 0
```

> **Caution:** Because of integer division, amounts below one won are dropped. A 15% discount on 999 won is 849.15 won, but 849 won is printed. Also, `price * (100 - rate)` is computed as `int`, so overflow occurs when the product exceeds 2147483647, for example for a price of 21474837 won or more with a discount rate of 0.

```text
할인율(%)? 15
제품의 가격? 999
할인가: 849원
제품의 가격? 0
```

---

<br>

## Exercise 22: Printing a Menu

**Textbook Problem:** Chapter 6 programming assignment 5

**Problem:** Write a menu-printing function with no return value and no parameters, and use it to print the menu, read a menu number, and show the selected menu. Selecting 0 ends the program. The full problem and sample run are in [Exercise 22](Exercises.md#exercise-22-printing-a-menu).

### Solution

**Approach:** Printing the menu needs no input value and returns none, so the function is written in the form `void print_menu(void)` ([Chapter 6, Section 2.4](Concepts_Lecture.md#24-parameters-and-arguments)). The structure of printing the menu inside a loop and handling the selection with `switch` is the same as the menu-driven program of [Chapter 5, Section 5.4](../Ch05_Control-Statements/Concepts_Lecture.md#54-menu-driven-program).

- **`print_menu()`:** Prints the menu and `선택? ` on one line without ending the line, so the user's input continues on the same line.
- **`main()`:** Calls `print_menu()` inside `while (1)` and reads a number. It ends the loop on 0 or input that is not a number; otherwise it prints the message for 1, 2, or 3 with `switch` and an error message in `default` for other numbers.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

void print_menu(void);

int main(void)
{
    int menu;

    while (1) {
        print_menu();
        if (scanf("%d", &menu) != 1 || menu == 0)  // 0 or invalid input ends the program
            break;

        switch (menu) {
        case 1: printf("파일 열기를 수행합니다.\n"); break;
        case 2: printf("파일 저장을 수행합니다.\n"); break;
        case 3: printf("인쇄를 수행합니다.\n");     break;
        default: printf("잘못 선택하셨습니다.\n");   break;
        }
    }

    return 0;
}

// Prints the menu line and the selection prompt
void print_menu(void)
{
    printf("[1.파일 열기  2.파일 저장  3.인쇄  0.종료] 선택? ");
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings and gives the same result as the sample run.

```text
[1.파일 열기  2.파일 저장  3.인쇄  0.종료] 선택? 1
파일 열기를 수행합니다.
[1.파일 열기  2.파일 저장  3.인쇄  0.종료] 선택? 2
파일 저장을 수행합니다.
[1.파일 열기  2.파일 저장  3.인쇄  0.종료] 선택? 0
```

Entering 3, which the sample run does not show, and 7, which is not on the menu, gives the following.

```text
[1.파일 열기  2.파일 저장  3.인쇄  0.종료] 선택? 3
인쇄를 수행합니다.
[1.파일 열기  2.파일 저장  3.인쇄  0.종료] 선택? 7
잘못 선택하셨습니다.
[1.파일 열기  2.파일 저장  3.인쇄  0.종료] 선택? 0
```

---

<br>

## Exercise 23: The Red, Green, and Blue Values of an RGB Color

**Textbook Problem:** Chapter 6 programming assignment 6

**Problem:** Define three functions that each obtain the red, green, or blue value of an RGB color, and use them to print in decimal the three values of an RGB color read in hexadecimal. The full problem and sample run are in [Exercise 23](Exercises.md#exercise-23-the-red-green-and-blue-values-of-an-rgb-color).

### Solution

**Approach:** Move the desired channel into the low 8 bits with a right shift and clear the other bits with `& 0xFF` ([Chapter 4, Section 6.3](../Ch04_Operators/Concepts_Lecture.md#63-practical-example-rgb-color)). [Chapter 4, Exercise 4](../Ch04_Operators/Solutions.md#exercise-4-convert-a-hexadecimal-rgb-value-to-red-green-and-blue-values) performs the same extraction without functions; this problem differs in defining one function per channel. The `0xFF0080` of the sample run is laid out as follows.

| Bits | 24-31 | 16-23 | 8-15 | 0-7 |
|:---:|:---:|:---:|:---:|:---:|
| Channel | Not used | blue | green | red |
| Hexadecimal | `00` | `FF` | `00` | `80` |
| Decimal | 0 | 255 | 0 | 128 |

*Table 2. Bit layout of `0xFF0080` and the value of each channel*

- **`get_red()`:** red is in bits 0-7, so `rgb & 0xFF` keeps only the low 8 bits.
- **`get_green()`:** `(rgb >> 8) & 0xFF` moves bits 8-15 down and takes them out.
- **`get_blue()`:** `(rgb >> 16) & 0xFF` takes out bits 16-23. Because of the mask, bits 24 and above do not get mixed in even when a hexadecimal number of seven or more digits is entered.
- **Parameter type:** The `%x` of `scanf` expects an `unsigned int *`, so `rgb` is declared `unsigned int`, and the three functions take parameters of the same type. A right shift of an unsigned integer always fills the vacated bits with 0 ([Chapter 4, Section 6.2](../Ch04_Operators/Concepts_Lecture.md#62-shift-operators)).
- **Input and output:** `%x` also reads input with the `0x` prefix. `%06X` prints uppercase hexadecimal padded to six digits with leading zeros.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int get_red(unsigned int rgb);
int get_green(unsigned int rgb);
int get_blue(unsigned int rgb);

int main(void)
{
    unsigned int rgb;

    printf("RGB 색상? ");
    scanf("%x", &rgb);   // %x also accepts the 0x prefix

    printf("RGB %06X의 red: %d, green: %d, blue: %d\n",
           rgb, get_red(rgb), get_green(rgb), get_blue(rgb));

    return 0;
}

// red is stored in bits 0-7
int get_red(unsigned int rgb)
{
    return rgb & 0xFF;
}

// green is stored in bits 8-15
int get_green(unsigned int rgb)
{
    return (rgb >> 8) & 0xFF;
}

// blue is stored in bits 16-23
int get_blue(unsigned int rgb)
{
    return (rgb >> 16) & 0xFF;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings and gives the same result as the sample run.

```text
RGB 색상? 0xff0080
RGB FF0080의 red: 128, green: 0, blue: 255
```

Entering `0xff` prints `0000FF`, because `%06X` pads the leading digits with zeros. With `%X` only `FF` would be printed.

```text
RGB 색상? 0xff
RGB 0000FF의 red: 255, green: 0, blue: 0
```

---

<br>

## Exercise 24: Leap Years from 2000 to 2100

**Textbook Problem:** Chapter 6 programming assignment 7

**Problem:** Write a function that takes a year as a parameter and determines whether it is a leap year, and use it to print all leap years from 2000 to 2100, ten per line. The full problem and sample run are in [Exercise 24](Exercises.md#exercise-24-leap-years-from-2000-to-2100).

### Solution

**Approach:** The leap-year condition is the same as in [Exercise 2](#exercise-2-leap-year-test), but the range ends at 2100 and only the years are printed, without a title line. A year is a leap year if it is divisible by 4 and not by 100, or if it is divisible by 400.

- **`is_leap_year()`:** Writes the leap-year condition as one expression, `(year % 4 == 0 && year % 100 != 0) || year % 400 == 0`, and returns its value. The result of relational and logical operations is 1 or 0, so it returns 1 for a leap year and 0 for a common year ([Chapter 4, Section 4.2](../Ch04_Operators/Concepts_Lecture.md#42-result-type)).
- **`main()`:** Increases `year` from 2000 to 2100, prints only the leap years, and adds 1 to `count`. It prints a space before a year only when the year is not the first on its line, and ends the line when `count` becomes a multiple of 10. After the loop, if the last line has fewer than ten years, it ends that line to finish the output.
- **Checking the result:** 2000 is divisible by 400, so it is a leap year, and 2100 is divisible by 100 but not by 400, so it is a common year. Of the 26 multiples of 4 from 2000 to 2100, excluding 2100 leaves 25 leap years, so two lines of ten and a last line of five are printed.

**Code:**

```c
#include <stdio.h>

int is_leap_year(int year);

int main(void)
{
    int year, count = 0;

    for (year = 2000; year <= 2100; year++) {
        if (is_leap_year(year)) {
            if (count % 10 != 0)
                printf(" ");      // separator between years on the same line
            printf("%d", year);
            count++;
            if (count % 10 == 0)
                printf("\n");     // 10 years per line
        }
    }
    if (count % 10 != 0)
        printf("\n");             // end the last, shorter line

    return 0;
}

// Returns 1 if year is a leap year and 0 otherwise
int is_leap_year(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings and gives the same result as the sample run. Spaces are printed only between years, so no space is left at the end of a line.

```text
2000 2004 2008 2012 2016 2020 2024 2028 2032 2036
2040 2044 2048 2052 2056 2060 2064 2068 2072 2076
2080 2084 2088 2092 2096
```

---

<br>

## Exercise 25: Checking for a Valid Date

**Textbook Problem:** Chapter 6 programming assignment 8

**Problem:** Write a function that takes a year, month, and day as parameters and returns 1 for a valid date and 0 otherwise, and use it to read the date again until a valid date is entered. The full problem and sample run are in [Exercise 25](Exercises.md#exercise-25-checking-for-a-valid-date).

### Solution

**Approach:** First check that the month is from 1 to 12, then check that the day is from 1 to the number of days of that month. The number of days of the month is found the same way as `GetDaysOfMonth()` in [Exercise 3](#exercise-3-number-of-days-in-a-month), but, as in the example of [Chapter 6, Section 2.5](Concepts_Lecture.md#25-function-call), the function takes the year and determines the leap year inside.

- **`is_leap_year()`:** The same function as in [Exercise 24](#exercise-24-leap-years-from-2000-to-2100).
- **`get_days_of_month()`:** Returns 29 or 28 for February depending on `is_leap_year(year)`, 30 for April, June, September, and November, and 31 for the other months. A month outside 1-12 also gets 31 through `default`, so the month must be checked before this function is called.
- **`is_valid_date()`:** Returns 0 if the year is less than 1 or the month is outside 1-12, and then returns 0 if the day is less than 1 or greater than the number of days of the month. If both checks pass, it returns 1. The problem does not set a range for the year, so the solution code treats any year of 1 or more as valid.
- **`main()`:** Reads a date inside `while (1)` and ends the loop with `break` when `is_valid_date()` returns 1. When it returns 0, the program prints an error message and reads again. After the loop it prints the date entered ([Chapter 5, Section 5.3](../Ch05_Control-Statements/Concepts_Lecture.md#53-input-validation-loop)).

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int is_leap_year(int year);
int get_days_of_month(int year, int month);
int is_valid_date(int year, int month, int day);

int main(void)
{
    int year, month, day;

    while (1) {
        printf("날짜 (연 월 일)? ");
        scanf("%d %d %d", &year, &month, &day);
        if (is_valid_date(year, month, day))
            break;
        printf("잘못 입력하셨습니다. 유효한 날짜를 입력하세요.\n");
    }
    printf("입력한 날짜는 %d년 %d월 %d일입니다.\n", year, month, day);

    return 0;
}

// Returns 1 if year is a leap year and 0 otherwise
int is_leap_year(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

// Returns the number of days in the given month (month must be 1-12)
int get_days_of_month(int year, int month)
{
    switch (month) {
    case 2:
        return is_leap_year(year) ? 29 : 28;
    case 4: case 6: case 9: case 11:
        return 30;
    default:
        return 31;
    }
}

// Returns 1 if year/month/day is a valid date and 0 otherwise
int is_valid_date(int year, int month, int day)
{
    if (year < 1 || month < 1 || month > 12)
        return 0;
    if (day < 1 || day > get_days_of_month(year, month))
        return 0;
    return 1;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings and gives the same result as the sample run. Month 13 fails the month check, and June 31 fails the day check because it exceeds June's 30 days.

```text
날짜 (연 월 일)? 2022 13 1
잘못 입력하셨습니다. 유효한 날짜를 입력하세요.
날짜 (연 월 일)? 2022 6 31
잘못 입력하셨습니다. 유효한 날짜를 입력하세요.
날짜 (연 월 일)? 2022 5 1
입력한 날짜는 2022년 5월 1일입니다.
```

February 29 is valid only in a leap year. 2023 and 2100 are common years, and 2024 is a leap year.

```text
날짜 (연 월 일)? 2023 2 29
잘못 입력하셨습니다. 유효한 날짜를 입력하세요.
날짜 (연 월 일)? 2100 2 29
잘못 입력하셨습니다. 유효한 날짜를 입력하세요.
날짜 (연 월 일)? 2024 2 29
입력한 날짜는 2024년 2월 29일입니다.
```

> **Caution:** If a value that is not a number is entered, `scanf` leaves that character unread in the input buffer, so the `scanf` of the next iteration fails at the same place and the error message repeats without end. To handle this case as well, check whether the return value of `scanf` is 3 and, if not, discard the rest of the line with `getchar()` before reading again.

---

<br>

## Exercise 26: Printing an Integer in Binary

**Textbook Problem:** Chapter 6 programming assignment 9

**Problem:** Write a function that takes an integer as a parameter and prints it in binary, and use it to print in binary an integer read in hexadecimal. The full problem and sample run are in [Exercise 26](Exercises.md#exercise-26-printing-an-integer-in-binary).

### Solution

**Approach:** Starting from the most significant bit, take out one bit at a time with a right shift and `& 1` and print it ([Chapter 4, Section 6.2](../Ch04_Operators/Concepts_Lecture.md#62-shift-operators)). One hexadecimal digit corresponds to four binary digits, so inserting a space every 4 bits makes each hexadecimal digit one group ([Chapter 3, Section 2.1](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#21-number-systems)). For example, `A` is `1010`, `B` is `1011`, and `4` is `0100`.

- **`print_binary()`:** Decreases `i` from 31 to 0, takes out bit `i` with `(num >> i) & 1`, and prints it. When `i` is a multiple of 4 and not 0, it prints a space after that bit, so the 32 bits are divided into eight groups of 4 bits. Its purpose is output, so the return type is `void`.
- **Parameter type:** The `%x` of `scanf` expects an `unsigned int *`, and the result of right-shifting a negative number can differ between implementations, so `unsigned int` is used. In Visual Studio and gcc, `unsigned int` is 32 bits.
- **`main()`:** Reads `0xabcd1234` with `%x`, prints the uppercase hexadecimal `ABCD1234` with `%X`, and calls `print_binary()`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

void print_binary(unsigned int num);

int main(void)
{
    unsigned int num;

    printf("정수? ");
    scanf("%x", &num);   // %x also accepts the 0x prefix

    printf("16진수 %X: ", num);
    print_binary(num);

    return 0;
}

// Prints the 32 bits of num from the most significant bit, in groups of 4
void print_binary(unsigned int num)
{
    int i;

    for (i = 31; i >= 0; i--) {
        printf("%u", (num >> i) & 1);
        if (i % 4 == 0 && i != 0)
            printf(" ");
    }
    printf("\n");
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings and gives the same result as the sample run.

```text
정수? 0xabcd1234
16진수 ABCD1234: 1010 1011 1100 1101 0001 0010 0011 0100
```

Entering a small value prints all 32 bits with leading zeros. `%x` also reads `1f`, entered without `0x`, as hexadecimal.

```text
정수? 1f
16진수 1F: 0000 0000 0000 0000 0000 0000 0001 1111
```

---

<br>

## Exercise 27: Divisors and the Number of Divisors

**Textbook Problem:** Chapter 6 programming assignment 10

**Problem:** Write a function that takes an integer as a parameter and prints its divisors and the number of divisors, and use it to print the divisors of each integer read. The program ends when 0 is entered. The full problem and sample run are in [Exercise 27](Exercises.md#exercise-27-divisors-and-the-number-of-divisors).

### Solution

**Approach:** Divide by each integer from 1 to the number in turn, print those that leave a remainder of 0, and count them. The function prints both the divisors and the count, so the return type is `void`.

- **`print_divisors()`:** First prints `"%d의 약수: "`, then increases `i` from 1 to `num`, printing each `i` with `num % i == 0` as `"%d "` and adding 1 to `count`. Each divisor is followed by a space, so one space appears between the last divisor and `=>`, and then `"=> 총 %d개\n"` is printed.
- **`main()`:** Reads an integer inside `while (1)` and ends the loop on 0 or input that is not a number. The problem does not say how to handle negative numbers, so the solution code prints a notice for a negative number and reads again with `continue` ([Chapter 5, Section 4.2](../Ch05_Control-Statements/Concepts_Lecture.md#42-continue)).

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

void print_divisors(int num);

int main(void)
{
    int num;

    while (1) {
        printf("양의 정수? ");
        if (scanf("%d", &num) != 1 || num == 0)  // stop on 0 or invalid input
            break;
        if (num < 0) {
            printf("양의 정수를 입력하세요.\n");
            continue;
        }
        print_divisors(num);
    }

    return 0;
}

// Prints all divisors of num and the number of divisors
void print_divisors(int num)
{
    int i, count = 0;

    printf("%d의 약수: ", num);
    for (i = 1; i <= num; i++) {
        if (num % i == 0) {
            printf("%d ", i);
            count++;
        }
    }
    printf("=> 총 %d개\n", count);
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings and gives the same result as the sample run.

```text
양의 정수? 100
100의 약수: 1 2 4 5 10 20 25 50 100 => 총 9개
양의 정수? 56
56의 약수: 1 2 4 7 8 14 28 56 => 총 8개
양의 정수? 0
```

Entering a negative number and 1 gives the following. The only divisor of 1 is 1.

```text
양의 정수? -12
양의 정수를 입력하세요.
양의 정수? 1
1의 약수: 1 => 총 1개
양의 정수? 0
```

---

<br>

## Exercise 28: Prime Numbers from 1 to N

**Textbook Problem:** Chapter 6 programming assignment 11

**Problem:** Define a function that takes an integer as a parameter and determines whether it is prime, and use it to print the primes from 1 to N, ten per line, for an N read. The full problem and sample run are in [Exercise 28](Exercises.md#exercise-28-prime-numbers-from-1-to-n).

### Solution

**Approach:** A prime is an integer of 2 or more whose only divisors are 1 and itself. Divide by 2, 3, and so on in turn; if some number divides it, it is not prime.

- **`is_prime()`:** A number less than 2 is not prime, so it returns 0. Otherwise it increases `i` from 2 and returns 0 when `num % i == 0`, and returns 1 if nothing divides it to the end. If `num` factors as `a` × `b` (`a` ≤ `b`), then `a` is at most √`num`, so it suffices to check until `i` exceeds √`num`. Writing the condition as `i <= num / i` instead of `i * i <= num` checks the same range without overflow of `i * i`.
- **`main()`:** Reads N, increases `i` from 1 to N, and prints each number for which `is_prime(i)` is 1 with `%3d`, right-aligned in 3 columns ([Chapter 3, Section 5.2](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#52-width-and-alignment)). It ends the line every ten numbers and ends the last line after the loop if it has fewer than ten numbers.
- **Checking the result:** There are 25 primes up to 100, so two lines of ten and a last line of five are printed.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int is_prime(int num);

int main(void)
{
    int n, i, count = 0;

    printf("1~N 사이의 소수를 구합니다. N은? ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        if (is_prime(i)) {
            printf("%3d", i);     // each prime takes 3 columns
            count++;
            if (count % 10 == 0)
                printf("\n");     // 10 primes per line
        }
    }
    if (count % 10 != 0)
        printf("\n");             // end the last, shorter line

    return 0;
}

// Returns 1 if num is a prime number and 0 otherwise
int is_prime(int num)
{
    int i;

    if (num < 2)
        return 0;
    for (i = 2; i <= num / i; i++) {   // checks divisors up to the square root of num
        if (num % i == 0)
            return 0;
    }
    return 1;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings and gives the same result as the sample run.

```text
1~N 사이의 소수를 구합니다. N은? 100
  2  3  5  7 11 13 17 19 23 29
 31 37 41 43 47 53 59 61 67 71
 73 79 83 89 97
```

---

<br>

## Exercise 29: An Accumulator

**Textbook Problem:** Chapter 6 programming assignment 12

**Problem:** Define a function that takes an operator and one operand as parameters, computes with the result of the previous operation, and prints the result, and use it to keep printing the results of the expressions read. Store the previous result in a global variable, and end the program when `0 0` is entered. The full problem and sample run are in [Exercise 29](Exercises.md#exercise-29-an-accumulator).

### Solution

**Approach:** The result of the previous operation must remain after each function call ends and must be shared by `main()` and the computing function, so it is stored in a global variable ([Chapter 6, Section 3.2](Concepts_Lecture.md#32-global-variables)). The computation for each operator is selected with `switch`, as in [Exercise 15](#exercise-15-turning-the-arithmetic-code-into-a-function).

- **Global variable `result`:** Stores the initial result 0. A global variable is initialized to 0 even without an initial value, but `= 0` is written to show the intent.
- **`accumulate()`:** Depending on the operator `op`, adds `operand` to `result`, subtracts it, multiplies by it, or divides by it. For a division by 0 or an unsupported operator, it prints a message and leaves `result` unchanged. At the end it prints the result with `"= %d "` without ending the line, so the next operator and operand are entered on the same line.
- **`main()`:** First prints the initial result 0 with `"%d "`. It then reads an operator and an operand with `" %c %d"`, where the space before `%c` skips the newline left by the previous input ([Chapter 5, Section 5.4](../Ch05_Control-Statements/Concepts_Lecture.md#54-menu-driven-program)). When `0 0` is entered, the character `'0'` arrives in the operator position, so `op == '0' && operand == 0` is checked before calling `accumulate()` to end the program. If the number of items read is not 2, the input is treated as invalid and the program ends.
- **Integer arithmetic:** The result and the operands are all `int`, so division is integer division. 110 / 10 in the sample run divides evenly and gives 11.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int result = 0;   // global variable: the result of the previous operation

void accumulate(char op, int operand);

int main(void)
{
    char op;
    int operand;

    printf("%d ", result);
    while (1) {
        if (scanf(" %c %d", &op, &operand) != 2)  // invalid input ends the program
            break;
        if (op == '0' && operand == 0)            // "0 0" ends the program
            break;
        accumulate(op, operand);
    }

    return 0;
}

// Applies op and operand to the previous result and prints the new result
void accumulate(char op, int operand)
{
    switch (op) {
    case '+': result += operand; break;
    case '-': result -= operand; break;
    case '*': result *= operand; break;
    case '/':
        if (operand == 0)
            printf("0으로 나눌 수 없습니다.\n");
        else
            result /= operand;
        break;
    default:
        printf("잘못된 연산자입니다.\n");
        break;
    }
    printf("= %d ", result);
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings and gives the same result as the sample run.

```text
0 + 22
= 22 * 5
= 110 / 10
= 11 - 5
= 6 0 0
```

Entering a division by 0 and the unsupported operator `%` prints a message and then shows the previous result unchanged.

```text
0 + 7
= 7 / 0
0으로 나눌 수 없습니다.
= 7 % 3
잘못된 연산자입니다.
= 7 * 3
= 21 0 0
```

> **Note:** **A form without a global variable.** This problem stores the result in a global variable to practice global variables. To avoid the global variable, change the function to take the previous result as an argument and return the new result, as in `int accumulate(int prev, char op, int operand)`, and store the return value in a local variable of `main()`. This makes it visible at each call which function changes the result ([Chapter 6, Section 3.2](Concepts_Lecture.md#32-global-variables)).
