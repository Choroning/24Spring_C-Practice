# Chapter 2 Exercises — C Program Basics

[Repository Guide](../../README.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

> **Last Updated:** 2026-10-27
>
> Warming-Up C Programming, 천정아, Ch 2

Exercises 1-10 are exercises 1-10 of Chapter 2 of the textbook, and Exercises 11-19 are programming assignments 1-9 of Chapter 2.

---

<br>

## Table of Contents

- [Exercise 1: Statements About Comments](#exercise-1-statements-about-comments)
- [Exercise 2: Statements About Functions](#exercise-2-statements-about-functions)
- [Exercise 3: The Function Called When a Program Starts](#exercise-3-the-function-called-when-a-program-starts)
- [Exercise 4: Statements About the `main` Function](#exercise-4-statements-about-the-main-function)
- [Exercise 5: Statements About Variables](#exercise-5-statements-about-variables)
- [Exercise 6: Format Specifiers of `printf` and Their Meanings](#exercise-6-format-specifiers-of-printf-and-their-meanings)
- [Exercise 7: The Format Specifier That Produces the Output](#exercise-7-the-format-specifier-that-produces-the-output)
- [Exercise 8: Two Things Needed to Declare a Variable](#exercise-8-two-things-needed-to-declare-a-variable)
- [Exercise 9: The Header for the I/O Library](#exercise-9-the-header-for-the-io-library)
- [Exercise 10: A Program That Reads and Prints a Character](#exercise-10-a-program-that-reads-and-prints-a-character)
- [Exercise 11: Printing Several Lines with One `printf`](#exercise-11-printing-several-lines-with-one-printf)
- [Exercise 12: Printing a Decimal Integer in Hexadecimal](#exercise-12-printing-a-decimal-integer-in-hexadecimal)
- [Exercise 13: Reading and Printing a Date](#exercise-13-reading-and-printing-a-date)
- [Exercise 14: Printing Hours, Minutes, and Seconds in Two Digits](#exercise-14-printing-hours-minutes-and-seconds-in-two-digits)
- [Exercise 15: Converting Dollars to Won](#exercise-15-converting-dollars-to-won)
- [Exercise 16: Choosing a Clothing Size](#exercise-16-choosing-a-clothing-size)
- [Exercise 17: The Sum and Difference of Two Real Numbers](#exercise-17-the-sum-and-difference-of-two-real-numbers)
- [Exercise 18: Printing Pi in Several Formats](#exercise-18-printing-pi-in-several-formats)
- [Exercise 19: Reading and Printing Octal, Decimal, and Hexadecimal Integers](#exercise-19-reading-and-printing-octal-decimal-and-hexadecimal-integers)

---

<br>

## Exercise 1: Statements About Comments

**Textbook Problem:** Chapter 2 exercise 1

**Problem:** Choose all the incorrect statements about comments.

- ① A comment is a description of the program.
- ② Comments are compiled by the C/C++ compiler.
- ③ A multi-line comment is written with `/*` and `*/`.
- ④ A one-line comment is written with `//`.
- ⑤ Comments can keep source code that has already been written from being compiled.
- ⑥ A `/* */` comment cannot be nested inside another `/* */` comment.
- ⑦ A C program must contain comments.

**[Solution](Solutions.md#exercise-1-statements-about-comments)**

---

<br>

## Exercise 2: Statements About Functions

**Textbook Problem:** Chapter 2 exercise 2

**Problem:** Choose all the incorrect statements about functions.

- ① A function needs a return type, a function name, and parameters.
- ② If there are no parameters, write `void` or leave the inside of `( )` empty.
- ③ What the function processes, that is, its statements, is written inside `{` and `}`.
- ④ The statements in a function are executed in order.
- ⑤ When the end of the function (`}`) or a `return` is reached, control goes back to the start of the function.
- ⑥ A statement ends with `.`.
- ⑦ A C program consists of one or more functions.

**[Solution](Solutions.md#exercise-2-statements-about-functions)**

---

<br>

## Exercise 3: The Function Called When a Program Starts

**Textbook Problem:** Chapter 2 exercise 3

**Problem:** What is a function like `main`, which is called when a C program first starts, called?

**[Solution](Solutions.md#exercise-3-the-function-called-when-a-program-starts)**

---

<br>

## Exercise 4: Statements About the `main` Function

**Textbook Problem:** Chapter 2 exercise 4

**Problem:** Choose all the correct statements about the `main` function.

- ① The return type of the `main` function is `int`.
- ② A C program may or may not have a `main` function.
- ③ `main`, `Main`, and `MAIN` are all the same function.
- ④ The `return` statement of the `main` function can be omitted.
- ⑤ It is the function that the operating system calls when the program starts.
- ⑥ It returns 0 on normal termination and a nonzero value on abnormal termination.

**[Solution](Solutions.md#exercise-4-statements-about-the-main-function)**

---

<br>

## Exercise 5: Statements About Variables

**Textbook Problem:** Chapter 2 exercise 5

**Problem:** Choose all the incorrect statements about variables.

- ① A variable is a space for storing a value.
- ② A variable is allocated in memory.
- ③ To store a value in a variable, assign it with `=`.
- ④ The data type can be omitted when a variable is declared.
- ⑤ The data type of a variable determines the size of the memory to be allocated.
- ⑥ A variable can be used without being declared.
- ⑦ A variable name is an identifier.

**[Solution](Solutions.md#exercise-5-statements-about-variables)**

---

<br>

## Exercise 6: Format Specifiers of `printf` and Their Meanings

**Textbook Problem:** Chapter 2 exercise 6

**Problem:** Match the format specifiers (1)-(5) of the `printf` function with their meanings ①-⑤.

**Format specifiers:**

- (1) `%d`
- (2) `%f`
- (3) `%c`
- (4) `%x`
- (5) `%e`

**Meanings:**

- ① Prints an integer in hexadecimal.
- ② Prints an integer in decimal.
- ③ Prints a real number in floating-point notation.
- ④ Prints a real number in exponential notation.
- ⑤ Prints a character.

**[Solution](Solutions.md#exercise-6-format-specifiers-of-printf-and-their-meanings)**

---

<br>

## Exercise 7: The Format Specifier That Produces the Output

**Textbook Problem:** Chapter 2 exercise 7

**Problem:** Look at the output of the following program and write the code that goes in the blank of the source code.

```c
#include <stdio.h>

int main(void)
{
    float pi = 3.141592;
    printf("pi = ________\n", pi);
}
```

**Sample Run:**

```text
pi = 3.14
```

**[Solution](Solutions.md#exercise-7-the-format-specifier-that-produces-the-output)**

---

<br>

## Exercise 8: Two Things Needed to Declare a Variable

**Textbook Problem:** Chapter 2 exercise 8

**Problem:** What are the two things needed to declare a variable?

**[Solution](Solutions.md#exercise-8-two-things-needed-to-declare-a-variable)**

---

<br>

## Exercise 9: The Header for the I/O Library

**Textbook Problem:** Chapter 2 exercise 9

**Problem:** What is the input/output library header needed to use the `scanf` and `printf` functions?

**[Solution](Solutions.md#exercise-9-the-header-for-the-io-library)**

---

<br>

## Exercise 10: A Program That Reads and Prints a Character

**Textbook Problem:** Chapter 2 exercise 10

**Problem:** The following program reads a character and prints it. Write the code that goes in blanks ①, ②, and ③ of the source code.

```c
// test.c
#define _CRT_SECURE_NO_WARNINGS     // needed to use scanf in Visual Studio 2022
#include ① ____________

int main(void)
{
    char ch;
    scanf("%c", ② ________);
    printf("ch = ③____\n", ch);
}
```

**[Solution](Solutions.md#exercise-10-a-program-that-reads-and-prints-a-character)**

---

<br>

## Exercise 11: Printing Several Lines with One `printf`

**Textbook Problem:** Chapter 2 programming assignment 1

**Problem:** Write a program that prints the following. Use the `printf` statement only once.

**Sample Run:**

```text
int main(void)
{
    return 0;
}
```

**[Solution](Solutions.md#exercise-11-printing-several-lines-with-one-printf)**

---

<br>

## Exercise 12: Printing a Decimal Integer in Hexadecimal

**Textbook Problem:** Chapter 2 programming assignment 2

**Problem:** Write a program that reads a decimal integer, converts it to hexadecimal, and prints it.

**Sample Run:**

```text
10진수 정수? 10
10진수 10은 16진수 a에 해당합니다.
```

**[Solution](Solutions.md#exercise-12-printing-a-decimal-integer-in-hexadecimal)**

---

<br>

## Exercise 13: Reading and Printing a Date

**Textbook Problem:** Chapter 2 programming assignment 3

**Problem:** Write a program that reads a date as a year, a month, and a day and prints it. The year, month, and day are read as integers.

**Sample Run:**

```text
연? 2022
월? 10
일? 1
입력한 날짜는 2022년 10월 1일 입니다.
```

**[Solution](Solutions.md#exercise-13-reading-and-printing-a-date)**

---

<br>

## Exercise 14: Printing Hours, Minutes, and Seconds in Two Digits

**Textbook Problem:** Chapter 2 programming assignment 4

**Problem:** Write a program that reads a time as hours, minutes, and seconds and prints it. For example, 1 hour 1 minute 1 second is printed as "01:01:01".

**Sample Run:**

```text
시? 1
분? 1
초? 1
입력한 시간은 01:01:01입니다.
```

**[Solution](Solutions.md#exercise-14-printing-hours-minutes-and-seconds-in-two-digits)**

---

<br>

## Exercise 15: Converting Dollars to Won

**Textbook Problem:** Chapter 2 programming assignment 5

**Problem:** Write a program that reads an amount in dollars and prints how many won it is. The dollar amount is read as a real number, and the won amount is printed as an integer. Assume that 1 dollar is 1000 won.

**Sample Run:**

```text
달러? 50.25
$50.25는 50250원입니다.
```

**[Solution](Solutions.md#exercise-15-converting-dollars-to-won)**

---

<br>

## Exercise 16: Choosing a Clothing Size

**Textbook Problem:** Chapter 2 programming assignment 6

**Problem:** Write a program that lets the user choose a clothing size and prints the chosen size. The size is read as one of the three characters S, M, and L.

**Sample Run:**

```text
옷 사이즈(S,M,L)? M
M 사이즈를 선택했습니다.
```

**[Solution](Solutions.md#exercise-16-choosing-a-clothing-size)**

---

<br>

## Exercise 17: The Sum and Difference of Two Real Numbers

**Textbook Problem:** Chapter 2 programming assignment 7

**Problem:** Write a program that reads two real numbers and computes and prints their sum and difference.

**Sample Run:**

```text
실수 2개? 12.34 0.5
12.340000 + 0.500000 = 12.840000
12.340000 - 0.500000 = 11.840000
```

**[Solution](Solutions.md#exercise-17-the-sum-and-difference-of-two-real-numbers)**

---

<br>

## Exercise 18: Printing Pi in Several Formats

**Textbook Problem:** Chapter 2 programming assignment 8

**Problem:** Given that the value of pi is 3.14159265, write a program that prints pi in several ways. Print it to 2, 4, 6, and 8 digits after the decimal point, and also in exponential notation. Also compare using a `float` variable with using a `double` variable to store pi.

**Sample Run:**

```text
pi = 3.14
pi = 3.1416
pi = 3.141593
pi = 3.14159265
pi = 3.141593e+00
```

**[Solution](Solutions.md#exercise-18-printing-pi-in-several-formats)**

---

<br>

## Exercise 19: Reading and Printing Octal, Decimal, and Hexadecimal Integers

**Textbook Problem:** Chapter 2 programming assignment 9

**Problem:** Write a program that reads an integer in octal, decimal, or hexadecimal and prints its value in octal, decimal, and hexadecimal. An octal number is entered with a leading 0, as in `012`, and a hexadecimal number is entered with a leading `0x`, as in `0x12`.

**Sample Run:**

```text
8진수로 입력하려면 012, 16진수로 입력하려면 0x12처럼 입력하세요.
정수? 0x12
 8진수: 022
10진수: 18
16진수: 0x12
```

**[Solution](Solutions.md#exercise-19-reading-and-printing-octal-decimal-and-hexadecimal-integers)**
