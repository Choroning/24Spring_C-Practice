# Chapter 6 Lab — Writing and Using Functions

[Repository Guide](../../README.md) | [English](Concepts_Lab.md) | [한국어](Concepts_Lab.ko.md)

> **Last Updated:** 2026-10-27
>
> 문제풀이 중심의 C언어 연습, 김용일과 강문설, Ch 7

> **Learning Objectives:**
> 1. Translate a mathematical function into the parameters, body, and return value of a C function by dividing it into input, work, and result
> 2. Explain the roles and positions of the prototype, definition, and call of a function
> 3. Distinguish and write the four forms of functions according to whether they have parameters and a return value
> 4. Trace how parameters and local variables are created and destroyed during a function call
> 5. Predict the results of using local and global variables in functions

---

## Table of Contents

- [1. What a Function Is](#1-what-a-function-is)
- [2. Writing Functions](#2-writing-functions)
  - [2.1 y = x + 3 as a C Function](#21-y--x--3-as-a-c-function)
  - [2.2 Prototype, Call, and Definition](#22-prototype-call-and-definition)
  - [2.3 A Function with Two Parameters](#23-a-function-with-two-parameters)
  - [2.4 A Function with No Parameters and No Return Value](#24-a-function-with-no-parameters-and-no-return-value)
  - [2.5 Why Functions Are Used and Their Four Forms](#25-why-functions-are-used-and-their-four-forms)
- [3. Function Calls and Memory](#3-function-calls-and-memory)
- [4. Local and Global Variables](#4-local-and-global-variables)
  - [4.1 A Parameter Is a Copy of the Argument](#41-a-parameter-is-a-copy-of-the-argument)
  - [4.2 A Global Variable Is Shared by All Functions](#42-a-global-variable-is-shared-by-all-functions)
- [5. Function Practice](#5-function-practice)
  - [5.1 Printing as Many Stars as Entered](#51-printing-as-many-stars-as-entered)
  - [5.2 A Function That Tells Uppercase from Lowercase](#52-a-function-that-tells-uppercase-from-lowercase)
  - [5.3 A Power Function](#53-a-power-function)
  - [5.4 A Function That Converts Degrees to Radians](#54-a-function-that-converts-degrees-to-radians)
  - [5.5 Summing Only the Positive Numbers](#55-summing-only-the-positive-numbers)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. What a Function Is

A **function** in C starts from the same idea as a function in mathematics. A mathematical function such as sin, cos, or a linear or quadratic function can be divided into three parts, an input, the work it does, and a result, and for the linear function y = x + 3 they are as follows ([Chapter 6, Section 1.1](Concepts_Lecture.md#11-why-functions)).

| Part | In y = x + 3 | In a C function |
|:-----|:-----|:-----|
| Input | The integer x | Parameter |
| Work (to do) | Compute x + 3 and assign it to y | Statements of the function body |
| Result | y | Return value |

*Table 1. Correspondence between a mathematical function and a C function*

---

<br>

## 2. Writing Functions

### 2.1 y = x + 3 as a C Function

Translating y = x + 3 into a C function requires the following.

- **Function name:** `getPlus`
- **Information to pass when running the function (parameter):** `int x`
- **Work:** Declare `int y;` and compute `y = x + 3;`.
- **Returning the result:** Give the result back to the place that asked the function to work. `return y;`
- **Data type of the result:** `y` is an integer, so the return type is `int`.

Putting these together gives the following **function definition**. The first line, made of the return type, name, and parameter list, is the **function header**, and the part inside the braces is the **function body** ([Chapter 6, Section 2.1](Concepts_Lecture.md#21-function-definition)).

```c
int getPlus(int x)      // function header
{                       // function body
    int y;
    y = x + 3;
    return y;
}
```

### 2.2 Prototype, Call, and Definition

A program that uses a function has three parts ([Chapter 6, Section 1.3](Concepts_Lecture.md#13-function-requirements)). In the following code, `int getPlus(int x);` before `main` is the **function prototype** or declaration, `getPlus(val)` inside `main` is a **function call**, and the code after `main` is the function definition.

```c
#include <stdio.h>
int getPlus(int x);     // function prototype (declaration)

int main(void)
{
    int val = 2, result;

    result = getPlus(val);                      // function call: the return value is assigned to result
    printf("1. result: %d \n", result);
    printf("2. result: %d \n", getPlus(3));     // function call: the return value is printed with %d

    return 0;
}

int getPlus(int x)      // function definition
{
    int y;
    y = x + 3;
    return y;
}
```

```text
1. result: 5 
2. result: 6 
```

- **Prototype:** The compiler reads the source from top to bottom, so when the definition comes after `main`, the prototype is declared first so that the return type and parameters of the function are known at the call ([Chapter 6, Section 2.6](Concepts_Lecture.md#26-function-declaration-prototype)).
- **Call:** `getPlus(val)` passes the value 2 of `val` to the parameter `x` and assigns the return value 5 to `result`. As with `getPlus(3)`, the return value can also be used directly as an argument of `printf` without storing it in a variable.

### 2.3 A Function with Two Parameters

Translating the quadratic function y = a² + x - 3 into C gives the function `getQuad` with two parameters (`int a`, `int x`). In a call, the arguments are passed in the order of the parameters, separated by commas.

```c
int getQuad(int a, int x)
{
    int y;
    y = a * a + x - 3;
    return y;
}
```

`getQuad(1, 3)` returns 1 + 3 - 3 = 1, and `getQuad(2, 4)` returns 4 + 4 - 3 = 5. The code that calls both functions in one program is [Example_ReturnValue.c](Example_ReturnValue.c).

```c
#include <stdio.h>
int getPlus(int x);
int getQuad(int a, int x);

int main()
{
    // getPlus(): one parameter
    int val = 2, result;

    result = getPlus(val);
    printf("1. result: %d \n", result);
    printf("2. result: %d \n", getPlus(3));

    // getQuad(): two parameters
    int a = 1, x = 3;

    result = getQuad(a, x);
    printf("1. result: %d \n", result);
    printf("2. result: %d \n", getQuad(2, 4));
}

int getPlus(int x) {
    int y;
    y = x + 3;
    return y;
}

int getQuad(int a, int x) {
    int y;
    y = a * a + x - 3;
    return y;
}
```

```text
1. result: 5 
2. result: 6 
1. result: 1 
2. result: 5 
```

### 2.4 A Function with No Parameters and No Return Value

Consider a function `showStar` that always prints five stars on the screen. It receives no information, so `void` is written in the parameter position (empty parentheses also work), and it has no result to give back, so its return type is also `void`. The `void` of the return type cannot be omitted. In a function without a return value, `return;` can be omitted.

```c
#include <stdio.h>
void showStar(void);    // prototype (declaration)

int main(void)
{
    showStar();         // call
    showStar();         // call

    return 0;
}

void showStar(void)     // definition
{
    printf("***** \n");
}
```

```text
***** 
***** 
```

> **Note:** In a definition, empty parentheses, as in `void showStar()`, make a function with no parameters. However, in C before C23, writing a prototype with empty parentheses, as in `void showStar();`, declares the function without parameter information, so the compiler does not check the number of arguments; writing `void` in prototypes is therefore safer ([Chapter 6, Section 2.4](Concepts_Lecture.md#24-parameters-and-arguments)).

### 2.5 Why Functions Are Used and Their Four Forms

Functions are defined for the following reasons ([Chapter 6, Section 1.1](Concepts_Lecture.md#11-why-functions)).

- **Better program quality through modularity:** Functions divided by feature can be written and tested separately.
- **Ease of maintenance and extension:** To change a feature, only that function needs to be modified.
- **Ease of problem solving:** A large problem is solved by dividing it into small problems (divide and conquer).

Functions fall into four forms according to whether they have parameters and a return value.

| Parameters | Return value | Example |
|:---:|:---:|:-----|
| Yes | Yes | `int getPlus(int x)` |
| Yes | No | `void showStar(int n)` (Section 5.1) |
| No | Yes | `int getInput(void)` (reads input and returns it) |
| No | No | `void showStar(void)` |

*Table 2. Forms of functions by whether they have parameters and a return value*

---

<br>

## 3. Function Calls and Memory

The following program shows how memory changes when a function is called.

```c
#include <stdio.h>
int Add(int i, int j); // function prototype

int main(void) {
    int d;
    d = Add(3, 4); // function call
    printf("%d \n", d);
    return 0; // may be omitted
}

int Add(int i, int j) { // function definition
    int result = i + j;
    return result;
}
```

```text
7 
```

1. When `main` starts, the memory of its local variable `d` is created. At this point `d` holds a garbage value.
2. Calling `Add(3, 4)` creates new memory for the parameters `i` and `j` of `Add` and copies the arguments 3 and 4 into them. Then the local variable `result` is created and 7 is stored in it.
3. When `return result;` executes, the value 7 is passed back to the caller, and the memory of the parameters and local variable of `Add`, `i`, `j`, and `result`, disappears.
4. `main` assigns the return value 7 to `d` and prints it. From C99, `return 0;` in `main` may be omitted.

```text
 While Add runs                      After Add returns
┌─────────────────────────┐        ┌─────────────────────────┐
│ Add   i = 3             │        │                         │
│       j = 4             │        │  (i, j, result freed)   │
│       result = 7        │        │                         │
├─────────────────────────┤        ├─────────────────────────┤
│ main  d = garbage       │        │ main  d = 7             │
└─────────────────────────┘        └─────────────────────────┘
```

*Figure 1. Memory during and after the call of the Add function*

In this way, the parameters and local variables of a function are created each time the function is called and disappear when it ends ([Chapter 6, Section 3.1](Concepts_Lecture.md#31-local-variables), [Section 4](Concepts_Lecture.md#4-function-call-overhead)).

---

<br>

## 4. Local and Global Variables

### 4.1 A Parameter Is a Copy of the Argument

Predict the result of the following code.

```c
#include <stdio.h>
int getPlus(int);

int main(void)
{
    int x = 3;
    printf("1. x: %d \n", x);
    printf("result: %d \n", getPlus(x));
    printf("2. x: %d \n", x);
}

int getPlus(int x) {
    x = x + 3;
    printf("3. x: %d \n", x);
    return x;
}
```

```text
1. x: 3 
3. x: 6 
result: 6 
2. x: 3 
```

The `x` of `main` and the parameter `x` of `getPlus` are different variables that only share a name. At the call, the value 3 of `main`'s `x` is copied into the parameter `x`, and `x = x + 3` inside `getPlus` changes only the parameter, to 6. So after `getPlus` ends, `main`'s `x` is still 3. Passing arguments by copying their values in this way is called **call by value** ([Chapter 6, Section 2.4](Concepts_Lecture.md#24-parameters-and-arguments)).

### 4.2 A Global Variable Is Shared by All Functions

Predict the result of the following code.

```c
#include <stdio.h>
int getPlus(void);
int x; // global variable

int main(void)
{
    x += 2;
    printf("1. x: %d \n", x);
    printf("result: %d \n", getPlus());
    printf("2. x: %d \n", x);
}

int getPlus(void) {
    x = x + 3;
    printf("3. x: %d \n", x);
    return x;
}
```

```text
1. x: 2 
3. x: 5 
result: 5 
2. x: 5 
```

`x` is a **global variable** declared outside all functions, so `main` and `getPlus` use the same memory. A global variable without an initial value is initialized to 0, so `x += 2` in `main` makes `x` 2. `x = x + 3` in `getPlus` changes the same global variable to 5, so the `x` printed in `main` after `getPlus` ends is also 5 ([Chapter 6, Section 3.2](Concepts_Lecture.md#32-global-variables)).

> **Caution:** A global variable can be changed by any function, which makes it hard to find where its value was changed. To exchange values between functions, use parameters and return values where possible.

---

<br>

## 5. Function Practice

The solution code of the following problems is the example files in this unit folder. Each file compiles with `gcc -std=c99 -Wall` without warnings, and the outputs are from actual runs. In programs whose messages end without `\n`, the next prompt follows the message directly in a real terminal.

### 5.1 Printing as Many Stars as Entered

**Problem:** Read an integer, pass it to a function, and write the function `showStar()` that prints that many `*`.

**Solution:** The `showStar` of Section 2.4 receives the number to print as the parameter `int n`. A `for` statement prints `*` n times, and there is no result to return, so the return type is `void`. If n is 0 or less, the loop never runs and nothing is printed.

**Code:** [Example_ShowStar.c](Example_ShowStar.c)

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>
void showStar(int n);

int main() {
    int num;
    printf(">> input value: ");
    scanf(" %d", &num);

    showStar(num);
}

void showStar(int n) {
    int i;
    for (i = 1; i <= n; i++) {
        printf("*");
    }
    return;
}
```

```text
>> input value: 5
*****
```

### 5.2 A Function That Tells Uppercase from Lowercase

**Problem:** Write and use a function `isUpper()` that receives a character and returns 1 for an uppercase letter, -1 for a lowercase letter, and 0 for anything that is not an English letter.

**Solution:** `isUpper()` returns the result of the test as an integer, and `main` chooses a message by that return value. Separating the test from the output lets `isUpper()` be reused unchanged in other programs. A `return` inside a function returns a value and ends the function at the same time, so if the first condition is true, the remaining conditions are not checked.

**Code:** [Example_IsUpper.c](Example_IsUpper.c)

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>
int isUpper(char ch);

int main()
{
    int ret;
    char alpha;
    printf(">> input char: ");
    scanf(" %c", &alpha);

    ret = isUpper(alpha);

    if (ret == 1) {
        printf("%c is a/an upper case!", alpha);
    }
    else if (ret == -1) {
        printf("%c is a/an lower case!", alpha);
    }
    else if (ret == 0) {
        printf("It's not an English alphabet!");
    }
}

int isUpper(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return 1;
    }
    else if (ch >= 'a' && ch <= 'z') {
        return -1;
    }
    else {
        return 0;
    }
}
```

```text
>> input char: Q
Q is a/an upper case!
```

```text
>> input char: q
q is a/an lower case!
```

```text
>> input char: 7
It's not an English alphabet!
```

### 5.3 A Power Function

**Problem:** Read two integers x and y and write the function `getPower()` that computes xʸ.

**Solution:** Initialize `xycal`, which stores the result, to 1, the identity of multiplication, and multiply by `x` y times. If y is 0, the loop does not run and x⁰ = 1 is returned.

**Code:** [Example_Power.c](Example_Power.c)

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>
int getPower(int x, int y);

int main()
{
    int x, y;

    printf(">> input two values: ");
    scanf(" %d %d", &x, &y);

    printf("%d to the power of %d: %d", x, y, getPower(x, y));
}

int getPower(int x, int y) {
    int i, xycal = 1;
    for (i = 0; i < y; i++) {
        xycal *= x;
    }
    return xycal;
}
```

```text
>> input two values: 2 10
2 to the power of 10: 1024
```

```text
>> input two values: 3 0
3 to the power of 0: 1
```

> **Caution:** If y is negative, the loop does not run and 1 is returned, so a value such as x⁻¹ cannot be obtained. Also, if the result exceeds the range of `int` (for example 2³¹), signed integer overflow occurs, which is undefined behavior.

### 5.4 A Function That Converts Degrees to Radians

**Problem:** Write the function `getRadian()` that converts an angle of 0°-359° to radians. Only 0-359 is assumed to be entered, so no range check is done. π is defined with `#define PI 3.14159`, and radian = degree / 180 × π.

**Solution:** The angle is received as an `int`, but the result has a fraction, so the return type is `double`. Dividing by a real constant, as in `deg / 180.0`, prevents integer division. Writing `deg / 180` would make 90 / 180 equal 0, so the result would be 0.

**Code:** [Example_Radian.c](Example_Radian.c)

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>
#define PI 3.14159
double getRadian(int deg);

int main()
{
    int deg;

    printf(">> input degree(0~359): ");
    scanf(" %d", &deg);

    printf("The radian value of %d degrees is %.2lf", deg, getRadian(deg));
}
double getRadian(int deg) {
    double caldeg;
    caldeg = (deg / 180.0) * PI;

    return caldeg;
}
```

```text
>> input degree(0~359): 90
The radian value of 90 degrees is 1.57
```

```text
>> input degree(0~359): 180
The radian value of 180 degrees is 3.14
```

### 5.5 Summing Only the Positive Numbers

**Problem:** Read ten integers in turn, check with the function `getSign()` whether each is positive, and print the sum of only the positive integers.

**Solution:** `getSign()` returns the result of the test as 1 or 0, so its return value can be used directly as a condition, as in `if (getSign(val))`. The input repeats ten times with `do-while`. The `getSign()` of this code also judges 0 as 1, but adding 0 does not change the sum, so the result is the same as adding only positive numbers. Code that solves the same task with a `for` statement and the condition `val > 0` is in [HW06 Problem 2](../../Coursework/HW06_Functions/Assignment-Explanation.md#3-problem-2-conditional-sum).

**Code:** [Example_PositiveSum.c](Example_PositiveSum.c)

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>
int getSign(int val);

int main()
{
    int count = 1, val, sum = 0;

    do {
        printf(">> (%d) input val: ", count);
        scanf(" %d", &val);

        if (getSign(val)) {
            sum += val;
        }
        count++;
    } while (count <= 10);

    printf("-> sum of positive values: %d", sum);
}
int getSign(int val) {
    if (val >= 0) {
        return 1;
    }
    else {
        return 0;
    }
}
```

```text
>> (1) input val: 3
>> (2) input val: -2
>> (3) input val: 5
>> (4) input val: 0
>> (5) input val: -7
>> (6) input val: 8
>> (7) input val: 1
>> (8) input val: -1
>> (9) input val: 4
>> (10) input val: 6
-> sum of positive values: 27
```

3 + 5 + 0 + 8 + 1 + 4 + 6 = 27.

---

<br>

## Summary

| Concept | Key Summary |
|:-----|:-----|
| Function | A block of code that receives input (parameters), does fixed work (body), and returns a result (return value). |
| Function definition | Consists of a header made of the return type, name, and parameter list, and a body inside braces. |
| Function prototype | A declaration that tells the compiler the return type and parameters in advance when the definition comes after the call. |
| Function call | Runs the function by passing arguments in the order of the parameters; the return value is stored in a variable or used directly in an expression. |
| `void` | Without a return value the return type is written as `void`, and without parameters `void` is written inside the parentheses. |
| Four forms | There are four forms of functions according to whether they have parameters and a return value. |
| Calls and memory | Parameters and local variables are created when the function is called and disappear when it ends. |
| Call by value | A parameter is a copy of the argument, so changing it inside the function does not change the caller's variable. |
| Global variable | Declared outside all functions and shared by all of them; it is initialized to 0 if it has no initial value. |

---

<br>

## Self-Check Questions

1. **Parts of a function:** A function that receives a radius r and returns the area of a circle πr² is to be written. Choose the function name, parameter, and return type, and write its prototype.

   <details>
   <summary>Answer</summary>

   For example, the name is `getCircleArea`, the parameter is `double r`, and since the result has a fraction, the return type is `double`. The prototype is `double getCircleArea(double r);`.

   </details>

2. **Prototype:** What happens with a C99 or later compiler if the prototype `int getPlus(int x);` is removed from the program of Section 2.2?

   <details>
   <summary>Answer</summary>

   There is no declaration when `main` calls `getPlus`, so the call becomes an implicit function declaration, which was removed in C99, and the compiler reports an error or a warning. The prototype must be put back, or the definition of `getPlus` moved before `main`.

   </details>

3. **Call by value:** Explain why the `x` of `main` is 3 even though `getPlus` of Section 4.1 changed its parameter to 6.

   <details>
   <summary>Answer</summary>

   At the call, the value 3 of `main`'s `x` is only copied into the parameter `x` of `getPlus`; the two variables occupy different memory. Inside `getPlus` only the copy changes, and the copy disappears when the function ends.

   </details>

4. **Global variables:** In the program of Section 4.2, how does the output change if `int x = 10;` is additionally declared inside `main`?

   <details>
   <summary>Answer</summary>

   Inside `main`, the local variable `x` hides the global variable, so `x += 2` makes the local variable 12 and `1. x: 12` is printed. `getPlus` changes the global variable `x` (0) to 3 and prints `3. x: 3` and `result: 3`, and the last line prints the local variable, giving `2. x: 12`.

   </details>

5. **Integer division:** If `(deg / 180.0) * PI` in `getRadian` of Section 5.4 is changed to `deg / 180 * PI`, what is the result when 90 is entered?

   <details>
   <summary>Answer</summary>

   `deg / 180` is an integer division, so 90 / 180 = 0, and 0 × π = 0 is returned, printing `0.00`. For angles of 180 or more only the quotient remains, so both 180 and 270 give 1 × π, which is wrong for 270.

   </details>
