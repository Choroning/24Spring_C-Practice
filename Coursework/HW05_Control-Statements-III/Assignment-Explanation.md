# HW5 Assignment Explanation — Control Statements III

[Repository Guide](../../README.md) | [English](Assignment-Explanation.md) | [한국어](Assignment-Explanation.ko.md)

> **Last Updated:** 2026-10-27

> **Learning Objectives:**
> 1. Update the maximum and minimum in a `while` loop that ends at the sentinel 0 while filtering out-of-range inputs
> 2. Compute a sum and an average with `do-while` by reading an input first and then handling the sentinel
> 3. Compute an alternating-sign sum with a `for` statement and the remainder operator
> 4. Print a pattern whose number of items per line grows and then shrinks with nested `for` statements

**Problem Source:** Prof. Jonguk Lee, Computer Language and Training Ⅰ (DCCS103-03)

---

## Table of Contents

- [1. Assignment Layout and How to Run](#1-assignment-layout-and-how-to-run)
- [2. Problem 1: Loop Practice (1)](#2-problem-1-loop-practice-1)
  - [2.1 Problem](#21-problem)
  - [2.2 Solution](#22-solution)
  - [2.3 Output and Edge Cases](#23-output-and-edge-cases)
- [3. Problem 2: Loop Practice (2)](#3-problem-2-loop-practice-2)
  - [3.1 Problem](#31-problem)
  - [3.2 Solution](#32-solution)
  - [3.3 Output and Edge Cases](#33-output-and-edge-cases)
- [4. Problem 3: Loop Practice (3)](#4-problem-3-loop-practice-3)
  - [4.1 Problem](#41-problem)
  - [4.2 Solution](#42-solution)
  - [4.3 Output](#43-output)
- [5. Problem 4: Loop Practice (4)](#5-problem-4-loop-practice-4)
  - [5.1 Problem](#51-problem)
  - [5.2 Solution](#52-solution)
  - [5.3 Output](#53-output)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Assignment Layout and How to Run

This loop assignment practices `while`, `do-while`, `for`, and nested `for` one at a time. Problems 1 and 2 read values until the sentinel 0 is entered, and Problems 3 and 4 are `for` loops with a fixed number of iterations.

```text
Coursework/HW05_Control-Statements-III/
├── Assignment-Explanation.ko.md   # this document (Korean)
├── Assignment-Explanation.md      # this document (English)
└── Solution/
    ├── Q1.c                       # Problem 1: maximum and minimum (while)
    ├── Q2.c                       # Problem 2: sum and average (do-while)
    ├── Q3.c                       # Problem 3: alternating-sign sum (for)
    └── Q4.c                       # Problem 4: number triangle (nested for)
```

*Figure 1. Directory layout of HW5*

The code of Problem 2 was written in Visual Studio (MSVC) and uses `scanf_s` for input. `scanf_s` is provided by MSVC and is missing from most standard libraries used with gcc and clang, so in other environments the code is compiled without changes by replacing it with `scanf` through the `-Dscanf_s=scanf` option. The other three programs use only the standard `scanf`. Each program is compiled and run as follows.

```bash
cd Coursework/HW05_Control-Statements-III/Solution
gcc -std=c99 -Wall -Dscanf_s=scanf -o Q2 Q2.c
./Q2
```

The line `Program ended with exit code: 0` at the end of the sample runs in the assignment is not program output but the exit message added by the Xcode console.

---

<br>

## 2. Problem 1: Loop Practice (1)

### 2.1 Problem

Write a program that continuously reads integers (no) between 1 and 100 from the user and prints the maximum and minimum.

**Program Requirements:**

1. Use a `while` statement.
2. When `0` is entered, stop reading input and print the maximum and minimum.
3. Referring to the sample run, handle inputs that are not within 0-100 as exceptions.

**Sample Run:**

```text
Input value(no): 3
Input value(no): 9
Input value(no): 54
Input value(no): 87
Input value(no): 5
Input value(no): 234
-- Error --
Input value(no): 3
Input value(no): 0
MAX: 87, MIN: 3

Program ended with exit code: 0
```

### 2.2 Solution

**Approach:** Inside an infinite `while (1)` loop, each value read is classified with an `else if` ladder as out of range, the sentinel 0, or a valid value ([Chapter 5, Section 5.2](../../Lecture-Notes/Ch05_Control-Statements/Concepts_Lecture.md#52-maxmin-tracking)).

- **Initial values:** Valid values are 1-100, so `max` starts at 0, below that range, and `min` starts at 100, the top of the range. The first valid value then always updates `max`, and it updates `min` unless it is 100, in which case 100 is already the correct value. This uses the two ends of the range instead of initializing with the first input.
- **Out-of-range values:** If `no > 100 || no < 0`, the program prints `-- Error --` and moves to the next input without updating.
- **Sentinel:** If the value is 0, `break` ends the loop. At that point, `max < min` means no valid value was entered (`max` is still 0 and `min` still 100), so `min` is set to 0 and `MAX: 0, MIN: 0` is printed.
- **Updating:** The conditional operator computes `max = (no > max) ? no : max;` and `min = (no < min) ? no : min;`.

**Code:** [Solution/Q1.c](Solution/Q1.c)

```c
/**
 * @file    A10303-3_C05Q1.c
 * @brief   Q1. 반복문 연습 (1)
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-12
 */

#include <stdio.h>

int main()
{
    int no = 0, max = 0, min = 100;

    while (1) {
        printf("Input value(no): ");
        scanf(" %d", &no);

        if (no > 100 || no < 0)
            printf("-- Error -- \n");
        else if (no == 0) {
            if (max < min)
                min = 0;
            break;
        }else {
            max = (no > max) ? no : max;
            min = (no < min) ? no : min;
        }
    }

    printf("MAX: %d, MIN: %d \n", max, min);
}
```

### 2.3 Output and Edge Cases

**Output:** 234 is out of range and ignored, and the remaining values 3, 9, 54, 87, 5, and 3 give the maximum 87 and the minimum 3. `-- Error -- ` and the result line each end with one trailing space.

```text
Input value(no): 3
Input value(no): 9
Input value(no): 54
Input value(no): 87
Input value(no): 5
Input value(no): 234
-- Error -- 
Input value(no): 3
Input value(no): 0
MAX: 87, MIN: 3 
```

> **Note:** Entering 0 first prints `MAX: 0, MIN: 0`. Negative numbers are treated as out of range, and the boundary value 100 is accepted as valid.

```text
Input value(no): 0
MAX: 0, MIN: 0 
Input value(no): -5
-- Error -- 
Input value(no): 100
Input value(no): 0
MAX: 100, MIN: 100 
```

---

<br>

## 3. Problem 2: Loop Practice (2)

### 3.1 Problem

Assume that only positive numbers including 0 (numbers 0 or greater) are entered. Compute and print the sum and average of the entered positive numbers. If 0 is entered first, the program prints `0만 입력되었습니다!` ("Only 0 was entered!").

**Sample Runs:**

```text
>> Input value: 1
>> Input value: 2
>> Input value: 2
>> Input value: 0
=====================
-> SUM: 5, AVE: 1.7

Program ended with exit code: 0
```

```text
>> Input value: 0
=====================
-> 0만 입력되었습니다!

Program ended with exit code: 0
```

### 3.2 Solution

**Approach:** Whether to stop is known only after a value is read, so the program uses `do-while`, which executes the body first and checks the condition afterward ([Chapter 5, Section 3.3](../../Lecture-Notes/Ch05_Control-Statements/Concepts_Lecture.md#33-do-while)).

- **Accumulating:** Each value read is added to `sum` right away and the counter `i` is incremented, and the loop repeats while `val != 0`. The final 0 is also added, but adding 0 does not change the sum.
- **Count:** The 0 was also counted once, so the number of positive values is `i - 1`.
- **Only 0 entered:** `i == 1` means the first input was 0, so the program prints the message. This check also prevents a division where `i - 1` is 0.
- **Average:** `(double) sum / (i - 1)` performs floating-point division, and `%.1lf` prints the result to one decimal place. 5 / 3 = 1.666... is rounded to `1.7`.

**Code:** [Solution/Q2.c](Solution/Q2.c)

```c
/**
 * @file    A10303-3_C05Q2.c
 * @brief   Q2. 반복문 연습 (2)
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-12
 */

#include <stdio.h>

int main()
{
	int val, sum = 0, i = 0;
	double ave;

	do {
		printf(">> Input value: ");
		scanf_s(" %d", &val);

		sum += val;
		i++;
	} while (val != 0);
	
	printf("===================== \n");
	
	if (i == 1)
		printf("-> 0만 입력되었습니다!");
	else {
		ave = (double) sum / (i - 1);
		printf("-> SUM: %d, AVE: %.1lf", sum, ave);
	}	
}
```

### 3.3 Output and Edge Cases

**Output:** The separator ends with one trailing space, and no newline is printed after the last line.

```text
>> Input value: 1
>> Input value: 2
>> Input value: 2
>> Input value: 0
===================== 
-> SUM: 5, AVE: 1.7
```

```text
>> Input value: 0
===================== 
-> 0만 입력되었습니다!
```

> **Note:** The problem assumes that no negative numbers are entered, so the code does not check for them. A negative number would simply be included in the sum and the count.

---

<br>

## 4. Problem 3: Loop Practice (3)

### 4.1 Problem

Write a program that prints the result of `1-2+3- ... +9-10` using a `for` statement.

**Sample Run:**

```text
1 - 2 + 3 - 4 + 5 - 6 + 7 - 8 + 9 - 10 = -5

Program ended with exit code: 0
```

### 4.2 Solution

**Approach:** Increase `count` from 1 to 10, adding it when it is odd and subtracting it when it is even ([Chapter 5, Section 3.4](../../Lecture-Notes/Ch05_Control-Statements/Concepts_Lecture.md#34-nested-loops)).

- **Odd or even:** If `count % 2` is non-zero (odd), `sum += count` executes, and if it is 0 (even), `sum -= count` executes.
- **Result:** The five pairs 1-2, 3-4, ..., 9-10 are each -1, so the sum is -5.
- **Output:** The expression part is printed as a literal string, and only the result is filled in with `%d`.

**Code:** [Solution/Q3.c](Solution/Q3.c)

```c
/**
 * @file    A10303-3_C05Q3.c
 * @brief   Q3. 반복문 연습 (3)
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-12
 */

#include <stdio.h>

int main()
{
	int count, sum = 0;
	
	for (count = 1; count <= 10; count++) {
		if (count % 2)
			sum += count;
		else
			sum -= count;
	}
	printf("1 - 2 + 3 - 4 + 5 - 6 + 7 - 8 + 9 - 10 = %d", sum);
}
```

### 4.3 Output

The output ends without a newline.

```text
1 - 2 + 3 - 4 + 5 - 6 + 7 - 8 + 9 - 10 = -5
```

---

<br>

## 5. Problem 4: Loop Practice (4)

### 5.1 Problem

Write code that prints the output shown in the sample run using nested `for` statements.

**Sample Run:**

```text
0
0 1
0 1 2
0 1 2 3
0 1 2 3 4
0 1 2 3
0 1 2
0 1
0

Program ended with exit code: 0
```

### 5.2 Solution

**Approach:** Split the output into the upper 5 lines, where the lines grow, and the lower 4 lines, where they shrink, and print each part with nested `for` loops. The outer loop variable `i` is the last number of the line, and the inner loop prints from 0 to `i`.

- **Upper part:** `i` increases from 0 to 4, and each line prints the i + 1 numbers from `0` to `i`.
- **Lower part:** `i` decreases from 3 to 0, and the same inner loop prints the numbers. The lower part starts at 3 so that the middle line `0 1 2 3 4` does not appear twice.
- **Spaces between numbers:** `printf("%d ", j)` adds a space after each number, and the line ends after the inner loop finishes.

**Code:** [Solution/Q4.c](Solution/Q4.c)

```c
/**
 * @file    A10303-3_C05Q4.c
 * @brief   Q4. 반복문 연습 (4)
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-13
 */

#include <stdio.h>

int main()
{
	int i = 0, j = 0;

	for (i = 0; i <= 4; i++) {
		for (j = 0; j <= i; j++)
			printf("%d ", j);
		printf("\n");
	}
	for (i = 3; i >= 0; i--) {
		for (j = 0; j <= i; j++)
			printf("%d ", j);
		printf("\n");
	}
}
```

### 5.3 Output

A trailing space remains after the last number of each line.

```text
0 
0 1 
0 1 2 
0 1 2 3 
0 1 2 3 4 
0 1 2 3 
0 1 2 
0 1 
0 
```

---

<br>

## Summary

| Concept | Key Summary |
|:--------|:------------|
| Sentinel loop | Inside `while (1)`, the sentinel 0 ends the loop with `break`, and an out-of-range value is skipped after an error message. |
| Initial max and min | When the input range is fixed at 1-100, `max` can start at 0 and `min` at 100 so that the first valid value updates them. |
| Input with `do-while` | When a value must be read before knowing whether to stop, `do-while`, which runs the body at least once, is the right choice. |
| Correcting the count for the sentinel | A counter that also counted the sentinel must be reduced by 1 to give the actual number of inputs, and that value is checked for 0 first to avoid dividing by zero. |
| Alternating-sign sum | Testing odd or even with `count % 2`, adding odd numbers and subtracting even numbers gives 1-2+3-...+9-10 = -5. |
| Number triangle | The growing and shrinking parts are split into two nested `for` loops, with starting values chosen so that the middle line is not repeated. |

---

<br>

## Self-Check Questions

1. **Conditions for the initial values:** Why can `max` start at 0 and `min` at 100 in Problem 1? What goes wrong with this approach if the inputs are integers from -100 to 100?

   <details>
   <summary>Answer</summary>

   Valid values are 1-100, so every valid value is greater than 0 and not greater than 100; the first valid value always updates `max`, and `min` also ends up correct. If negative inputs are allowed and every value is negative, `max` is never updated from 0, so 0, which was never entered, is printed as the maximum. In that case, `max` and `min` must be initialized with the first valid value, as in Chapter 5, Section 5.2.

   </details>

2. **Sum and average:** If 4 and then 0 are entered into the program of Problem 2, what are `sum`, `i`, and the output?

   <details>
   <summary>Answer</summary>

   After 4 is read, `sum` is 4 and `i` is 1, and after 0 is read, `sum` is 4 and `i` is 2, and the loop ends. `i` is not 1, so the average is 4 / (2 - 1) = 4.0, and `-> SUM: 4, AVE: 4.0` is printed.

   </details>

3. **Extending the alternating-sign sum:** If the loop of Problem 3 is extended to 100 to compute `1-2+3-...+99-100`, what is the result?

   <details>
   <summary>Answer</summary>

   It is -50, because the 50 pairs (1-2), (3-4), ..., (99-100) are each -1.

   </details>

4. **Output count:** How many lines does the program of Problem 4 print, and how many numbers are printed in total?

   <details>
   <summary>Answer</summary>

   It prints 9 lines, 5 in the upper part and 4 in the lower part. The numbers total 1 + 2 + 3 + 4 + 5 = 15 in the upper part and 4 + 3 + 2 + 1 = 10 in the lower part, 25 in all.

   </details>
