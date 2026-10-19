# Chapter 04 — Operators

> **Last Updated:** 2026-03-16

---

## Table of Contents

- [1. Expressions and Operands](#1-expressions-and-operands)
  - [1.1 Expressions](#11-expressions)
  - [1.2 Operators and Operands](#12-operators-and-operands)
- [2. Arithmetic Operators](#2-arithmetic-operators)
  - [2.1 Operators](#21-operators)
  - [2.2 Integer Division vs Float Division](#22-integer-division-vs-float-division)
  - [2.3 Modulo Operator](#23-modulo-operator)
  - [2.4 Math Formula Conversion to C](#24-math-formula-conversion-to-c)
- [3. Increment and Decrement Operators](#3-increment-and-decrement-operators)
  - [3.1 Prefix vs Postfix](#31-prefix-vs-postfix)
  - [3.2 Standalone vs In Expressions](#32-standalone-vs-in-expressions)
  - [3.3 Restrictions](#33-restrictions)
  - [3.4 Detailed Trace Example](#34-detailed-trace-example)
- [4. Relational Operators](#4-relational-operators)
  - [4.1 Comparison Operators](#41-comparison-operators)
  - [4.2 Result Type](#42-result-type)
  - [4.3 Common Mistake: `=` vs `==`](#43-common-mistake--vs-)
- [5. Logical Operators](#5-logical-operators)
  - [5.1 AND, OR, NOT](#51-and-or-not)
  - [5.2 Truth Tables](#52-truth-tables)
  - [5.3 Short-Circuit Evaluation](#53-short-circuit-evaluation)
  - [5.4 Truthiness in C](#54-truthiness-in-c)
- [6. Bitwise Operators](#6-bitwise-operators)
  - [6.1 Bitwise AND, OR, XOR, NOT](#61-bitwise-and-or-xor-not)
  - [6.2 Shift Operators](#62-shift-operators)
  - [6.3 Practical Example: RGB Color](#63-practical-example-rgb-color)
- [7. Assignment Operators](#7-assignment-operators)
  - [7.1 Simple and Compound Assignment](#71-simple-and-compound-assignment)
  - [7.2 Chained Assignment](#72-chained-assignment)
- [8. Conditional Operator](#8-conditional-operator)
  - [8.1 Ternary Operator](#81-ternary-operator)
  - [8.2 Equivalent if/else](#82-equivalent-ifelse)
- [9. Type Conversion in Expressions](#9-type-conversion-in-expressions)
  - [9.1 Implicit Promotion](#91-implicit-promotion)
  - [9.2 Cast Operator](#92-cast-operator)
  - [9.3 sizeof of Expression Result](#93-sizeof-of-expression-result)
- [10. Operator Precedence and Associativity](#10-operator-precedence-and-associativity)
  - [10.1 Precedence Table](#101-precedence-table)
  - [10.2 Associativity](#102-associativity)
  - [10.3 Use Parentheses When in Doubt](#103-use-parentheses-when-in-doubt)
- [Summary](#summary)

---

<br>

## 1. Expressions and Operands

### 1.1 Expressions

An **expression** is any element in C that produces a value. Expressions include:

| Kind | Example | Value |
|:-----|:--------|:------|
| Constant (literal) | `42` | `42` |
| Variable | `x` (where `x = 10`) | `10` |
| Operation | `3 + 4` | `7` |
| Function call | `sqrt(9.0)` | `3.0` |
| Assignment | `x = 5` | `5` |

Every expression has a **type** and a **value**. Even an assignment like `x = 5` is an expression whose value is `5`.

```c
int x;
x = 5;              // assignment expression, value is 5
printf("%d\n", x=5); // prints 5 — assignment is an expression
```

### 1.2 Operators and Operands

An **operator** is a symbol that performs an operation on one or more **operands**.

Operators are classified by the **number of operands** they take:

| Category | Operands | Examples |
|:---------|:--------:|:--------|
| Unary | 1 | `sizeof(x)`, `-x`, `+x`, `!a`, `~a`, `++x`, `x--` |
| Binary | 2 | `a + b`, `a = b`, `a > b`, `a && b` |
| Ternary | 3 | `a ? b : c` |

```c
int a = 10, b = 3;

sizeof(a);    // unary — one operand (a)
a + b;        // binary — two operands (a, b)
a > b ? a : b; // ternary — three operands (a>b, a, b)
```

---

<br>

## 2. Arithmetic Operators

### 2.1 Operators

| Operator | Name | Example | Result |
|:--------:|:-----|:--------|:-------|
| `+` | Addition | `7 + 3` | `10` |
| `-` | Subtraction | `7 - 3` | `4` |
| `*` | Multiplication | `7 * 3` | `21` |
| `/` | Division | `7 / 3` | `2` (integer) |
| `%` | Modulo (remainder) | `7 % 3` | `1` |
| `+x` | Unary plus | `+5` | `5` |
| `-x` | Unary minus (negation) | `-5` | `-5` |

> **Note:** Unary `+` and `-` are different from binary `+` and `-`. Unary operates on a single operand: `+x` is the value itself, `-x` negates the value.

### 2.2 Integer Division vs Float Division

When **both operands** of `/` are integers, C performs **integer division** — the fractional part is **truncated** (not rounded).

```c
int a = 7, b = 2;
printf("%d\n", a / b);       // 3  (not 3.5 — truncated!)
printf("%d\n", -7 / 2);      // -3 (truncates toward zero)
```

To get a floating-point result, **at least one operand** must be a floating-point type:

```c
int a = 7, b = 2;
double result;

result = a / b;              // int / int = 3 → assigned as 3.0
result = (double)a / b;      // double / int = 3.5
result = a / (double)b;      // int / double = 3.5
result = 7.0 / 2;            // double / int = 3.5
```

> **Warning:** `result = a / b;` performs integer division **first** (result: 3), then converts 3 to 3.0 for assignment. The cast or literal must appear **in the division itself**, not after.

### 2.3 Modulo Operator

The `%` (modulo) operator returns the **remainder** of integer division. It works **only with integer operands**.

```c
printf("%d\n", 10 % 3);   // 1   (10 = 3*3 + 1)
printf("%d\n", 10 % 5);   // 0   (10 = 5*2 + 0)
printf("%d\n", -7 % 2);   // -1  (sign follows dividend in C99+)
```

```c
// ❌ Compile error — % does not work with floats
// double r = 7.5 % 2.0;
```

Common use cases:
- **Even/odd check:** `n % 2 == 0` means even.
- **Extracting digits:** `n % 10` gives the last digit.
- **Cyclic wraparound:** `i % N` keeps `i` in range `[0, N-1]`.

### 2.4 Math Formula Conversion to C

Mathematical notation must be rewritten using C operators. Key rules:
- Multiplication must be explicit (`2x` becomes `2*x`).
- Division uses `/`, and you must handle integer vs float division.
- Exponents use repeated multiplication or `pow()` from `<math.h>`.

| Math Formula | C Expression | Notes |
|:-------------|:-------------|:------|
| (a + b) / 2 | `(a + b) / 2.0` | Use `2.0` to avoid integer division |
| C = 5/9 (F - 32) | `9.0 / 5 * (F - 32)` | `9/5` would be `1` (integer division!) |
| x^3 + 2x - 5 | `x*x*x + 2*x - 5` | Explicit multiplication; no `^` operator for power |
| (a + b) / (a^2 * b^2) | `(double)(a + b) / (a*a * b*b)` | Cast to avoid integer truncation |

```c
// Fahrenheit to Celsius
int F = 100;
double C = 5.0 / 9 * (F - 32);   // 37.777...
// ❌ Wrong: 5/9 * (F - 32) → 0 * 68 = 0 (integer division!)

// Average of two integers
int a = 7, b = 4;
double avg = (a + b) / 2.0;       // 5.5
// ❌ Wrong: (a + b) / 2 → 11 / 2 = 5 (integer division!)

// Polynomial: x^3 + 2x - 5
int x = 3;
int result = x*x*x + 2*x - 5;    // 27 + 6 - 5 = 28

// Fraction with integer operands
int p = 3, q = 4;
double frac = (double)(p + q) / (p*p * q*q);  // 7.0 / 144 = 0.048611...
```

---

<br>

## 3. Increment and Decrement Operators

### 3.1 Prefix vs Postfix

| Operator | Name | Action |
|:--------:|:-----|:-------|
| `++x` | Prefix increment | Increment x **first**, then use the new value |
| `--x` | Prefix decrement | Decrement x **first**, then use the new value |
| `x++` | Postfix increment | Use the current value of x **first**, then increment |
| `x--` | Postfix decrement | Use the current value of x **first**, then decrement |

### 3.2 Standalone vs In Expressions

When used **standalone** (as the only operation on a line), prefix and postfix produce the **same effect**:

```c
int x = 5;
x++;    // x becomes 6
++x;    // x becomes 7
// Both just increment x by 1 — no difference in standalone use
```

The difference appears **inside expressions**:

```c
int a, x;

// Prefix: increment FIRST, then use
x = 5;
a = ++x;   // x becomes 6, then a = 6
// Result: x = 6, a = 6

// Postfix: use FIRST, then increment
x = 5;
a = x++;   // a = 5 (old value), then x becomes 6
// Result: x = 6, a = 5
```

> **Key Point:** Think of prefix as "change, then read" and postfix as "read, then change."

### 3.3 Restrictions

`++` and `--` can **only** be applied to variables (lvalues). They cannot be used on constants or general expressions.

```c
int count = 5;
count++;        // ✅ OK — variable
++count;        // ✅ OK — variable

// 10++;         // ❌ Error — constant
// (count+1)--;  // ❌ Error — expression, not a variable
// ++(a+b);      // ❌ Error — expression
```

### 3.4 Detailed Trace Example

```c
#include <stdio.h>

int main(void) {
    int a = 5, b = 5;

    printf("a   = %d\n", a);       // a   = 5
    printf("a++ = %d\n", a++);     // a++ = 5  (prints 5, then a becomes 6)
    printf("a   = %d\n", a);       // a   = 6

    printf("b   = %d\n", b);       // b   = 5
    printf("++b = %d\n", ++b);     // ++b = 6  (b becomes 6, then prints 6)
    printf("b   = %d\n", b);       // b   = 6

    return 0;
}
```

Step-by-step trace:

| Line | Expression | Printed Value | `a` after | `b` after |
|:-----|:-----------|:------------:|:---------:|:---------:|
| `printf("a   = %d\n", a)` | `a` | 5 | 5 | 5 |
| `printf("a++ = %d\n", a++)` | `a++` | 5 | 6 | 5 |
| `printf("a   = %d\n", a)` | `a` | 6 | 6 | 5 |
| `printf("b   = %d\n", b)` | `b` | 5 | 6 | 5 |
| `printf("++b = %d\n", ++b)` | `++b` | 6 | 6 | 6 |
| `printf("b   = %d\n", b)` | `b` | 6 | 6 | 6 |

---

<br>

## 4. Relational Operators

### 4.1 Comparison Operators

Relational operators compare two values and produce an integer result.

| Operator | Meaning | Example | Result |
|:--------:|:--------|:--------|:------:|
| `>` | Greater than | `5 > 3` | `1` |
| `<` | Less than | `5 < 3` | `0` |
| `>=` | Greater than or equal | `5 >= 5` | `1` |
| `<=` | Less than or equal | `5 <= 3` | `0` |
| `==` | Equal to | `5 == 5` | `1` |
| `!=` | Not equal to | `5 != 3` | `1` |

### 4.2 Result Type

In C, relational expressions always evaluate to an `int`: **1 for true**, **0 for false**. There is no dedicated `bool` type in C89/C90.

```c
int result;
result = (10 > 5);      // result = 1 (true)
result = (10 == 5);     // result = 0 (false)
printf("%d\n", 3 < 7);  // prints 1
printf("%d\n", 3 > 7);  // prints 0
```

### 4.3 Common Mistake: `=` vs `==`

| Symbol | Meaning | Usage |
|:------:|:--------|:------|
| `=` | **Assignment** | `x = 5;` stores 5 in x |
| `==` | **Equality comparison** | `x == 5` checks if x equals 5 |

```c
int x = 10;

if (x == 5) { ... }  // ✅ Comparison — checks if x is 5
if (x = 5)  { ... }  // ⚠ Assignment — sets x to 5, then checks if 5 is non-zero (always true!)
```

> **Warning:** `if (x = 5)` compiles without error but it assigns 5 to x and always evaluates to true (since 5 is non-zero). This is one of the most common bugs in C. Some compilers issue a warning, but not all.

---

<br>

## 5. Logical Operators

### 5.1 AND, OR, NOT

Logical operators combine or negate boolean conditions.

| Operator | Name | Description | Example |
|:--------:|:-----|:------------|:--------|
| `&&` | Logical AND | True if **both** operands are true | `(a > 0) && (b > 0)` |
| `\|\|` | Logical OR | True if **at least one** operand is true | `(a > 0) \|\| (b > 0)` |
| `!` | Logical NOT | Inverts true/false | `!(a > 0)` |

```c
int age = 25, income = 3000;

// AND: both conditions must be true
if (age >= 20 && income >= 2000)
    printf("Eligible\n");

// OR: at least one condition must be true
if (age < 18 || age > 65)
    printf("Special rate\n");

// NOT: inverts the condition
if (!0)
    printf("This prints\n");  // !0 = 1 (true)
```

### 5.2 Truth Tables

**AND (`&&`)**

| A | B | A && B |
|:-:|:-:|:------:|
| 0 | 0 | 0 |
| 0 | 1 | 0 |
| 1 | 0 | 0 |
| 1 | 1 | 1 |

**OR (`||`)**

| A | B | A \|\| B |
|:-:|:-:|:--------:|
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 1 |

**NOT (`!`)**

| A | !A |
|:-:|:--:|
| 0 | 1 |
| non-zero | 0 |

### 5.3 Short-Circuit Evaluation

C evaluates logical expressions **left to right** and **stops as soon as the result is determined**:

- **`&&`:** If the left operand is **false (0)**, the right operand is **not evaluated** (result is already 0).
- **`||`:** If the left operand is **true (non-zero)**, the right operand is **not evaluated** (result is already 1).

```c
int a = 0, b = 5;

// Short-circuit AND: a is 0 (false), so (b++) is never evaluated
if (a && b++) {
    // not entered
}
printf("b = %d\n", b);  // b = 5 (b++ was skipped!)

// Short-circuit OR: a is 0 (false), so right side IS evaluated
a = 0;
b = 5;
if (a || b++) {
    // entered (b++ evaluates to 5, which is true)
}
printf("b = %d\n", b);  // b = 6 (b++ was executed)
```

> **Tip:** Short-circuit evaluation is useful for **guarding** potentially dangerous operations:
> ```c
> if (b != 0 && a / b > 2) { ... }  // division only happens if b != 0
> ```

### 5.4 Truthiness in C

C does **not** have a native boolean type (in C89). Instead:
- **0** is treated as **false**.
- **Any non-zero value** (positive or negative) is treated as **true**.

```c
int x = -5;
if (x)   printf("true\n");   // prints "true" — x is non-zero
if (!0)  printf("true\n");   // prints "true" — !0 = 1

printf("%d\n", !0);    // 1
printf("%d\n", !5);    // 0  (any non-zero becomes 0)
printf("%d\n", !-3);   // 0  (negative non-zero is also true, so !(-3) = 0)
```

> **Key Point:** The result of `!`, `&&`, and `||` is always `0` or `1` (type `int`), even though the input can be any integer value.

---

<br>

## 6. Bitwise Operators

Bitwise operators work on the **individual bits** of integer values.

### 6.1 Bitwise AND, OR, XOR, NOT

| Operator | Name | Description |
|:--------:|:-----|:------------|
| `&` | Bitwise AND | 1 only if **both** bits are 1 |
| `\|` | Bitwise OR | 1 if **at least one** bit is 1 |
| `^` | Bitwise XOR | 1 if bits are **different** |
| `~` | Bitwise NOT | Flips all bits (one's complement) |

Bit-level truth table:

| a | b | a & b | a \| b | a ^ b | ~a |
|:-:|:-:|:-----:|:------:|:-----:|:--:|
| 0 | 0 | 0 | 0 | 0 | 1 |
| 0 | 1 | 0 | 1 | 1 | 1 |
| 1 | 0 | 0 | 1 | 1 | 0 |
| 1 | 1 | 1 | 1 | 0 | 0 |

```c
unsigned char a = 0xB5;  // 1011 0101
unsigned char b = 0x6D;  // 0110 1101

printf("a & b = %02X\n", a & b);   // 0010 0101 = 0x25
printf("a | b = %02X\n", a | b);   // 1111 1101 = 0xFD
printf("a ^ b = %02X\n", a ^ b);   // 1101 1000 = 0xD8
printf("~a    = %02X\n", (unsigned char)~a);  // 0100 1010 = 0x4A
```

> **Warning:** Do not confuse bitwise operators (`&`, `|`) with logical operators (`&&`, `||`). Bitwise operators work bit-by-bit on integers; logical operators treat the entire value as true/false.

### 6.2 Shift Operators

| Operator | Name | Description |
|:--------:|:-----|:------------|
| `<<` | Left shift | Shift bits left by n positions; fills with 0 on the right |
| `>>` | Right shift | Shift bits right by n positions; fills with 0 (unsigned) or sign bit (signed) |

```c
unsigned char x = 0x0D;    // 0000 1101 = 13

printf("%02X\n", x << 1);  // 0001 1010 = 0x1A = 26  (×2)
printf("%02X\n", x << 4);  // 1101 0000 = 0xD0 = 208 (×16)
printf("%02X\n", x >> 1);  // 0000 0110 = 0x06 = 6   (÷2)
printf("%02X\n", x >> 2);  // 0000 0011 = 0x03 = 3   (÷4)
```

> **Tip:** Left shifting by n is equivalent to multiplying by 2^n. Right shifting by n is equivalent to dividing by 2^n (for unsigned values).

### 6.3 Practical Example: RGB Color

In a 32-bit RGB model, a single `unsigned int` stores three color channels (and an unused high byte):

```
Bit position:  31──24  23──16  15───8   7───0
               [ 0x00 ][ Blue ][ Green ][ Red  ]
```

**Combining R, G, B into a single RGB value** (needed for Q3):

Use left shift (`<<`) to position each channel, then OR (`|`) to combine:

```c
unsigned int red = 255, green = 0, blue = 130;

unsigned int rgb = (blue << 16) | (green << 8) | red;
printf("RGB = 0X%06X\n", rgb);  // RGB = 0X8200FF
```

Step-by-step:
```
red   = 0x000000FF              (bits 0-7)
green = 0x00000000  << 8  → 0x00000000  (bits 8-15)
blue  = 0x00000082  << 16 → 0x00820000  (bits 16-23)
OR all together:             0x008200FF
```

**Extracting R, G, B from a single RGB value** (needed for Q4):

Use right shift (`>>`) and AND mask (`& 0xFF`) to isolate each channel:

```c
unsigned int rgb = 0xA73B03;

unsigned int red   = rgb & 0xFF;           // bits 0-7
unsigned int green = (rgb >> 8) & 0xFF;    // bits 8-15
unsigned int blue  = (rgb >> 16) & 0xFF;   // bits 16-23

printf("Red   = 0X%02X (%d)\n", red, red);     // Red   = 0X03 (3)
printf("Green = 0X%02X (%d)\n", green, green);  // Green = 0X3B (59)
printf("Blue  = 0X%02X (%d)\n", blue, blue);    // Blue  = 0XA7 (167)
```

Step-by-step:
```
rgb         = 0x00A73B03

red   = rgb & 0xFF           = 0x03  (mask lower 8 bits)
green = (rgb >> 8) & 0xFF    = 0x3B  (shift right 8, then mask)
blue  = (rgb >> 16) & 0xFF   = 0xA7  (shift right 16, then mask)
```

> **Key Point:** The mask `0xFF` (binary `1111 1111`) isolates exactly 8 bits. `& 0xFF` zeroes out all bits except the lowest 8. Shifting first moves the desired channel into the low 8 bits, then masking extracts it.

---

<br>

## 7. Assignment Operators

### 7.1 Simple and Compound Assignment

The **simple assignment** operator `=` stores a value in a variable. **Compound assignment** operators combine an arithmetic or bitwise operation with assignment.

| Operator | Equivalent | Example |
|:--------:|:-----------|:--------|
| `=` | — | `x = 10` |
| `+=` | `x = x + y` | `x += 3` → `x = x + 3` |
| `-=` | `x = x - y` | `x -= 2` → `x = x - 2` |
| `*=` | `x = x * y` | `x *= 4` → `x = x * 4` |
| `/=` | `x = x / y` | `x /= 2` → `x = x / 2` |
| `%=` | `x = x % y` | `x %= 3` → `x = x % 3` |
| `&=` | `x = x & y` | `x &= 0xFF` |
| `\|=` | `x = x \| y` | `x \|= 0x80` |
| `^=` | `x = x ^ y` | `x ^= mask` |
| `<<=` | `x = x << n` | `x <<= 4` |
| `>>=` | `x = x >> n` | `x >>= 8` |

```c
int score = 80;
score += 10;   // score = 80 + 10 = 90
score -= 5;    // score = 90 - 5 = 85
score *= 2;    // score = 85 * 2 = 170
score /= 10;   // score = 170 / 10 = 17
score %= 3;    // score = 17 % 3 = 2
```

### 7.2 Chained Assignment

Assignment is **right-associative**, so chained assignments evaluate right-to-left:

```c
int a, b, c;
a = b = c = 0;
// Evaluated as: a = (b = (c = 0))
// c = 0 → b = 0 → a = 0
```

```c
int x, y;
x = y = 10 + 5;
// y = 15, then x = 15
```

---

<br>

## 8. Conditional Operator

### 8.1 Ternary Operator

The **conditional operator** `? :` is the only ternary operator in C (three operands).

```
condition ? value_if_true : value_if_false
```

```c
int a = 10, b = 20;
int max = (a > b) ? a : b;    // max = 20

printf("%s\n", (a % 2 == 0) ? "even" : "odd");  // "even"
```

### 8.2 Equivalent if/else

The conditional operator is a compact alternative to simple `if/else`:

```c
// Using if/else
int abs_val;
if (x >= 0)
    abs_val = x;
else
    abs_val = -x;

// Using ternary — equivalent
int abs_val = (x >= 0) ? x : -x;
```

> **Tip:** Use the ternary operator for simple, short expressions. For complex logic with multiple statements, prefer `if/else` for readability.

---

<br>

## 9. Type Conversion in Expressions

### 9.1 Implicit Promotion

When operands in an expression have different types, C automatically **promotes** smaller types to larger types before performing the operation.

**Integer promotion:** `char` and `short` are always promoted to `int` when used in any arithmetic expression.

```c
char a = 10, b = 20;
// In the expression a + b:
// a is promoted to int, b is promoted to int
// Result type: int
printf("%d\n", sizeof(a + b));  // 4 (int), not 1 (char)
```

**Usual arithmetic conversion** (for binary operators):

```
char / short → int → long → long long → float → double → long double
```

The smaller type is converted to match the larger type.

```c
int i = 5;
double d = 2.5;
double result = i + d;   // i promoted to double → 5.0 + 2.5 = 7.5
```

### 9.2 Cast Operator

The **cast operator** `(type)` explicitly converts a value to a specified type. The cast is a **unary operator** with high precedence.

```c
int a = 7, b = 2;

// Without cast — integer division
double r1 = a / b;           // 3.0

// With cast — floating-point division
double r2 = (double)a / b;   // 3.5
```

Important: the cast applies only to the **immediately following operand**:

```c
int a = 3, b = 4;

(double)(a + b)              // casts the sum (7) to double → 7.0
(double)a + b                // casts a only → 3.0 + 4 = 7.0
(double)(a / b)              // ⚠ integer division first (0), then cast → 0.0
```

### 9.3 sizeof of Expression Result

`sizeof` applied to an expression returns the size of the expression's **result type**, not the operand type.

```c
char c = 'A';
short s = 100;

printf("%zu\n", sizeof(c));        // 1 (char)
printf("%zu\n", sizeof(c + c));    // 4 (char + char → int, due to integer promotion)
printf("%zu\n", sizeof(s + s));    // 4 (short + short → int)
printf("%zu\n", sizeof(c + 1.0));  // 8 (char + double → double)
```

> **Key Point:** Even adding two `char` values produces an `int` result because of integer promotion.

---

<br>

## 10. Operator Precedence and Associativity

### 10.1 Precedence Table

When an expression has multiple operators, **precedence** determines which operations are performed first. Higher precedence means the operator binds more tightly.

| Precedence | Operators | Description |
|:----------:|:----------|:------------|
| 1 (highest) | `()` `[]` `->` `.` | Grouping, subscript, member access |
| 2 | `!` `~` `++` `--` `+x` `-x` `(type)` `*` `&` `sizeof` | Unary operators |
| 3 | `*` `/` `%` | Multiplication, division, modulo |
| 4 | `+` `-` | Addition, subtraction |
| 5 | `<<` `>>` | Bitwise shift |
| 6 | `<` `<=` `>` `>=` | Relational (inequality) |
| 7 | `==` `!=` | Relational (equality) |
| 8 | `&` | Bitwise AND |
| 9 | `^` | Bitwise XOR |
| 10 | `\|` | Bitwise OR |
| 11 | `&&` | Logical AND |
| 12 | `\|\|` | Logical OR |
| 13 | `?:` | Conditional (ternary) |
| 14 (lowest) | `=` `+=` `-=` `*=` `/=` `%=` etc. | Assignment |

```c
int x = 2 + 3 * 4;      // 3*4 first → 2 + 12 = 14 (not 20)
int y = (2 + 3) * 4;    // 2+3 first → 5 * 4 = 20
int z = 5 > 3 && 2 < 4; // (5>3) && (2<4) → 1 && 1 = 1
```

### 10.2 Associativity

When operators have the **same precedence**, **associativity** determines the evaluation order.

| Associativity | Operators | Example |
|:--------------|:----------|:--------|
| Left-to-right | Most binary operators: `+`, `-`, `*`, `/`, `%`, `<`, `>`, `==`, `&&`, etc. | `a - b - c` = `(a - b) - c` |
| Right-to-left | Unary operators, assignment, ternary | `a = b = c` = `a = (b = c)` |

```c
int result = 10 - 3 - 2;
// Left-to-right: (10 - 3) - 2 = 5 (not 10 - (3-2) = 9)

int a, b, c;
a = b = c = 0;
// Right-to-left: a = (b = (c = 0))
```

### 10.3 Use Parentheses When in Doubt

Rather than memorizing the entire precedence table, use **parentheses** to make your intent explicit.

```c
// Ambiguous — is it (a & b) == 0 or a & (b == 0)?
if (a & b == 0) { ... }   // ⚠ Actually: a & (b == 0), because == has higher precedence than &

// Clear — always use parentheses with bitwise operators
if ((a & b) == 0) { ... } // ✅ Correct and readable
```

> **Tip:** Bitwise operators (`&`, `|`, `^`) have **lower precedence** than relational operators (`==`, `!=`). This is a common source of bugs. Always parenthesize bitwise expressions in comparisons.

---

<br>

## Summary

| Concept | Key Takeaway |
|:--------|:-------------|
| Expression | Anything with a value: constant, variable, operation, function call, assignment |
| Unary / Binary / Ternary | 1, 2, or 3 operands; e.g., `sizeof`, `+`, `?:` |
| Arithmetic Operators | `+`, `-`, `*`, `/`, `%`; unary `+x`, `-x` |
| Integer Division | `int / int` truncates; cast at least one operand for float result |
| Modulo `%` | Remainder of integer division; integers only |
| Formula Conversion | Use `2.0` or cast to prevent integer division; explicit `*` for multiplication |
| Prefix `++x` | Increment first, then use the value |
| Postfix `x++` | Use the value first, then increment |
| Increment Restriction | Only on variables; not on constants or expressions |
| Relational Operators | `>`, `<`, `>=`, `<=`, `==`, `!=`; result is 0 or 1 |
| `=` vs `==` | Assignment vs comparison; mixing them is a common bug |
| Logical Operators | `&&` (AND), `\|\|` (OR), `!` (NOT) |
| Short-Circuit | `&&` stops on false; `\|\|` stops on true; right operand may be skipped |
| Truthiness | 0 is false; any non-zero is true |
| Bitwise Operators | `&`, `\|`, `^`, `~` operate on individual bits |
| Shift Operators | `<<` (left, multiply by 2^n), `>>` (right, divide by 2^n) |
| RGB Combining | `(blue << 16) \| (green << 8) \| red` |
| RGB Extracting | `(rgb >> n) & 0xFF` to isolate each channel |
| Compound Assignment | `+=`, `-=`, `*=`, `/=`, `%=`, `&=`, `\|=`, `^=`, `<<=`, `>>=` |
| Chained Assignment | `a = b = c = 0` (right-to-left) |
| Ternary Operator | `condition ? true_val : false_val` — compact if/else |
| Implicit Promotion | `char`/`short` always promoted to `int` in expressions |
| Cast Operator | `(type)expr` — explicit conversion; applies to immediately following operand |
| Precedence | Unary > `*`/`/`/`%` > `+`/`-` > relational > logical > assignment |
| Associativity | Most binary: left-to-right; unary/assignment/ternary: right-to-left |
| Parentheses | When in doubt, parenthesize; especially with bitwise operators |

---
