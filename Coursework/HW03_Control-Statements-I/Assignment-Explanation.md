# HW3 Assignment Explanation — Control Statements I

[Repository Guide](../../README.md) | [English](Assignment-Explanation.md) | [한국어](Assignment-Explanation.ko.md)

> **Last Updated:** 2026-10-19

> **Learning Objectives:**
> 1. Explain the form and evaluation order of the conditional operator `? :`
> 2. Find the maximum of three values by applying the conditional operator twice
> 3. Check boundary conditions to confirm that the result is correct even for inputs with equal or negative values

**Problem Source:** Prof. Jonguk Lee, Computer Language and Training Ⅰ (DCCS103-03)

---

## Table of Contents

- [1. Assignment Layout and How to Run](#1-assignment-layout-and-how-to-run)
- [2. Problem 1: Comparing Magnitudes](#2-problem-1-comparing-magnitudes)
  - [2.1 Problem](#21-problem)
  - [2.2 Solution](#22-solution)
  - [2.3 Output and Edge Cases](#23-output-and-edge-cases)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Assignment Layout and How to Run

This assignment finds the largest of three integers with only the conditional operator, without an `if` statement. The conditional operator is an expression that chooses one of two values by a condition, so the assignment practices expressing a selection structure as an expression rather than a statement.

```text
Coursework/HW03_Control-Statements-I/
├── Assignment-Explanation.ko.md   # this document (Korean)
├── Assignment-Explanation.md      # this document (English)
└── Solution/
    └── Q1.c                       # Problem 1: comparing magnitudes
```

*Figure 1. Directory layout of HW3*

The program was written in Visual Studio (MSVC) and uses `scanf_s` for input. `scanf_s` is provided by MSVC and is missing from most standard libraries used with gcc and clang, so in other environments the code is compiled without changes by replacing it with `scanf` through the `-Dscanf_s=scanf` option. The outputs in this document were obtained with the following commands.

```bash
cd Coursework/HW03_Control-Statements-I/Solution
gcc -std=c99 -Wall -Dscanf_s=scanf -o Q1 Q1.c
./Q1
```

The line `Program ended with exit code: 0` at the end of the sample runs in the assignment is not program output but the exit message added by the Xcode console.

---

<br>

## 2. Problem 1: Comparing Magnitudes

### 2.1 Problem

Read three integers separated by spaces from the user and print the largest value. Only the conditional operator may be used.

**Sample Runs:**

```text
Input 3 values: 3 -4 9
Max: 9

Program ended with exit code: 0
```

```text
Input 3 values: 23 4 -5
Max: 23

Program ended with exit code: 0
```

```text
Input 3 values: -12 -3 -24
Max: -3

Program ended with exit code: 0
```

### 2.2 Solution

**Approach:** The conditional operator `condition ? value1 : value2` yields value1 as the value of the expression if the condition is true and value2 if it is false ([Chapter 4, Section 8.1](../../Lecture-Notes/Ch04_Operators/Concepts_Lecture.md#81-ternary-operator)). One conditional operator finds the maximum of two values, so the maximum of three values is found in two steps.

- **Step 1:** `max1 = num1 > num2 ? num1 : num2;` finds the larger of the first two numbers.
- **Step 2:** `max2 = max1 > num3 ? max1 : num3;` finds the larger of the result of step 1 and the third number. This value is the maximum of the three numbers.
- **Why no parentheses are needed:** The relational operator `>` has higher precedence than the conditional operator, which in turn has higher precedence than the assignment operator ([Chapter 4, Section 10.1](../../Lecture-Notes/Ch04_Operators/Concepts_Lecture.md#101-precedence-table)). Therefore `max1 = num1 > num2 ? num1 : num2` is computed as `max1 = ((num1 > num2) ? num1 : num2)`.

**Code:** [Solution/Q1.c](Solution/Q1.c)

```c
/**
 * @file    A10303-1_C05Q1.c
 * @brief   Q1. 대소 비교
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-28
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *	    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
	int num1, num2, num3;
	int max1, max2;

	printf("Input 3 values: ");
	scanf_s(" %d %d %d", &num1, &num2, &num3);

	max1 = num1 > num2 ? num1 : num2;
	max2 = max1 > num3 ? max1 : num3;

	printf("Max: %d", max2);
}
```

### 2.3 Output and Edge Cases

**Output:** Identical to the three sample runs. The program prints no newline at the end of the output. In the third run, -12 > -3 is false, so `max1` becomes -3, and -3 > -24 is true, so `max2` is also -3.

```text
Input 3 values: 3 -4 9
Max: 9
Input 3 values: 23 4 -5
Max: 23
Input 3 values: -12 -3 -24
Max: -3
```

> **Note:** **Equal values.** If two numbers are equal, `num1 > num2` is false and `num2` is chosen, but since the two values are equal, the result does not change. Even if all three numbers are equal, that value is printed. To write it as a single expression without intermediate variables, nest the conditional operators, as in `num1 > num2 ? (num1 > num3 ? num1 : num3) : (num2 > num3 ? num2 : num3)`.

```text
Input 3 values: 5 5 5
Max: 5
```

---

<br>

## Summary

| Concept | Key Summary |
|:--------|:------------|
| Conditional operator | `condition ? value1 : value2` is the only ternary operator in C, yielding value1 if the condition is true and value2 otherwise. |
| Maximum of two values | `a > b ? a : b` finds the larger of two values without an `if` statement. |
| Maximum of three values | It is found in two steps: first the maximum of two values, which is then compared with the third value. |
| Precedence | Relational, conditional, and assignment operators bind in that order, so this expression needs no parentheses. |
| Boundary conditions | The result is correct even with equal or all-negative values because the program only compares them. |

---

<br>

## Self-Check Questions

1. **Evaluating the conditional operator:** Write the values of `r` and `y` after executing `int x = 1, y = 0; int r = x ? 10 : y++;`.

   <details>
   <summary>Answer</summary>

   `r` is 10 and `y` is 0. The condition `x` is true (non-zero), so the second operand 10 becomes the value of the expression, and the third operand `y++` is not evaluated. The conditional operator evaluates only the chosen one of the two values.

   </details>

2. **Tracing the intermediate steps:** For the input `23 4 -5`, write the values of `max1` and `max2` in order.

   <details>
   <summary>Answer</summary>

   23 > 4 is true, so `max1` is 23, and 23 > -5 is true, so `max2` is 23.

   </details>

3. **Minimum:** Which part of the code must change to find the smallest of the three values in the same way?

   <details>
   <summary>Answer</summary>

   Change the comparison in both conditional operators from `>` to `<`. `min1 = num1 < num2 ? num1 : num2;` followed by `min2 = min1 < num3 ? min1 : num3;` gives the minimum of the three values.

   </details>

4. **A single expression:** Write an expression that finds the maximum of `a`, `b`, and `c` with only conditional operators and no intermediate variables, and find its value for `a = 5, b = 9, c = 7`.

   <details>
   <summary>Answer</summary>

   It is `a > b ? (a > c ? a : c) : (b > c ? b : c)`. 5 > 9 is false, so `(b > c ? b : c)` is evaluated, and 9 > 7 is true, so the value is 9.

   </details>
