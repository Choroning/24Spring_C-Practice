# Chapter 3 Exercises — Data Types and Variables

[Repository Guide](../../README.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

> **Last Updated:** 2026-10-27
>
> Warming-Up C Programming, 천정아, Ch 3

Exercises 1-8 are exercises 1-8 of Chapter 3 of the textbook, and Exercises 9-18 are programming assignments 1-10 of Chapter 3.

---

<br>

## Table of Contents

- [Exercise 1: Statements About Data Types](#exercise-1-statements-about-data-types)
- [Exercise 2: Meanings of Escape Sequences](#exercise-2-meanings-of-escape-sequences)
- [Exercise 3: Statements About Variables](#exercise-3-statements-about-variables)
- [Exercise 4: Valid Variable Declarations](#exercise-4-valid-variable-declarations)
- [Exercise 5: Statements About Constants](#exercise-5-statements-about-constants)
- [Exercise 6: Advantages of Symbolic Constants](#exercise-6-advantages-of-symbolic-constants)
- [Exercise 7: Lines That Cause Compile Errors](#exercise-7-lines-that-cause-compile-errors)
- [Exercise 8: Printing Out-of-Range Values](#exercise-8-printing-out-of-range-values)
- [Exercise 9: Area and Perimeter of a Square](#exercise-9-area-and-perimeter-of-a-square)
- [Exercise 10: Area and Perimeter of a Rectangle](#exercise-10-area-and-perimeter-of-a-rectangle)
- [Exercise 11: Computing Potential Energy](#exercise-11-computing-potential-energy)
- [Exercise 12: Area of a Right Triangle](#exercise-12-area-of-a-right-triangle)
- [Exercise 13: Converting Dollars to Won](#exercise-13-converting-dollars-to-won)
- [Exercise 14: Converting Won to Dollars](#exercise-14-converting-won-to-dollars)
- [Exercise 15: Converting Yards to Meters](#exercise-15-converting-yards-to-meters)
- [Exercise 16: Converting Inches to Centimeters](#exercise-16-converting-inches-to-centimeters)
- [Exercise 17: Converting Square Meters to Pyeong](#exercise-17-converting-square-meters-to-pyeong)
- [Exercise 18: Square and Cube of a Real Number](#exercise-18-square-and-cube-of-a-real-number)

---

<br>

## Exercise 1: Statements About Data Types

**Textbook Problem:** Chapter 3 exercise 1

**Problem:** Choose all the incorrect statements about data types.

- ① The size of each data type is fixed regardless of the platform.
- ② The character type is `char`, and its size is 2 bytes.
- ③ Floating-point types also come in signed and unsigned forms.
- ④ For integer types, the larger the data type, the wider the valid range.
- ⑤ The `char` type can also be regarded as an integer type.
- ⑥ Storing a value larger than the maximum of the data type in an integer variable makes the variable larger.
- ⑦ Storing a value smaller than the minimum of the data type in an integer variable sets it to a value within the valid range.
- ⑧ Storing a value larger than the largest representable real number in a floating-point variable sets it to 0.
- ⑨ The precision of a real number is determined by the exponent part.
- ⑩ Real numbers can always be represented exactly.

**[Solution](Solutions.md#exercise-1-statements-about-data-types)**

---

<br>

## Exercise 2: Meanings of Escape Sequences

**Textbook Problem:** Chapter 3 exercise 2

**Problem:** Match each escape sequence with its meaning.

**Escape sequences:**

- (1) `'\0'`
- (2) `'\a'`
- (3) `'\b'`
- (4) `'\t'`
- (5) `'\n'`
- (6) `'\\'`

**Meanings:**

- ① Newline
- ② Null character
- ③ Horizontal tab
- ④ Bell
- ⑤ Backslash
- ⑥ Backspace

**[Solution](Solutions.md#exercise-2-meanings-of-escape-sequences)**

---

<br>

## Exercise 3: Statements About Variables

**Textbook Problem:** Chapter 3 exercise 3

**Problem:** Choose all the correct statements about variables.

- ① A variable can be declared without a data type.
- ② A value can be read from a variable.
- ③ A variable is allocated in memory.
- ④ A variable can be declared without a name.
- ⑤ The value of a variable cannot be changed.
- ⑥ Storing a value in a variable is called initialization.
- ⑦ A variable that is not explicitly initialized is initialized to 0.

**[Solution](Solutions.md#exercise-3-statements-about-variables)**

---

<br>

## Exercise 4: Valid Variable Declarations

**Textbook Problem:** Chapter 3 exercise 4

**Problem:** Choose all the valid variable declarations.

- ① `char default;`
- ② `int %_of_market;`
- ③ `unsigned short maxCount;`
- ④ `int num; double num;`
- ⑤ `int x = 100, y, z = 200;`
- ⑥ `int elapsed sec;`

**[Solution](Solutions.md#exercise-4-valid-variable-declarations)**

---

<br>

## Exercise 5: Statements About Constants

**Textbook Problem:** Chapter 3 exercise 5

**Problem:** Choose all the incorrect statements about constants.

- ① A constant cannot be changed, so it cannot appear on the left side of `=`.
- ② The value of a constant is not stored in memory; it is used only once and then disappears.
- ③ A constant with a name is called a literal constant.
- ④ Using literal constants makes code easy to read and easy to modify.
- ⑤ A data type is needed to define a macro constant.
- ⑥ A macro constant inside a string is not replaced.
- ⑦ A `const` variable cannot be changed, so it is not allocated in memory.
- ⑧ Changing a `const` variable causes a compile error.

**[Solution](Solutions.md#exercise-5-statements-about-constants)**

---

<br>

## Exercise 6: Advantages of Symbolic Constants

**Textbook Problem:** Chapter 3 exercise 6

**Problem:** Write two advantages of using symbolic constants instead of literal constants.

**[Solution](Solutions.md#exercise-6-advantages-of-symbolic-constants)**

---

<br>

## Exercise 7: Lines That Cause Compile Errors

**Textbook Problem:** Chapter 3 exercise 7

**Problem:** Find all the lines of the following source code that cause a compile error. The two-digit number at the start of each line is the line number.

```c
01  #include <stdio.h>
02  #define MAX 1000
03  #define MIN 0;
04
05  int main(void)
06  {
07      int x = 10;
08      const int y = 20;
09
10      MAX = 2000;
11      x = MAX - 1;
12      y = MAX - 2;
13      printf("range: %d ~ %d\n", MIN, MAX);
14  }
```

**[Solution](Solutions.md#exercise-7-lines-that-cause-compile-errors)**

---

<br>

## Exercise 8: Printing Out-of-Range Values

**Textbook Problem:** Chapter 3 exercise 8

**Problem:** Write the output of the following program.

```c
#include <stdio.h>
#include <limits.h>

int main(void)
{
    char a = CHAR_MIN - 1;     // CHAR_MIN is defined as -128
    short b = SHRT_MIN - 1;    // SHRT_MIN is defined as -32768
    char ch = '\t';

    printf("%d, %d, %x\n", a, b, ch);
}
```

**[Solution](Solutions.md#exercise-8-printing-out-of-range-values)**

---

<br>

## Exercise 9: Area and Perimeter of a Square

**Textbook Problem:** Chapter 3 programming assignment 1

**Problem:** Write a program that reads the length of one side and computes the area and perimeter of the square.

**Sample Run:**

```text
한 변의 길이 ? 5
정사각형의 넓이: 25
정사각형의 둘레: 20
```

**[Solution](Solutions.md#exercise-9-area-and-perimeter-of-a-square)**

---

<br>

## Exercise 10: Area and Perimeter of a Rectangle

**Textbook Problem:** Chapter 3 programming assignment 2

**Problem:** Write a program that reads the width and the height and computes the area and perimeter of the rectangle.

**Sample Run:**

```text
가로의 길이? 10
세로의 길이? 20
직사각형의 넓이: 200
직사각형의 둘레: 60
```

**[Solution](Solutions.md#exercise-10-area-and-perimeter-of-a-rectangle)**

---

<br>

## Exercise 11: Computing Potential Energy

**Textbook Problem:** Chapter 3 programming assignment 3

**Problem:** Write a program that reads a mass and a height and computes the potential energy. The mass is entered in kg and the height in m, and the potential energy is 9.8 × mass × height.

**Sample Run:**

```text
질량(kg)? 10
높이(m)? 5
위치에너지: 490.00 J
```

> **Note:** The mass and the height may also be entered as real numbers. To read a `float` variable, use the format specifier `%f`, and to read a `double` variable, use `%lf`. If the fractional part is omitted in the input, it is taken to be 0.

**[Solution](Solutions.md#exercise-11-computing-potential-energy)**

---

<br>

## Exercise 12: Area of a Right Triangle

**Textbook Problem:** Chapter 3 programming assignment 4

**Problem:** Write a program that reads the base and the height and computes the area of the right triangle.

**Sample Run:**

```text
밑변과 높이? 3 7
직각삼각형의 면적: 10.50
```

**[Solution](Solutions.md#exercise-12-area-of-a-right-triangle)**

---

<br>

## Exercise 13: Converting Dollars to Won

**Textbook Problem:** Chapter 3 programming assignment 5

**Problem:** Write a program that reads the won/dollar exchange rate and an amount in dollars and prints how many won it is.

**Sample Run:**

```text
USD? 150
원/달러 환율? 1210
USD 150 = KRW 181500.00
```

**[Solution](Solutions.md#exercise-13-converting-dollars-to-won)**

---

<br>

## Exercise 14: Converting Won to Dollars

**Textbook Problem:** Chapter 3 programming assignment 6

**Problem:** Write a program that reads the won/dollar exchange rate and an amount in won and prints how many dollars it is.

**Sample Run:**

```text
KRW? 500000
원/달러 환율? 1210
KRW 500000 = USD 413.22
```

**[Solution](Solutions.md#exercise-14-converting-won-to-dollars)**

---

<br>

## Exercise 15: Converting Yards to Meters

**Textbook Problem:** Chapter 3 programming assignment 7

**Problem:** Write a program that reads a length in yards (yd), converts it to meters (m), and prints it. 1 yd equals 0.9144 m.

**Sample Run:**

```text
길이(yd)? 100
100 yd = 91.440000 m
```

**[Solution](Solutions.md#exercise-15-converting-yards-to-meters)**

---

<br>

## Exercise 16: Converting Inches to Centimeters

**Textbook Problem:** Chapter 3 programming assignment 8

**Problem:** Write a program that reads a length in inches (in) and converts it to centimeters (cm). 1 in equals 2.54 cm. Use a macro constant in the program.

**Sample Run:**

```text
길이(in)? 10
10.00 in = 25.40 cm
```

**[Solution](Solutions.md#exercise-16-converting-inches-to-centimeters)**

---

<br>

## Exercise 17: Converting Square Meters to Pyeong

**Textbook Problem:** Chapter 3 programming assignment 9

**Problem:** Write a program that reads the area of an apartment in square meters (m²) and prints how many pyeong it is. 1 m² equals 0.3025 pyeong. Use a symbolic constant in the program.

**Sample Run:**

```text
아파트의 면적(제곱미터)? 113
113.00 제곱미터 = 34.18 평
```

**[Solution](Solutions.md#exercise-17-converting-square-meters-to-pyeong)**

---

<br>

## Exercise 18: Square and Cube of a Real Number

**Textbook Problem:** Chapter 3 programming assignment 10

**Problem:** Write a program that reads a real number and prints its square and cube. Allow the real number to be entered both in decimal notation, as in 12.34, and in exponent notation, as in 1.234e2, and print the square and the cube in exponent notation.

**Sample Run:**

```text
실수? 3.0e-1
제곱: 9.000000e-02
세제곱: 2.700000e-02
```

**[Solution](Solutions.md#exercise-18-square-and-cube-of-a-real-number)**
