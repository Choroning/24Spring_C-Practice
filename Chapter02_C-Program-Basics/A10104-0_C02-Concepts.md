# Chapter 02 — C Program Basics

> **Last Updated:** 2026-03-16
>
> **Textbook Reference:** *Warming-Up C Programming, 2nd Edition* — Chapter 2

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

---

<br>

## 1. First C Program

### 1.1 Program Structure

Every C program follows a basic structure. Here is the simplest complete program, annotated line by line:

```c
// first.c
#include <stdio.h>    // I/O library header

int main(void)        // entry point function
{
    printf("First C Program\n");  // console output
    return 0;         // exit code to OS
}
```

```
C Program Structure
├── Preprocessor Directives   #include <stdio.h>
├── main Function             int main(void) { ... }
│   ├── Statements            printf("...\n");
│   └── Return Statement      return 0;
└── Other Functions           (defined later in the course)
```

| Part | Role |
|:-----|:-----|
| `#include <stdio.h>` | Include the standard I/O library so `printf` and `scanf` can be used |
| `int main(void)` | Define the entry point; OS calls this function first |
| `{ ... }` | Braces delimit the function body |
| `printf("...\n");` | Output a string to the console |
| `return 0;` | Return exit code 0 (normal termination) to the OS |

> **Key Point:** Every statement inside a function must end with a semicolon (`;`). Preprocessor directives (`#include`) do **not** end with a semicolon.

### 1.2 Comments

Comments are ignored by the compiler. They exist solely for human readers.

| Style | Syntax | Scope |
|:------|:-------|:------|
| Block comment | `/* ... */` | Can span multiple lines |
| Line comment | `// ...` | From `//` to end of line |

```c
/* This is a block comment.
   It can span multiple lines. */

// This is a line comment.

int x = 10;  // inline comment after code
```

**Commenting out code** — temporarily disable code without deleting it:

```c
/* printf("This line is disabled.\n"); */

// printf("This line is also disabled.\n");
```

> **Warning:** Block comments **cannot be nested**. `/* outer /* inner */ still inside? */` causes a compile error because `*/` closes the comment at the first match.

### 1.3 `main` Function

The `main` function is the **entry point** of every C program. When the OS runs a compiled program, execution begins at `main`.

| Rule | Description |
|:-----|:------------|
| Exactly one `main` | Every program must have one and only one `main` function |
| Return type `int` | `main` returns an integer exit code to the OS |
| Parameter `void` | `void` means no arguments; parentheses can also be empty `()` |
| Case-sensitive | `main` is valid; `Main`, `MAIN`, `mAiN` are **not** the entry point |

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

The `return` statement in `main` sends an **exit code** (also called exit status) back to the operating system.

| Exit Code | Meaning |
|:---------:|:--------|
| `0` | Normal termination (success) |
| Non-zero | Abnormal termination (error) |

```c
int main(void)
{
    printf("Hello\n");
    return 0;   // tell the OS: program finished successfully
}
```

The OS or a calling script can inspect this exit code to determine whether the program succeeded or failed.

> **Tip:** In C99 and later, if `return` is omitted at the end of `main`, the compiler implicitly returns `0`. However, it is good practice to write `return 0;` explicitly for clarity.

---

<br>

## 2. Input and Output

### 2.1 Console I/O

C does not have built-in I/O keywords. Instead, I/O is provided through **library functions** declared in **header files**.

```c
#include <stdio.h>   // stdio = standard input/output
```

| Term | Meaning |
|:-----|:--------|
| `#include` | Preprocessor directive that copies the contents of a header file into the source |
| `<stdio.h>` | Standard I/O header; provides `printf`, `scanf`, etc. |
| Standard input | Keyboard (default) |
| Standard output | Console/screen (default) |
| Header file | A file (`.h`) containing function declarations needed by the compiler |

```
┌──────────┐    stdin     ┌─────────┐    stdout    ┌──────────┐
│ Keyboard │ ──────────▶  │ Program │ ──────────▶  │  Screen  │
└──────────┘   (scanf)    └─────────┘   (printf)   └──────────┘
```

> **Key Point:** Without `#include <stdio.h>`, the compiler does not know the declarations of `printf` and `scanf`, and will report an error (or warning, depending on the standard).

### 2.2 `printf`

`printf` (print formatted) writes formatted output to the console.

**Basic syntax:**

```c
printf("format string", value1, value2, ...);
```

The **format string** can contain:
- Plain text — printed as-is
- **Format specifiers** — placeholders replaced by the corresponding values
- **Escape sequences** — special characters like `\n`

#### Format Specifiers

| Specifier | Type | Example |
|:---------:|:-----|:--------|
| `%d` | `int` (decimal) | `printf("%d", 42);` → `42` |
| `%f` | `float`/`double` | `printf("%f", 3.14);` → `3.140000` |
| `%c` | `char` (character) | `printf("%c", 'A');` → `A` |
| `%s` | string | `printf("%s", "hi");` → `hi` |
| `%x` | `int` (hexadecimal) | `printf("%x", 255);` → `ff` |
| `%e` | `float`/`double` (scientific) | `printf("%e", 0.001);` → `1.000000e-03` |

```c
int age = 20;
double height = 175.5;

printf("Age: %d\n", age);           // Age: 20
printf("Height: %f cm\n", height);  // Height: 175.500000 cm
printf("Height: %.1f cm\n", height); // Height: 175.5 cm
```

#### Newline and Cursor Behavior

`printf` does **not** automatically move to the next line. The cursor stays at the end of the printed text. Use `\n` to insert a newline.

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

> **Tip:** Multiple `printf` calls continue printing from where the cursor was left. Think of `printf` as appending to the current cursor position.

### 2.3 `scanf`

`scanf` (scan formatted) reads formatted input from the keyboard.

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

By default, `scanf` uses whitespace (spaces, tabs, newlines) as delimiters between values.

```c
int day, month, year;
scanf("%d/%d/%d", &day, &month, &year);  // user types: 16/03/2026
// day = 16, month = 3, year = 2026
```

> **Warning:** Forgetting `&` in `scanf` is a common beginner mistake. Without `&`, the program passes the **value** of the variable (likely garbage) instead of its **address**, causing undefined behavior or a crash.

#### Format Specifiers for `scanf`

| Specifier | Type | Example |
|:---------:|:-----|:--------|
| `%d` | `int` | `scanf("%d", &n);` |
| `%f` | `float` | `scanf("%f", &f);` |
| `%lf` | `double` | `scanf("%lf", &d);` |
| `%c` | `char` | `scanf("%c", &ch);` |
| `%s` | string (char array) | `scanf("%s", str);` (no `&` for arrays) |

> **Key Point:** For `double`, `printf` uses `%f` but `scanf` uses `%lf`. This is a common source of bugs.

### 2.4 Variables in I/O

Variables must be **declared** before they can be used in `printf` or `scanf`.

**Declaration** — tells the compiler the variable's type and name:

```c
int count;       // declare an integer variable
double price;    // declare a floating-point variable
```

**Assignment** — stores a value in a variable:

```c
count = 5;
price = 19.99;
```

**Declaration + Initialization** — declare and assign in one statement:

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

> **Tip:** Always initialize variables before using them. Uninitialized variables hold garbage values and cause unpredictable results.

---

<br>

## 3. C Statements

A C program is composed of **statements** — instructions that the computer executes in order. Every statement ends with a semicolon (`;`).

| Statement Type | Purpose | Example | Covered In |
|:---------------|:--------|:--------|:-----------|
| Declaration | Create a variable | `int x;` | Chapter 2 |
| Input | Read data from keyboard | `scanf("%d", &x);` | Chapter 2 |
| Output | Display data to screen | `printf("%d", x);` | Chapter 2 |
| Assignment | Store a value | `x = 10;` | Chapter 2 |
| Conditional | Execute code based on condition | `if (x > 0) { ... }` | Chapter 5 |
| Loop | Repeat code | `for (i = 0; i < 10; i++) { ... }` | Chapter 5 |
| Function call | Call another function | `result = add(a, b);` | Chapter 6 |

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

Statements execute **sequentially** — from top to bottom, one after another — unless a control statement (conditional or loop) changes the flow.

> **Note:** Conditional (`if`, `switch`) and loop (`for`, `while`, `do-while`) statements are introduced briefly here for awareness. Detailed coverage is in Chapter 5.

---

<br>

## Summary

| Concept | Key Takeaway |
|:--------|:-------------|
| Program Structure | `#include` → `main` function → statements → `return` |
| Comments | `/* block */` and `// line`; cannot nest block comments |
| `main` Function | Entry point; one per program; returns `int`; case-sensitive |
| Exit Code | `return 0` = success; non-zero = error; can be omitted in C99+ |
| `#include <stdio.h>` | Required for `printf` and `scanf`; standard I/O header |
| `printf` | Formatted output; `%d`, `%f`, `%c`, `%s`, `%x`, `%e`; cursor stays after last character |
| `\n` | Newline escape; `printf` does not auto-newline |
| `scanf` | Formatted input; requires `&` (address-of); `%lf` for `double` |
| Variables | Declare before use; initialize to avoid garbage values |
| Statements | Declaration, input, output, assignment, conditional, loop — all end with `;` |

---
