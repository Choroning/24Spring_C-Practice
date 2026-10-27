# Chapter 4 Lab — Operators

[Repository Guide](../../README.md) | [English](Concepts_Lab.md) | [한국어](Concepts_Lab.ko.md)

> **Last Updated:** 2026-10-27
>
> 문제풀이 중심의 C언어 연습, 김용일과 강문설, Ch 4

> **Learning Objectives:**
> 1. Distinguish operators from operands and list the operators of C by kind
> 2. Compute and store values with arithmetic operators, the assignment operator, and compound assignment operators
> 3. Trace step by step the value of an expression mixing prefix and postfix increment and decrement operators and the changes of its variables
> 4. Find the results of relational, logical, and conditional operators and choose a value by a condition
> 5. Determine the order of evaluation of an expression from operator precedence and associativity

---

## Table of Contents

- [1. Operators and Operands](#1-operators-and-operands)
- [2. Arithmetic and Assignment Operators](#2-arithmetic-and-assignment-operators)
  - [2.1 Arithmetic Operators](#21-arithmetic-operators)
  - [2.2 Assignment and Compound Assignment Operators](#22-assignment-and-compound-assignment-operators)
- [3. Increment and Decrement Operators](#3-increment-and-decrement-operators)
  - [3.1 Prefix and Postfix](#31-prefix-and-postfix)
  - [3.2 Standalone Use and Use Inside Expressions](#32-standalone-use-and-use-inside-expressions)
- [4. Relational and Logical Operators](#4-relational-and-logical-operators)
  - [4.1 Relational Operators](#41-relational-operators)
  - [4.2 Logical Operators](#42-logical-operators)
- [5. The Conditional Operator and Other Operators](#5-the-conditional-operator-and-other-operators)
  - [5.1 The Conditional Operator](#51-the-conditional-operator)
  - [5.2 The Comma Operator, the Cast Operator, and sizeof](#52-the-comma-operator-the-cast-operator-and-sizeof)
- [6. Operator Precedence and Associativity](#6-operator-precedence-and-associativity)
- [7. Practice Problems](#7-practice-problems)
  - [7.1 Predicting Increment Operator Results](#71-predicting-increment-operator-results)
  - [7.2 Quotient and Remainder](#72-quotient-and-remainder)
  - [7.3 Printing the Larger Number with the Conditional Operator](#73-printing-the-larger-number-with-the-conditional-operator)
  - [7.4 Predicting Relational, Logical, and sizeof Results](#74-predicting-relational-logical-and-sizeof-results)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Operators and Operands

An **operator** is a symbol used to request an operation, and an **operand** is a value the operation is applied to. In `4 + 3`, `+` is the operator and 4 and 3 are the operands ([Chapter 4, Section 1.2](Concepts_Lecture.md#12-operators-and-operands)). The operators of C are classified as follows.

- **Arithmetic operators:** `+`, `-`, `*`, `/`, `%`, and the sign operator `-`
- **Assignment operators:** `=`, `+=`, `-=`, `*=`, `/=`, and so on
- **Increment and decrement operators:** `++`, `--`
- **Relational operators:** `<`, `<=`, `>`, `>=`, `==`, `!=`
- **Logical operators:** `!`, `&&`, `||`
- **Conditional operator:** `? :`
- **Bitwise operators:** `&`, `|`, `^`, `~`, `<<`, `>>` ([Chapter 4, Section 6](Concepts_Lecture.md#6-bitwise-operators))
- **Other operators:** the comma `,`, the cast `(type)`, and `sizeof`

---

<br>

## 2. Arithmetic and Assignment Operators

### 2.1 Arithmetic Operators

Arithmetic operators are used for ordinary arithmetic.

| Operator | Example | Meaning | Associativity |
|:---:|:---:|:-----|:---:|
| `+` | `4 + 3` | Addition | Left → right |
| `-` | `4 - 3` | Subtraction | Left → right |
| `*` | `4 * 3` | Multiplication | Left → right |
| `/` | `4 / 3` | Division | Left → right |
| `%` | `4 % 3` | Remainder | Left → right |

*Table 1. Arithmetic operators*

When both operands are integers, `/` gives the quotient with the fractional part dropped, so `4 / 3` is 1, and `%` gives the remainder, so `4 % 3` is 1. `%` can be used only with integers ([Chapter 4, Section 2.2](Concepts_Lecture.md#22-integer-division-vs-float-division), [Section 2.3](Concepts_Lecture.md#23-modulo-operator)).

### 2.2 Assignment and Compound Assignment Operators

The assignment operator `=` stores the value on the right in the memory of the variable on the left. Executing `int a = 3; int b = 5; a = b;` stores the value 5 of `b` in `a`, and `b` stays 5. A **compound assignment operator**, which combines the assignment operator with an arithmetic operator, stores the result of an operation on the variable's current value back into that variable ([Chapter 4, Section 7.1](Concepts_Lecture.md#71-simple-and-compound-assignment)).

```c
#include <stdio.h>

int main(void)
{
    int a = 15;
    int b = 20;

    a += b;     // same as a = a + b;
    printf("Result : %d \n", a);

    return 0;
}
```

```text
Result : 35 
```

| Compound assignment | Equivalent assignment |
|:---:|:---:|
| `a += b` | `a = a + b` |
| `a -= b` | `a = a - b` |
| `a *= b` | `a = a * b` |
| `a /= b` | `a = a / b` |
| `a %= b` | `a = a % b` |

*Table 2. Compound assignment operators and their equivalent assignments*

`a *= b + 1` equals `a = a * (b + 1)`, not `a = a * b + 1`. Compound assignment operators have the lowest precedence after the comma operator, so the whole expression on the right is computed first.

---

<br>

## 3. Increment and Decrement Operators

### 3.1 Prefix and Postfix

The **increment and decrement operators** `++` and `--` increase or decrease the value of a variable by 1. The **prefix** form, written before the variable, and the **postfix** form, written after it, differ in when the value is used inside an expression ([Chapter 4, Section 3.1](Concepts_Lecture.md#31-prefix-vs-postfix)).

| Operator | Example | Meaning |
|:---:|:-----|:-----|
| `++a` | `printf("%d", ++a)` | Increments by 1 first, then uses the incremented value |
| `a++` | `printf("%d", a++)` | Uses the current value first, then increments by 1 |
| `--b` | `printf("%d", --b)` | Decrements by 1 first, then uses the decremented value |
| `b--` | `printf("%d", b--)` | Uses the current value first, then decrements by 1 |

*Table 3. Prefix and postfix increment and decrement operators*

### 3.2 Standalone Use and Use Inside Expressions

The following program compares eight cases starting from `a = 3`.

```c
#include <stdio.h>

int main(void)
{
    int a, b;

    a = 3; a + 1;          printf("1. a: %d\n", a);        // the result of a + 1 is discarded
    a = 3; a = a + 1;      printf("2. a: %d\n", a);
    a = 3; ++a;            printf("3. a: %d\n", a);
    a = 3; a++;            printf("4. a: %d\n", a);
    a = 3; b = ++a;        printf("5. %d, %d\n", a, b);    // increment first, then use
    a = 3; b = a++;        printf("6. %d, %d\n", a, b);    // use first, then increment
    a = 3; b = ++a * 3;    printf("7. %d, %d\n", a, b);
    a = 3; b = a++ * 3;    printf("8. %d, %d\n", a, b);

    return 0;
}
```

```text
1. a: 3
2. a: 4
3. a: 4
4. a: 4
5. 4, 4
6. 4, 3
7. 4, 12
8. 4, 9
```

- **1 and 2:** `a + 1;` computes 4 but stores it nowhere, so `a` stays 3. The compiler issues the warning "expression result unused" for this statement. To change the value, it must be assigned as in 2.
- **3 and 4:** When an increment operator is used as a standalone statement, prefix and postfix give the same result. In both cases `a` increases by 1 to 4 ([Chapter 4, Section 3.2](Concepts_Lecture.md#32-standalone-vs-in-expressions)).
- **5 and 6:** Inside an expression they differ. `b = ++a` increments `a` to 4 and assigns 4 to `b`, while `b = a++` assigns the current value 3 of `a` to `b` and then increments `a` to 4.
- **7 and 8:** `++a * 3` is 4 × 3 = 12, and `a++ * 3` uses the 3 before the increment, giving 3 × 3 = 9. In both cases `a` is 4 after the statement.

> **Caution:** Incrementing or decrementing a variable in an expression that also uses or assigns that variable again, as in `a = a++;` or `printf("%d %d", a, a++);`, is undefined behavior ([Chapter 4, Section 3.3](Concepts_Lecture.md#33-restrictions)).

---

<br>

## 4. Relational and Logical Operators

### 4.1 Relational Operators

A **relational operator** compares the two operands and yields 1 for true and 0 for false as a value of type `int` ([Chapter 4, Section 4.1](Concepts_Lecture.md#41-comparison-operators)).

| Operator | Example | Meaning |
|:---:|:---:|:-----|
| `<` | `a < b` | Is a less than b |
| `>` | `a > b` | Is a greater than b |
| `==` | `a == b` | Are a and b equal |
| `!=` | `a != b` | Are a and b not equal |
| `<=` | `a <= b` | Is a less than or equal to b |
| `>=` | `a >= b` | Is a greater than or equal to b |

*Table 4. Relational operators*

### 4.2 Logical Operators

**Logical operators** express AND, OR, and NOT, and their result is 1 or 0 like that of relational operators. An operand is judged false if it is 0 and true otherwise ([Chapter 4, Section 5.1](Concepts_Lecture.md#51-and-or-not)).

| Operator | Name | Example | Meaning |
|:---:|:-----|:---:|:-----|
| `&&` | Logical AND | `e1 && e2` | 1 if both expressions are true |
| `\|\|` | Logical OR | `e1 \|\| e2` | 1 if at least one expression is true |
| `!` | Logical NOT | `!a` | 0 if a is true, 1 if false |

*Table 5. Logical operators*

| e1 | e2 | `e1 && e2` | `e1 \|\| e2` | `!e1` |
|:---:|:---:|:---:|:---:|:---:|
| True | True | 1 | 1 | 0 |
| True | False | 0 | 1 | 0 |
| False | True | 0 | 1 | 1 |
| False | False | 0 | 0 | 1 |

*Table 6. Truth table of the logical operators*

The following program prints the results of relational and logical operators and of the conditional operator (Section 5.1).

```c
#include <stdio.h>

int main(void)
{
    int a = 15, b = 20;
    int c;

    printf("Result : %d \n", a == b);   // false: 0
    printf("Result : %d \n", a < 20);   // true: 1

    c = (a < b) && (a > b);
    printf("Result: %d \n", c);
    c = (a < b) || (a > b);
    printf("Result: %d \n", c);

    c = (a < b) ? a : b;
    printf("Result: %d \n", c);
    printf("Result: %d \n", (a > b) ? a : b);

    return 0;
}
```

```text
Result : 0 
Result : 1 
Result: 0 
Result: 1 
Result: 15 
Result: 20 
```

`(a < b) && (a > b)` is true && false, so 0, and `(a < b) || (a > b)` is true || false, so 1. `&&` does not evaluate the right expression if the left one is false, and `||` does not if the left one is true ([Chapter 4, Section 5.3](Concepts_Lecture.md#53-short-circuit-evaluation)).

---

<br>

## 5. The Conditional Operator and Other Operators

### 5.1 The Conditional Operator

The **conditional operator** `condition ? value1 : value2` chooses value1 after `?` if the condition is true and value2 after `:` if it is false. It has three operands, so it is also called the ternary operator ([Chapter 4, Section 8.1](Concepts_Lecture.md#81-ternary-operator)). In the program of Section 4.2, `c = (a < b) ? a : b;` assigns the value 15 of `a` to `c` because 15 < 20 is true, and `(a > b) ? a : b` yields 20 because the condition is false. The conditional operator is an expression, so it can be used directly where a value is needed, such as an argument of `printf`.

### 5.2 The Comma Operator, the Cast Operator, and sizeof

```c
a = 10, b = 5;   // assigns 10 to a, then 5 to b
(int) ave;       // makes a temporary int value from the double ave (the fraction is dropped)
sizeof(int)      // the memory size used by the type int
```

- **Comma operator:** Evaluates the expressions from the left in order, and the value of the whole expression is that of the last one.
- **Cast operator:** `(int) ave` creates a new temporary value of type `int` from the value of the real variable `ave` with its fractional part dropped. The value of `ave` itself does not change ([Chapter 4, Section 9.2](Concepts_Lecture.md#92-cast-operator)).
- **`sizeof`:** Yields the size of the memory a type or value occupies, in bytes ([Chapter 3, Section 7](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#7-sizeof-operator)).

---

<br>

## 6. Operator Precedence and Associativity

When an expression has several operators, those with higher **precedence** are evaluated first, and operators of equal precedence are evaluated according to their **associativity** ([Chapter 4, Section 10](Concepts_Lecture.md#10-operator-precedence-and-associativity)).

| Precedence | Operators | Associativity |
|:---:|:-----|:---:|
| 1 | `()` `[]` `.` `->` postfix `++` `--` | Left → right |
| 2 | `!` `~` prefix `++` `--` unary `+` `-` `(type)` `*` `&` `sizeof` | Right → left |
| 3 | `*` `/` `%` | Left → right |
| 4 | `+` `-` | Left → right |
| 5 | `<<` `>>` | Left → right |
| 6 | `<` `<=` `>` `>=` | Left → right |
| 7 | `==` `!=` | Left → right |
| 8 | `&` | Left → right |
| 9 | `^` | Left → right |
| 10 | `\|` | Left → right |
| 11 | `&&` | Left → right |
| 12 | `\|\|` | Left → right |
| 13 | `?:` | Right → left |
| 14 | `=` `+=` `-=` `*=` `/=` `%=` `&=` `\|=` `^=` `<<=` `>>=` | Right → left |
| 15 | `,` | Left → right |

*Table 7. Precedence and associativity of the C operators*

The postfix increment and decrement operators belong to level 1, and the prefix increment and decrement operators and the unary sign operators to level 2. The unary operators of level 2 associate from right to left, so `-!x` is evaluated as `-(!x)`. The `*` and `&` of level 2 are the pointer dereference and address operators, covered in Chapter 8. For an expression whose precedence is confusing, it is better to make the order of evaluation clear with parentheses.

---

<br>

## 7. Practice Problems

Each program compiles with `gcc -std=c99 -Wall` without warnings, and the outputs are from actual runs.

### 7.1 Predicting Increment Operator Results

**Problem:** Predict the output of the following program.

```c
#include <stdio.h>

int main(void)
{
    int n = 2, b = 0;

    printf(" %d \n", ++n);
    printf(" %d \n", n++);
    printf(" %d \n", n + 1);
    printf(" %d \n", n);
    printf("------- \n");
    printf(" %d \n", ++n * 3);
    printf(" %d \n", n++ * 3);
    printf(" %d \n", n);
    printf("------- \n");
    printf(" %d \n", b = n++);
    printf(" %d, %d \n", b, n);
    printf(" %d \n", b = ++n / 2);
    printf(" %d, %d \n", b, n);

    return 0;
}
```

**Solution:** Trace in order the value each statement prints and the values of `n` and `b` after the statement.

| Statement | Output | `n` after | `b` after |
|:-----|:---:|:---:|:---:|
| `++n` | 3 | 3 | 0 |
| `n++` | 3 | 4 | 0 |
| `n + 1` | 5 | 4 | 0 |
| `n` | 4 | 4 | 0 |
| `++n * 3` | 15 | 5 | 0 |
| `n++ * 3` | 15 | 6 | 0 |
| `n` | 6 | 6 | 0 |
| `b = n++` | 6 | 7 | 6 |
| `b, n` | 6, 7 | 7 | 6 |
| `b = ++n / 2` | 4 | 8 | 4 |
| `b, n` | 4, 8 | 8 | 4 |

*Table 8. The output of each statement and the values of the variables*

- `n + 1` prints 5 but does not assign it to `n`, so `n` stays 4.
- `++n * 3` increments `n` to 5 and gives 5 × 3 = 15, and `n++ * 3` uses the 5 before the increment to give 15 and then increments `n` to 6.
- The value of the assignment expression `b = n++` is the assigned value 6.
- In `b = ++n / 2`, `n` becomes 8, and the integer division 8 / 2 = 4 is assigned to `b`.

```text
 3 
 3 
 5 
 4 
------- 
 15 
 15 
 6 
------- 
 6 
 6, 7 
 4 
 4, 8 
```

### 7.2 Quotient and Remainder

**Problem:** Read two integers `vOne` and `vTwo` and print the quotient and the remainder.

**Solution:** Division `/` between integers gives the quotient, and `%` gives the remainder. The two results always satisfy `vOne == (vOne / vTwo) * vTwo + vOne % vTwo`.

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int vOne, vTwo;

    printf("Input two values: ");
    scanf("%d %d", &vOne, &vTwo);

    printf("quotient: %d\n", vOne / vTwo);     // integer division drops the fraction
    printf("remainder: %d\n", vOne % vTwo);

    return 0;
}
```

```text
Input two values: 13 3
quotient: 4
remainder: 1
```

> **Caution:** From C99, integer division truncates toward zero, so dividing a negative number makes both the quotient and the remainder negative. Entering `-13` and `3` gives the quotient -4 and the remainder -1. Also, entering 0 for `vTwo` divides by zero, which is undefined behavior.

```text
Input two values: -13 3
quotient: -4
remainder: -1
```

### 7.3 Printing the Larger Number with the Conditional Operator

**Problem:** Read two integers and print the larger one. Use the conditional operator, and add variables if needed.

**Solution:** Assign to the variable `max` the value of `(a > b) ? a : b`, which chooses `a` if the condition `a > b` is true and `b` otherwise. If the two numbers are equal, the condition is false and `b` is chosen, but the value is the same.

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int a, b, max;

    printf("input two values: ");
    scanf("%d %d", &a, &b);

    max = (a > b) ? a : b;     // the larger of a and b
    printf("MAX: %d\n", max);

    return 0;
}
```

```text
input two values: -3 89
MAX: 89
```

```text
input two values: -3 -23
MAX: -3
```

Finding the largest of three integers with the conditional operator only is covered in [HW03 Problem 4](../../Coursework/HW03_Control-Statements-I/Assignment-Explanation.md#5-problem-4-comparing-magnitudes).

### 7.4 Predicting Relational, Logical, and sizeof Results

**Problem:** Predict the output of the following code.

```c
#include <stdio.h>

int main(void)
{
    int no = 100, count = 20;
    char ch = 'A';

    printf(" %d", no > count);
    printf(" %d", no < count * 4);
    printf(" %d", (no != 100) || (count >= 20));
    printf(" %d", (no <= 100) && (count > 20));
    printf("\n------\n");
    printf(" %d \n", !(no > count));
    printf(" %zu \n", sizeof(char));
    printf(" %zu \n", sizeof(ch));
    printf(" %zu \n", sizeof('A'));
    printf(" %zu \n", sizeof(3.2));

    return 0;
}
```

**Solution:**

- `no > count` is 100 > 20, so 1.
- In `no < count * 4`, `*` is computed before `<`, giving 100 < 80, so 0.
- `(no != 100) || (count >= 20)` is false || true, so 1.
- `(no <= 100) && (count > 20)` is true && false, so 0.
- `!(no > count)` is !1, so 0.
- `sizeof(char)` and `sizeof(ch)` are 1, the type of the character constant `'A'` is `int`, so `sizeof('A')` is 4, and the type of the real constant `3.2` is `double`, so `sizeof(3.2)` is 8 ([Chapter 3 Lab, Section 4](../Ch03_Data-Types-and-Variables/Concepts_Lab.md#4-the-sizeof-operator)).

```text
 1 0 1 0
------
 0 
 1 
 1 
 4 
 8 
```

The result of `sizeof` has the type `size_t`, so from C99 it is printed with `%zu`. A problem of the same form with different variable values and `sizeof` operands is in [HW03 Problem 1](../../Coursework/HW03_Control-Statements-I/Assignment-Explanation.md#2-problem-1-values-of-operators).

---

<br>

## Summary

| Concept | Key Summary |
|:-----|:-----|
| Operators and operands | An operator is a symbol that requests an operation, and an operand is a value the operation is applied to. |
| Arithmetic operators | `+`, `-`, `*`, `/`, and `%`; between integers, `/` gives the quotient and `%` the remainder. |
| Compound assignment operators | `a += b` equals `a = a + b`, and the whole expression on the right is computed first. |
| Increment and decrement operators | As standalone statements, prefix and postfix give the same result, but inside an expression prefix uses the incremented value and postfix the value before the increment. |
| Relational operators | Compare two values and yield 1 for true and 0 for false. |
| Logical operators | Combine conditions with `&&`, `\|\|`, and `!`, and the result is 1 or 0. |
| Conditional operator | `condition ? value1 : value2` is an expression that chooses one of two values by a condition. |
| Other operators | The comma operator evaluates expressions in order, the cast operator makes a temporary value, and `sizeof` gives a size. |
| Precedence and associativity | Operators of higher precedence are evaluated first, equal precedence follows associativity, and the unary, conditional, and assignment operators associate from right to left. |

---

<br>

## Self-Check Questions

1. **Increment and decrement:** With `int x = 5, y;`, write `x` and `y` after executing `y = x-- * 2;`.

   <details>
   <summary>Answer</summary>

   It is a postfix decrement, so the 5 before the decrement is used and `y` is 5 × 2 = 10, and after the statement `x` is 4.

   </details>

2. **Compound assignment:** With `int a = 6, b = 2;`, write `a` after executing `a /= b + 1;`.

   <details>
   <summary>Answer</summary>

   A compound assignment operator computes the whole expression on the right first, so it is `a = a / (b + 1)`, that is, 6 / 3 = 2.

   </details>

3. **Logical operations:** With `int a = 0, b = 5;`, what is the value of `b` after evaluating `a && (b = 10)`?

   <details>
   <summary>Answer</summary>

   `a` is 0 (false), so `&&` yields 0 without evaluating the right expression. Therefore `b = 10` is not executed and `b` stays 5.

   </details>

4. **Precedence:** With `int x = 3;`, find the value of `x + 2 > 4 && x * 2 == 6` and show the order of evaluation with parentheses.

   <details>
   <summary>Answer</summary>

   It is evaluated as `((x + 2) > 4) && ((x * 2) == 6)`; 5 > 4 is true and 6 == 6 is true, so the value is 1. Arithmetic operators have higher precedence than relational operators, and relational operators higher than logical operators.

   </details>

5. **Remainder:** Write expressions that give the ones digit and the tens digit of a positive integer `n`.

   <details>
   <summary>Answer</summary>

   The ones digit is `n % 10` and the tens digit is `n / 10 % 10`. `/` and `%` have the same precedence and associate from left to right, so `n / 10 % 10` is evaluated as `(n / 10) % 10`. For example, with n = 357, the ones digit is 7 and the tens digit is 35 % 10 = 5.

   </details>
