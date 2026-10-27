# Chapter 6 Exercises — Functions

[Repository Guide](../../README.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

> **Last Updated:** 2026-10-27
>
> Warming-Up C Programming, 천정아, Ch 6

**Problem Source:** Prof. Younghee Im, Computer Language Ⅰ (DCCS101-04)

Exercises 1-3 are lab problems, Exercises 4-17 are exercises 1-14 of Chapter 6 of the textbook, and Exercises 18-29 are programming assignments 1-12 of Chapter 6.

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

**Problem:** Define a function `round()` that receives a real number and returns the integer obtained by rounding it at the first decimal place. Using this function, write a program that reads real numbers until `0.0` is entered and prints the rounded result of each in turn.

|               | Program       | `round()` Function |
|:-------------:|:------------:|:-----------:|
|**Input**       |Real number (0.0 to quit)|Real number          |
|**Output**      |Rounded result   |Rounded value       |

*Table 1. Input and output of the program and the `round()` function in Exercise 1*

**Program Requirements:**

- The `round()` function must work correctly for both positive and negative numbers.

**Sample Run:**

```text
실수를 입력하세요 (0.0 입력 시 종료): 2.75
2.750000의 반올림 결과 = 3

실수를 입력하세요 (0.0 입력 시 종료): 9.1
9.100000의 반올림 결과 = 9

실수를 입력하세요 (0.0 입력 시 종료): -6.3
-6.300000의 반올림 결과 = -6

실수를 입력하세요 (0.0 입력 시 종료): -7.815
-7.815000의 반올림 결과 = -8

실수를 입력하세요 (0.0 입력 시 종료): 0.0

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-1-rounding-a-real-number)**

---

<br>

## Exercise 2: Leap Year Test

**Problem:** Define a function `isLeapYear()` that receives a year and determines whether it is a leap year. Using this function, write a program that prints all leap years from 2000 to 2150, 10 per line.

The leap year conditions are as follows.

1. A year divisible by 4 is a leap year.
2. A year that meets condition 1 and is divisible by 100 is a common year.
3. A year that meets conditions 1 and 2 and is divisible by 400 is a leap year.

|               | Program                    | `isLeapYear()` Function |
|:-------------:|:-------------------------:|:------------:|
|**Input**       | None                       | Year          |
|**Output**      |List of leap years from 2000 to 2150|1: leap year, 0: common year|

*Table 2. Input and output of the program and the `isLeapYear()` function in Exercise 2*

**Program Requirements:**

1. Print the results 10 per line.
2. Separate the items with a space character.

**Sample Run:**

```text
-------------------------------------------------
               2000~2150년 사이의 윤년
-------------------------------------------------
2000 2004 2008 2012 2016 2020 2024 2028 2032 2036
2040 2044 2048 2052 2056 2060 2064 2068 2072 2076
2080 2084 2088 2092 2096 2104 2108 2112 2116 2120
2124 2128 2132 2136 2140 2144 2148

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-2-leap-year-test)**

---

<br>

## Exercise 3: Number of Days in a Month

**Problem:** Define a function `GetDaysOfMonth()` that receives a year and a month and returns the number of days in that month. Using this function, write a program that reads a year and a month from the user and prints the number of days in that month.

|               | Program    | `GetDaysOfMonth()` Function |
|:-------------:|:---------:|:--------------------:|
|**Input**       | Year, month    | Year, month               |
|**Output**      |Days of that month| Number of days                |

*Table 3. Input and output of the program and the `GetDaysOfMonth()` function in Exercise 3*

**Program Requirements:**

1. January, March, May, July, August, October, and December have 31 days, and April, June, September, and November have 30 days.
2. February has 29 days in a leap year and 28 days in a common year.
3. Determine whether the year is a leap year with the `isLeapYear()` function written in Exercise 2.

**Sample Run:**

```text
연도와 월을 입력하세요: 2017 4
2017년 4월은 30일까지 있습니다.

Program ended with exit code: 0
```

```text
연도와 월을 입력하세요: 2020 8
2020년 8월은 31일까지 있습니다.

Program ended with exit code: 0
```

```text
연도와 월을 입력하세요: 2000 2
2000년 2월은 29일까지 있습니다.

Program ended with exit code: 0
```

```text
연도와 월을 입력하세요: 2100 2
2100년 2월은 28일까지 있습니다.

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-3-number-of-days-in-a-month)**

---

<br>

## Exercise 4: The Concept of a Function

**Textbook Problem:** Chapter 6 exercise 1

**Problem:** Choose all the incorrect statements about the concept of a function.

- ① It is code that provides a specific feature, grouped together and given a name.
- ② A function can be viewed as a black box model that, given an input, performs a specific task and then outputs a result.
- ③ To call a function, the internal code of the function must be known in detail.
- ④ The code of a function is copied every time the function is called.
- ⑤ Part of code that has already been written can also be defined as a function.

**[Solution](Solutions.md#exercise-4-the-concept-of-a-function)**

---

<br>

## Exercise 5: Advantages of Using Functions

**Textbook Problem:** Chapter 6 exercise 2

**Problem:** Choose all the advantages of using functions.

- ① The code is duplicated, so the executable file becomes larger.
- ② The reusability of the code increases.
- ③ The program is easy to maintain.
- ④ The code is long and complicated, so it is hard to read.
- ⑤ Functions are written and used around features, so the modularity of the program increases.

**[Solution](Solutions.md#exercise-5-advantages-of-using-functions)**

---

<br>

## Exercise 6: Statements About Functions

**Textbook Problem:** Chapter 6 exercise 3

**Problem:** Choose all the incorrect statements about functions.

- ① The definition of a function cannot be omitted.
- ② A function without a return value omits the return type.
- ③ The declaration of a function describes what the function actually does.
- ④ When a function is called, arguments are passed to it and its return value is received.
- ⑤ When a function is called with fewer arguments than parameters, 0 is passed in their place.
- ⑥ To call a function, a declaration or a definition of the function is always required.
- ⑦ When a function is called, the values of the arguments are computed first.
- ⑧ Functions with the same name can be defined several times.
- ⑨ The names of the parameters can be omitted in a function declaration.
- ⑩ The declaration of a function can be omitted.
- ⑪ The same function can be declared several times.

**[Solution](Solutions.md#exercise-6-statements-about-functions)**

---

<br>

## Exercise 7: Return Types and Parameters

**Textbook Problem:** Chapter 6 exercise 4

**Problem:** Choose all the incorrect statements about the return types and parameters of functions.

- ① The return type of a function is the data type of the value that the function returns as its result.
- ② When a function returns no value as its result, `void` is written.
- ③ If the return type is omitted, it is taken to be `void`.
- ④ When a function produces two or more results, parameters must be used instead of the return value.
- ⑤ A parameter is a variable that stores a value passed into the function from the place where it is called.
- ⑥ If a function has no parameters, `void` is written or the `( )` is left empty.
- ⑦ A function can have at most 8 parameters.
- ⑧ The parameters of a function are also a kind of local variable created when the function is called.

**[Solution](Solutions.md#exercise-7-return-types-and-parameters)**

---

<br>

## Exercise 8: The Three Requirements of a Function

**Textbook Problem:** Chapter 6 exercise 5

**Problem:** Write all three requirements of a function.

**[Solution](Solutions.md#exercise-8-the-three-requirements-of-a-function)**

---

<br>

## Exercise 9: Calling a Function with a Return Value and Parameters

**Textbook Problem:** Chapter 6 exercise 6

**Problem:** Choose all the incorrect statements about calling a function that has a return value and parameters.

- ① When a function is called, the values of the arguments are passed to the parameters.
- ② If the data types of an argument and a parameter differ, the parameter is converted to the data type of the argument.
- ③ If the return value of a function is not used, the function is not called.
- ④ If an argument of a function is an expression, the value of the expression is computed first.
- ⑤ If an argument of a function is a function call, the return value of that call is used as the argument after the call.
- ⑥ If the return value of a function does not match the return type, it is converted.
- ⑦ The number of arguments must equal the number of parameters.
- ⑧ The order of the arguments and the parameters may differ.

**[Solution](Solutions.md#exercise-9-calling-a-function-with-a-return-value-and-parameters)**

---

<br>

## Exercise 10: Local and Global Variables

**Textbook Problem:** Chapter 6 exercise 7

**Problem:** Choose all the incorrect statements about local variables and global variables.

- ① A local variable is a variable declared inside a function or a block.
- ② Local variables with the same name cannot be declared in different functions.
- ③ A local variable declared in another function cannot be used.
- ④ The parameters of a function are also local variables.
- ⑤ A variable declared inside an `if` or `while` block can be used even after leaving that block.
- ⑥ A local variable declared inside a function is created and destroyed as many times as the function is called.
- ⑦ A global variable is a variable declared outside functions.
- ⑧ A global variable can be used regardless of where it is declared in the source file.
- ⑨ If there is a local variable with the same name as a global variable, the global variable cannot be used.
- ⑩ A global variable is created when the program starts and destroyed when the program terminates.

**[Solution](Solutions.md#exercise-10-local-and-global-variables)**

---

<br>

## Exercise 11: Prototype of a Function That Computes the Perimeter of a Rectangle

**Textbook Problem:** Chapter 6 exercise 8

**Problem:** Write the prototype of a function that receives the width and height as parameters and computes the perimeter of a rectangle. The width, the height, and the perimeter are all integers.

**[Solution](Solutions.md#exercise-11-prototype-of-a-function-that-computes-the-perimeter-of-a-rectangle)**

---

<br>

## Exercise 12: Prototype of a Function That Checks for an English Letter

**Textbook Problem:** Chapter 6 exercise 9

**Problem:** Write the prototype of a function that receives a character as a parameter and checks whether it is an English letter.

**[Solution](Solutions.md#exercise-12-prototype-of-a-function-that-checks-for-an-english-letter)**

---

<br>

## Exercise 13: Prototype of a Function That Computes a Discounted Price

**Textbook Problem:** Chapter 6 exercise 10

**Problem:** Write the prototype of a function that receives the price of a product and a discount rate as parameters and computes the discounted price.

**[Solution](Solutions.md#exercise-13-prototype-of-a-function-that-computes-a-discounted-price)**

---

<br>

## Exercise 14: Prototype of a Function That Computes the Greatest Common Divisor

**Textbook Problem:** Chapter 6 exercise 11

**Problem:** Write the prototype of a function that receives two integers as parameters and computes their greatest common divisor.

**[Solution](Solutions.md#exercise-14-prototype-of-a-function-that-computes-the-greatest-common-divisor)**

---

<br>

## Exercise 15: Turning the Arithmetic Code into a Function

**Textbook Problem:** Chapter 6 exercise 12

**Problem:** In the following code, define the whole `switch` statement, from `switch (op) {` to its matching closing `}`, as a function. Choose the return type, the name, and the parameters of the function yourself. Then modify the code so that it calls the function.

```c
#define _CRT_SECURE_NO_WARNINGS      // Visual Studio 2022에서 scanf 사용 시 필요
#include <stdio.h>

int main(void)
{
    int x, y;                        // 피연산자
    char op;                         // 연산자 기호를 문자로 저장할 변수
    printf("수식 ? ");
    scanf("%d %c %d", &x, &op, &y);  // 10 + 30 형태로 입력받는다.

    switch (op) {
    case '+':   printf("%d + %d = %d\n", x, y, x + y);    break;
    case '-':   printf("%d - %d = %d\n", x, y, x - y);    break;
    case '*':   printf("%d * %d = %d\n", x, y, x * y);    break;
    case '/':   printf("%d / %d = %d\n", x, y, x / y);    break;
    default:    printf("잘못된 수식입니다.\n");         break;
    }
}
```

**[Solution](Solutions.md#exercise-15-turning-the-arithmetic-code-into-a-function)**

---

<br>

## Exercise 16: The Code Needed in the Blank

**Textbook Problem:** Chapter 6 exercise 13

**Problem:** Write the code needed in place of `[빈칸]` (blank) in the following program.

```c
#define _CRT_SECURE_NO_WARNINGS      // Visual Studio 2022에서 scanf 사용 시 필요
#include <stdio.h>
[빈칸]
int main(void)
{
    int hour, min, sec;
    printf("시간 분 초? ");
    scanf("%d %d %d", &hour, &min, &sec);
    printf("%d시간 %d분 %d초 = %d초\n", hour, min, sec, get_seconds(hour, min, sec));
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

**[Solution](Solutions.md#exercise-16-the-code-needed-in-the-blank)**

---

<br>

## Exercise 17: Output of a Program with Variables of the Same Name

**Textbook Problem:** Chapter 6 exercise 14

**Problem:** Write the output of the following program.

```c
#include <stdio.h>

int data = 100;

int main(void)
{
    int data = 10;
    int i;
    for (i = 0; i < data; i++) {
        int data = 1;
        data += 3;
        if (data > 10)
            break;
    }
    printf("data = %d\n", data);
}
```

**[Solution](Solutions.md#exercise-17-output-of-a-program-with-variables-of-the-same-name)**

---

<br>

## Exercise 18: Printing Multiples of an Integer

**Textbook Problem:** Chapter 6 programming assignment 1

**Problem:** Write a function that receives an integer and a number of multiples as parameters and prints the multiples of the integer. Using this function, write a program that prints 20 multiples of each integer entered. The program terminates when a value less than or equal to 0 is entered. Write the function without a return value and with parameters only.

**Sample Run:**

```text
정수? 3
3 6 9 12 15 18 21 24 27 30 33 36 39 42 45 48 51 54 57 60
정수? 11
11 22 33 44 55 66 77 88 99 110 121 132 143 154 165 176 187 198 209 220
정수? 0
```

**[Solution](Solutions.md#exercise-18-printing-multiples-of-an-integer)**

---

<br>

## Exercise 19: Perimeter of a Rectangle

**Textbook Problem:** Chapter 6 programming assignment 2

**Problem:** Write a function that receives the width and height as parameters and computes the perimeter of a rectangle. Using this function, write a program that computes the perimeter of a rectangle from the width and height entered. Write the function with a return value and parameters.

**Sample Run:**

```text
가로? 100
세로? 200
직사각형의 둘레: 600
```

**[Solution](Solutions.md#exercise-19-perimeter-of-a-rectangle)**

---

<br>

## Exercise 20: Distance Between Two Points

**Textbook Problem:** Chapter 6 programming assignment 3

**Problem:** Write a function that receives the x and y coordinates of two points as parameters and computes the straight-line distance between them. Using this function, write a program that computes the straight-line distance from the start point to the end point entered. Write the function with a return value and parameters.

**Sample Run:**

```text
직선의 시작점 좌표? 0 0
직선의 끝점 좌표? 3 4
(0, 0)~(3, 4) 직선의 길이: 5.000000
```

**[Solution](Solutions.md#exercise-20-distance-between-two-points)**

---

<br>

## Exercise 21: Computing Discounted Prices

**Textbook Problem:** Chapter 6 programming assignment 4

**Problem:** Write a function that receives the price of a product and a discount rate as parameters and computes the discounted price. Using this function, write a program that first reads the discount rate and then, for each product price entered, computes and prints the discounted price. The program terminates when 0 is entered as the price. Write the function with a return value and parameters.

**Sample Run:**

```text
할인율(%)? 20
제품의 가격? 10000
할인가: 8000원
제품의 가격? 5000
할인가: 4000원
제품의 가격? 0
```

**[Solution](Solutions.md#exercise-21-computing-discounted-prices)**

---

<br>

## Exercise 22: Printing a Menu

**Textbook Problem:** Chapter 6 programming assignment 5

**Problem:** Write a function that prints a menu as in the sample run. Using this function, write a program that prints the menu, reads a menu number, and shows the selected menu. Write the function without a return value or parameters.

**Sample Run:**

```text
[1.파일 열기  2.파일 저장  3.인쇄  0.종료] 선택? 1
파일 열기를 수행합니다.
[1.파일 열기  2.파일 저장  3.인쇄  0.종료] 선택? 2
파일 저장을 수행합니다.
[1.파일 열기  2.파일 저장  3.인쇄  0.종료] 선택? 0
```

**[Solution](Solutions.md#exercise-22-printing-a-menu)**

---

<br>

## Exercise 23: The Red, Green, and Blue Values of an RGB Color

**Textbook Problem:** Chapter 6 programming assignment 6

**Problem:** Define a function that obtains the red value of an RGB color, a function that obtains the green value, and a function that obtains the blue value. Using these functions, write a program that prints, in decimal, the red, green, and blue values of an RGB color entered in hexadecimal. As in the sample run, bits 0-7 of the RGB color hold red, bits 8-15 hold green, and bits 16-23 hold blue. Write the functions with a return value and parameters.

**Sample Run:**

```text
RGB 색상? 0xff0080
RGB FF0080의 red: 128, green: 0, blue: 255
```

**[Solution](Solutions.md#exercise-23-the-red-green-and-blue-values-of-an-rgb-color)**

---

<br>

## Exercise 24: Leap Years from 2000 to 2100

**Textbook Problem:** Chapter 6 programming assignment 7

**Problem:** Write a function that receives a year as a parameter and determines whether it is a leap year. Using this function, write a program that finds and prints all the leap years between 2000 and 2100. As in the sample run, print 10 years per line. Write the function with a return value and parameters.

**Sample Run:**

```text
2000 2004 2008 2012 2016 2020 2024 2028 2032 2036
2040 2044 2048 2052 2056 2060 2064 2068 2072 2076
2080 2084 2088 2092 2096
```

**[Solution](Solutions.md#exercise-24-leap-years-from-2000-to-2100)**

---

<br>

## Exercise 25: Checking for a Valid Date

**Textbook Problem:** Chapter 6 programming assignment 8

**Problem:** Write a function that receives a year, a month, and a day as parameters and checks whether they form a valid date. The function returns 1 if the date passed in the parameters is valid and 0 otherwise. Using this function, write a program that reads a date. When an invalid date is entered, the program keeps reading the date again until a valid one is entered.

**Sample Run:**

```text
날짜 (연 월 일)? 2022 13 1
잘못 입력하셨습니다. 유효한 날짜를 입력하세요.
날짜 (연 월 일)? 2022 6 31
잘못 입력하셨습니다. 유효한 날짜를 입력하세요.
날짜 (연 월 일)? 2022 5 1
입력한 날짜는 2022년 5월 1일입니다.
```

**[Solution](Solutions.md#exercise-25-checking-for-a-valid-date)**

---

<br>

## Exercise 26: Printing an Integer in Binary

**Textbook Problem:** Chapter 6 programming assignment 9

**Problem:** Write a function that receives an integer as a parameter and prints it in binary. Using this function, write a program that prints an integer entered in hexadecimal in binary. Write the function without a return value and with parameters only.

**Sample Run:**

```text
정수? 0xabcd1234
16진수 ABCD1234: 1010 1011 1100 1101 0001 0010 0011 0100
```

**[Solution](Solutions.md#exercise-26-printing-an-integer-in-binary)**

---

<br>

## Exercise 27: Divisors and the Number of Divisors

**Textbook Problem:** Chapter 6 programming assignment 10

**Problem:** Write a function that receives an integer as a parameter, finds its divisors and the number of divisors, and prints them. Using this function, write a program that finds and prints the divisors of each integer entered. The program terminates when 0 is entered. Write the function without a return value and with parameters only.

**Sample Run:**

```text
양의 정수? 100
100의 약수: 1 2 4 5 10 20 25 50 100 => 총 9개
양의 정수? 56
56의 약수: 1 2 4 7 8 14 28 56 => 총 8개
양의 정수? 0
```

**[Solution](Solutions.md#exercise-27-divisors-and-the-number-of-divisors)**

---

<br>

## Exercise 28: Prime Numbers from 1 to N

**Textbook Problem:** Chapter 6 programming assignment 11

**Problem:** Define a function that receives an integer as a parameter and checks whether it is a prime number. Using this function, write a program that finds and prints all the prime numbers between 1 and N. N is entered by the user, and the primes are printed 10 per line as in the sample run. Write the function with a return value and parameters.

**Sample Run:**

```text
1~N 사이의 소수를 구합니다. N은? 100
  2  3  5  7 11 13 17 19 23 29
 31 37 41 43 47 53 59 61 67 71
 73 79 83 89 97
```

**[Solution](Solutions.md#exercise-28-prime-numbers-from-1-to-n)**

---

<br>

## Exercise 29: An Accumulator

**Textbook Problem:** Chapter 6 programming assignment 12

**Problem:** An accumulator is a calculator that keeps performing calculations on the result of the previous operation. Define a function that receives an operator and one operand as parameters, performs the calculation with the result of the previous operation, and prints the result. Using this function, write a program that prints the results of the expressions entered. The program terminates when `0 0` is entered. Store the result of the previous operation in a global variable.

**Sample Run:** The `0` printed first is the initial result, and on each line the operator and operand, such as `+ 22` or `* 5`, are entered after the result.

```text
0 + 22
= 22 * 5
= 110 / 10
= 11 - 5
= 6 0 0
```

**[Solution](Solutions.md#exercise-29-an-accumulator)**
