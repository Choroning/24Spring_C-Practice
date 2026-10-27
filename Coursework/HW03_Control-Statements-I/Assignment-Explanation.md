# HW3 Assignment Explanation — Control Statements I

[Repository Guide](../../README.md) | [English](Assignment-Explanation.md) | [한국어](Assignment-Explanation.ko.md)

> **Last Updated:** 2026-10-27
>
> 문제풀이 중심의 C언어 연습, 김용일과 강문설, Ch 4, 5

> **Learning Objectives:**
> 1. Find the values produced by the relational, logical, and `sizeof` operators and explain why those values result
> 2. Express conditions involving ranges and negation as expressions with relational and logical operators
> 3. Trace expressions that mix prefix and postfix increment and decrement operators step by step and identify undefined behavior
> 4. Explain the form and evaluation order of the conditional operator `? :`
> 5. Find the maximum of three values by applying the conditional operator twice
> 6. Check boundary conditions to confirm that the result is correct even for inputs with equal or negative values

**Problem Source:** Prof. Jonguk Lee, Computer Language and Training Ⅰ (DCCS103-03)

---

## Table of Contents

- [1. Assignment Layout and How to Run](#1-assignment-layout-and-how-to-run)
- [2. Problem 1: Values of Operators](#2-problem-1-values-of-operators)
  - [2.1 Problem](#21-problem)
  - [2.2 Solution](#22-solution)
  - [2.3 Output](#23-output)
- [3. Problem 2: Writing Conditions as Expressions](#3-problem-2-writing-conditions-as-expressions)
  - [3.1 Problem](#31-problem)
  - [3.2 Solution](#32-solution)
- [4. Problem 3: Increment, Decrement, and Assignment](#4-problem-3-increment-decrement-and-assignment)
  - [4.1 Problem](#41-problem)
  - [4.2 Solution](#42-solution)
  - [4.3 Output and Undefined Behavior](#43-output-and-undefined-behavior)
- [5. Problem 4: Comparing Magnitudes](#5-problem-4-comparing-magnitudes)
  - [5.1 Problem](#51-problem)
  - [5.2 Solution](#52-solution)
  - [5.3 Output and Edge Cases](#53-output-and-edge-cases)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Assignment Layout and How to Run

This assignment consists of four problems on the operators of Chapter 4. Problems 1 and 3 are written problems that ask for the output of a given program and the reason for that output, Problem 2 is a written problem that expresses conditions stated in words as expressions with relational and logical operations, and Problem 4 is a coding problem that finds the largest of three integers with only the conditional operator, without an `if` statement. Problem 1 is a partly modified version of exercise 7 in Chapter 4 of the textbook, and Problem 2 modifies exercise 1 in Chapter 5 so that it can be answered without an `if` statement. The conditional operator is an expression that chooses one of two values by a condition, so Problem 4 practices expressing a selection structure as an expression rather than a statement.

```text
Coursework/HW03_Control-Statements-I/
├── Assignment-Explanation.ko.md   # this document (Korean)
├── Assignment-Explanation.md      # this document (English)
└── Solution/
    └── Q4.c                       # Problem 4: comparing magnitudes
```

*Figure 1. Directory layout of HW3*

Problems 1, 2, and 3 are written problems, so their answers and explanations are given in this document without solution files. The outputs of Problems 1 and 3 come from compiling and running the programs of the problems as they are.

The program of Problem 4 was written in Visual Studio (MSVC) and uses `scanf_s` for input. `scanf_s` is provided by MSVC and is missing from most standard libraries used with gcc and clang, so in other environments the code is compiled without changes by replacing it with `scanf` through the `-Dscanf_s=scanf` option. Problem 4 is compiled and run as follows.

```bash
cd Coursework/HW03_Control-Statements-I/Solution
gcc -std=c99 -Wall -Dscanf_s=scanf -o Q4 Q4.c
./Q4
```

The line `Program ended with exit code: 0` at the end of the sample runs in the assignment is not program output but the exit message added by the Xcode console.

---

<br>

## 2. Problem 1: Values of Operators

### 2.1 Problem

**Textbook Problem:** Chapter 4 exercise 7 (partly modified)

Write the output of the following program and explain why that output results.

```c
#include <stdio.h>
int main()
{
	int no = 10, count = 20;
	char ch = 'a';
	printf(" %d", no > count);
	printf(" %d", no < count * 4);
	printf(" %d", (no != 10) || (count >= 20));
	printf(" %d", (no <= 10) && (count > 20));
	printf("\n------\n");
	printf(" %d \n", !(no > count));
	printf(" %d \n", 3);
	printf(" %d \n", ch);
	printf(" %d \n", 'b');
	printf(" %d \n", sizeof(3.2));
	printf(" %d \n", sizeof(3.2f));
	printf(" %d \n", sizeof(float));
	printf(" %d \n", sizeof(double));
}
```

### 2.2 Solution

**Approach:** The relational and logical operators yield 1 for true and 0 for false as a value of type `int` ([Chapter 4, Section 4.2](../../Lecture-Notes/Ch04_Operators/Concepts_Lecture.md#42-result-type), [Chapter 4, Section 5.4](../../Lecture-Notes/Ch04_Operators/Concepts_Lecture.md#54-truthiness-in-c)). Printing a `char` value or a character constant with `%d` gives the character code, and `sizeof` yields the size of its operand in bytes ([Chapter 3, Section 7](../../Lecture-Notes/Ch03_Data-Types-and-Variables/Concepts_Lecture.md#7-sizeof-operator)). The value each `printf` prints and the reason are as follows.

| Printed expression | Value | Reason |
|:-----|:-----|:-----|
| `no > count` | 0 | 10 > 20 is false. |
| `no < count * 4` | 1 | `*` has higher precedence than `<`, so it is computed as 10 < 80, which is true. |
| `(no != 10) \|\| (count >= 20)` | 1 | The left side 10 != 10 is false, but the right side 20 >= 20 is true, so the result of `\|\|` is 1. |
| `(no <= 10) && (count > 20)` | 0 | The left side 10 <= 10 is true, but the right side 20 > 20 is false, so the result of `&&` is 0. |
| `!(no > count)` | 1 | `no > count` is 0, so `!0` is 1. |
| `3` | 3 | The integer constant 3 is printed as it is. |
| `ch` | 97 | `ch` holds 97, the ASCII code of `'a'`, which is promoted to `int` when passed to `printf`. |
| `'b'` | 98 | In C a character constant has type `int`, and its value is 98, the ASCII code of `'b'`. |
| `sizeof(3.2)` | 8 | A floating-point constant without a suffix has type `double`. |
| `sizeof(3.2f)` | 4 | A floating-point constant with the suffix `f` has type `float`. |
| `sizeof(float)` | 4 | This is the size of type `float`. |
| `sizeof(double)` | 8 | This is the size of type `double`. |

*Table 1. Value printed by each expression of Problem 1*

The C standard does not fix the sizes of `float` and `double`, but in most environments that use the IEEE 754 formats they are 4 bytes and 8 bytes. `||` and `&&` do not evaluate the right operand when the left operand alone decides the result ([Chapter 4, Section 5.3](../../Lecture-Notes/Ch04_Operators/Concepts_Lecture.md#53-short-circuit-evaluation)), but in this program the left side alone does not decide either logical expression, so the right side is evaluated as well.

The output layout is also part of the result. The format string `" %d"` of the first four `printf` calls has no newline, so the four values follow one another on one line, separated by spaces. The fifth call `printf("\n------\n")` ends that line, prints `------`, and moves to a new line again. The remaining eight lines use the format string `" %d \n"`, so each value has one space before it and one after it.

### 2.3 Output

Compiling and running the program of the problem as it is gives the following output. The values of Table 1 appear in the output layout described above.

```text
 0 1 1 0
------
 1 
 3 
 97 
 98 
 8 
 4 
 4 
 8 
```

> **Caution:** The result of `sizeof` has the unsigned integer type `size_t`, so compiling this program with `gcc -std=c99 -Wall` gives a format mismatch warning (`-Wformat`) on the four lines that print `sizeof` with `%d`. This environment still prints the values above, but printing with `%d` in a 64-bit environment where `size_t` is larger than `int` is in principle undefined behavior. Since C99, use `%zu` as in `printf(" %zu \n", sizeof(3.2));`, or convert to `int` as in `(int)sizeof(3.2)` and print with `%d`.

---

<br>

## 3. Problem 2: Writing Conditions as Expressions

### 3.1 Problem

**Textbook Problem:** Chapter 5 exercise 1 (modified)

Express the following descriptions as computer expressions (using relational and logical operations and so on). Since the `if` statement has not been covered yet, answer with expressions only.

- (1) The integer `number` is greater than 1 and less than 10.
- (2) The integer `number` lies in 1-10.
- (3) The character constant `ch` is neither `'q'` nor `'z'`.
- (4) `no` is a number between 1 and 10 but is not 5.
- (5) `no` is not a number between 1 and 10.
- (6) `ch` is a space character (`' '`) or a newline character (`'\n'`).

### 3.2 Solution

**Approach:** The mathematical range notation 1 < x < 10 means that both comparisons hold, so in C the two relational expressions are joined with `&&`. When a description requires two conditions to hold together, join them with `&&`, when either one is enough, join them with `||`, and express negation with the opposite relational operator or `!`. Relational operators have higher precedence than logical operators, and `&&` has higher precedence than `||` ([Chapter 4, Section 10.1](../../Lecture-Notes/Ch04_Operators/Concepts_Lecture.md#101-precedence-table)), so the expressions below need no parentheses.

| Item | Expression | Another expression with the same meaning |
|:-----|:-----|:-----|
| (1) | `number > 1 && number < 10` | `1 < number && number < 10` |
| (2) | `number >= 1 && number <= 10` | `!(number < 1 \|\| number > 10)` |
| (3) | `ch != 'q' && ch != 'z'` | `!(ch == 'q' \|\| ch == 'z')` |
| (4) | `no >= 1 && no <= 10 && no != 5` | `(no >= 1 && no <= 10) && !(no == 5)` |
| (5) | `no < 1 \|\| no > 10` | `!(no >= 1 && no <= 10)` |
| (6) | `ch == ' ' \|\| ch == '\n'` | `!(ch != ' ' && ch != '\n')` |

*Table 2. Expression for each description*

- **Ends of the range:** (1) excludes 1 and 10, so it uses `>` and `<`, and (2) includes 1 and 10, so it uses `>=` and `<=`. "Between 1 and 10" in (4) and (5) is taken as a range that includes 1 and 10, as in (2). If the ends are meant to be excluded, change to `>` and `<` as in (1).
- **Negation and De Morgan's laws:** (5) is the negation of (2). By De Morgan's laws `!(A && B)` equals `!A || !B`, so `!(no >= 1 && no <= 10)` becomes `!(no >= 1) || !(no <= 10)`, that is, `no < 1 || no > 10`. The two expressions of (3) also turn into each other by the same law, which says that `!(A || B)` equals `!A && !B`.
- **Checking boundary values:** The expression of (1) is 0 when `number` is 1, 1 when it is 2, 1 when it is 9, and 0 when it is 10, while the expression of (2) is 1 at 1 and 10 as well. Unlike (2), (4) becomes 0 at 5. The two expressions in each row give the same value for every integer from -20 to 30 and every character with ASCII code 0 to 127.

> **Caution:** **A common mistake.** Writing (1) as in mathematics, `1 < number < 10`, compiles, but it is computed as `(1 < number) < 10`. The result of the left comparison is 0 or 1, and both are less than 10, so this expression is always 1 regardless of the value of `number`. gcc and clang warn about this expression under `-Wall`. Also, writing (3) as `ch != 'q' || ch != 'z'` always gives 1, because a character cannot equal both `'q'` and `'z'` at once, so one of the two comparisons is always true.

---

<br>

## 4. Problem 3: Increment, Decrement, and Assignment

### 4.1 Problem

Write the output of the following program and explain why that output results.

```c
#include <stdio.h>

int main()
{
	int a = 3, b = 0;
	printf("%d , %d \n", a, b);

	b = ++a * 2;
	printf("%d , %d \n", a, b);

	a = b-- * 2;
	printf("%d , %d \n", a, b);

	a = a++ % 4;
	printf("%d , %d \n", a, b);

	a += a * b;
	printf("%d , %d \n", a, b);
}
```

### 4.2 Solution

**Approach:** The prefix increment `++a` first increases `a` by 1 and then uses the increased value in the expression, while the postfix decrement `b--` uses the current value of `b` in the expression and then decreases it by 1 ([Chapter 4, Section 3.1](../../Lecture-Notes/Ch04_Operators/Concepts_Lecture.md#31-prefix-vs-postfix)). The increment and decrement operators have higher precedence than `*` and `%`, so `++a * 2` is computed as `(++a) * 2`. The compound assignment `a += a * b` is the same as `a = a + (a * b)` ([Chapter 4, Section 7.1](../../Lecture-Notes/Ch04_Operators/Concepts_Lecture.md#71-simple-and-compound-assignment)). The values after each statement are as follows.

| Statement | Computation | `a` | `b` |
|:-----|:-----|:-----|:-----|
| `int a = 3, b = 0;` | Initializes the variables. | 3 | 0 |
| `b = ++a * 2;` | After `a` becomes 4, 4 * 2 = 8 is assigned to `b`. | 4 | 8 |
| `a = b-- * 2;` | With the current value 8 of `b`, 8 * 2 = 16 is assigned to `a`, and `b` becomes 7. | 16 | 7 |
| `a = a++ % 4;` | The order between assigning 16 % 4 = 0 and `a++` setting `a` to 17 is not specified (Section 4.3). With gcc and clang, 0 remains. | 0 | 7 |
| `a += a * b;` | `a = 0 + 0 * 7`, so it is 0. | 0 | 7 |

*Table 3. Variable values after each statement of Problem 3*

Each `printf` prints `a` and `b` at that point according to the format string `"%d , %d \n"`, so on every line ` , ` comes between the two values and one space remains at the end of the line.

### 4.3 Output and Undefined Behavior

Compiling and running the program of the problem with gcc and with clang gives the same output, shown below.

```text
3 , 0 
4 , 8 
16 , 7 
0 , 7 
0 , 7 
```

The 0 on the fourth line is not a result guaranteed by the C standard. In `a = a++ % 4;`, the side effect of `a++` (storing 17 in `a`) and the assignment (storing 0 in `a`) change the same variable, and the C standard does not specify the order of these two modifications. Modifying the same variable twice without an order inside one expression is **undefined behavior**, so the compiler may apply either one first and may produce a different result. gcc gives the warning "operation on 'a' may be undefined" (`-Wsequence-point`) under `-Wall`, and clang gives the warning "multiple unsequenced modifications to 'a'" (`-Wunsequenced`). If the assignment is applied last, 0 remains as above, but a compiler that translates the code so that the increment is applied last leaves a different value, and the last line changes too. For example, if `a` is 1 on the fourth line, the last line is 1 + 1 * 7 = 8, giving `8 , 7`.

> **Caution:** If the intended computation is only the remainder, write `a = a % 4;`, and if the increment comes first, write `a++;` and then `a = a % 4;` on the next line, so that one statement modifies the same variable only once. The earlier statements `b = ++a * 2;` and `a = b-- * 2;` each modify `a` and `b` only once, so their results are determined.

---

<br>

## 5. Problem 4: Comparing Magnitudes

### 5.1 Problem

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

### 5.2 Solution

**Approach:** The conditional operator `condition ? value1 : value2` yields value1 as the value of the expression if the condition is true and value2 if it is false ([Chapter 4, Section 8.1](../../Lecture-Notes/Ch04_Operators/Concepts_Lecture.md#81-ternary-operator)). One conditional operator finds the maximum of two values, so the maximum of three values is found in two steps.

- **Step 1:** `max1 = num1 > num2 ? num1 : num2;` finds the larger of the first two numbers.
- **Step 2:** `max2 = max1 > num3 ? max1 : num3;` finds the larger of the result of step 1 and the third number. This value is the maximum of the three numbers.
- **Why no parentheses are needed:** The relational operator `>` has higher precedence than the conditional operator, which in turn has higher precedence than the assignment operator ([Chapter 4, Section 10.1](../../Lecture-Notes/Ch04_Operators/Concepts_Lecture.md#101-precedence-table)). Therefore `max1 = num1 > num2 ? num1 : num2` is computed as `max1 = ((num1 > num2) ? num1 : num2)`.

**Code:** [Solution/Q4.c](Solution/Q4.c)

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

### 5.3 Output and Edge Cases

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
| Values of relational and logical operations | The relational and logical operators yield 1 for true and 0 for false as a value of type `int`. |
| Characters and `sizeof` | Printing a character with `%d` gives its character code, and a floating-point constant without a suffix has the size of `double`, while one with `f` has the size of `float`. |
| Range conditions | The mathematical 1 < x < 10 is written as `x > 1 && x < 10`, and the negation of a condition swaps `&&` and `\|\|` and reverses each comparison by De Morgan's laws. |
| Increment and decrement operators | Prefix changes the value and then uses it, postfix uses it and then changes it, and modifying the same variable twice in one expression, as in `a = a++ % 4`, is undefined behavior. |
| Conditional operator | `condition ? value1 : value2` is the only ternary operator in C, yielding value1 if the condition is true and value2 otherwise. |
| Maximum of two values | `a > b ? a : b` finds the larger of two values without an `if` statement. |
| Maximum of three values | It is found in two steps: first the maximum of two values, which is then compared with the third value. |
| Precedence | Relational, conditional, and assignment operators bind in that order, so this expression needs no parentheses. |
| Boundary conditions | The result is correct even with equal or all-negative values because the program only compares them. |

---

<br>

## Self-Check Questions

1. **Values of relational and logical operations:** For `int x = 7;`, write the output of `printf("%d %d", x > 5 && x < 7, !(x % 2));`.

   <details>
   <summary>Answer</summary>

   It is `0 0`. `x > 5` is true but `x < 7` is false, so the result of `&&` is 0. `x % 2` is 1, so `!1` is 0.

   </details>

2. **Negating a range condition:** Write the condition that the integer `score` is not between 0 and 100 inclusive as an expression without `!`.

   <details>
   <summary>Answer</summary>

   It is `score < 0 || score > 100`. Applying De Morgan's laws to the negation of `score >= 0 && score <= 100` turns `&&` into `||` and reverses each comparison.

   </details>

3. **Postfix increment and assignment:** Write the values of `a` and `b` after executing `int a = 5, b; b = a++ + 2;`, and explain why, unlike `a = a++ % 4;`, the result of this statement is determined.

   <details>
   <summary>Answer</summary>

   `a` is 6 and `b` is 7. `a++` uses the current value 5 in the expression and increases `a` to 6, and 5 + 2 = 7 is assigned to `b`. This statement modifies `a` only once through `a++` and `b` only once through the assignment, so the result does not depend on the order in which they are applied.

   </details>

4. **Evaluating the conditional operator:** Write the values of `r` and `y` after executing `int x = 1, y = 0; int r = x ? 10 : y++;`.

   <details>
   <summary>Answer</summary>

   `r` is 10 and `y` is 0. The condition `x` is true (non-zero), so the second operand 10 becomes the value of the expression, and the third operand `y++` is not evaluated. The conditional operator evaluates only the chosen one of the two values.

   </details>

5. **Tracing the intermediate steps:** For the input `23 4 -5`, write the values of `max1` and `max2` in order.

   <details>
   <summary>Answer</summary>

   23 > 4 is true, so `max1` is 23, and 23 > -5 is true, so `max2` is 23.

   </details>

6. **Minimum:** Which part of the code must change to find the smallest of the three values in the same way?

   <details>
   <summary>Answer</summary>

   Change the comparison in both conditional operators from `>` to `<`. `min1 = num1 < num2 ? num1 : num2;` followed by `min2 = min1 < num3 ? min1 : num3;` gives the minimum of the three values.

   </details>

7. **A single expression:** Write an expression that finds the maximum of `a`, `b`, and `c` with only conditional operators and no intermediate variables, and find its value for `a = 5, b = 9, c = 7`.

   <details>
   <summary>Answer</summary>

   It is `a > b ? (a > c ? a : c) : (b > c ? b : c)`. 5 > 9 is false, so `(b > c ? b : c)` is evaluated, and 9 > 7 is true, so the value is 9.

   </details>
