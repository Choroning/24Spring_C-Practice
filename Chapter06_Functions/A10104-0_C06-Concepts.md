# Chapter 06 — Functions

> **Last Updated:** 2026-03-16

---

## Table of Contents

- [1. Function Concepts](#1-function-concepts)
  - [1.1 Why Functions](#11-why-functions)
  - [1.2 Function Types](#12-function-types)
  - [1.3 Function Requirements](#13-function-requirements)
- [2. Function Basics](#2-function-basics)
  - [2.1 Function Definition](#21-function-definition)
  - [2.2 Return Type](#22-return-type)
  - [2.3 Function Name](#23-function-name)
  - [2.4 Parameters and Arguments](#24-parameters-and-arguments)
  - [2.5 Function Call](#25-function-call)
  - [2.6 Function Declaration (Prototype)](#26-function-declaration-prototype)
- [3. Local and Global Variables](#3-local-and-global-variables)
  - [3.1 Local Variables](#31-local-variables)
  - [3.2 Global Variables](#32-global-variables)
  - [3.3 Scope Rules](#33-scope-rules)
- [4. Function Call Overhead](#4-function-call-overhead)
- [5. Recursive Functions (Introduction)](#5-recursive-functions-introduction)
- [Summary](#summary)

---

<br>

## 1. Function Concepts

### 1.1 Why Functions

A **function** is a named, reusable block of code that performs a specific task. Without functions, programs become long, repetitive, and hard to maintain. Functions provide four core benefits:

| Benefit | Description |
|:--------|:------------|
| **Code Reuse** | Write once, call many times — no copy-pasting |
| **Modularity** | Break a large problem into smaller, manageable pieces |
| **Readability** | `main()` reads like an outline; details are hidden inside functions |
| **Maintainability** | Fix a bug in one function — every call site is fixed automatically |

**Before — everything in `main()`:**

```c
#include <stdio.h>

int main() {
    // --- compute factorial of 5 ---
    int fact1 = 1;
    for (int i = 1; i <= 5; i++) {
        fact1 *= i;
    }
    printf("5! = %d\n", fact1);

    // --- compute factorial of 8 (duplicated logic!) ---
    int fact2 = 1;
    for (int i = 1; i <= 8; i++) {
        fact2 *= i;
    }
    printf("8! = %d\n", fact2);

    return 0;
}
```

**After — logic extracted into a function:**

```c
#include <stdio.h>

int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    printf("5! = %d\n", factorial(5));
    printf("8! = %d\n", factorial(8));
    return 0;
}
```

The duplicated loop is gone. If the factorial algorithm needs to change, we edit only `factorial()`.

### 1.2 Function Types

C programs use three categories of functions:

```
Functions in C
├── 1. Entry-point function  ← main()
├── 2. Library functions     ← printf(), scanf(), sqrt(), ...
└── 3. User-defined functions← written by the programmer
```

| Category | Example | Notes |
|:---------|:--------|:------|
| Entry point | `main()` | Every C program must have exactly one `main()`. Execution starts here. |
| Library | `printf()`, `scanf()`, `sqrt()` | Provided by the C standard library. Must `#include` the appropriate header (`<stdio.h>`, `<math.h>`, etc.). |
| User-defined | `factorial()`, `isLeapYear()` | Written by the programmer to solve specific sub-problems. |

> **Key Point:** `#include <stdio.h>` does **not** include the function code itself. It includes the **declarations** (prototypes) so the compiler knows how to call them. The actual implementation is linked later by the linker.

### 1.3 Function Requirements

To use a function in C, three elements are needed:

```
Three Requirements for Using a Function
┌──────────────┐    ┌──────────────┐    ┌──────────────┐
│  Definition  │    │  Declaration │    │    Call      │
│              │    │              │    │              │
│ What it does │    │ Promise of   │    │ Actually run │
│ (full body)  │    │ existence    │    │ the function │
└──────────────┘    └──────────────┘    └──────────────┘
```

| Element | Purpose | Required? |
|:--------|:--------|:----------|
| **Definition** | Implements the function (header + body) | Yes, exactly once |
| **Declaration** (prototype) | Tells the compiler the function exists (return type, name, parameters) | Needed if the call appears **before** the definition |
| **Call** | Executes the function with specific arguments | Yes, otherwise the function is never used |

---

<br>

## 2. Function Basics

### 2.1 Function Definition

A function definition consists of a **header** and a **body**.

```
┌─── Function Header ─────────────────────────┐
│  return_type  function_name(parameter_list) │
└─────────────────────────────────────────────┘
┌─── Function Body ───┐
│  {                  │
│      statements;    │
│      return value;  │
│  }                  │
└─────────────────────┘
```

**Annotated example:**

```c
/*  return type
 *    │
 *    │    function name
 *    │       │
 *    │       │        parameter list
 *    │       │            │            */
    int     factorial   (int n)          // ← header
    {                                    // ← body begins
        int result = 1;                  //   local variable
        for (int i = 1; i <= n; i++) {
            result *= i;
        }
        return result;                   //   return value to caller
    }                                    // ← body ends
```

| Component | Description |
|:----------|:------------|
| Return type | Data type of the value sent back to the caller (`int`, `double`, `void`, ...) |
| Function name | Identifier following the naming rules (see 2.3) |
| Parameter list | Comma-separated list of `type name` pairs that receive values from the caller |
| Body `{}` | The block of code that executes when the function is called |

### 2.2 Return Type

The return type specifies what kind of value the function sends back.

| Return Type | Meaning | Example |
|:------------|:--------|:--------|
| `int` | Returns an integer | `int factorial(int n)` |
| `double` | Returns a floating-point number | `double getAverage(int a, int b)` |
| `void` | Returns nothing | `void printMenu(void)` |

```c
// int return type
int square(int x) {
    return x * x;
}

// double return type
double average(int a, int b) {
    return (double)(a + b) / 2;
}

// void return type — no return value
void printLine(void) {
    printf("--------------------\n");
}
```

**Important rules:**

1. **A function can return only ONE value.** To return multiple results, you need pointers (covered in Chapter 8).
2. If the return type is omitted, the compiler defaults to `int` (C89 behavior). **Always write the return type explicitly** — omitting it is deprecated and error-prone.
3. A `void` function may use `return;` (no value) to exit early, or simply let execution fall through to the closing `}`.

```c
void printIfPositive(int n) {
    if (n <= 0) {
        return;           // early exit, no value
    }
    printf("%d\n", n);
}   // implicit return here
```

> **Preview (Chapter 8):** To effectively return multiple values from a function, pass pointers as parameters. The function can then modify the caller's variables directly through those pointers.

### 2.3 Function Name

Function names follow the same **identifier rules** as variables (Chapter 3):

| Rule | Example |
|:-----|:--------|
| Must start with a letter or `_` | `factorial`, `_helper` |
| Can contain letters, digits, `_` | `calc2dArea` |
| Cannot be a C keyword | ~~`return`~~, ~~`int`~~ |
| Case-sensitive | `factorial` and `Factorial` are different |

**Naming conventions (recommended):**

| Convention | Style | Example |
|:-----------|:------|:--------|
| snake_case | `verb_noun` | `get_factorial`, `is_leap_year` |
| camelCase | `verbNoun` | `getFactorial`, `isLeapYear` |
| PascalCase | `VerbNoun` | `GetDaysOfMonth`, `PrintMenu` |

> **Tip:** Choose **one** naming convention and use it consistently throughout your program. Use verb+noun pairs that describe what the function does: `getFactorial`, `isLeapYear`, `printMenu`.

> **Warning:** In C, you **cannot** define two functions with the same name (no overloading). Each function name must be unique within the program.

### 2.4 Parameters and Arguments

**Parameter** and **argument** are related but distinct concepts:

| Term | Also Called | Location | Role |
|:-----|:-----------|:---------|:-----|
| **Parameter** | Formal parameter | In the function **definition** | A local variable that receives the incoming value |
| **Argument** | Actual parameter | At the function **call site** | The actual value or expression passed to the function |

```c
//                 parameter (formal)
//                    ↓
int square(int x) {
    return x * x;
}

int main() {
    int result = square(5);   // 5 is the argument (actual)
    //                 ↑
    //              argument
    return 0;
}
```

**Parameter declaration rules:**

```c
// CORRECT: each parameter needs its own type
int add(int a, int b) {
    return a + b;
}

// WRONG: cannot share type like variable declarations
// int add(int a, b) { ... }   ← compile error!
```

**No-parameter functions:**

```c
// Both forms mean "no parameters":
void printMenu(void) { ... }   // explicit void — preferred
void printMenu() { ... }       // empty parentheses — also valid in definitions
```

> **Key Point:** In a **prototype** (declaration), `void printMenu()` means "unspecified parameters" (accepts anything), while `void printMenu(void)` means "zero parameters." Always use `void` in prototypes for clarity.

**Pass by value:**

In C, arguments are passed **by value**. The parameter receives a **copy** of the argument. Changes to the parameter do **not** affect the original variable.

```c
void tryToChange(int x) {
    x = 100;   // modifies the LOCAL copy only
    printf("Inside function: x = %d\n", x);   // 100
}

int main() {
    int num = 5;
    tryToChange(num);
    printf("After function call: num = %d\n", num);  // still 5!
    return 0;
}
```

```
Output:
Inside function: x = 100
After function call: num = 5
```

> **Preview (Chapter 8):** To modify the caller's variable, pass its **address** (pointer) instead of its value. This is called "pass by reference" (via pointers).

### 2.5 Function Call

To execute a function, write its name followed by parentheses containing the arguments.

```c
// Calling a function and using its return value
int result = factorial(5);              // store return value
printf("8! = %d\n", factorial(8));      // use return value directly in expression

// Calling a void function
printLine();                            // no return value to capture
```

**Rules for function calls:**

1. The function must be **defined or declared** before the point where it is called.
2. The number and types of arguments must match the parameters.
3. The return value can be used in any expression, assigned to a variable, or discarded.

**Calling a function from another function:**

```c
#include <stdio.h>

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int GetDaysOfMonth(int year, int month) {
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;   // calls isLeapYear()
    }
    switch (month) {
    case 4: case 6: case 9: case 11:
        return 30;
    default:
        return 31;
    }
}

int main() {
    int days = GetDaysOfMonth(2024, 2);       // calls GetDaysOfMonth()
    printf("Feb 2024 has %d days\n", days);   // 29
    return 0;
}
```

### 2.6 Function Declaration (Prototype)

A **function declaration** (also called a **prototype**) tells the compiler about a function's interface **before** its full definition appears.

**Syntax:**

```c
return_type function_name(parameter_list);   // ← semicolon, no body
```

**Why prototypes are needed:**

The C compiler reads source code **top to bottom**. If `main()` calls a function that is defined *below* `main()`, the compiler does not yet know that function's return type or parameter types. A prototype solves this by declaring the interface early.

```c
#include <stdio.h>

// ─── Prototypes (declarations) ───
int factorial(int n);         // parameter name included (recommended)
int isLeapYear(int);          // parameter name omitted (also valid)

int main() {
    printf("5! = %d\n", factorial(5));      // OK — prototype seen above
    printf("Leap? %d\n", isLeapYear(2024)); // OK — prototype seen above
    return 0;
}

// ─── Definitions ───
int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
```

**Prototype rules:**

| Rule | Example |
|:-----|:--------|
| Must match the definition's return type and parameter types | `int factorial(int n);` matches `int factorial(int n) { ... }` |
| Parameter **names** are optional in prototypes | `int add(int, int);` is valid |
| Must end with a **semicolon** | `int factorial(int n);` (not `int factorial(int n) { }`) |
| Typically placed **before `main()`** or in a header file | Convention for readability |

> **Tip:** Always include parameter names in prototypes even though they are optional. It serves as documentation: `double power(double base, int exponent);` is far more readable than `double power(double, int);`.

**Without a prototype — what goes wrong:**

```c
#include <stdio.h>

int main() {
    // If factorial() is defined below and NO prototype exists above:
    // The compiler may assume int return type (C89) or produce an error (C99+)
    printf("5! = %d\n", factorial(5));   // warning or error!
    return 0;
}

int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) result *= i;
    return result;
}
```

> **Warning:** In C99 and later, calling a function without a prior declaration or definition is an **error**. Always provide a prototype or define the function before using it.

---

<br>

## 3. Local and Global Variables

### 3.1 Local Variables

A **local variable** is declared inside a block `{}` — typically inside a function body. It exists only while that block is executing.

```c
void funcA() {
    int x = 10;   // local to funcA
    printf("funcA: x = %d\n", x);
}

void funcB() {
    int x = 20;   // local to funcB — independent from funcA's x
    printf("funcB: x = %d\n", x);
}

int main() {
    funcA();   // prints: funcA: x = 10
    funcB();   // prints: funcB: x = 20
    // printf("%d", x);   // ERROR — x is not accessible here
    return 0;
}
```

**Characteristics of local variables:**

| Property | Description |
|:---------|:------------|
| Scope | From declaration to the end of the enclosing `{}` block |
| Lifetime | Created when the block is entered, destroyed when it exits |
| Initial value | **Undefined** (garbage) unless explicitly initialized |
| Independence | Different functions can use the same variable name without conflict |

```c
int main() {
    for (int i = 0; i < 3; i++) {
        int temp = i * 10;   // created each iteration, destroyed at end of iteration
        printf("%d ", temp);
    }
    // printf("%d", temp);  // ERROR — temp does not exist here
    return 0;
}
```

> **Warning:** Local variables are **not** automatically initialized to zero. Always initialize them before use, or you will get unpredictable garbage values.

### 3.2 Global Variables

A **global variable** is declared **outside all functions**, typically at the top of the file. It is accessible from its declaration point to the end of the file.

```c
#include <stdio.h>

int count = 0;   // global variable — accessible everywhere below this line

void increment() {
    count++;   // modifies the global variable
}

void printCount() {
    printf("count = %d\n", count);
}

int main() {
    increment();
    increment();
    increment();
    printCount();   // count = 3
    return 0;
}
```

**Characteristics of global variables:**

| Property | Description |
|:---------|:------------|
| Scope | From declaration point to the end of the source file |
| Lifetime | Entire program execution (created at program start, destroyed at program end) |
| Initial value | **Automatically initialized to `0`** (unlike local variables) |
| Accessibility | Any function defined after the declaration can access it |

```c
#include <stdio.h>

int g;   // global — automatically initialized to 0

int main() {
    printf("g = %d\n", g);   // g = 0 (guaranteed)

    int local;
    // printf("local = %d\n", local);  // DANGEROUS — uninitialized, garbage value
    return 0;
}
```

> **Warning:** Avoid overusing global variables. They make it hard to track which functions modify them, leading to **hidden dependencies** and bugs that are difficult to debug. Prefer passing values as parameters.

### 3.3 Scope Rules

When a local variable and a global variable share the same name, the **local variable takes precedence** within its scope. This is called **shadowing**.

```c
#include <stdio.h>

int x = 100;   // global

void demo() {
    int x = 50;   // local — shadows the global x
    printf("Inside demo(): x = %d\n", x);       // 50 (local)
}

int main() {
    printf("Before demo(): x = %d\n", x);       // 100 (global)
    demo();
    printf("After demo(): x = %d\n", x);        // 100 (global, unchanged)

    {
        int x = 999;   // block-local — shadows the global x
        printf("Inside block: x = %d\n", x);    // 999
    }
    printf("After block: x = %d\n", x);         // 100 (global)

    return 0;
}
```

```
Output:
Before demo(): x = 100
Inside demo(): x = 50
After demo(): x = 100
Inside block: x = 999
After block: x = 100
```

**Scope resolution priority:**

```
When the same name exists at multiple levels:
  Inner block variable  >  Outer block variable  >  Global variable
  (innermost scope wins)
```

| Scope Level | Variable | Accessible Where |
|:------------|:---------|:-----------------|
| Block `{}` | Declared inside a block | Only within that block |
| Function | Declared at the top of a function | Throughout the function |
| File (global) | Declared outside all functions | From declaration to end of file |

> **Tip:** Avoid naming local variables the same as global variables. Shadowing makes code confusing and is a common source of bugs. Use distinct, descriptive names.

---

<br>

## 4. Function Call Overhead

Every function call involves a sequence of behind-the-scenes operations managed by the **call stack**:

```
Function Call Mechanism
─────────────────────────────────────────
1. Save the return address (where to come back)
2. Save CPU register values
3. Push arguments onto the stack
4. Jump to the function code
5. Execute the function body
6. Place return value in a register
7. Pop the stack (restore registers, arguments)
8. Jump back to the return address
─────────────────────────────────────────
```

This process is called **function call overhead**. For large functions that perform significant computation, the overhead is negligible. However, for **very small functions** (e.g., a one-line calculation), the overhead can be relatively significant compared to the actual work.

```c
// Small function — overhead is relatively large compared to the work done
int square(int x) {
    return x * x;
}

// Called in a tight loop — overhead accumulates
for (int i = 0; i < 1000000; i++) {
    result += square(i);   // function call overhead × 1,000,000
}
```

> **Key Point:** C++ introduces `inline` functions to mitigate this overhead: the compiler substitutes the function body directly at the call site, eliminating the call/return mechanism. C99 also supports the `inline` keyword, but its behavior differs slightly from C++.

> **Tip:** Do not avoid functions just to reduce overhead. The readability, maintainability, and reusability benefits of functions far outweigh the small performance cost in nearly all cases. Only optimize if profiling reveals an actual bottleneck.

---

<br>

## 5. Recursive Functions (Introduction)

A **recursive function** is a function that calls **itself**. Every recursive function needs:

1. **Base case** — a condition that stops the recursion
2. **Recursive case** — the function calls itself with a smaller/simpler input

```c
#include <stdio.h>

// Factorial: n! = n × (n-1) × ... × 2 × 1
int factorial(int n) {
    if (n <= 1) {         // base case
        return 1;
    }
    return n * factorial(n - 1);   // recursive case
}

int main() {
    printf("5! = %d\n", factorial(5));   // 120
    return 0;
}
```

**Execution trace for `factorial(4)`:**

```
factorial(4)
  → 4 * factorial(3)
       → 3 * factorial(2)
            → 2 * factorial(1)
                 → returns 1      (base case)
            → returns 2 * 1 = 2
       → returns 3 * 2 = 6
  → returns 4 * 6 = 24
```

**Another example — count the number of digits in a positive integer:**

```c
int countDigits(int n) {
    if (n < 10) {         // base case: single digit
        return 1;
    }
    return 1 + countDigits(n / 10);   // recursive case
}
// countDigits(9128) = 1 + countDigits(912)
//                   = 1 + 1 + countDigits(91)
//                   = 1 + 1 + 1 + countDigits(9)
//                   = 1 + 1 + 1 + 1 = 4
```

> **Warning:** A recursive function without a proper base case will call itself infinitely, causing a **stack overflow** (the call stack runs out of memory). Always ensure the base case is reachable.

> **Key Point:** Any problem that can be solved recursively can also be solved with a loop (iteration). Recursion is elegant for problems that are naturally self-similar (factorial, Fibonacci, tree traversal), but iterative solutions are often more efficient due to lower function call overhead.

---

<br>

## Summary

| Concept | Key Takeaway |
|:--------|:-------------|
| Why Functions | Code reuse, modularity, readability, maintainability |
| Function Types | Entry point (`main`), library (`printf`, `scanf`), user-defined |
| Function Requirements | Definition (body), declaration (prototype), call (invocation) |
| Function Definition | Header (return type + name + parameters) + body `{}` |
| Return Type | `int`, `double`, `void`; only ONE value can be returned; omitting defaults to `int` (deprecated) |
| Function Name | Identifier rules from Ch3; verb+noun convention; no duplicate names in C |
| Parameters vs Arguments | Parameter = receiving variable in definition; Argument = actual value at call site |
| Pass by Value | Arguments are copied; changes to parameters do not affect originals |
| Function Call | Must be declared/defined before the call point; return value usable in expressions |
| Function Prototype | `return_type name(params);` — allows calling before definition; param names optional |
| Local Variables | Declared inside `{}`; exist only during block execution; not auto-initialized |
| Global Variables | Declared outside all functions; accessible file-wide; auto-initialized to `0` |
| Scope Rules | Inner scope shadows outer scope; local > global when same name |
| Function Call Overhead | Save/restore registers, push/pop stack; small functions have relatively high overhead |
| Recursive Functions | Function calls itself; needs base case + recursive case; risk of stack overflow |
| Multiple Return Values | Not directly possible; use pointers (Chapter 8 preview) |

---
