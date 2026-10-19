# Chapter 2 — C Program Basics

[Repository Guide](../../README.md) | [English](Concepts_Lecture.md) | [한국어](Concepts_Lecture.ko.md)

> **Last Updated:** 2026-10-19
>
> Warming-Up C Programming, 천정아, Ch 2

> **Learning Objectives:**
> 1. Explain the basic structure of a C program and the roles of comments, the `main` function, and the exit code
> 2. Explain the parts of a function and the flow of calling a function and returning from it
> 3. Print values using the format string, format specifiers, field width, and precision of `printf`
> 4. Read one or more values with `scanf` and explain why `&` is required
> 5. Declare, assign, and initialize variables and use them for input and output

---

## Table of Contents

- [1. First C Program](#1-first-c-program)
  - [1.1 Program Structure](#11-program-structure)
  - [1.2 Comments](#12-comments)
  - [1.3 `main` Function](#13-main-function)
  - [1.4 Exit Code](#14-exit-code)
- [2. Input and Output](#2-input-and-output)
  - [2.1 Console I/O](#21-console-io)
  - [2.2 `printf`](#22-printf)
  - [2.3 `scanf`](#23-scanf)
  - [2.4 Variables in I/O](#24-variables-in-io)
- [3. C Statements](#3-c-statements)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. First C Program

### 1.1 Program Structure

Every C program follows a basic structure. Here is the simplest complete program, annotated line by line.

```c
// first.c
#include <stdio.h>    // I/O library header

int main(void)        // entry point function
{
    printf("First C Program\n");  // console output
    return 0;         // exit code to OS
}
```

```text
C Program Structure
├── Preprocessor Directives   #include <stdio.h>
├── main Function             int main(void) { ... }
│   ├── Statements            printf("...\n");
│   └── Return Statement      return 0;
└── Other Functions           (Chapter 6)
```

*Figure 1. Structure of a C program*

| Part | Role |
|:-----|:-----|
| `#include <stdio.h>` | Prepare to use the standard I/O library so `printf` and `scanf` can be used |
| `int main(void)` | Define the entry point; the function called first when the program starts |
| `{ ... }` | Braces delimit the function body |
| `printf("...\n");` | Output a string to the console |
| `return 0;` | Return exit code 0 (normal termination) to the OS |

*Table 1. Parts of the first program and their roles*

> **Key Point:** Statements inside a function must end with a semicolon (`;`) (blocks enclosed in braces and the control statements of Chapter 5 are exceptions). Preprocessor directives (`#include`) do **not** end with a semicolon.

### 1.2 Comments

**Comments** provide information about the source code or keep part of the source code from being compiled. They are ignored by the compiler and exist solely for human readers.

| Style | Syntax | Scope |
|:------|:-------|:------|
| Block comment | `/* ... */` | Can span multiple lines |
| Line comment | `// ...` | From `//` to end of line |

*Table 2. The two kinds of comments in C*

The `//` line comment was added in C99 and is now available in most C compilers. A block comment can also be placed in the middle of code.

```c
/* This is a block comment.
   It can span multiple lines. */

// This is a line comment.

int x = 10;  // inline comment after code
```

**Commenting out code** means temporarily keeping code that has already been written from being compiled, without deleting it.

```c
/* printf("This line is disabled.\n"); */

// printf("This line is also disabled.\n");
```

> **Caution:** Block comments **cannot be nested**. `/* outer /* inner */ still inside? */` causes a compile error because `*/` closes the comment at the first match.

### 1.3 `main` Function

A C program consists of a single `main` function, or of `main` and several other functions. A **function** consists of the following three parts, and its body is made up of statements that end with semicolons (declarations, input, output, conditionals, loops, etc.).

| Part | Meaning | In `int main(void)` |
|:-----|:--------|:-----|
| Return type | The type of the value the function returns | `int` |
| Function name | The name that identifies the function | `main` |
| Parameters | The values needed to perform the function | `void` (none) |

*Table 3. Parts of a function*

When a function is called, the statements inside `{ }` are executed in order from the top. When execution reaches the end of the function (`}`) or a `return`, control goes back to where the function was called (the function returns).

The `main` function is the **entry point** of every C program. The entry point is the function agreed to be called when a C program first starts, so when the OS runs a compiled program, execution begins at `main`.

| Rule | Description |
|:-----|:------------|
| Exactly one `main` | Every program must have one and only one `main` function |
| Return type `int` | `main` returns an integer exit code to the OS |
| Parameter `void` | `void` means no arguments; parentheses can also be empty `()` |
| Case-sensitive | `main` is valid; `Main`, `MAIN`, `mAiN` are **not** the entry point |

*Table 4. Rules for the `main` function*

```c
int main(void)    // ✅ standard form
{
    return 0;
}
```

```c
int main()        // ✅ also valid (empty parameter list)
{
    return 0;
}
```

> **Key Point:** C is **case-sensitive**. `main` and `Main` are different identifiers. Only lowercase `main` is recognized as the entry point by the compiler.

### 1.4 Exit Code

The `return` statement in `main` sends an **exit code** (also called exit status) back to the operating system. The exit code is the return value of `main` (an `int`) and represents the program's termination status.

| Exit Code | Meaning |
|:---------:|:--------|
| `0` | Normal termination (success) |
| Non-zero | Abnormal termination (error) |

*Table 5. Meaning of exit codes*

```c
int main(void)
{
    printf("Hello\n");
    return 0;   // tell the OS: program finished successfully
}
```

The OS or a calling script can inspect this exit code to determine whether the program succeeded or failed.

> **Note:** **Omitting `return 0`.** In C99 and later, if `return` is omitted at the end of `main`, the compiler implicitly returns `0`. This exception applies only to `main`. However, it is good practice to write `return 0;` explicitly for clarity.

---

<br>

## 2. Input and Output

### 2.1 Console I/O

A **console program** runs in a console (command prompt): it takes input from the keyboard, processes it, and prints the result to the console as text. C does not have built-in I/O keywords. Instead, an **I/O library** provides the input and output features every C program needs, and programs perform I/O through **library functions** declared in **header files**.

```c
#include <stdio.h>   // stdio = standard input/output
```

| Term | Meaning |
|:-----|:--------|
| `#include` | Preprocessor directive that copies the contents of a header file into the source |
| `<stdio.h>` | Standard I/O header; provides `printf`, `scanf`, etc. |
| Standard input | Keyboard (default) |
| Standard output | Console/screen (default) |
| Header file | A file (`.h`) with information about library functions (name, return type, parameters), that is, the function declarations needed by the compiler |

*Table 6. Terms related to console I/O*

To use a library, its header file must be included with `#include`.

```text
┌──────────┐    stdin     ┌─────────┐    stdout    ┌──────────┐
│ Keyboard │ ──────────▶  │ Program │ ──────────▶  │  Screen  │
└──────────┘   (scanf)    └─────────┘   (printf)   └──────────┘
```

*Figure 2. Flow of standard input and standard output*

> **Key Point:** Without `#include <stdio.h>`, the compiler does not know the declarations of `printf` and `scanf`, and will report an error (or warning, depending on the standard).

### 2.2 `printf`

`printf` (print formatted) writes formatted output to the console. Besides printing strings, it can print values according to a format.

**Basic syntax:**

```c
printf("format string", value1, value2, ...);
```

The **format string** is written inside `" "` and can contain the following.
- Plain text is printed as-is.
- **Format specifiers**, made of `%` and an agreed character, are placeholders replaced by the corresponding values.
- **Escape sequences** represent special characters such as `\n`.

#### Format Specifiers

| Specifier | Type | Example |
|:---------:|:-----|:--------|
| `%d` | `int` (decimal) | `printf("%d", 42);` → `42` |
| `%f` | `float`/`double` | `printf("%f", 3.14);` → `3.140000` |
| `%c` | `char` (character) | `printf("%c", 'A');` → `A` |
| `%s` | string | `printf("%s", "hi");` → `hi` |
| `%x` | `int` (hexadecimal) | `printf("%x", 255);` → `ff` |
| `%X` | `int` (hexadecimal, uppercase) | `printf("%X", 255);` → `FF` |
| `%e` | `float`/`double` (scientific) | `printf("%e", 0.001);` → `1.000000e-03` |

*Table 7. Main format specifiers of `printf`*

`%F` and `%E` are the same as `%f` and `%e` but print characters such as infinity (`INF`) and the exponent sign (`E`) in uppercase. When a format string has several format specifiers, the specifiers and the values to print correspond in order, and their counts must match.

```c
int age = 20;
double height = 175.5;

printf("Age: %d\n", age);           // Age: 20
printf("Height: %f cm\n", height);  // Height: 175.500000 cm
printf("Height: %.1f cm\n", height); // Height: 175.5 cm
```

#### Field Width and Precision

A format specifier can include a **field width** and a **precision**. The width is written as an integer between `%` and `d` (`%6d`), and the value is printed right-aligned in that width. Writing `-` before the width (`%-6d`) left-aligns it. The precision is written as `.` and an integer between `%` and `f` (`%.2f`), and width and precision can be combined (`%8.2f`). Without a width, the value is printed from the left using only as many characters as it needs; without a precision, `%f` prints 6 digits after the decimal point.

```c
int num = 123;
double pi = 3.14159;

printf("[%d]\n", num);       // [123]
printf("[%6d]\n", num);      // [   123]   (width 6, right-aligned)
printf("[%-6d]\n", num);     // [123   ]   (width 6, left-aligned)
printf("[%f]\n", pi);        // [3.141590] (6 decimal places)
printf("[%.2f]\n", pi);      // [3.14]
printf("[%8.2f]\n", pi);     // [    3.14] (width 8, 2 decimal places)
```

Other formats such as zero padding (`%06d`) are covered in Chapter 3, Section 5.2.

#### Newline and Cursor Behavior

`printf` does **not** automatically move to the next line. The cursor stays at the end of the printed text. Use the newline character `\n` to print the text and then move the cursor to the next line.

```c
printf("Hello");
printf("World\n");
// Output: HelloWorld   (no space, no line break between them)
```

```c
printf("Line 1\n");
printf("Line 2\n");
// Output:
// Line 1
// Line 2
```

> **Note:** **Cursor position.** Multiple `printf` calls continue printing from the last cursor position of the previous output. Think of `printf` as appending to the current cursor position.

### 2.3 `scanf`

`scanf` (scan formatted) reads values typed on the keyboard in the console into variables according to a format.

**Basic syntax:**

```c
scanf("format string", &variable1, &variable2, ...);
```

The `&` (**address-of operator**) is required before each variable. `scanf` needs the memory address to store the input value.

```c
int num;
printf("Enter a number: ");
scanf("%d", &num);            // read an integer from keyboard
printf("You entered: %d\n", num);
```

#### Reading Multiple Values

```c
int a, b;
scanf("%d %d", &a, &b);  // user types: 10 20
// a = 10, b = 20
```

To read several values, write several format specifiers. The specifiers and the variables that receive input correspond in order, and their counts must match. Numeric specifiers such as `%d` and `%f` skip any leading whitespace (spaces, tabs, newlines) before reading, so whitespace acts as a delimiter between values. A space between format specifiers in the format string makes `scanf` ignore all whitespace in the input before reading the next item. This rule matters most before `%c`, which does not skip whitespace (`"%c %c"` reads `a` and `b` from `a b`, but `"%c%c"` reads `a` and a space).

```c
int day, month, year;
scanf("%d/%d/%d", &day, &month, &year);  // user types: 16/03/2026
// day = 16, month = 3, year = 2026
```

Ordinary characters such as `/` in the format string must match the same characters in the input.

> **Caution:** Forgetting `&` in `scanf` is a common beginner mistake. Without `&`, the program passes the **value** of the variable (likely garbage) instead of its **address**, causing undefined behavior or a crash.

#### Format Specifiers for `scanf`

| Specifier | Type | Example |
|:---------:|:-----|:--------|
| `%d` | `int` (read as decimal) | `scanf("%d", &n);` |
| `%x` | `int` (read as hexadecimal) | `scanf("%x", &n);` |
| `%i` | `int` (read as decimal, octal, or hexadecimal) | `scanf("%i", &n);` (`012` is octal, `0x12` is hexadecimal) |
| `%f` | `float` | `scanf("%f", &f);` |
| `%lf` | `double` | `scanf("%lf", &d);` |
| `%c` | `char` | `scanf("%c", &ch);` |
| `%s` | string (char array) | `scanf("%s", str);` (no `&` for arrays) |

*Table 8. Main format specifiers of `scanf`*

> **Key Point:** For `double`, `printf` uses `%f` but `scanf` uses `%lf`. This is a common source of bugs. Since C99, `%lf` in `printf` also behaves the same as `%f`.

> **Note:** **Visual Studio and `scanf`.** Visual Studio 2022 treats `scanf` as an unsafe function and reports a compile error (C4996) under its default settings. The `scanf_s` it recommends instead is defined in Annex K, an optional part of C11, so the standard libraries of gcc and clang usually do not have it. To use `scanf` intentionally according to standard C (ANSI C), write `#define _CRT_SECURE_NO_WARNINGS` at the very top of the source file (before any `#include`) so that no error occurs.

### 2.4 Variables in I/O

A **variable** is a space for storing a value. The computer stores values in memory; memory stores values one byte at a time and identifies each byte by its **address**. A variable gives a name to a memory space so that it can be accessed by name instead of by address. A **data type** is the kind of data used in a program, such as `char`, `int`, or `float`, and it determines the size of the memory space needed (`char` is 1 byte; `int` and `float` are usually 4 bytes) and the meaning of the value stored in memory (Chapter 3).

Variables must be **declared** before they can be used in `printf` or `scanf`.

**Declaration** tells the compiler the variable's type and name.

```c
int count;       // declare an integer variable
double price;    // declare a floating-point variable
```

A variable name is made of letters, digits, and the underscore (`_`), and its first character must be a letter or an underscore (Chapter 3, Section 3.2). **Assignment** stores a value in a variable. Write `=` after the variable name followed by the value, and assign a value of the same type as the variable's data type.

```c
count = 5;
price = 19.99;
```

Unlike the equals sign in mathematics, the `=` of C is the **assignment operator**, which stores the value on its right (R-value) in the memory space of the variable written on its left (L-value). **Declaration + initialization** declares and assigns in one statement.

```c
int count = 5;
double price = 19.99;
```

**Using variables with `printf` and `scanf`:**

```c
#include <stdio.h>

int main(void)
{
    int quantity;
    double unit_price;

    printf("Enter quantity and unit price: ");
    scanf("%d %lf", &quantity, &unit_price);   // input

    double total = quantity * unit_price;

    printf("Quantity: %d\n", quantity);          // output
    printf("Unit Price: %.2f\n", unit_price);
    printf("Total: %.2f\n", total);

    return 0;
}
```

> **Note:** **Tip on initializing variables.** Always initialize variables before using them. Uninitialized local variables hold garbage values and cause unpredictable results.

---

<br>

## 3. C Statements

A C program is composed of **statements**. A statement is the basic unit of a C program, an instruction that the computer executes in order, and statements such as declarations, input, output, and assignments end with a semicolon (`;`).

| Statement Type | Purpose | Example | Covered In |
|:---------------|:--------|:--------|:-----------|
| Declaration | Create a variable | `int x;` | Chapter 2 |
| Input | Read data from keyboard | `scanf("%d", &x);` | Chapter 2 |
| Output | Display data to screen | `printf("%d", x);` | Chapter 2 |
| Assignment | Store a value | `x = 10;` | Chapter 2 |
| Conditional | Execute code based on condition | `if (x > 0) { ... }` | Chapter 5 |
| Loop | Repeat code | `for (i = 0; i < 10; i++) { ... }` | Chapter 5 |
| Function call | Call another function | `result = add(a, b);` | Chapter 6 |

*Table 9. Kinds of C statements and the chapters that cover them*

```c
int main(void)
{
    int a, b, sum;            // declaration statements
    scanf("%d %d", &a, &b);  // input statement
    sum = a + b;              // assignment statement
    printf("%d\n", sum);      // output statement
    return 0;                 // return statement
}
```

Statements execute **sequentially**, from top to bottom, one after another. Execution proceeds in order unless a control statement (conditional or loop) changes the flow. Blocks enclosed in braces and control statements such as `if` and `for` do not end with a semicolon.

> **Note:** Conditional (`if`, `switch`) and loop (`for`, `while`, `do-while`) statements are introduced briefly here for awareness. Detailed coverage is in Chapter 5.

---

<br>

## Summary

| Concept | Key Summary |
|:--------|:-------------|
| Program Structure | A C program consists of `#include`, the `main` function, statements, and `return`. |
| Comments | There are two kinds, `/* block */` and `// line` (C99), and block comments cannot be nested. |
| Functions | A function consists of a return type, a name, and parameters, and returns to its caller at `}` or `return`. |
| `main` Function | It is the single entry point per program, returns `int`, and its name is case-sensitive. |
| Exit Code | `return 0` means success and a non-zero value means an error, and since C99 it can be omitted only in `main`. |
| `#include <stdio.h>` | The standard I/O header must be included to use `printf` and `scanf`. |
| `printf` | It produces formatted output with `%d`, `%f`, `%c`, `%s`, `%x`, `%e`, and others, and the cursor stays after the last character. |
| Field Width and Precision | `%6d` right-aligns, `%-6d` left-aligns, and `%.2f` prints 2 digits after the decimal point. |
| `\n` | It is the newline escape sequence, and `printf` does not start a new line automatically. |
| `scanf` | It reads formatted input, needs `&` (address-of) before each variable, and reads `double` with `%lf`. |
| Variables | A variable is a named memory space that must be declared before use and initialized to avoid garbage values. |
| Statements | Declarations, input, output, assignments, and similar statements end with a semicolon and execute sequentially from top to bottom. |

---

<br>

## Self-Check Questions

1. **Cursor behavior:** Write the output of the following code line by line.

   ```c
   printf("A");
   printf("B\n");
   printf("C\n");
   ```

   <details>
   <summary>Answer</summary>

   The first line is `AB` and the second line is `C`. `printf("A")` does not end the line, so the `B` of the next `printf` is printed on the same line, and the cursor moves to the next line only after `\n`.

   </details>

2. **Mistakes with `scanf`:** Find and fix the two errors in the following code.

   ```c
   double d;
   scanf("%f", d);
   ```

   <details>
   <summary>Answer</summary>

   A `double` must be read with `%lf` in `scanf`, and `&` must be placed before the variable so that the address for storing the value is passed. The corrected code is `scanf("%lf", &d);`.

   </details>

3. **Field width and precision:** Write the output of `printf("[%5d][%-5d][%7.3f]\n", 42, 42, 3.14159);`.

   <details>
   <summary>Answer</summary>

   It is `[   42][42   ][  3.142]`. `%5d` right-aligns in 5 columns with 3 spaces in front, and `%-5d` left-aligns with 3 spaces after. `%7.3f` rounds 3.14159 to 3 decimal places as `3.142` (5 characters) and right-aligns it in 7 columns, so 2 spaces come first.

   </details>

4. **Functions and exit codes:** What happens when `main` reaches `return 0;`? What happens if `return` is omitted?

   <details>
   <summary>Answer</summary>

   The `main` function ends, and exit code 0 is passed to the operating system to report that the program terminated normally. Since C99, reaching the end (`}`) of `main` returns 0 just like `return 0;`, so it can be omitted, but this exception applies only to `main`.

   </details>
