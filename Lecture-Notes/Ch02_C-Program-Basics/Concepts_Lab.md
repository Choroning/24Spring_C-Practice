# Chapter 2 Lab — Printing Strings and Variables

[Repository Guide](../../README.md) | [English](Concepts_Lab.md) | [한국어](Concepts_Lab.ko.md)

> **Last Updated:** 2026-10-27
>
> 문제풀이 중심의 C언어 연습, 김용일과 강문설, Ch 2

> **Learning Objectives:**
> 1. Distinguish characters that look like numbers from numbers that can be computed, based on the fact that `printf` prints the string inside double quotes as it is
> 2. Explain a variable as a memory area that holds data and state the memory size each data type needs
> 3. Distinguish declaration, initialization, and assignment of variables and explain the L-value and R-value of the assignment operator `=`
> 4. Print the results of computations by specifying with format specifiers where the values of variables are printed
> 5. Set the number of digits after the decimal point for real numbers and print the ASCII value of a character

---

## Table of Contents

- [1. Printing Strings](#1-printing-strings)
  - [1.1 Printing a String with printf](#11-printing-a-string-with-printf)
  - [1.2 Characters That Look Like Numbers and Computation](#12-characters-that-look-like-numbers-and-computation)
- [2. Variables](#2-variables)
  - [2.1 A Memory Area That Holds Data](#21-a-memory-area-that-holds-data)
  - [2.2 Data Types and Memory Sizes](#22-data-types-and-memory-sizes)
  - [2.3 Variable Declarations and Variable Names](#23-variable-declarations-and-variable-names)
  - [2.4 Initialization, Assignment, and Computation](#24-initialization-assignment-and-computation)
- [3. Printing the Results of Computations](#3-printing-the-results-of-computations)
  - [3.1 Variable Names Inside a String](#31-variable-names-inside-a-string)
  - [3.2 Format Specifiers](#32-format-specifiers)
- [4. Practice Problems](#4-practice-problems)
  - [4.1 Sum of Integer Variables](#41-sum-of-integer-variables)
  - [4.2 Sum and Difference of Real Variables](#42-sum-and-difference-of-real-variables)
  - [4.3 Setting the Digits After the Decimal Point](#43-setting-the-digits-after-the-decimal-point)
  - [4.4 The ASCII Value of a Character](#44-the-ascii-value-of-a-character)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Printing Strings

### 1.1 Printing a String with printf

The `printf` function prints the contents between the double quotes (`" "`) on the console screen as they are. `\n` is an escape sequence for a newline, so it does not appear as characters on the screen but makes the next output start on a new line ([Chapter 2, Section 2.2](Concepts_Lecture.md#22-printf)).

```c
#include <stdio.h>

int main(void)
{
    printf("2022년 3월 1학기 C언어 강의\n");
    printf("3 + 3 = 6\n");          // the characters 3, +, 3, =, 6 are printed as they are
    printf("2 + 6 = 5 \n");         // no calculation happens inside a string

    return 0;
}
```

```text
2022년 3월 1학기 C언어 강의
3 + 3 = 6
2 + 6 = 5 
```

### 1.2 Characters That Look Like Numbers and Computation

The second line of the program above prints `3 + 3 = 6`, but this is not the result of the computer adding. The `3`, `+`, `=`, and `6` inside the double quotes are all characters, and `printf` only sends those characters to the screen in order. That is why the mathematically wrong `2 + 6 = 5` of the third line is also printed without any error. Digits inside double quotes are thus not numbers that can be computed but **characters that look like numbers**.

To make the computer actually add, write the numbers outside the double quotes as an expression and indicate with the format specifier `%d` where the result is printed (Section 3.2).

```c
#include <stdio.h>

int main(void)
{
    printf("3 + 3 = 6\n");             // characters that look like numbers
    printf("3 + 3 = %d\n", 3 + 3);     // the integer 3 + 3 is computed, then printed

    return 0;
}
```

```text
3 + 3 = 6
3 + 3 = 6
```

The two lines of output are the same, but the 6 of the second line is the integer value computed from `3 + 3`. Changing the expression of the second line to `3 + 4` changes its output to 7, while the first line always prints 6 unless its string is edited.

---

<br>

## 2. Variables

### 2.1 A Memory Area That Holds Data

To compute numbers, a place is needed to keep the data for the computation and take it out again. The place where a computer keeps data is **memory**, and programming languages keep and use data in areas of memory.

> **Definition:** A **variable** is a memory area in which a program keeps data. A **variable declaration** tells the computer to secure a memory area for the data to be used.

In languages such as C, C++, and Java, the memory space for data must be secured before the data is used. That is, a variable must be declared before it is used ([Chapter 3, Section 3.1](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#31-declaration-and-initialization)).

### 2.2 Data Types and Memory Sizes

Data comes in kinds such as integers (`3`), real numbers (`3.2`), single characters (`'A'`, `'b'`), and strings (`"Hello"`), which are called **data types**. In C, the programmer must state clearly with keywords such as `int` and `double` what kind of data is used, and the computer secures memory of the size suited to that type.

| Kind of data | Keyword | Memory size |
|:-----|:-----|:-----|
| Integer | `int` | 4 bytes (32 bits) |
| Real number | `float` | 4 bytes (32 bits) |
| Real number | `double` | 8 bytes (64 bits) |
| One character | `char` | 1 byte (8 bits) |

*Table 1. Kinds of data, keywords, and memory sizes*

A **bit** is one cell of memory that holds a single 0 or 1, and a **byte** is a unit of 8 bits. So an `int` variable of 4 bytes represents one integer with 4 × 8 = 32 bits. A string is several characters joined together and is covered separately in Chapter 9.

> **Caution:** The sizes in the table are those of Visual Studio and most PC compilers today. The C standard fixes only that `char` is 1 byte and the minimum range each type must represent, so the size of `int` can differ between platforms ([Chapter 3, Section 1.1](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#11-integer-types)).

### 2.3 Variable Declarations and Variable Names

A program that computes `2 + 3 = 5` has three pieces of information, 2, 3, and the sum 5, so it needs three memory spaces that hold integers. Yet declaring only the type three times as `int;` would leave the programmer no way to reach that memory in the code, even if memory were secured. In fact, a declaration of only `int;` without a name creates no variable in C, and the compiler issues a warning.

When declaring a variable, a name is given to the memory space. At the time the program is written, the memory does not exist yet, so the programmer refers to memory spaces by variable names. When the program runs, memory is allocated to each variable, and the computer reaches that memory not by the variable name but by an automatically assigned **memory address**.

```c
int val_1;   // declares a variable and names it
int val_2;
int sum;
```

```text
 Variable name    Example address       Stored value
┌──────────┐    ┌──────────┐       ┌──────────┐
│  val_1   │ ─▶ │ 0xdefdd0 │ ─────▶│ garbage  │
├──────────┤    ├──────────┤       ├──────────┤
│  val_2   │ ─▶ │ 0xdefdc4 │ ─────▶│ garbage  │
├──────────┤    ├──────────┤       ├──────────┤
│  sum     │ ─▶ │ 0xdefdb8 │ ─────▶│ garbage  │
└──────────┘    └──────────┘       └──────────┘
```

*Figure 1. Names, memory addresses, and stored values of three variables that are only declared*

The addresses in the figure are examples that can change on each run. A local variable that is declared without a value holds an unknown value left over in that memory, a **garbage value**.

### 2.4 Initialization, Assignment, and Computation

There are two ways to put a value into a variable. Putting a value in while declaring the variable is **initialization**, and putting a value later into a variable already declared is **assignment**.

```c
int val_1 = 2;   // initialization: declaration and assignment at once
```

The `=` of C means something different from the equals sign of mathematics. In mathematics, `=` means that the left and right sides are equal, but in C, `=` is the **assignment operator**, which stores the value on the right in the memory area on the left. What comes on the left-hand side of `=` is the **L-value** and what comes on the right-hand side is the **R-value**, and the value of the R-value is always stored in the memory area the L-value refers to. That is why the L-value must be a variable that stands for a memory area, and a constant cannot be written on the left, as in `2 = val_1`.

```c
#include <stdio.h>

int main(void)
{
    int val_1 = 2;              // declaration with initialization
    int val_2 = 3;
    int sum;                    // declaration only: the value is indeterminate

    sum = val_1 + val_2;        // read 2 and 3, add them, assign 5 to sum
    printf("val_1 + val_2 = sum \n");                    // names inside a string are just characters
    printf("%d + %d = %d \n", val_1, val_2, sum);        // %d marks where each value is printed

    return 0;
}
```

`sum = val_1 + val_2;` runs in the following order.

1. Read the value 2 of `val_1` from memory.
2. Read the value 3 of `val_2` from memory.
3. Compute 2 + 3.
4. Store the result 5 in the memory area of `sum`. The garbage value that was in `sum` becomes 5.

---

<br>

## 3. Printing the Results of Computations

### 3.1 Variable Names Inside a String

Running the program of Section 2.4 prints the following. The first `printf` prints not `2 + 3 = 5` but the first line, `val_1 + val_2 = sum`.

```text
val_1 + val_2 = sum 
2 + 3 = 5 
```

`printf` only prints the string inside the double quotes one character at a time and does not recognize the `val_1` or `sum` inside it as variable names. To print the value of a variable, the position where the value is printed must be marked in the string with a special symbol, just as the newline character `\n` is.

### 3.2 Format Specifiers

A **format specifier** is a symbol that specifies where and in what format the value of a variable is printed, and it is also called a format letter. `printf("%d + %d = %d \n", val_1, val_2, sum);` is interpreted as follows ([Chapter 2, Section 2.2](Concepts_Lecture.md#22-printf)).

- **Format string:** A `%d` is written at each of the three places where a decimal integer is printed. `d` is the initial of decimal.
- **Arguments:** After the closing double quote, the values to print are written in the order of the format specifiers, separated by commas. The value of `val_1` goes in the first `%d`, the value of `val_2` in the second, and the value of `sum` in the third.

| Kind of data | Keyword in the declaration | Format specifier |
|:-----|:-----|:-----|
| Integer | `int` | `%d` (decimal), `%x` (hexadecimal) |
| Real number | `float`, `double` | `%f` (decimal notation), `%e` (exponent notation) |
| Character | `char` | `%c` |

*Table 2. Format specifiers by kind of data*

> **Caution:** If a format specifier and its argument do not match in type, for example printing a `double` value with `%d`, the behavior is undefined in the C standard, and a meaningless value is usually printed. The numbers of format specifiers and arguments must also be equal.

---

<br>

## 4. Practice Problems

The following problems practice printing the values of variables with format specifiers.

### 4.1 Sum of Integer Variables

**Problem:** Initialize the integer variables `a` and `b` to 20 and -5, and print the values of the two variables and their sum in the form `20 + -5 = 15`.

**Solution:** Write `%d` at the three places where values are printed, and pass the expression `a + b` as an argument instead of storing the sum in a variable. An expression used as an argument is computed before `printf` is called. `%d` prints a negative number with its sign.

```c
#include <stdio.h>

int main(void)
{
    int a = 20, b = -5;

    printf("%d + %d = %d\n", a, b, a + b);

    return 0;
}
```

```text
20 + -5 = 15
```

### 4.2 Sum and Difference of Real Variables

**Problem:** Initialize the variables `ave` and `sum`, which hold values with two digits after the decimal point, to 10.25 and 4.32, and print the sum and the difference of the two variables.

**Solution:** The values have fractions, so real-type variables are used and printed with the format specifier `%f`. Here `double`, which has higher precision, is used ([Chapter 3, Section 1.2](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#12-floating-point-types)).

```c
#include <stdio.h>

int main(void)
{
    double ave = 10.25, sum = 4.32;

    printf("%f + %f = %f\n", ave, sum, ave + sum);
    printf("%f - %f = %f\n", ave, sum, ave - sum);

    return 0;
}
```

```text
10.250000 + 4.320000 = 14.570000
10.250000 - 4.320000 = 5.930000
```

Unless specified otherwise, `%f` prints six digits after the decimal point, so `10.25` appears as `10.250000`.

### 4.3 Setting the Digits After the Decimal Point

**Problem:** Change the output of Section 4.2 so that only two digits after the decimal point appear, as in `10.25 + 4.32 = 14.57`.

**Solution:** Putting `.2` between `%` and `f` as `%.2f` prints two digits after the decimal point, rounding at the next digit ([Chapter 3, Section 5.2](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#52-width-and-alignment)). Change the two `printf` statements of the program in Section 4.2 as follows.

```c
printf("%.2f + %.2f = %.2f\n", ave, sum, ave + sum);
printf("%.2f - %.2f = %.2f\n", ave, sum, ave - sum);
```

```text
10.25 + 4.32 = 14.57
10.25 - 4.32 = 5.93
```

> **Note:** 10.25 - 4.32 is an operation on real numbers that are not exactly representable in binary, so the internal value is an approximation very close to 5.93. `%f` and `%.2f` round at the printed digit, so the difference is not visible, but it shows up with more digits, as in `%.17f` ([Chapter 3, Section 1.2](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#12-floating-point-types)).

### 4.4 The ASCII Value of a Character

**Problem:** Initialize the variable `ch` to an English letter (here `'A'`) and print the ASCII value of that letter. Writing the value directly in the string, as in `printf("'A'의 ASCII값은 65입니다! \n");`, is not allowed.

**Solution:** A `char` variable stores a character as the integer code of that character. So printing the same variable with `%c` gives the character, and printing it with `%d` gives the code value ([Chapter 3, Section 1.3](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#13-character-type)).

```c
#include <stdio.h>

int main(void)
{
    char ch = 'A';

    printf("%c의 ASCII값은 %d입니다!\n", ch, ch);   // the same value printed as a character and as an integer

    return 0;
}
```

```text
A의 ASCII값은 65입니다!
```

**ASCII (American Standard Code for Information Interchange)** is the American standard code that assigns the numbers 0-127 to English letters, digits, and symbols. The following is part of it.

| Decimal | Hex | Character | Decimal | Hex | Character | Decimal | Hex | Character |
|-----:|-----:|:---:|-----:|-----:|:---:|-----:|-----:|:---:|
| 32 | 0x20 | (space) | 64 | 0x40 | `@` | 96 | 0x60 | `` ` `` |
| 33 | 0x21 | `!` | 65 | 0x41 | `A` | 97 | 0x61 | `a` |
| 34 | 0x22 | `"` | 66 | 0x42 | `B` | 98 | 0x62 | `b` |
| 35 | 0x23 | `#` | 67 | 0x43 | `C` | 99 | 0x63 | `c` |
| 36 | 0x24 | `$` | 68 | 0x44 | `D` | 100 | 0x64 | `d` |
| 37 | 0x25 | `%` | 69 | 0x45 | `E` | 101 | 0x65 | `e` |
| 38 | 0x26 | `&` | 70 | 0x46 | `F` | 102 | 0x66 | `f` |

*Table 3. Part of the ASCII code values*

The codes of uppercase and lowercase letters differ by 32 (0x20), so `'a' - 'A'` is 32.

---

<br>

## Summary

| Concept | Key Summary |
|:-----|:-----|
| Printing strings | `printf` prints the string inside double quotes one character at a time as it is. |
| Characters that look like numbers | Digits inside double quotes are characters, so they are not computed. |
| Variable | A memory area that holds data; it must be declared before it is used. |
| Data type | A keyword such as `int`, `float`, `double`, or `char` that states the kind of data and determines the memory size. |
| Variable name | The name by which the programmer refers to a memory area; at run time the computer reaches it by its memory address. |
| Initialization | Putting a value into a variable while declaring it. |
| Assignment operator | `=` stores the value of the R-value in the memory area the L-value refers to. |
| Format specifier | Specifies where and in what format a value is printed; the arguments follow in order, separated by commas. |
| Digits after the decimal point | Specifying a precision, as in `%.2f`, prints the value rounded to that digit. |
| ASCII value | Printing a `char` variable with `%d` prints the code value of the character. |

---

<br>

## Self-Check Questions

1. **Strings and expressions:** `printf("5 * 4 = 20\n");` and `printf("5 * 4 = %d\n", 5 * 4);` print the same result. What is the difference between the two statements?

   <details>
   <summary>Answer</summary>

   The first statement only prints the characters `5 * 4 = 20` inside the double quotes and performs no multiplication. The second prints the integer 20, computed from the expression `5 * 4`, in the place of `%d`. If the numbers are changed to `5 * 5`, the first statement prints the edited string as it is, so the result can be wrong, whereas the second prints the computed 25.

   </details>

2. **L-value:** `val_1 = 2;` is valid, but `2 = val_1;` is a compile error. Explain why in terms of L-values and R-values.

   <details>
   <summary>Answer</summary>

   The assignment operator `=` stores the value of the R-value in the memory area the L-value refers to. `val_1` is a variable with a memory area, so it can be an L-value, but the constant 2 has no memory area to store a value in, so it cannot be an L-value.

   </details>

3. **Garbage values:** If only `int sum;` is declared and `printf("%d\n", sum);` is executed, what value is printed?

   <details>
   <summary>Answer</summary>

   An uninitialized local variable holds an unknown garbage value left over in that memory, so a different value can be printed on each run. This value is not one the program set and must not be used, so a variable is initialized or assigned a value before it is used.

   </details>

4. **Format specifiers:** Write a `printf` statement that prints the value 3.14159 of the `double` variable `x` as `3.14`. Also, when the `char` variable `c` holds `'a'`, what does `printf("%d", c);` print?

   <details>
   <summary>Answer</summary>

   `printf("%.2f\n", x);`. `%.2f` prints the value rounded to the second digit after the decimal point. The ASCII code of `'a'` is 97, so `printf("%d", c);` prints 97.

   </details>
