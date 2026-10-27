# HW6 Assignment Explanation — Functions

[Repository Guide](../../README.md) | [English](Assignment-Explanation.md) | [한국어](Assignment-Explanation.ko.md)

> **Last Updated:** 2026-10-27

> **Learning Objectives:**
> 1. Write a function that computes the sum from 0 to the input by choosing the loop direction from the sign of the input
> 2. Use a function that tests a condition and returns 1 or 0 in a conditional expression
> 3. Explain the layout that declares function prototypes before `main()` and places the definitions after `main()`
> 4. Identify inputs for which the accumulated sum exceeds the range of `int`

**Problem Source:** Prof. Jonguk Lee, Computer Language and Training Ⅰ (DCCS103-03)

---

## Table of Contents

- [1. Assignment Layout and How to Run](#1-assignment-layout-and-how-to-run)
- [2. Problem 1: Computing a Sum](#2-problem-1-computing-a-sum)
  - [2.1 Requirements](#21-requirements)
  - [2.2 Solution Approach](#22-solution-approach)
  - [2.3 Code and Output](#23-code-and-output)
  - [2.4 Edge Cases](#24-edge-cases)
- [3. Problem 2: Conditional Sum](#3-problem-2-conditional-sum)
  - [3.1 Requirements](#31-requirements)
  - [3.2 Solution Approach](#32-solution-approach)
  - [3.3 Code and Output](#33-code-and-output)
  - [3.4 Edge Cases](#34-edge-cases)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Assignment Layout and How to Run

This assignment consists of two problems that write and call user-defined functions. Both solutions follow the layout that declares the function prototype before `main()` and places the definition after `main()` ([Chapter 6, Section 2.6](../../Lecture-Notes/Ch06_Functions/Concepts_Lecture.md#26-function-declaration-prototype)).

```text
Coursework/HW06_Functions/
└── Solution/
    ├── Q1.c    # Problem 1: sum from 0 to the input with getSum()
    └── Q2.c    # Problem 2: sum of only the positive values with getSign()
```

*Figure 1. Directory layout of the HW6 assignment*

```bash
cd Coursework/HW06_Functions/Solution
gcc -std=c99 -Wall -o Q1 Q1.c && ./Q1
gcc -std=c99 -Wall -o Q2 Q2.c && ./Q2
```

The last line of the sample runs, `Program ended with exit code: 0`, is not program output but the exit message added by the Xcode console. Neither `main()` has a `return` statement, but since C99, reaching the closing `}` of `main()` is treated as returning 0.

---

<br>

## 2. Problem 1: Computing a Sum

### 2.1 Requirements

Read an arbitrary integer from the user and, referring to the sample runs, compute and print the sum from 0 to the input integer through the function `getSum()`.

**Sample Run:**

```text
>> Enter value: 4
-> Sum(4) ---> 10

Program ended with exit code: 0
```

```text
>> Enter value: -3
-> Sum(-3) ---> -6

Program ended with exit code: 0
```

As the second sample run shows, a negative input is summed going down from 0 to that number. For -3, the sum is 0 + (-1) + (-2) + (-3) = -6.

### 2.2 Solution Approach

`getSum()` computes the sum by splitting into three cases according to the sign of the parameter `val`.

| Range of `val` | Processing | Example |
|:-----|:-----|:-----|
| `val > 0` | Add while increasing `i` from 1 to `val` | `getSum(4)` = 1 + 2 + 3 + 4 = 10 |
| `val == 0` | Return 0 immediately | `getSum(0)` = 0 |
| `val < 0` | Add while decreasing `i` from -1 to `val` | `getSum(-3)` = (-1) + (-2) + (-3) = -6 |

*Table 1. Processing of `getSum()` by the sign of `val`*

Adding 0 does not change the sum, so the two loops start from 1 and -1 rather than 0. `sum` is a local variable initialized to 0, and each case ends with `return sum;` to send back the result. `main()` passes the input value to `getSum()` as an argument and uses the return value directly as an argument of `printf`, printing it in the format `-> Sum(%d) ---> %d`.

The same value can be computed without a loop using the formula for the sum of an arithmetic sequence: $\frac{n(n+1)}{2}$ if $n \ge 0$, and $\frac{n(1-n)}{2}$ if $n < 0$.

### 2.3 Code and Output

**Code:** [Solution/Q1.c](Solution/Q1.c)

```c
/**
 * @file    A10303-1_C06Q1.c
 * @brief   Q1. 합 구하기
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-01
 */

#include <stdio.h>
int getSum(int val);

int main()
{
	int val;

	printf(">> Enter value: ");
	scanf(" %d", &val);

	printf("-> Sum(%d) ---> %d", val, getSum(val));
}

int getSum(int val) {
	int i, sum = 0;

	if (val > 0) {
		for (i = 1; i <= val; i++) {
			sum += i;
		}
		return sum;
	}
	else if (val == 0) {
		return 0;
	}
	else {
		for (i = -1; i >= val; i--) {
			sum += i;
		}
		return sum;
	}
}
```

**Output:** Because no newline is printed after the result, the next shell prompt continues on the same line in a terminal.

```text
>> Enter value: 4
-> Sum(4) ---> 10
```

```text
>> Enter value: -3
-> Sum(-3) ---> -6
```

### 2.4 Edge Cases

- **0 and 1:** Entering 0 prints 0 from the `val == 0` branch, and entering 1 runs the loop once and prints 1.
- **Overflow:** The maximum of a 32-bit `int` is 2,147,483,647. The sum up to 65535 is $\frac{65535 \times 65536}{2}$ = 2,147,450,880, which is within range, but the sum up to 65536, 2,147,516,416, exceeds it, so signed integer overflow (undefined behavior) occurs at `sum += i`. Likewise, negative inputs give correct sums only down to -65535.
- **Invalid input:** If a non-numeric character is entered, `scanf` fails and stores no value in `val`, so reading the uninitialized `val` is undefined behavior. Checking that the return value of `scanf` is 1 prevents this.

---

<br>

## 3. Problem 2: Conditional Sum

### 3.1 Requirements

Read 10 arbitrary integers from the user in turn and, referring to the sample run, check whether each input is positive or negative through the function `getSign()`, add only the positive values, and print the sum.

**Sample Run:**

```text
>> (1) Input value: 3
>> (2) Input value: -1
>> (3) Input value: 2
>> (4) Input value: -4
>> (5) Input value: 1
>> (6) Input value: 2
>> (7) Input value: -5
>> (8) Input value: -23
>> (9) Input value: 5
>> (10) Input value: 6
-> Sum of positive values: 19

Program ended with exit code: 0
```

The positive values in the sample run are 3, 2, 1, 2, 5, and 6, and their sum is 19.

### 3.2 Solution Approach

`getSign()` returns 1 if the parameter `tmp` is greater than 0 and 0 otherwise. `main()` increases `i` from 1 to 10, prints the prompt `>> (i) Input value: `, reads an integer, and adds it to `sum` only when `if (getSign(val))` is true. A condition in C is true whenever it is nonzero, so the return value of `getSign()` can be used as the condition directly without a comparison.

Each input overwrites the same variable `val`, so the 10 values need not all be stored, and only `sum`, which the total requires, is initialized to 0 outside the loop.

### 3.3 Code and Output

**Code:** [Solution/Q2.c](Solution/Q2.c)

```c
/**
 * @file    A10303-1_C06Q2.c
 * @brief   Q2. 조건에 따라 합 구하기
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-01
 */

#include <stdio.h>
int getSign(int tmp);

int main()
{
	int val, i, sum = 0;

	for (i = 1; i <= 10; i++) {
		printf(">> (%d) Input value: ", i);
		scanf(" %d", &val);
		
		if (getSign(val)) {
			sum += val;
		}
	}
	printf("-> Sum of positive values: %d", sum);
}

int getSign(int tmp) 
{
	if (tmp > 0) {
		return 1;
	}
	else {
		return 0;
	}
}
```

**Output:** Entering the 10 values of the sample run prints the sum 19.

```text
>> (1) Input value: 3
>> (2) Input value: -1
>> (3) Input value: 2
>> (4) Input value: -4
>> (5) Input value: 1
>> (6) Input value: 2
>> (7) Input value: -5
>> (8) Input value: -23
>> (9) Input value: 5
>> (10) Input value: 6
-> Sum of positive values: 19
```

### 3.4 Edge Cases

- **Handling 0:** `getSign(0)` returns 0, so 0 is not counted as positive. Adding 0 leaves the sum unchanged, so changing the condition to `tmp >= 0` gives the same result.
- **Input with no positive values:** If all 10 values are 0 or less, `sum` stays at its initial value 0 and `-> Sum of positive values: 0` is printed.
- **Name and return value of the function:** Despite its name, `getSign()` does not return three signs (-1, 0, 1) but only tells whether the value is positive, so it cannot be used as is for a problem that must distinguish 0 from negative values. This problem only needs to pick out positive values, so 1 and 0 suffice.

---

<br>

## Summary

| Concept | Key Summary |
|:-----|:-----|
| `getSum()` | It adds going up from 1 for a positive input and going down from -1 for a negative input, and returns 0 immediately for 0. |
| Sum formula | The same sum can be computed without a loop as $\frac{n(n+1)}{2}$ for $n \ge 0$ and $\frac{n(1-n)}{2}$ for $n < 0$. |
| Overflow | With a 32-bit `int`, the sum stays in range only for inputs from -65535 to 65535. |
| `getSign()` | It returns 1 for a positive value and 0 otherwise, so its return value can be used directly as an `if` condition. |
| Function prototype | Because the definitions come after `main()`, prototypes must be placed before `main()` for the calls to compile. |
| Return of `main()` | Since C99, reaching the closing `}` of `main()` is treated as returning 0. |

---

<br>

## Self-Check Questions

1. **Return values:** In the solution's `getSum()`, what are the return values of `getSum(-1)`, `getSum(0)`, and `getSum(5)`?

   <details>
   <summary>Answer</summary>

   `getSum(-1)` adds only -1 in the `val < 0` branch, so it is -1; `getSum(0)` is 0 from the `val == 0` branch; and `getSum(5)` is 1 + 2 + 3 + 4 + 5 = 15.

   </details>

2. **Function prototype:** What happens if the line `int getSum(int val);` is deleted from `Q1.c`?

   <details>
   <summary>Answer</summary>

   The definition of `getSum()` comes after `main()`, so the compiler does not know the function at the point where `main()` calls it. Since C99 has removed implicit declarations from the standard, gcc 14 and later and clang 16 and later report an error, and earlier versions report a warning. Moving the definition before `main()` lets the code compile without a prototype.

   </details>

3. **Overflow:** With a 32-bit `int`, what is the largest positive input for which `getSum()` returns the correct sum?

   <details>
   <summary>Answer</summary>

   It is 65535. $\frac{65535 \times 65536}{2}$ = 2,147,450,880 is less than the maximum `int` value 2,147,483,647, but entering 65536 makes the sum 2,147,516,416, which exceeds the range.

   </details>

4. **Changing the condition:** If the condition of `getSign()` is changed to `tmp >= 0`, does the output of Problem 2 change?

   <details>
   <summary>Answer</summary>

   It does not change. 0 is now added as well, but adding 0 does not change the sum, so the printed sum is the same for every input.

   </details>

5. **Sum formula:** Compute the value of `getSum(-3)` with the formula, without a loop.

   <details>
   <summary>Answer</summary>

   For $n < 0$ the formula is $\frac{n(1-n)}{2}$, so the value is $\frac{(-3)(1-(-3))}{2} = \frac{(-3) \times 4}{2} = -6$.

   </details>
