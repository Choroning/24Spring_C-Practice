# HW3 Assignment Handout — Control Statements I

[Repository Guide](../../../README.md) | [English](Assignment.md) | [한국어](Assignment.ko.md)

> **Last Updated:** 2026-11-24

This is the third assignment of section 3 of Computer Language and Training Ⅰ. It consists of two problems that ask for the output of a given program and the reason for it, one problem that expresses conditions given in words as expressions, and one coding problem.

- **Contents:** For a coding problem, an analysis of the code must be written together with the code.
- **Sample Runs:** The line `Program ended with exit code: 0` at the end of a sample run is not output of the program but a termination message that the Xcode console appends.

---

<br>

## Problem 1. Values of Operators

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

---

<br>

## Problem 2. Writing Conditions as Expressions

**Textbook Problem:** Chapter 5 exercise 1 (modified)

Express the following descriptions as computer expressions (using relational and logical operations and so on). Since the `if` statement has not been covered yet, answer with expressions only.

- (1) The integer `number` is greater than 1 and less than 10.
- (2) The integer `number` lies in 1-10.
- (3) The character constant `ch` is neither `'q'` nor `'z'`.
- (4) `no` is a number between 1 and 10 but is not 5.
- (5) `no` is not a number between 1 and 10.
- (6) `ch` is a space character (`' '`) or a newline character (`'\n'`).

---

<br>

## Problem 3. Increment, Decrement, and Assignment

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

---

<br>

## Problem 4. Comparing Magnitudes

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

---

<br>

After solving the problems, see the [assignment explanation](../Assignment-Explanation.md) for the answers and solutions.
