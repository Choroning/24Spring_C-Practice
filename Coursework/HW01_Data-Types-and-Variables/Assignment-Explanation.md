# HW1 Assignment Explanation — Data Types and Variables

[Repository Guide](../../README.md) | [English](Assignment-Explanation.md) | [한국어](Assignment-Explanation.ko.md)

> **Last Updated:** 2026-10-27
>
> 문제풀이 중심의 C언어 연습, 김용일과 강문설, Ch 2, 3

> **Learning Objectives:**
> 1. Explain the stages from source code to an executable and the concepts of variables and ASCII codes
> 2. Declare an integer variable, assign or initialize its value, and print it
> 3. Print the same integer value with `%d` and `%c` and explain the relationship between ASCII codes and characters
> 4. Match an output format with format specifiers that set field width, alignment, and zero padding
> 5. Perform the four arithmetic operations and the remainder operation on values stored in variables and explain the result of integer division

**Problem Source:** Prof. Jonguk Lee, Computer Language and Training Ⅰ (DCCS103-03)

---

## Table of Contents

- [1. Assignment Layout and How to Run](#1-assignment-layout-and-how-to-run)
- [2. Written Questions](#2-written-questions)
  - [2.1 Stages of Building an Executable](#21-stages-of-building-an-executable)
  - [2.2 Variables](#22-variables)
  - [2.3 ASCII Code](#23-ascii-code)
- [3. Coding Problems](#3-coding-problems)
  - [3.1 Q1. Variable Practice (1)](#31-q1-variable-practice-1)
  - [3.2 Q2. Variable Practice (2)](#32-q2-variable-practice-2)
  - [3.3 Q3. Variable Practice (3)](#33-q3-variable-practice-3)
  - [3.4 Q4. Variable Practice (4)](#34-q4-variable-practice-4)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Assignment Layout and How to Run

This assignment practices declaring, initializing, and assigning variables and the format specifiers of `printf`, covered in Chapters 2 and 3. It consists of three written questions and four coding problems (Q1-Q4), and the coding problems require submitting a code analysis and a screenshot of the output along with the code. Q2 is textbook problem 2-6, and Q3 is textbook problem 3-4.

```text
Coursework/HW01_Data-Types-and-Variables/
├── Assignment-Explanation.ko.md
├── Assignment-Explanation.md
└── Solution/
    ├── Q1.c    # declaring, assigning, and printing a variable
    ├── Q2.c    # printing an integer and its ASCII character
    ├── Q3.c    # field width, alignment, zero padding
    └── Q4.c    # arithmetic and remainder operations
```

*Figure 1. Directory layout of Assignment 1*

Compile and run each solution as follows. All four files compile without warnings with `gcc -std=c99 -Wall` on Apple clang 21 on macOS.

```bash
cd Coursework/HW01_Data-Types-and-Variables/Solution
gcc -std=c99 -Wall -o q1 Q1.c
./q1
```

The last line of each sample run, `Program ended with exit code: 0`, is not printed by the program; it is a message Xcode shows in the console after the program ends. None of the four solutions has a `return` statement in `main`, but since C99 reaching the end of `main` returns 0, so every exit code is 0 ([Chapter 2, Section 1.4](../../Lecture-Notes/Ch02_C-Program-Basics/Concepts_Lecture.md#14-exit-code)). The four solutions also define `main` with empty parentheses, as in `int main()`; this is a valid definition, and adding `-Wextra -pedantic` only makes clang issue a `-Wstrict-prototypes` warning without affecting behavior.

---

<br>

## 2. Written Questions

### 2.1 Stages of Building an Executable

**Problem:** Explain each stage that source code goes through to become an executable.

**Explanation:** Source code becomes an executable through four stages: preprocessing, compiling, assembling, and linking.

| Stage | What It Does | Result |
|:-----|:-----|:-----|
| Preprocessing | The preprocessor inserts the contents of header files named by `#include`, replaces `#define` macros, and removes comments | Preprocessed source (`.i`) |
| Compiling | The compiler checks syntax and types and translates C code into assembly code | Assembly source (`.s`) |
| Assembling | The assembler converts assembly code into machine code | Object file (`.o`; `.obj` in Visual Studio) |
| Linking | The linker combines the object files with the code of library functions such as `printf` and resolves external references | Executable (`.exe`) |

*Table 1. Stages from source code to an executable*

In Visual Studio, a single build command runs all four stages. An object file is produced only when there are no errors up to the compiling stage, and an executable only when there are no errors up to the linking stage. The detailed process is summarized in [Chapter 1, Section 3.2](../../Lecture-Notes/Ch01_Programming-and-C-Language/Concepts_Lecture.md#32-build-process).

### 2.2 Variables

**Problem:** What is a variable?

**Explanation:** A **variable** is a memory space given a name for storing a value, and its value can change while the program runs. The computer accesses each byte of memory by its address, but when writing code the programmer accesses the space by the variable's name instead of the address. A variable must be declared with a data type and a name before use, and the data type determines how much memory the variable occupies (`int` is usually 4 bytes) and how the stored bits are interpreted. Giving a value at the moment of declaration is called **initialization**, and storing a value in an existing variable with `=` is called **assignment**. See [Chapter 2, Section 2.4](../../Lecture-Notes/Ch02_C-Program-Basics/Concepts_Lecture.md#24-variables-in-io) and [Chapter 3, Section 3](../../Lecture-Notes/Ch03_Data-Types-and-Variables/Concepts_Lecture.md#3-variables) for details.

### 2.3 ASCII Code

**Problem:** What is ASCII code?

**Explanation:** **ASCII (American Standard Code for Information Interchange)** is a 7-bit character code that assigns an integer code to each character. Its 128 codes from 0 to 127 consist of 33 control characters (0-31 and 127) and 95 printable characters (32-126). For example, `'A'` is 65, `'a'` is 97, and `'0'` is 48. Storing a character in a C `char` variable actually stores its ASCII code, so printing the same value with `%d` gives the code and with `%c` gives the character. See [Chapter 3, Section 1.3](../../Lecture-Notes/Ch03_Data-Types-and-Variables/Concepts_Lecture.md#13-character-type) for details.

---

<br>

## 3. Coding Problems

### 3.1 Q1. Variable Practice (1)

**Problem:** Referring to the sample run, write code that performs the following steps.

- (a) Declare a variable that can hold an integer
- (b) Assign the integer data `2020` to the variable
- (c) Print the information assigned to the variable

**Sample Run:**

```text
data: 2020

Program ended with exit code: 0
```

**Approach:** Because the problem presents declaration, assignment, and printing as separate steps, the solution writes a declaration and an assignment statement separately instead of an initialization (`int data = 2020;`).

- (a) Declaring an integer variable with `int data;` reserves a memory space for an integer (usually 4 bytes) and names it `data`. At this point its value is an undetermined garbage value.
- (b) The assignment operator `=` stores the value 2020 on its right in the memory space of the variable `data` on its left.
- (c) In the format string `"data: %d"` of `printf`, `%d` is replaced by the value stored in `data`, so `data: 2020` is printed.

**Code:** [Solution/Q1.c](Solution/Q1.c)

```c
/**
 * @file    A10303-1_C03Q1.c
 * @brief   Q1. 변수 연습 (1)
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-13
 */

#include <stdio.h>

int main()
{
	int data;
	data = 2020;
	printf("data: %d", data);
}
```

**Actual Output:**

```text
data: 2020
```

The output matches the first line of the sample run. The format string has no `\n` at the end, so the line does not end after the output, and when the program runs in a terminal, the shell prompt appears right after `data: 2020`.

**Edge cases:** Calling `printf` before the assignment in (b) would read an uninitialized local variable and print a garbage value, which is undefined behavior. 2020 is within the range of `int` (-2,147,483,648 to 2,147,483,647), so no overflow occurs.

### 3.2 Q2. Variable Practice (2)

**Problem:** Write a program that initializes the variable `val` to an arbitrary integer between 0 and 255 and prints the value stored in the variable and the corresponding ASCII character.

**Sample Run:**

```text
val 98의 ASCII에 해당하는 문자: b

Program ended with exit code: 0
```

**Reference:** In the sample above, `val` is initialized to `98`, and the printed `98` and the character `b` are the information stored in `val`. (The output text means "The character corresponding to ASCII of val 98: b".)

**Approach:** `int val = 65;` declares the variable and gives it a value at the same time (initialization). The same variable is passed to `printf` twice with different format specifiers. `%d` prints the value as a decimal integer, and `%c` converts the `int` argument to `unsigned char` and prints the single character with that code. So although only one value is stored, both the integer 65 and the character `A` are printed.

**Code:** [Solution/Q2.c](Solution/Q2.c)

```c
/**
 * @file    A10303-1_C03Q2.c
 * @brief   Q2. 변수 연습 (2)
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-13
 */

#include <stdio.h>

int main()
{
	int val = 65;
	printf("val %d의 ASCII에 해당하는 문자: %c", val, val);
}
```

**Actual Output:**

```text
val 65의 ASCII에 해당하는 문자: A
```

The sample run initializes `val` to 98 and the solution initializes it to 65, so the number and character differ. The problem allows any value between 0 and 255, so both meet the requirement, and changing the solution's initial value to 98 prints `val 98의 ASCII에 해당하는 문자: b`, exactly the same as the sample run.

**Edge cases:**

- ASCII defines codes 0-127. Of these, only 32-126 are visible characters; 0-31 and 127 are control characters, so printing them with `%c` acts like a newline (10) or tab (9), or shows nothing.
- 128-255 are not ASCII values, so the output depends on the terminal's character encoding. In a UTF-8 terminal, this single byte is not a valid character and appears as a broken character.
- The source file is saved in UTF-8, so the Korean text in the format string prints correctly in UTF-8 terminals on macOS and Linux, but it may be garbled in a Windows console whose code page is CP949.

### 3.3 Q3. Variable Practice (3)

**Problem:** Referring to the sample run and the figure, initialize the integer variables `no`, `in`, and `out` and print them.

![Figure 2. Output columns and alignment of variables no, in, and out](../../images/HW01_Output-Format.png)

*Figure 2. Output columns and alignment of variables no, in, and out*

Print the variables `no`, `in`, and `out` so that they occupy 5, 6, and 6 columns in that order, aligned right, left, and right, respectively, and fill the empty columns of `out` with 0 as in the sample run.

**Sample Run:**

```text
   34124   000512

Program ended with exit code: 0
```

**Approach:** Read the initial values `no` = 34, `in` = 124, and `out` = 512 from the digits in the figure's columns, and specify the field width, alignment, and zero padding together in each format specifier ([Chapter 3, Section 5.2](../../Lecture-Notes/Ch03_Data-Types-and-Variables/Concepts_Lecture.md#52-width-and-alignment)).

| Variable | Format Specifier | Meaning | Output |
|:-----|:-----|:-----|:-----|
| `no` | `%5d` | Width 5, right-aligned (default) | `␣␣␣34` |
| `in` | `%-6d` | Width 6, left-aligned | `124␣␣␣` |
| `out` | `%06d` | Width 6, right-aligned, empty columns filled with 0 | `000512` |

*Table 2. Format specifiers and output in Q3 (␣ is a space)*

The three format specifiers are written back to back without spaces in a single format string `"%5d%-6d%06d"`, so 5 + 6 + 6 = 17 characters are printed on one line. The three trailing spaces of `in` create the gap between `124` and `000512`.

**Code:** [Solution/Q3.c](Solution/Q3.c)

```c
/**
 * @file    A10303-1_C03Q3.c
 * @brief   Q3. 변수 연습 (3)
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-13
 */

#include <stdio.h>

int main()
{
	int no = 34;
	int in = 124;
	int out = 512;

	printf("%5d%-6d%06d", no, in, out);
}
```

**Actual Output:**

```text
   34124   000512
```

The output matches the first line of the sample run character for character, including the three leading spaces.

**Edge cases:**

- The field width is a minimum width. If a value has more digits than the width, it is printed in full without truncation, so if `no` were 123456, `%5d` would print `123456` and break the alignment.
- When `-` and `0` are used together, `0` is ignored. `%-06d` is the same as `%-6d`, and gcc and clang warn about this combination.
- When a negative number is zero-padded, the sign comes first. If `out` were -512, `%06d` would print `-00512`.

### 3.4 Q4. Variable Practice (4)

**Problem:** Declare two variables `vOne` and `vTwo`, initialize them to `13` and `3`, and, referring to the sample run, write code that performs and prints the four arithmetic operations. Do not print by inserting integer values directly inside the `printf` statements.

**Sample Run:**

```text
13 + 3 = 16
13 - 3 = 10
13 * 3 = 39
13 / 3 = 4
13 % 3 = 1

Program ended with exit code: 0
```

**Approach:** Both operands and the result are printed through variables and expressions, so no integer literal appears inside `printf`. Each line uses three format specifiers and passes `vOne`, `vTwo`, and the result in order, and the result is computed directly in the argument position, as in `vOne + vTwo`.

- Both operands are `int`, so `/` is integer division. The fractional part of 13 / 3 = 4.33... is discarded, giving 4.
- `%` is the remainder operator, and 13 % 3 is 1. The two results satisfy (13 / 3) × 3 + 13 % 3 = 4 × 3 + 1 = 13.
- In a format string, `%` marks the start of a format specifier, so to print the character `%` itself, write `%%`.

**Code:** [Solution/Q4.c](Solution/Q4.c)

```c
/**
 * @file    A10303-1_C03Q4.c
 * @brief   Q4. 변수 연습 (4)
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-13
 */

#include <stdio.h>

int main()
{
	int vOne = 13;
	int vTwo = 3;

	printf("%d + %d = %d\n", vOne, vTwo, vOne + vTwo);
	printf("%d - %d = %d\n", vOne, vTwo, vOne - vTwo);
	printf("%d * %d = %d\n", vOne, vTwo, vOne * vTwo);
	printf("%d / %d = %d\n", vOne, vTwo, vOne / vTwo);
	printf("%d %% %d = %d\n", vOne, vTwo, vOne % vTwo);
}
```

**Actual Output:**

```text
13 + 3 = 16
13 - 3 = 10
13 * 3 = 39
13 / 3 = 4
13 % 3 = 1
```

All five lines match the sample run. Unlike Q1-Q3, every format string has a `\n`, so each result is printed on its own line.

**Edge cases:**

- If `vTwo` were 0, `/` and `%` would divide by zero, which is undefined behavior. Check the divisor first if it can be 0.
- Since C99, integer division truncates toward zero, so if `vOne` were -13, -13 / 3 would be -4 and -13 % 3 would be -1. The sign of the remainder follows the left operand.
- `%` can be used only with integer types. If a floating-point quotient is needed, cast as in `(double)vOne / vTwo` ([Chapter 3, Section 6.2](../../Lecture-Notes/Ch03_Data-Types-and-Variables/Concepts_Lecture.md#62-explicit-conversion-casting)).

---

<br>

## Summary

| Concept | Key Summary |
|:-----|:-----|
| Build Stages | Source code becomes an executable through preprocessing, compiling, assembling, and linking. |
| Variables | A variable is a named memory space for storing a value, declared with a data type and a name before use. |
| Declaration, Assignment, Initialization | Q1 assigns with `=` after the declaration, and Q2-Q4 initialize at the declaration. |
| ASCII Code | ASCII is a 7-bit code that assigns each character an integer code from 0 to 127, and 32-126 are the printable characters. |
| `%d` and `%c` | For the same integer value, `%d` prints it in decimal and `%c` prints the character with that code. |
| Field Width and Alignment | `%5d` right-aligns, `%-6d` left-aligns, `%06d` zero-pads, and the width is a minimum width. |
| Integer Division and Remainder | `/` between `int` values discards the fractional part, `%` gives the remainder, and `%%` prints the character `%`. |
| Exit Code | Since C99, reaching the end of `main` returns 0, so the exit codes of all four solutions are 0. |

---

<br>

## Self-Check Questions

1. **`%d` and `%c`:** What is printed if the initial value in Q2 is changed to 48?

   <details>
   <summary>Answer</summary>

   `val 48의 ASCII에 해당하는 문자: 0` is printed. `%d` prints 48 in decimal, and `%c` prints the digit character `'0'`, whose ASCII code is 48.

   </details>

2. **Field width and alignment:** Write the output of `printf("[%4d][%-4d][%04d]", 7, 7, 7);`.

   <details>
   <summary>Answer</summary>

   It is `[   7][7   ][0007]`. `%4d` right-aligns in 4 columns with 3 spaces in front, `%-4d` left-aligns with 3 spaces after, and `%04d` fills the 3 leading spaces with 0.

   </details>

3. **Integer division and remainder:** If `vOne` is changed to 17 and `vTwo` to 5 in Q4, what are the results on the `/` and `%` lines?

   <details>
   <summary>Answer</summary>

   They are `17 / 5 = 3` and `17 % 5 = 2`. Integer division discards the fractional part of 3.4, giving 3, and the remainder is 17 - 3 × 5 = 2.

   </details>

4. **`%%`:** What goes wrong if the last `printf` in Q4 uses a single `%` instead of `%%`?

   <details>
   <summary>Answer</summary>

   `printf` interprets `%` as the start of a format specifier, so it tries to read the `% %` in `"%d % %d = %d\n"` as a format specifier. That is not a valid format specifier, so the result is undefined in the C standard. When run on macOS, `% %` is printed as a single `%` and the following `d` remains an ordinary character, so `13 %d = 3` is printed; the format specifiers and arguments fall out of step, and the last argument is not used. clang warns about the unused argument. To print the character `%`, write `%%`.

   </details>

5. **Uninitialized variable:** What is printed if the line `data = 2020;` is deleted from Q1?

   <details>
   <summary>Answer</summary>

   `data` is an uninitialized local variable, so a garbage value is read and the output cannot be predicted. This is undefined behavior, and the compiler may warn that an uninitialized variable is used (Visual Studio may even treat it as a compile error).

   </details>
