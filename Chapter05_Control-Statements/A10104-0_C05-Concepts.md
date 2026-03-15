# Chapter 05 — Control Statements

> **Last Updated:** 2026-03-16
>
> **Textbook Reference:** *Warming-Up C Programming, 2nd Edition* — Chapter 5

---

## 📑 Table of Contents

- [1. Control Statements Overview](#1-control-statements-overview)
- [2. Conditional Statements](#2-conditional-statements)
  - [2.1 `if`](#21-if)
  - [2.2 Compound Statements / Blocks](#22-compound-statements--blocks)
  - [2.3 `if-else`](#23-if-else)
  - [2.4 `else if`](#24-else-if)
  - [2.5 Nested `if`](#25-nested-if)
  - [2.6 Multiple Independent `if`](#26-multiple-independent-if)
  - [2.7 `switch`](#27-switch)
  - [2.8 `if-else` vs `switch` Comparison](#28-if-else-vs-switch-comparison)
- [3. Loop Statements](#3-loop-statements)
  - [3.1 `for`](#31-for)
  - [3.2 `while`](#32-while)
  - [3.3 `do-while`](#33-do-while)
  - [3.4 Nested Loops](#34-nested-loops)
  - [3.5 `for` vs `while` vs `do-while` Comparison](#35-for-vs-while-vs-do-while-comparison)
- [4. Branch Statements](#4-branch-statements)
  - [4.1 `break`](#41-break)
  - [4.2 `continue`](#42-continue)
  - [4.3 `goto`](#43-goto)
  - [4.4 `return`](#44-return)
- [5. Common Patterns](#5-common-patterns)
  - [5.1 Counter and Accumulator](#51-counter-and-accumulator)
  - [5.2 Max/Min Tracking](#52-maxmin-tracking)
  - [5.3 Input Validation Loop](#53-input-validation-loop)
  - [5.4 Menu-Driven Program](#54-menu-driven-program)
- [Summary](#summary)

---

<br>

## 1. Control Statements Overview

By default, C executes statements **sequentially** (top to bottom). **Control statements** alter this flow by branching or repeating.

```
Program Flow
├── Sequential   ← default (top to bottom)
├── Conditional  ← choose which path to take
├── Loop         ← repeat a block
└── Branch       ← jump to another location
```

| Category | Purpose | C Keywords |
|:---------|:--------|:-----------|
| Conditional | Execute different blocks based on conditions | `if`, `else`, `else if`, `switch`, `case`, `default` |
| Loop | Repeat a block while a condition is true | `for`, `while`, `do-while` |
| Branch | Jump out of or skip within a block | `break`, `continue`, `goto`, `return` |

> **Key Point:** The **ternary operator** (`? :`) is a conditional *expression*, not a statement, but serves a similar purpose: `max = (a > b) ? a : b;`

---

<br>

## 2. Conditional Statements

### 2.1 `if`

The `if` statement executes a block **only when** the condition is true (non-zero).

**Syntax:**

```c
if (condition) {
    // executed when condition is true (non-zero)
}
```

**Execution flow:**

```
        ┌───────────┐
        │ condition │
        └────┬──────┘
        true │  false
             ▼          ──────► (skip)
       ┌────────────┐
       │ statement  │
       └────────────┘
             │
             ▼
        (next code)
```

```c
int score = 85;

if (score >= 60) {
    printf("Passed!\n");
}
```

> **Tip:** In C, any non-zero value is **true**, and zero is **false**. So `if (1)` always executes, `if (0)` never executes.

### 2.2 Compound Statements / Blocks

A **compound statement** (block) groups multiple statements with braces `{}`.

```c
if (score >= 90) {
    printf("Grade: A\n");
    printf("Excellent!\n");
}
```

Without braces, only the **first statement** belongs to `if`:

```c
if (score >= 90)
    printf("Grade: A\n");      // belongs to if
    printf("Excellent!\n");    // ALWAYS executes (not part of if!)
```

> **Warning:** Always use braces `{}` even for single statements. This prevents bugs when adding lines later and makes intent clear.

### 2.3 `if-else`

Provides two paths: one for true, one for false.

**Syntax:**

```c
if (condition) {
    // executed when true
} else {
    // executed when false
}
```

**Execution flow:**

```
       ┌───────────┐
       │ condition │
       └────┬──────┘
   true     │     false
     ▼      │       ▼
┌───────┐   │   ┌────────┐
│ if    │   │   │ else   │
│ block │   │   │ block  │
└───────┘   │   └────────┘
   │        │        │
   └────────┴────────┘
            ▼
       (next code)
```

```c
int num = 7;

if (num % 2 == 0) {
    printf("%d is even\n", num);
} else {
    printf("%d is odd\n", num);
}
```

**When to use `if-else` vs two separate `if` statements:**

```c
// if-else: exactly one branch executes (mutually exclusive)
if (x > 0) {
    printf("positive\n");
} else {
    printf("non-positive\n");
}

// Two separate ifs: both conditions are checked independently
if (x > 0) {
    printf("positive\n");
}
if (x % 2 == 0) {
    printf("even\n");
}
```

### 2.4 `else if`

The `else if` ladder checks conditions **sequentially**. Once a true condition is found, its block executes and all remaining conditions are **skipped**.

**Syntax:**

```c
if (condition1) {
    // block 1
} else if (condition2) {
    // block 2
} else if (condition3) {
    // block 3
} else {
    // default block (optional)
}
```

The final `else` is **optional** but recommended as a catch-all.

```c
int score;
printf("Enter score: ");
scanf("%d", &score);

if (score >= 90) {
    printf("Grade: A\n");
} else if (score >= 80) {
    printf("Grade: B\n");
} else if (score >= 70) {
    printf("Grade: C\n");
} else if (score >= 60) {
    printf("Grade: D\n");
} else {
    printf("Grade: F\n");
}
```

> **Key Point:** Because conditions are checked in order, `score >= 80` implicitly means `80 <= score < 90` (since `score >= 90` was already rejected). You do **not** need `score >= 80 && score < 90`.

### 2.5 Nested `if`

An `if` statement inside another `if` or `else` block.

```c
int x, y;
scanf("%d %d", &x, &y);

if (x == 0 && y == 0) {
    printf("Origin\n");
} else if (x == 0) {
    printf("On the y-axis\n");
} else if (y == 0) {
    printf("On the x-axis\n");
} else {
    if (x > 0 && y > 0) {
        printf("Quadrant 1\n");
    } else if (x < 0 && y > 0) {
        printf("Quadrant 2\n");
    } else if (x < 0 && y < 0) {
        printf("Quadrant 3\n");
    } else {
        printf("Quadrant 4\n");
    }
}
```

> **Warning:** Deeply nested `if` statements become hard to read. Consider using `else if` ladders or early returns to flatten the structure.

### 2.6 Multiple Independent `if`

When conditions are **not mutually exclusive**, use separate `if` statements. Each condition is evaluated independently.

```c
int temp = 35;

if (temp > 30) {
    printf("Hot\n");       // prints
}
if (temp > 20) {
    printf("Warm\n");      // also prints
}
if (temp > 10) {
    printf("Mild\n");      // also prints
}
```

All three conditions are true, so all three messages print. Compare this to `else if`, where only the **first** matching block would execute.

### 2.7 `switch`

The `switch` statement selects a block based on the value of an **integer or character expression**. It is often cleaner than a long `else if` ladder for discrete value matching.

**Syntax:**

```c
switch (expression) {
case value1:
    // statements
    break;
case value2:
    // statements
    break;
// ...
default:
    // executed if no case matches
}
```

```c
char unit;
printf("Temperature unit (C/F): ");
scanf(" %c", &unit);

switch (unit) {
case 'C':
case 'c':
    printf("Celsius\n");
    break;
case 'F':
case 'f':
    printf("Fahrenheit\n");
    break;
default:
    printf("Invalid unit!\n");
}
```

**Critical rules:**

| Rule | Detail |
|:-----|:-------|
| Expression type | Must be `int` or `char` (integer types). **Not** `float`, `double`, or `string`. |
| Case labels | Must be **constant** values (not variables). |
| `break` | Required to prevent **fall-through**. Without it, execution continues to the next case. |
| `default` | Optional. Handles values not matched by any case. |
| Duplicate cases | Not allowed. Each case label must be unique. |

**Fall-through behavior (missing `break`):**

```c
int n = 1;
switch (n) {
case 1:
    printf("one\n");      // prints
    // no break!
case 2:
    printf("two\n");      // also prints! (fall-through)
    break;
case 3:
    printf("three\n");
    break;
}
// Output: one
//         two
```

> **Warning:** Forgetting `break` is one of the most common bugs in C. Intentional fall-through (like grouping `'C'` and `'c'`) should be clearly documented.

**Using `switch` with integer ranges (score grading):**

```c
int score = 85;
switch (score / 10) {
case 10:
case 9:
    printf("A\n");
    break;
case 8:
    printf("B\n");
    break;
case 7:
    printf("C\n");
    break;
case 6:
    printf("D\n");
    break;
default:
    printf("F\n");
}
```

### 2.8 `if-else` vs `switch` Comparison

| Feature | `if-else` | `switch` |
|:--------|:----------|:---------|
| Condition type | Any boolean expression | Integer/character equality only |
| Range checks | `score >= 90` | Not directly (use `score / 10`) |
| Multiple values | `if (x == 1 \|\| x == 2)` | `case 1: case 2:` (fall-through) |
| Float/string | Supported | Not supported |
| Readability | Better for ranges/complex conditions | Better for many discrete values |
| Performance | Sequential check | May use jump table (faster for many cases) |

> **Tip:** Use `switch` when comparing a single variable against many **constant integer/char values**. Use `if-else` for ranges, floating-point comparisons, or complex conditions.

---

<br>

## 3. Loop Statements

### 3.1 `for`

The `for` loop is ideal when the **number of iterations is known** in advance.

**Syntax:**

```c
for (initialization; condition; update) {
    // loop body
}
```

**Execution flow:**

```
      init
        │
        ▼
┌─► condition ──false──► exit
│       │
│      true
│       ▼
│   loop body
│       │
│       ▼
└── update
```

1. **Initialization** — executes once before the loop starts.
2. **Condition** — checked before each iteration. If false, the loop exits.
3. **Loop body** — executes if condition is true.
4. **Update** — executes after each iteration, then goes back to step 2.

```c
// Print 1 to 5
for (int i = 1; i <= 5; i++) {
    printf("%d ", i);
}
// Output: 1 2 3 4 5
```

**Common patterns:**

```c
// Count down
for (int i = 10; i >= 1; i--) {
    printf("%d ", i);
}

// Step by 2
for (int i = 0; i <= 10; i += 2) {
    printf("%d ", i);
}

// Sum from 1 to 100
int sum = 0;
for (int i = 1; i <= 100; i++) {
    sum += i;
}
printf("Sum: %d\n", sum);  // 5050
```

**Omitting parts of `for`:**

```c
int i = 0;
for ( ; i < 5; ) {      // init and update omitted
    printf("%d ", i);
    i++;
}

for (;;) {               // infinite loop (all parts omitted)
    // use break to exit
}
```

> **Warning:** An infinite loop without `break` or `return` will run forever and freeze your program.

### 3.2 `while`

The `while` loop is ideal when the **termination condition depends on runtime input** or events.

**Syntax:**

```c
while (condition) {
    // loop body
}
```

**Execution flow:**

```
    ┌─► condition ──false──► exit
    │       │
    │      true
    │       ▼
    │   loop body
    │       │
    └───────┘
```

The condition is checked **before** each iteration. If false initially, the body never executes.

```c
// Sentinel-controlled loop: -1 to stop
int num, sum = 0, count = 0;

printf("Enter number (-1 to stop): ");
scanf("%d", &num);

while (num != -1) {
    sum += num;
    count++;
    printf("Enter number (-1 to stop): ");
    scanf("%d", &num);
}

if (count > 0) {
    printf("Sum: %d, Average: %.2f\n", sum, (double)sum / count);
}
```

**Infinite loop with `break`:**

```c
while (1) {
    int n;
    printf("Enter a positive number: ");
    scanf("%d", &n);
    if (n > 0) {
        printf("You entered: %d\n", n);
        break;
    }
    printf("Invalid! Try again.\n");
}
```

### 3.3 `do-while`

The `do-while` loop **always executes at least once**, then checks the condition.

**Syntax:**

```c
do {
    // loop body
} while (condition);  // <-- semicolon required!
```

**Execution flow:**

```
    ┌───────┐
    │       ▼
    │   loop body(execute first)
    │       │
    │       ▼
    │   condition ──false──► exit
    │       │
    └──── true
```

```c
int choice;
do {
    printf("1. Play  2. Quit\n");
    printf("Choice: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > 2) {
        printf("Invalid choice!\n");
    }
} while (choice != 2);
printf("Goodbye!\n");
```

> **Warning:** Do not forget the **semicolon** after `while(condition);` in a `do-while` loop. This is a common syntax error.

**Guaranteed single execution:**

```c
// do-while: body always runs at least once
int x = 100;
do {
    printf("x = %d\n", x);  // prints once even though x > 10
} while (x < 10);

// while: body may never run
while (x < 10) {
    printf("x = %d\n", x);  // never prints
}
```

### 3.4 Nested Loops

A loop inside another loop. The **inner loop completes all iterations** for each single iteration of the outer loop.

**Left-aligned triangle pattern:**

```c
int n = 4;
for (int i = 1; i <= n; i++) {        // rows
    for (int j = 1; j <= i; j++) {    // columns
        printf("*");
    }
    printf("\n");
}
```

Output:
```
*
**
***
****
```

**Right-aligned triangle pattern:**

```c
int n = 4;
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n - i; j++) {   // leading spaces
        printf(" ");
    }
    for (int j = 1; j <= i; j++) {       // stars
        printf("*");
    }
    printf("\n");
}
```

Output:
```
   *
  **
 ***
****
```

**Multiplication table (2D output):**

```c
for (int i = 1; i <= 9; i++) {
    for (int j = 1; j <= 9; j++) {
        printf("%3d", i * j);
    }
    printf("\n");
}
```

**Alternating sign sum (`1-2+3-4+...+9-10`):**

```c
int sum = 0;
for (int i = 1; i <= 10; i++) {
    if (i % 2 == 1) {
        sum += i;
    } else {
        sum -= i;
    }
}
printf("Result: %d\n", sum);  // -5
```

### 3.5 `for` vs `while` vs `do-while` Comparison

| Feature | `for` | `while` | `do-while` |
|:--------|:------|:--------|:-----------|
| Best for | Known iteration count | Unknown count, event-driven | Must execute at least once |
| Condition check | Before each iteration | Before each iteration | After each iteration |
| Minimum executions | 0 | 0 | 1 |
| Typical use | Counting, iterating arrays | Sentinel loops, reading input | Input validation, menus |
| Syntax | `for (init; cond; upd)` | `while (cond)` | `do { } while (cond);` |

> **Key Point:** Any `for` loop can be rewritten as a `while` loop and vice versa. Choose whichever makes the intent clearest.

```c
// Equivalent loops:

// for version
for (int i = 0; i < 5; i++) {
    printf("%d ", i);
}

// while version
int i = 0;
while (i < 5) {
    printf("%d ", i);
    i++;
}
```

---

<br>

## 4. Branch Statements

### 4.1 `break`

`break` immediately exits the **innermost enclosing loop** or `switch` statement.

```c
for (int i = 1; i <= 100; i++) {
    if (i * i > 50) {
        printf("First i where i^2 > 50: %d\n", i);
        break;  // exits the for loop
    }
}
```

In nested loops, `break` only exits the **inner** loop:

```c
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        if (j == 1) {
            break;  // exits inner loop only
        }
        printf("(%d,%d) ", i, j);
    }
}
// Output: (0,0) (1,0) (2,0)
```

### 4.2 `continue`

`continue` skips the **rest of the current iteration** and jumps to the next iteration (or to the condition check in `while`/`do-while`, or to the update step in `for`).

```c
// Print odd numbers only
for (int i = 1; i <= 10; i++) {
    if (i % 2 == 0) {
        continue;  // skip even numbers
    }
    printf("%d ", i);
}
// Output: 1 3 5 7 9
```

> **Tip:** `continue` in a `for` loop jumps to the **update** expression (`i++`), not the condition. In a `while` loop, it jumps directly to the **condition** check — so make sure the loop variable is updated before `continue`, or you'll get an infinite loop.

### 4.3 `goto`

`goto` unconditionally jumps to a labeled statement. It is **generally avoided** because it makes code hard to follow (spaghetti code).

```c
for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
        if (i + j == 15) {
            goto found;  // break out of both loops
        }
    }
}
found:
printf("Done\n");
```

> **Warning:** Avoid `goto` in almost all cases. The only acceptable use is breaking out of deeply nested loops. Use `break`, `continue`, or functions instead.

### 4.4 `return`

`return` exits the **current function** and optionally returns a value. In `main`, it terminates the program.

```c
int find_first_negative(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            return arr[i];  // exits function immediately
        }
    }
    return 0;  // no negative found
}
```

---

<br>

## 5. Common Patterns

### 5.1 Counter and Accumulator

A **counter** tracks how many times something occurs. An **accumulator** tracks a running total.

```c
int sum = 0;    // accumulator
int count = 0;  // counter
int num;

printf("Enter numbers (0 to stop):\n");
while (1) {
    scanf("%d", &num);
    if (num == 0) {
        break;
    }
    sum += num;
    count++;
}

if (count > 0) {
    printf("Sum: %d\n", sum);
    printf("Count: %d\n", count);
    printf("Average: %.2f\n", (double)sum / count);
}
```

> **Key Point:** Always cast to `double` before dividing when you need a floating-point average: `(double)sum / count`. Integer division `sum / count` truncates the decimal part.

### 5.2 Max/Min Tracking

Initialize max/min with the **first input**, then update as new values arrive.

```c
int num, max, min, count = 0;

while (1) {
    printf("Input value (0 to stop): ");
    scanf("%d", &num);
    if (num == 0) {
        break;
    }

    if (count == 0) {
        max = min = num;  // first value initializes both
    } else {
        if (num > max) max = num;
        if (num < min) min = num;
    }
    count++;
}

if (count > 0) {
    printf("MAX: %d, MIN: %d\n", max, min);
}
```

You can also use the **ternary operator** for compact max/min:

```c
int a, b, c;
scanf("%d %d %d", &a, &b, &c);

int max = (a > b) ? a : b;
max = (max > c) ? max : c;
printf("Max: %d\n", max);
```

### 5.3 Input Validation Loop

Use `do-while` to ensure valid input before proceeding.

```c
int score;
do {
    printf("Enter score (0-100): ");
    scanf("%d", &score);
    if (score < 0 || score > 100) {
        printf("Error! Score must be 0-100.\n");
    }
} while (score < 0 || score > 100);

printf("Valid score: %d\n", score);
```

### 5.4 Menu-Driven Program

Combine `while(1)` with `switch` for interactive menus.

```c
#include <stdio.h>

int main() {
    char menu;

    while (1) {
        printf("========================\n");
        printf("1. Option A\n");
        printf("2. Option B\n");
        printf("3. Quit\n");
        printf("========================\n");

        // Input validation with do-while
        do {
            printf("Select: ");
            scanf(" %c", &menu);
            if (menu < '1' || menu > '3') {
                printf("Invalid! Try again.\n");
            }
        } while (menu < '1' || menu > '3');

        if (menu == '3') {
            printf("Goodbye!\n");
            break;
        }

        switch (menu) {
        case '1':
            printf("You selected Option A\n");
            break;
        case '2':
            printf("You selected Option B\n");
            break;
        }
    }

    return 0;
}
```

> **Tip:** When reading a `char` with `scanf`, use `" %c"` (with a leading space) to skip any leftover whitespace/newline characters in the input buffer.

---

<br>

## Summary

| Concept | Key Takeaway |
|:--------|:-------------|
| Control Statements | Alter sequential flow: conditional, loop, branch |
| `if` | Executes block when condition is non-zero (true) |
| Compound Statement | `{}` groups multiple statements; always use braces |
| `if-else` | Two mutually exclusive paths based on one condition |
| `else if` | Sequential condition checking; first match wins, rest skipped |
| Nested `if` | `if` inside another `if`/`else`; avoid deep nesting |
| Multiple `if` | Each condition checked independently; not mutually exclusive |
| `switch` | Integer/char equality matching; `break` required to prevent fall-through |
| `switch` vs `if-else` | `switch` for discrete values; `if-else` for ranges/complex conditions |
| `for` | Best for known iteration count; `for(init; cond; update)` |
| `while` | Condition checked first; best for sentinel/event-driven loops |
| `do-while` | Body executes at least once; semicolon after `while()` |
| Nested Loops | Inner loop completes fully per outer iteration; used for 2D patterns |
| `break` | Exits innermost loop or `switch` |
| `continue` | Skips to next iteration; jumps to update (`for`) or condition (`while`) |
| `goto` | Jumps to label; generally avoided (spaghetti code) |
| `return` | Exits current function; in `main`, terminates program |
| Counter/Accumulator | `count++` and `sum += val` for tallying and totaling |
| Max/Min Tracking | Initialize with first input; update with each comparison |
| Input Validation | `do-while` ensures at least one prompt before checking |
| Menu-Driven | `while(1)` + `switch` + `do-while` for interactive programs |
| Ternary Operator | `(cond) ? val_true : val_false` — compact inline conditional |

---
