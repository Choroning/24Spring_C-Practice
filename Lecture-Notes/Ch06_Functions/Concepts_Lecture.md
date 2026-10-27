# Chapter 6 — Functions

[Repository Guide](../../README.md) | [English](Concepts_Lecture.md) | [한국어](Concepts_Lecture.ko.md)

> **Last Updated:** 2026-10-27
>
> Warming-Up C Programming, 천정아, Ch 6

> **Learning Objectives:**
> 1. Explain why functions are needed and describe the three kinds of functions
> 2. Write function definitions, declarations (prototypes), and calls and tell them apart
> 3. Explain the relationship between parameters and arguments and how pass by value works
> 4. Compare the scope, lifetime, and initial value of local and global variables
> 5. Explain function call overhead and the base case of a recursive function

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
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Function Concepts

### 1.1 Why Functions

A **function** is a named, reusable block of code that performs a specific task. A function can be viewed as a black box that takes inputs (parameters) and produces a result (return value); the caller can use the function without knowing how it is implemented. Without functions, programs become long, repetitive, and hard to maintain. Functions provide four core benefits:

| Benefit | Description |
|:--------|:------------|
| **Code Reuse** | Write once and call many times, so the same code never has to be copied and pasted |
| **Modularity** | Break a large problem into smaller, manageable pieces |
| **Readability** | `main()` reads like an outline; details are hidden inside functions |
| **Maintainability** | Fix a bug in one function and every call site is fixed automatically |

*Table 1. Four benefits of functions*

**Before (everything inside `main()`):**

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

**After (the repeated logic extracted into a function):**

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

The duplicated loop is gone. If the factorial algorithm needs to change, only `factorial()` has to be edited.

### 1.2 Function Types

C programs use three categories of functions:

```text
Functions in C
├── 1. Entry-point function  ← main()
├── 2. Library functions     ← printf(), scanf(), sqrt(), ...
└── 3. User-defined functions← written by the programmer
```

*Figure 1. Three kinds of functions in C*

| Category | Example | Notes |
|:---------|:--------|:------|
| Entry point | `main()` | Every C program must have exactly one `main()`. It is called from the operating system side when the program starts, and the programmer never calls it directly. Execution starts here. |
| Library | `printf()`, `scanf()`, `sqrt()` | Provided by the C standard library. Must `#include` the appropriate header (`<stdio.h>`, `<math.h>`, etc.). |
| User-defined | `factorial()`, `isLeapYear()` | Written by the programmer to solve specific sub-problems. |

*Table 2. Examples and characteristics of each kind of function*

> **Key Point:** `#include <stdio.h>` does **not** include the function code itself. It includes the **declarations** (prototypes) so the compiler knows how to call them. The actual implementation is linked later by the linker.

### 1.3 Function Requirements

To use a function in C, three elements are needed:

```text
Three Requirements for Using a Function
┌──────────────┐    ┌──────────────┐    ┌──────────────┐
│  Definition  │    │  Declaration │    │    Call      │
│              │    │              │    │              │
│ What it does │    │ Promise of   │    │ Actually run │
│ (full body)  │    │ existence    │    │ the function │
└──────────────┘    └──────────────┘    └──────────────┘
```

*Figure 2. Three elements of using a function*

| Element | Purpose | Required? |
|:--------|:--------|:----------|
| **Definition** | Implements the function (header + body) | Yes, exactly once |
| **Declaration** (prototype) | Tells the compiler the function exists (return type, name, parameters) | Needed if the call appears **before** the definition |
| **Call** | Executes the function with specific arguments | Yes, otherwise the function is never used |

*Table 3. Three elements of using a function and whether each is required*

Of the three elements, only the declaration can be omitted; it is unnecessary when the function definition appears before the call.

---

<br>

## 2. Function Basics

### 2.1 Function Definition

A function definition consists of a **header** and a **body**.

```text
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

*Figure 3. Header and body of a function definition*

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
| Function name | Identifier following the naming rules (see Section 2.3) |
| Parameter list | Comma-separated list of `type name` pairs that receive values from the caller |
| Body `{}` | The block of code that executes when the function is called |

*Table 4. Components of a function definition*

### 2.2 Return Type

The return type specifies what kind of value the function sends back.

| Return Type | Meaning | Example |
|:------------|:--------|:--------|
| `int` | Returns an integer | `int factorial(int n)` |
| `double` | Returns a floating-point number | `double getAverage(int a, int b)` |
| `void` | Returns nothing | `void printMenu(void)` |

*Table 5. Kinds of return types*

```c
// int return type
int square(int x) {
    return x * x;
}

// double return type
double average(int a, int b) {
    return (double)(a + b) / 2;
}

// void return type: no return value
void printLine(void) {
    printf("--------------------\n");
}
```

**Important rules:**

1. **A function can return only ONE value.** To return multiple results, you need pointers (covered in Chapter 8).
2. If the return type is omitted, C89 assumed `int`. C99 removed this implicit `int` rule from the standard, so **always write the return type explicitly.**
3. A `void` function may use `return;` (no value) to exit early, or simply let execution fall through to the closing `}`.
4. A function whose return type is not `void` must send back a value with `return expression;`, and if the type of the expression differs from the return type, the value is converted to the return type (for example, `return 3.7;` in an `int` function returns 3).

```c
void printIfPositive(int n) {
    if (n <= 0) {
        return;           // early exit, no value
    }
    printf("%d\n", n);
}   // implicit return here
```

> **Note:** **Preview.** To send back several values from a function, pass pointers as parameters. The function can then modify the caller's variables directly through those pointers; Chapter 8 covers this in detail.

### 2.3 Function Name

Function names follow the same **identifier rules** as variables (Chapter 3):

| Rule | Example |
|:-----|:--------|
| Must start with a letter or `_` | `factorial`, `_helper` |
| Can contain letters, digits, `_` | `calc2dArea` |
| Cannot be a C keyword | ~~`return`~~, ~~`int`~~ |
| Case-sensitive | `factorial` and `Factorial` are different |

*Table 6. Identifier rules for function names*

**Naming conventions (recommended):**

| Convention | Style | Example |
|:-----------|:------|:--------|
| snake_case | `verb_noun` | `get_factorial`, `is_leap_year` |
| camelCase | `verbNoun` | `getFactorial`, `isLeapYear` |
| PascalCase | `VerbNoun` | `GetDaysOfMonth`, `PrintMenu` |

*Table 7. Naming conventions for function names*

> **Note:** **Tip.** Choose **one** naming convention and use it consistently throughout your program. Use verb and noun combinations that describe what the function does (`getFactorial`, `isLeapYear`, `printMenu`).

> **Caution:** In C, you **cannot** define two functions with the same name (no overloading). Each function name must be unique within the program.

### 2.4 Parameters and Arguments

**Parameter** and **argument** are related but distinct concepts:

| Term | Also Called | Location | Role |
|:-----|:-----------|:---------|:-----|
| **Parameter** | Formal parameter | In the function **definition** | A local variable that receives the incoming value |
| **Argument** | Actual parameter | At the function **call site** | The actual value or expression passed to the function |

*Table 8. Comparison of parameters and arguments*

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

Omitting a parameter's type in a function definition is a compile error, and through C17 omitting a parameter's name is also an error (C23 allows unnamed parameters in definitions as well). There is no limit on the number of parameters.

**No-parameter functions:**

```c
// Both forms mean "no parameters":
void printMenu(void) { ... }   // explicit void: preferred
void printMenu() { ... }       // empty parentheses: also valid in definitions
```

> **Key Point:** In a **prototype** (declaration) before C23, `void printMenu()` declares a function without specifying the number or types of its parameters, so the compiler does not check the arguments, while `void printMenu(void)` means the function takes no parameters. Since C23, empty parentheses also mean no parameters. Always use `void` in prototypes for clarity.

**Pass by value:**

In C, arguments are passed **by value**. A parameter is a local variable that is created when the function is called and initialized with a **copy** of the argument, and it is destroyed when the function returns. Therefore changes to the parameter do **not** affect the original variable.

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

```text
Output:
Inside function: x = 100
After function call: num = 5
```

> **Note:** **Preview.** To modify the caller's variable, pass its **address** (pointer) instead of its value. This is often called **pass by reference**, but strictly speaking it is still pass by value, because the address itself is copied. Chapter 8 covers this in detail.

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
2. The number and order of arguments must match the parameters. If an argument's type differs from the parameter's type, the argument is converted to the parameter's type wherever a prototype is visible (for example, passing 101 to a `char` parameter passes the character `'e'`).
3. The return value can be used in any expression, assigned to a variable, or discarded.
4. An argument is itself an expression, so its value is computed first and then the function is called.
5. A call to a function whose return type is `void` has no value, so it cannot be used as an operand of another expression.

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

A **function declaration** (also called a **prototype** or **signature**) tells the compiler about a function's interface **before** its full definition appears.

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
    printf("5! = %d\n", factorial(5));      // OK: prototype seen above
    printf("Leap? %d\n", isLeapYear(2024)); // OK: prototype seen above
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

*Table 9. Rules for function prototypes*

> **Note:** **Tip.** Always include parameter names in prototypes even though they are optional. The names serve as documentation, so `double power(double base, int exponent);` is far more readable than `double power(double, int);`.

**What goes wrong without a prototype:**

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

> **Caution:** Since C99, implicit declaration (calling a function without a prior declaration) has been removed from the standard, so the compiler must issue a diagnostic. gcc 14 and later and clang 16 and later treat it as an **error** by default, while earlier versions only warn and assume a function returning `int`. Always provide a prototype or define the function before using it.

---

<br>

## 3. Local and Global Variables

### 3.1 Local Variables

A **local variable** is a variable declared inside a block `{}`, usually inside a function body. It exists only while that block is executing.

```c
void funcA() {
    int x = 10;   // local to funcA
    printf("funcA: x = %d\n", x);
}

void funcB() {
    int x = 20;   // local to funcB: independent from funcA's x
    printf("funcB: x = %d\n", x);
}

int main() {
    funcA();   // prints: funcA: x = 10
    funcB();   // prints: funcB: x = 20
    // printf("%d", x);   // ERROR: x is not accessible here
    return 0;
}
```

**Characteristics of local variables:**

| Property | Description |
|:---------|:------------|
| Scope | From declaration to the end of the enclosing `{}` block |
| Lifetime | Created when the block is entered, destroyed when it exits |
| Storage | Usually the stack area |
| Initial value | **Undefined** (garbage) unless explicitly initialized |
| Independence | Different functions can use the same variable name without conflict |

*Table 10. Characteristics of local variables*

```c
int main() {
    for (int i = 0; i < 3; i++) {
        int temp = i * 10;   // created each iteration, destroyed at end of iteration
        printf("%d ", temp);
    }
    // printf("%d", temp);  // ERROR: temp does not exist here
    return 0;
}
```

A local variable inside a function is created anew each time the function is called and destroyed when it returns, and a local variable inside a loop block is created and destroyed on every iteration. Parameters are local variables too, so changing a parameter inside a function does not affect the caller; to pass a value computed by the function back to the caller, use the return value.

> **Caution:** Local variables are **not** automatically initialized to zero. Always initialize them before use, or you will get unpredictable garbage values.

### 3.2 Global Variables

A **global variable** is declared **outside all functions**, typically at the top of the file. It is accessible from its declaration point to the end of the file.

```c
#include <stdio.h>

int count = 0;   // global variable: accessible everywhere below this line

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

All three calls to `increment()` change the same `count`, so `printCount()` prints 3. A value assigned to a global variable inside a function remains after the function returns.

**Characteristics of global variables:**

| Property | Description |
|:---------|:------------|
| Scope | From declaration point to the end of the source file |
| Lifetime | Entire program execution (created at program start, destroyed at program end) |
| Storage | The data area |
| Initial value | **Automatically initialized to `0`** (unlike local variables) |
| Accessibility | Any function defined after the declaration can access it |

*Table 11. Characteristics of global variables*

```c
#include <stdio.h>

int g;   // global: automatically initialized to 0

int main() {
    printf("g = %d\n", g);   // g = 0 (guaranteed)

    int local;
    // printf("local = %d\n", local);  // DANGEROUS: uninitialized, garbage value
    return 0;
}
```

> **Caution:** Avoid overusing global variables. They make it hard to track which functions modify them, leading to **hidden dependencies** and bugs that are difficult to debug. Prefer passing values as parameters.

### 3.3 Scope Rules

When a local variable and a global variable share the same name, the **local variable takes precedence** within its scope. This is called **shadowing**.

```c
#include <stdio.h>

int x = 100;   // global

void demo() {
    int x = 50;   // local: shadows the global x
    printf("Inside demo(): x = %d\n", x);       // 50 (local)
}

int main() {
    printf("Before demo(): x = %d\n", x);       // 100 (global)
    demo();
    printf("After demo(): x = %d\n", x);        // 100 (global, unchanged)

    {
        int x = 999;   // block-local: shadows the global x
        printf("Inside block: x = %d\n", x);    // 999
    }
    printf("After block: x = %d\n", x);         // 100 (global)

    return 0;
}
```

```text
Output:
Before demo(): x = 100
Inside demo(): x = 50
After demo(): x = 100
Inside block: x = 999
After block: x = 100
```

**Scope resolution priority:**

```text
When the same name exists at multiple levels:
  Inner block variable  >  Outer block variable  >  Global variable
  (innermost scope wins)
```

*Figure 4. Priority when variables with the same name exist in several scopes*

| Scope Level | Variable | Accessible Where |
|:------------|:---------|:-----------------|
| Block `{}` | Declared inside a block | Only within that block |
| Function | Declared at the top of a function | From the declaration to the end of the function |
| File (global) | Declared outside all functions | From declaration to end of file |

*Table 12. Accessible range of variables at each scope level*

> **Note:** **Tip.** Avoid naming local variables the same as global variables. Shadowing makes code confusing and is a common source of bugs. Use distinct, descriptive names.

---

<br>

## 4. Function Call Overhead

Every function call involves a sequence of behind-the-scenes operations managed by the **call stack**:

```text
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

*Figure 5. Steps of a function call and return*

The exact steps and their order depend on the CPU and the calling convention. For example, on x86-64 the first several arguments are passed in registers rather than on the stack.

> **[Systems Programming]** The stack frame created on the stack for each call (return address, saved registers, local variables) and the calling convention that decides which registers or stack locations carry the arguments are part of the machine-level representation of programs covered in Systems Programming. Knowing this structure explains both why local variables disappear when a function returns (Section 3.1) and where the function call overhead comes from.

This process is called **function call overhead**. For large functions that perform significant computation, the overhead is negligible. However, for **very small functions** (e.g., a one-line calculation), the overhead can be relatively significant compared to the actual work.

```c
// Small function: overhead is relatively large compared to the work done
int square(int x) {
    return x * x;
}

// Called in a tight loop: overhead accumulates
for (int i = 0; i < 1000000; i++) {
    result += square(i);   // function call overhead × 1,000,000
}
```

> **Key Point:** C++ introduced `inline` functions to mitigate this overhead. `inline` is a request to expand the function body directly at the call site and eliminate the call and return steps, but the compiler decides whether to actually expand it. C99 also supports the `inline` keyword, but its linkage rules differ slightly from C++.

> **Note:** **Tip.** Do not avoid functions just to reduce overhead. The readability, maintainability, and reusability benefits of functions far outweigh the small performance cost in nearly all cases. Only optimize if profiling reveals an actual bottleneck.

---

<br>

## 5. Recursive Functions (Introduction)

A **recursive function** is a function that calls **itself**. Every recursive function needs:

1. **Base case:** a condition that stops the recursion.
2. **Recursive case:** the case in which the function calls itself with a smaller or simpler input.

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

```text
factorial(4)
  → 4 * factorial(3)
       → 3 * factorial(2)
            → 2 * factorial(1)
                 → returns 1      (base case)
            → returns 2 * 1 = 2
       → returns 3 * 2 = 6
  → returns 4 * 6 = 24
```

*Figure 6. Recursive call trace of factorial(4)*

**Another example (counting the digits of a positive integer):**

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

> **Caution:** A recursive function without a proper base case will call itself infinitely, causing a **stack overflow** (the call stack runs out of memory). Always ensure the base case is reachable.

> **Key Point:** Any problem that can be solved recursively can also be solved with a loop (iteration), managing a stack explicitly if necessary. Recursion is elegant for problems that are naturally self-similar (factorial, Fibonacci, tree traversal), but iterative solutions are often more efficient due to lower function call overhead.

---

<br>

## Summary

| Concept | Key Summary |
|:-----|:-----|
| Why Functions | Functions improve code reuse, modularity, readability, and maintainability. |
| Function Types | Functions are divided into the entry-point function (`main`), library functions (`printf`, `scanf`), and user-defined functions. |
| Function Requirements | Using a function requires a definition, a declaration (prototype), and a call, and the declaration can be omitted if the definition comes before the call. |
| Function Definition | A function definition consists of a header made of the return type, name, and parameter list, and a body enclosed in `{}`. |
| Return Type | The return type is `int`, `double`, `void`, and so on; a function can return only one value, and omitting the return type has not been allowed since C99. |
| Function Name | A function name follows the identifier rules of Chapter 3 and combines a verb and a noun, and C does not allow two functions with the same name. |
| Parameters and Arguments | A parameter is a local variable in the definition that receives a value, and an argument is the actual value passed at the call. |
| Pass by Value | The argument's value is copied into the parameter, so changing the parameter does not change the original variable. |
| Function Call | A declaration or definition must appear before the call point, and the return value can be used inside expressions. |
| Function Prototype | A prototype of the form `return_type name(params);` allows calling a function before its definition, and parameter names may be omitted in it. |
| Local Variables | A local variable is declared inside `{}`, exists only while the block executes, and is not initialized automatically. |
| Global Variables | A global variable is declared outside all functions, can be used from its declaration to the end of the file, and is automatically initialized to `0`. |
| Scope Rules | When names are the same, a variable in an inner scope hides one in an outer scope, so a local variable takes precedence over a global variable. |
| Function Call Overhead | Every call needs saving the return address and registers, passing arguments, and restoring them, so the share of overhead grows as the function gets smaller. |
| Recursive Functions | A recursive function calls itself, and a stack overflow occurs if there is no base case or the base case is never reached. |
| Multiple Return Values | A function cannot return several values directly, so pointer parameters are used, which Chapter 8 covers. |

---

<br>

## Self-Check Questions

1. **Pass by value:** If `void addTen(int n) { n += 10; }` is defined and `main()` runs `int x = 5; addTen(x); printf("%d\n", x);`, what is printed?

   <details>
   <summary>Answer</summary>

   5 is printed. When `addTen()` is called, the parameter `n` is a local variable initialized with a copy of the value 5 of `x`, so changing `n` to 15 does not change `x`. `n` is destroyed when the function returns.

   </details>

2. **Function prototype:** To call `double average(int a, int b)`, defined below `main()`, from `main()`, what must be written before `main()`?

   <details>
   <summary>Answer</summary>

   Write the prototype `double average(int a, int b);`. The form without parameter names, `double average(int, int);`, is also valid in a prototype; either way it ends with a semicolon and has no body. Without a prototype, compilers for C99 and later issue a warning or an error for the implicit declaration.

   </details>

3. **Scope:** Given the global variable `int x = 1;` and the function `void f(void) { int x = 2; x++; }`, what is printed if `main()` calls `f();` and then runs `printf("%d\n", x);`?

   <details>
   <summary>Answer</summary>

   1 is printed. The `x` inside `f()` is a local variable that shadows the global `x`, so `x++` changes only the local variable to 3, and that local variable is destroyed when `f()` returns. The `x` in `main()` refers to the global variable, so its value is still 1.

   </details>

4. **Recursion trace:** For `countDigits()` in Section 5, find the return values of `countDigits(50070)` and `countDigits(0)`, and state how many times the function is called in total for `countDigits(50070)`.

   <details>
   <summary>Answer</summary>

   `countDigits(50070)` is called 5 times in total, with 50070, 5007, 500, 50, and 5; at 5 it meets the base case `n < 10` and returns 1, and each level adds 1, so it returns 5. `countDigits(0)` returns 1 because 0 satisfies the base case from the start.

   </details>

5. **Initial values of variables:** What are the values of an uninitialized global variable `int g;` and an uninitialized local variable `int local;` inside `main()`?

   <details>
   <summary>Answer</summary>

   The global variable `g` is automatically initialized to 0 when the program starts, so it is guaranteed to be 0. The local variable `local` is not initialized automatically, so its value is indeterminate, and reading it before initializing it yields an unpredictable garbage value.

   </details>
